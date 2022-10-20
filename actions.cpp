#include "actions.h"
#include "dino.h"
#include "modifiers.h"
#include "logger.h"
#include <functional>
#include "utils.h"
#include <cmath>
#include <algorithm>

using namespace std;
using namespace actions;

std::list<std::unique_ptr<Action>> actions::Attack(double _factor, int _flags)
{
    std::list<std::unique_ptr<Action>> list;
    list.emplace_back(new PrepareAttack())->target = TARGET_SELF;
    list.emplace_back(new AttackAction(_factor, _flags))->target = TARGET_INHERIT;
    list.emplace_back(new Revenge())->target = TARGET_ALL_OPPONENTS;
    return std::move(list);
}

std::list<std::unique_ptr<Action>> actions::Rend(double _factor, int _flags)
{
    return std::move(actions::Attack(_factor / 100., _flags | REND));
}

void PrepareAttack::Do(Dino &self, Dino &target) const
{
    self.crit = rand() % 100 < self.CritChanceFactor() * 100;
    self.prepared_damage_factor = self.DamageFactor();
    REMOVE_MODS(self, mod_it->OutgoingAttack(), DEBUG("%s used out %s\n", self.Name().c_str(), modifier->name.c_str()));
    self.killer = false;
}

void AttackAction::Do(Dino &self, Dino &target) const
{
    double damage;
    if (flags & REND)
        damage = target.max_total_health * (1 - target.kind->rend_resistance);
    else
        damage = self.damage;
    damage = floor(damage * self.prepared_damage_factor);
    damage *= factor;
    damage *= 1 + target.vulnerability;
    bool crit = self.crit;
    if (crit)
        damage *= 1.25;
    bool cloak = self.CloakFactor() != 1;
    if (cloak) {
        damage *= self.CloakFactor();
        if (!self.attacker)
            REMOVE_MODS(self, mod_it->Type() == CLOAK, DEBUG("%s used out %s\n", self.Name().c_str(), modifier->name.c_str()));
    }
    bool shield = target.Shield();
    if (shield)
        damage *= 1 - target.Shield();
    bool dodge = (~flags & PRECISE) && rand() % 100 < target.DodgeChance() * 100;
    if (dodge)
        damage *= 1 - target.DodgeFactor();
    bool armor = (~flags & BYPASS_ARMOR) && target.armor > 0;
    if (armor)
        damage *= 1 - target.armor;
    damage = floor(damage);
    REMOVE_MODS(target, mod_it->IncomingAttack(), DEBUG("%s used out %s\n", target.Name().c_str(), modifier->name.c_str()));
    int absorbed = 0;
    if ((~flags & GROUP) && this->target != TARGET_ALL_OPPONENTS) {
        absorbed = (int)damage - target.Absorb((int)damage);
        damage -= absorbed;
    }
    self.last_damage = damage;
    if (!self.attacker)
        target.attacker = &self;
    target.Hit(damage);
    WARNING("%s attacks %s for %d%s%s%s%s%s%s%s\n", self.Name().c_str(), target.Name().c_str(), (int)damage, target.vulnerability ? " Vulnerability" : "", cloak ? strprintf(" Cloak*%.1lf", self.CloakFactor()).c_str() : "", crit ? " Crit" : "", shield ? " Shield" : "", dodge ? " Dodge" : "", armor ? " Armor" : "", absorbed ? " Absorbed" : "");
    if (!target.Alive()) {
        ERROR("%s dies!\n", target.Name().c_str());
        self.killer = true;
    } else if (target.health == 0)
        INFO("%s is immune to HP changes.\n", target.Name().c_str());
}

void Revenge::Do(Dino &self, Dino &target) const
{
    if (self.killer)
        target.Impose(&revenge, self);
}

std::list<std::unique_ptr<Action>> actions::Heal(double _factor, int _flags)
{
    std::list<std::unique_ptr<Action>> list;
    list.emplace_back(new PrepareAttack())->target = TARGET_SELF;
    list.emplace_back(new HealAction(_factor, _flags))->target = TARGET_INHERIT;
    return std::move(list);
}

std::list<std::unique_ptr<Action>> actions::FixedHeal(double _factor, int _flags)
{
    std::list<std::unique_ptr<Action>> list;
    list.emplace_back(new HealAction(_factor / 100., _flags|FIXED))->target = TARGET_INHERIT;
    return std::move(list);
}

void HealAction::Do(Dino &self, Dino &target) const
{
    double heal;
    if (flags & FIXED)
        heal = self.max_health;
    else
        heal = self.damage * self.prepared_damage_factor;
    heal = floor(heal);
    heal *= factor;
    heal = floor(heal);
    if (target.health == 0) {
        INFO("%s is immune to HP changes\n", target.Name().c_str());
        return;
    }
    heal = target.HealAbsorb((int)heal);
    target.Heal((int)heal);
    WARNING("%s heals %s for %d\n", self.Name().c_str(), target.Name().c_str(), (int)heal);
}

void RallyHeal::Do(Dino &self, Dino &target) const
{
    int heal = floor(self.max_health * factor);
    if (target.health == 0) {
        INFO("%s is immune to HP changes\n", target.Name().c_str());
        return;
    }
    target.Heal(heal);
    WARNING("%s rally heals %s for %d\n", self.Name().c_str(), target.Name().c_str(), heal);
}

void ImposeVulnerability::Do(Dino &self, Dino &target) const
{
    target.Impose(&vulnerability, self);
}

void Cleanse::Do(Dino &self, Dino &target) const
{
    target.Dispose(flags, self);
}

void Remove::Do(Dino &self, Dino &target) const
{
    target.Dispose(flags, self);
}

std::list<std::unique_ptr<Action>> actions::Taunt(int _duration)
{
    std::list<std::unique_ptr<Action>> list;
    list.emplace_back(new Remove(TAUNT))->target = TARGET_TEAM;
    list.emplace_back(new TauntAction(_duration))->target = TARGET_SELF;
    return std::move(list);
}

void TauntAction::Do(Dino &self, Dino &target) const
{
    target.Impose(&taunt, self);
}

void IncreaseCritChance::Do(Dino &self, Dino &target) const
{
    target.Impose(&increased_crit_chance, self);
}

void IncreaseDamage::Do(Dino &self, Dino &target) const
{
    target.Impose(&increased_damage, self);
}

void ReduceSpeed::Do(Dino &self, Dino &target) const
{
    target.Impose(&reduced_speed, self);
}

void ReduceDamage::Do(Dino &self, Dino &target) const
{
    target.Impose(&reduced_damage, self);
}

void Dodge::Do(Dino &self, Dino &target) const
{
    target.Impose(&dodge, self);
}

void IncreaseSpeed::Do(Dino &self, Dino &target) const
{
    target.Impose(&increased_speed, self);
}

void ReduceCritChance::Do(Dino &self, Dino &target) const
{
    target.Impose(&reduced_crit_chance, self);
}

void Shield::Do(Dino &self, Dino &target) const
{
    target.Impose(&shield, self);
}

void DevourHeal::Do(Dino &self, Dino &target) const
{
    target.Impose(&devour_heal, self);
}

void DamageOverTime::Do(Dino &self, Dino &target) const
{
    target.Impose(&damage_over_time, self);
}

void Stun::Do(Dino &self, Dino &target) const
{
    if (rand() % 100 < (factor * (1 - target.kind->stun_resistance)) * 100.)
        target.Impose(&stun, self);
}

void Cloak::Do(Dino &self, Dino &target) const
{
    target.Impose(&cloak, self);
}

std::list<std::unique_ptr<Action>> actions::UnableToSwap(int _duration)
{
    return std::move(std::list<std::unique_ptr<Action>>());
}

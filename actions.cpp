#include "actions.h"
#include "dino.h"
#include "modifiers.h"
#include "logger.h"
#include <functional>
#include "utils.h"
#include <cmath>

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
    for (auto mod_it = self.mods.begin(); mod_it != self.mods.end(); ) {
        if (mod_it->OutgoingAttack()) {
            auto modifier = mod_it->modifier;
            modifier->Dispose(self, &*mod_it);
            self.mods.erase(mod_it++);
            LOG("%s used out %s\n", self.Name().c_str(), modifier->name.c_str());
        } else
            ++mod_it;
    }
    self.killer = false;
}

void AttackAction::Do(Dino &self, Dino &target) const
{
    double damage;
    if (flags & REND)
        damage = (target.max_total_health * factor * (1 - target.kind[target.round].rend_resistance));
    else
        damage = (self.damage * factor); // здесь определённо хуйня
    damage = (damage * self.prepared_damage_factor);
    damage = (damage * (1 + target.vulnerability));
    damage = floor(damage); // тут определённо floor
    bool crit = self.crit;
    if (crit)
        damage = floor(damage * 1.25);
    bool shield = target.Shield();
    if (shield)
        damage = floor(damage * (1 - target.Shield()));
    bool dodge = (~flags & PRECISE) && rand() % 100 < target.DodgeChance() * 100;
    if (dodge)
        damage = floor(damage * (1 - target.DodgeFactor()));
    bool armor = (~flags & BYPASS_ARMOR) && target.armor > 0;
    if (armor)
        damage = floor(damage * (1 - target.armor));
    damage = floor(damage);
    for (auto mod_it = target.mods.begin(); mod_it != target.mods.end(); ) {
        if (mod_it->IncomingAttack()) {
            auto modifier = mod_it->modifier;
            modifier->Dispose(target, &*mod_it);
            target.mods.erase(mod_it++);
            LOG("%s used out %s\n", target.Name().c_str(), modifier->name.c_str());
        } else
            ++mod_it;
    }
    self.last_damage = damage;
    target.attacker = &self;
    target.Hit(damage);
    LOG("%s attacks %s for %d%s%s%s%s\n", self.Name().c_str(), target.Name().c_str(), (int)damage, crit ? " Crit" : "", shield ? " Shield" : "", dodge ? " Dodge" : "", armor ? " Armor" : "");
    if (!target.Alive()) {
        LOG("%s dies!\n", target.Name().c_str());
        self.killer = true;
    } else if (target.health == 0)
        LOG("%s is immune to HP changes.\n", target.Name().c_str());
}

void Revenge::Do(Dino &self, Dino &target) const
{
    if (self.killer)
        target.Impose(&revenge, self);
}

void Heal::Do(Dino &self, Dino &target) const
{
    int heal = Round(Round(self.damage * factor) * self.DamageFactor());
    if (target.health == 0) {
        LOG("%s is immune to HP changes\n", target.Name().c_str());
        return;
    }
    target.Heal(heal);
    LOG("%s heals %s for %d\n", self.Name().c_str(), target.Name().c_str(), heal);
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

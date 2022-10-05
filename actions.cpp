#include "actions.h"
#include "dino.h"
#include "modifiers.h"
#include "logger.h"
#include <functional>
#include "utils.h"

using namespace std;
using namespace actions;

function<bool(const Dino &,const Dino &)> TargetCmp[] = {
    [](const Dino &dino1, const Dino &dino2) -> bool { return false; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health < dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health > dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Damage() < dino2.Damage(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Damage() > dino2.Damage(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Speed() < dino2.Speed(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Speed() > dino2.Speed(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health < dino2.health; },
};

ActionGroup RemoveTauntAction(TARGET_TEAM, {new Remove(TAUNT)});

void ActionGroup::Do(Dino &self, Dino *team[], int team_size) const
{
    if (target == TARGET_ALL_OPPONENTS) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            for (int i = 0; i < team_size; ++i) {
                if (team[i]->team == self.team)
                    continue;
                if (!team[i]->Alive())
                    continue;
                actions[a]->Do(self, *team[i], team, team_size);
            }
        }
    } else if (target == TARGET_TEAM) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            for (int i = 0; i < team_size; ++i) {
                if (team[i]->team != self.team)
                    continue;
                if (!team[i]->Alive())
                    continue;
                actions[a]->Do(self, *team[i], team, team_size);
            }
        }
    } else if (target == TARGET_SELF) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            actions[a]->Do(self, self, team, team_size);
        }
    } else if (target == TARGET_ATTACKER) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            if (!self.attacker->Alive())
                continue;
            actions[a]->Do(self, *self.attacker, team, team_size);
        }
    } else if (target == TARGET_LOWEST_HP_TEAMMATE) {
        int tgt = -1;
        int count = 0;
        for (int i = 0; i < team_size; ++i) {
            if (team[i]->team != self.team)
                continue;
            if (!team[i]->Alive())
                continue;
            if (tgt == -1) {
                tgt = i;
                count = 1;
            } else if (TargetCmp[target](*team[tgt], *team[i]))
                continue;
            else if (TargetCmp[target](*team[i], *team[tgt])) {
                tgt = i;
                count = 1;
            } else if (rand() % ++count == 0)
                tgt = i;
        }
        for (int a = 0; a < (int)actions.size(); ++a) {
            actions[a]->Do(self, *team[tgt], team, team_size);
        }
    } else {
        int tgt = -1;
        int count = 0;
        for (int i = 0; i < team_size; ++i) {
            if (team[i]->team == self.team)
                continue;
            if (!team[i]->Alive())
                continue;
            if (target != TARGET_RANDOM && team[i]->Taunt() && rand() % 100 < (1 - self.kind[self.round].taunt_resistance) * 100) {
                tgt = i;
                break;
            }
            if (tgt == -1) {
                tgt = i;
                count = 1;
            } else if (TargetCmp[target](*team[tgt], *team[i]))
                continue;
            else if (TargetCmp[target](*team[i], *team[tgt])) {
                tgt = i;
                count = 1;
            } else if (rand() % ++count == 0)
                tgt = i;
        }
        for (int a = 0; a < (int)actions.size(); ++a) {
            if (!team[tgt]->Alive())
                continue;
            actions[a]->Do(self, *team[tgt], team, team_size);
        }
    }
}

void Attack::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    // учитывать стаи
    int damage = Round(Round(self.damage * factor) * (self.DamageFactor() + target.vulnerability));
    bool crit = rand() % 100 < self.CritChanceFactor() * 100;
    if (crit)
        damage = Round(damage * 1.25);
    bool shield = target.Shield();
    if (shield)
        damage = Round(damage * (1 - target.Shield()));
    bool dodge = (~flags & PRECISE) && rand() % 100 < target.DodgeChance() * 100;
    if (dodge)
        damage = Round(damage * (1 - target.DodgeFactor()));
    bool armor = (~flags & BYPASS_ARMOR) && target.armor > 0;
    if (armor)
        damage = Round(damage * (1 - target.armor));
    for (auto mod_it = self.mods.begin(); mod_it != self.mods.end(); ) {
        if (mod_it->OutgoingAttack()) {
            auto modifier = mod_it->modifier;
            modifier->Dispose(self, &*mod_it);
            self.mods.erase(mod_it++);
            LOG("%s used up %s\n", self.Name().c_str(), modifier->name.c_str());
        } else
            ++mod_it;
    }
    for (auto mod_it = target.mods.begin(); mod_it != target.mods.end(); ) {
        if (mod_it->IncomingAttack()) {
            auto modifier = mod_it->modifier;
            modifier->Dispose(target, &*mod_it);
            target.mods.erase(mod_it++);
            LOG("%s used up %s\n", target.Name().c_str(), modifier->name.c_str());
        } else
            ++mod_it;
    }
    self.last_damage = damage;
    target.attacker = &self;
    target.Hit(damage);
    LOG("%s attacks %s for %d%s%s%s%s\n", self.Name().c_str(), target.Name().c_str(), damage, crit ? " Crit" : "", shield ? " Shield" : "", dodge ? " Dodge" : "", armor ? " Armor" : "");
    if (!target.Alive()) {
        LOG("%s dies!\n", target.Name().c_str());
        target.Revenge(team, team_size);
    } else if (target.health == 0)
        LOG("%s is immune to HP changes.\n", target.Name().c_str());
}

void Heal::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    int heal = Round(Round(self.damage * factor) * self.DamageFactor());
    if (target.health == 0) {
        LOG("%s is immune to HP changes\n", target.Name().c_str());
        return;
    }
    target.Heal(heal);
    LOG("%s heals %s for %d\n", self.Name().c_str(), target.Name().c_str(), heal);
}

void ImposeVulnerability::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&vulnerability, self);
}

void Cleanse::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Dispose(flags, self);
}

void Remove::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Dispose(flags, self);
}

void Taunt::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    RemoveTauntAction.Do(self, team, team_size);
    target.Impose(&taunt, self);
}

void IncreaseCritChance::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&increased_crit_chance, self);
}

void IncreaseDamage::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&increased_damage, self);
}

void ReduceSpeed::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&reduced_speed, self);
}

void ReduceDamage::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&reduced_damage, self);
}

void Dodge::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&dodge, self);
}

void IncreaseSpeed::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&increased_speed, self);
}

void ReduceCritChance::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&reduced_crit_chance, self);
}

void Shield::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&shield, self);
}

void DevourHeal::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&devour_heal, self);
}

void DamageOverTime::Do(Dino &self, Dino &target, Dino *team[], int team_size) const
{
    target.Impose(&damage_over_time, self);
}

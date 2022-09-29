#include "actions.h"
#include "dino.h"
#include "modifiers.h"
#include "logger.h"
#include <functional>
#include "utils.h"

using namespace std;

function<bool(const Dino &,const Dino &)> TargetCmp[] = {
    [](const Dino &dino1, const Dino &dino2) -> bool { return false; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health < dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health > dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.damage < dino2.damage; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.damage > dino2.damage; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.speed < dino2.speed; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.speed > dino2.speed; },
};

void ActionGroup::Do(Dino &self, Dino *team[], int team_size) const
{
    if (target == TARGET_ALL_OPPONENTS) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            for (int i = 0; i < team_size; ++i) {
                if (team[i]->team == self.team)
                    continue;
                actions[a]->Do(self, *team[i]);
            }
        }
    } else if (target == TARGET_TEAM) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            for (int i = 0; i < team_size; ++i) {
                if (team[i]->team != self.team)
                    continue;
                actions[a]->Do(self, *team[i]);
            }
        }
    } else if (target == TARGET_SELF) {
        for (int a = 0; a < (int)actions.size(); ++a) {
            actions[a]->Do(self, self);
        }
    } else {
        int tgt = -1;
        int count = 0;
        for (int i = 0; i < team_size; ++i) {
            if (team[i]->team == self.team)
                continue;
            if (target != TARGET_RANDOM && team[i]->taunt) {
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
            actions[a]->Do(self, *team[tgt]);
        }
    }
}

void Attack::Do(Dino &self, Dino &target) const
{
    // учитывать стаи
    int damage = round(round(self.damage * factor) * (self.DamageFactor() + target.vulnerability));
    bool shield = target.shields;
    if (shield)
        damage = round(damage * (1 - target.shields));
    bool crit = rand() % 100 < self.CritChanceFactor() * 100;
    if (crit)
        damage = round(damage * 1.25);
    bool dodge = (~flags & PRECISE) && rand() % 100 < target.dodge_factor * 100;
    if (dodge)
        damage = round(damage * (1 - target.dodge));
    bool armor = ~flags & BYPASS_ARMOR;
    if (armor)
        damage = round(damage * (1 - target.armor));
    for (auto mod_it = self.mods.begin(); mod_it != self.mods.end(); ) {
        if (mod_it->OutgoingAttack())
            self.mods.erase(mod_it++);
        else
            ++mod_it;
    }
    for (auto mod_it = target.mods.begin(); mod_it != target.mods.end(); ) {
        if (mod_it->IncomingAttack())
            target.mods.erase(mod_it++);
        else
            ++mod_it;
    }
    Logger::Log("%s attacks %s for %d%s%s%s\n", self.name.c_str(), target.name.c_str(), damage, crit ? " Crit" : "", shield ? " Shield" : "", dodge ? " Dodge" : "", armor ? " Armor" : "");
    target.health -= damage;
    if (target.health < 0)
        target.health = 0;
    if (target.Alive())
        target.CounterAttack(self);
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

void ImposeTaunt::Do(Dino &self, Dino &target) const
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

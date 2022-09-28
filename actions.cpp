#include "actions.h"
#include "dino.h"
#include "modifiers.h"
#include <functional>

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
        int tgt = 0;
        int count = 0;
        for (int i = 0; i < team_size; ++i) {
            if (team[i]->team == self.team)
                continue;
            if (target != TARGET_RANDOM && team[i]->taunt) {
                tgt = i;
                break;
            }
            if (TargetCmp[target](*team[tgt], *team[i]))
                continue;
            else if (TargetCmp[target](*team[i], *team[tgt]) || rand() % ++count == 0)
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
    int damage = self.damage * factor * (self.DamageFactor() + target.vulnerability) * (1 - target.shields);
    bool armor = ~flags & BYPASS_ARMOR;
    if (armor)
        damage *= 1 - target.armor;
    bool crit = rand() % 100 < self.CritChanceFactor() * 100;
    if (crit)
        damage *= 1.25;
    bool dodge = (~flags & PRECISE) && rand() % 100 < target.dodge_factor * 100;
    if (dodge)
        damage *= 1 - target.dodge;
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
    printf("%s attacks %s for %d%s%s%s\n", self.name.c_str(), target.name.c_str(), damage, crit ? " Crit" : "", dodge ? " Dodge" : "", armor ? " Armor" : "");
    target.health -= damage;
    if (target.health < 0)
        target.health = 0;
    if (target.Alive())
        target.CounterAttack(self);
}

void ImposeVulnerability::Do(Dino &self, Dino &target) const
{
    target.Impose(&vulnerability);
    printf("%s imposes vulnerability to %s for %d turn(s) %d attack(s)\n", self.name.c_str(), target.name.c_str(), vulnerability.duration, vulnerability.number);
}

void CleanseReducedDamage::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(REDUCE_DAMAGE);
    printf("%s cleares %d vulnerabilities from %s\n", self.name.c_str(), count, target.name.c_str());
}

void Remove::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(flags);
    printf("%s removes %d modifiers from %s\n", self.name.c_str(), count, target.name.c_str());
}

void RemoveDodge::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(DODGE);
    printf("%s removes %d dodges from %s\n", self.name.c_str(), count, target.name.c_str());
}

void RemoveCloak::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(CLOAK);
    printf("%s removes %d cloaks from %s\n", self.name.c_str(), count, target.name.c_str());
}

void RemoveIncresedSpeed::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(INCRESED_SPEED);
    printf("%s removes %d incresed speed from %s\n", self.name.c_str(), count, target.name.c_str());
}

void ImposeTaunt::Do(Dino &self, Dino &target) const
{
    target.Impose(new Taunt(duration));
    printf("%s imposes taunt to %s for %d turn(s)\n", self.name.c_str(), target.name.c_str(), duration);
}

void BreakShields::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(SHIELD);
    printf("%s breaks %d shields from %s\n", self.name.c_str(), count, target.name.c_str());
}

void RemoveTaunt::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(TAUNT);
    printf("%s removes %d taunts from %s\n", self.name.c_str(), count, target.name.c_str());
}

void CleanseCritChanceReduction::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(CRIT_CHANCE_REDUCTION);
    printf("%s cleares %d crit chance reduction from %s\n", self.name.c_str(), count, target.name.c_str());
}

void IncreaseCritChance::Do(Dino &self, Dino &target) const
{
    target.Impose(&increased_crit_chance);
    printf("%s increases crit chance by %d%% for %s for %d turn(s), %d attacks\n", self.name.c_str(), (int)(increased_crit_chance.factor * 100), target.name.c_str(), increased_crit_chance.duration, increased_crit_chance.number);
}

void IncreaseDamage::Do(Dino &self, Dino &target) const
{
    target.Impose(&increased_damage);
    printf("%s increases damage by %d%% for %s for %d turn(s), %d attacks\n", self.name.c_str(), (int)(increased_damage.factor * 100), target.name.c_str(), increased_damage.duration, increased_damage.number);
}

void CleanseVulnerable::Do(Dino &self, Dino &target) const
{
    int count = target.Dispose(VULNERABILITY);
    printf("%s cleares %d vulnerables from %s\n", self.name.c_str(), count, target.name.c_str());
}

void ReduceSpeed::Do(Dino &self, Dino &target) const
{
    target.Impose(&reduced_speed);
    printf("%s reduses speed by %d%% for %s for %d turn(s)\n", self.name.c_str(), (int)(reduced_speed.factor * 100), target.name.c_str(), reduced_speed.duration);
}


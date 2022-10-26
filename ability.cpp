#include "ability.h"

#include "dino.h"
#include <memory.h>
#include "actions.h"

using namespace actions;
using namespace std;

void Ability::Prepare(Dino &self, int *cooldown, bool *priority) const
{
    if (priority != nullptr)
        *priority = this->priority;
    if (cooldown != nullptr)
        *cooldown = this->cooldown;
}

function<bool(const Dino &,const Dino &)> TargetCmp[] = {
    [](const Dino &dino1, const Dino &dino2) -> bool { return false; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health < dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health > dino2.health; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Damage() < dino2.Damage(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Damage() > dino2.Damage(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Speed() < dino2.Speed(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.Speed() > dino2.Speed(); },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.n_positive_effects > dino2.n_positive_effects; },
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.health < dino2.health; },
};

function<bool(const Dino &, const Dino &)> CheckTarget[] = {
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // random
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // lowest hp
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // highest hp
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // lowest damage
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // highest damage
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // lowest speed
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // highest speed
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team != dino2.team; }, // most positive effects
    [](const Dino &dino1, const Dino &dino2) -> bool { return dino1.team == dino2.team; }, // lowest hp teammate
};

void Ability::Do(Dino &self, Dino team[], int team_size) const
{
    int n_targets = (int)(sizeof(TargetCmp) / sizeof(*TargetCmp));
    int dino_id[n_targets];
    memset(dino_id, -1, sizeof(dino_id));
    for (int target = 0; target < n_targets; ++target) {
        int count = 0;
        for (int i = 0; i < team_size; ++i) {
            if (!team[i].Alive())
                continue;
            if (!CheckTarget[target](self, team[i]))
                continue;
            if (target != TARGET_RANDOM && team[i].Taunt() && rand() % 100 < (1 - self.kind->taunt_resistance) * 100) {
                dino_id[target] = i;
                break;
            }
            if (dino_id[target] == -1) {
                dino_id[target] = i;
                count = 1;
            } else if (TargetCmp[target](team[dino_id[target]], team[i]))
                continue;
            else if (TargetCmp[target](team[i], team[dino_id[target]])) {
                dino_id[target] = i;
                count = 1;
            } else if (rand() % ++count == 0)
                dino_id[target] = i;
        }
    }
    for (const auto &action: actions) {
        switch(action->target) {
        case TARGET_ALL_OPPONENTS:
            for (int i = 0; i < team_size; ++i) {
                if (team[i].team == self.team)
                    continue;
                if (!team[i].Alive())
                    continue;
                action->Do(self, team[i]);
            }
            break;
        case TARGET_TEAM:
            for (int i = 0; i < team_size; ++i) {
                if (team[i].team != self.team)
                    continue;
                if (!team[i].Alive())
                    continue;
                action->Do(self, team[i]);
            }
            break;
        case TARGET_SELF:
            action->Do(self, self);
            break;
        case TARGET_ATTACKER:
            if (!self.attacker->Alive())
                continue;
            action->Do(self, *self.attacker);
            break;
        default:
            action->Do(self, team[dino_id[action->target]]);
            break;
        }
    }
}

void RevengeAbility::Prepare(Dino &self, int *cooldown, bool *priority) const
{
    self.revenge_ready = self.revenge;
    if (self.revenge_ready)
        revenge_ability.Prepare(self, cooldown, priority);
    else
        Ability::Prepare(self, cooldown, priority);

}

void RevengeAbility::Do(Dino &self, Dino team[], int size) const
{
    if (self.revenge_ready)
        revenge_ability.Do(self, team, size);
    else
        Ability::Do(self, team, size);
}

void ThreatenedAbility::Prepare(Dino &self, int *cooldown, bool *priority) const
{
    self.threatened = threat_checker(self);
    if (self.threatened)
        threatened_ability.Prepare(self, cooldown, priority);
    else
        Ability::Prepare(self, cooldown, priority);
}

void ThreatenedAbility::Do(Dino &self, Dino team[], int size) const
{
    if (self.threatened)
        threatened_ability.Do(self, team, size);
    else
        Ability::Do(self, team, size);
}

void CounterAbility::Do(Dino &self, Dino team[], int size) const
{
    Ability::Do(self, team, size);
}

void ThreatenedCounterAbility::Do(Dino &self, Dino team[], int size) const
{
    if (threat_checker(self))
        threatened_ability.Do(self, team, size);
    else
        Ability::Do(self, team, size);
}

#include "dino.h"
#include "modifiers.h"
#include "actions.h"
#include "logger.h"
#include <memory>
#include <memory.h>

using namespace std;
using namespace modifiers;
using namespace actions;

bool Ability::Priority(Dino &dino) const
{
    if (dino.threatened)
        return threatened_ability->priority;
    return priority;
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
    auto &actions = self.threatened ? threatened_ability->actions : this->actions;
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

static const double LevelFactor[] = {
        0,
        0.2953027716977619,
        0.31006791028265,
        0.3255713057967825,
        0.3418498710866216,
        0.3589423646409527,
        0.37688948287300034,
        0.3957339570166504,
        0.4155206548674829,
        0.43629668761085705,
        0.45811152199139993,
        0.48101709809096993,
        0.5050679529955184,
        0.5303213506452944,
        0.5568374181775592,
        0.5846792890864372,
        0.6139132535407591,
        0.644608916217797,
        0.6768393620286869,
        0.7106813301301212,
        0.7462153966366274,
        0.7835261664684589,
        0.8227024747918819,
        0.863837598531476,
        0.9070294784580498,
        0.9523809523809523,
        1,
        1.05,
        1.1025,
        1.1576250000000001,
        1.2155062500000002
};
static const double BoostFactor[] = {1.0, 1.025, 1.05, 1.075, 1.1, 1.125, 1.15, 1.175, 1.2, 1.225, 1.25, 1.275, 1.3, 1.325, 1.35, 1.375, 1.4, 1.425, 1.45, 1.475, 1.5};

Dino::Dino(int _team, int _index, int _level, int _health_boost, int _damage_boost, int _speed_boost, const DinoKind *_kind)
    : kind(_kind)
    , rounds((int)kind->ability.size())
    , team(_team)
    , index(_index)
    , level(_level)
    , health_boost(_health_boost)
    , damage_boost(_damage_boost)
    , speed_boost(_speed_boost)
    , max_health(_kind->health * LevelFactor[level] * BoostFactor[health_boost])
    , health(max_health)
    , damage(_kind->damage * LevelFactor[level] * BoostFactor[damage_boost])
    , speed(_kind->speed + 2 * speed_boost)
    , crit_chance_factor(_kind->crit)
    , armor(_kind->armor)
    , total_health(rounds * (int)(kind->health * LevelFactor[level] * BoostFactor[health_boost]))
    , max_total_health(total_health)
{
    for (int i = 0; i < (int)kind->ability[round].size(); ++i) {
        cooldown[i] = Ability(i)->delay;
    }
    for (int i = 1; i < kind->flock; ++i) {
        flock_segment.push_back(i * max_health / kind->flock);
    }
}

bool Dino::Prepare(int _ability_id)
{
    if (!Alive())
        return true;
    if (cooldown[_ability_id] != 0)
        return false;
    for (int i = 0; i < 4; ++i) {
        if (cooldown[i] > 0)
            --cooldown[i];
    }
    ability_id = _ability_id;
    cooldown[ability_id] = Ability(ability_id)->cooldown;
    threatened = Ability(ability_id)->Threatened(*this);
    priority = Ability(ability_id)->Priority(*this);
    return true;
}

void Dino::Attack(Dino team[], int size)
{
    if (!Alive())
        return;
    if (!stun) {
        INFO("%s uses %s!\n", Name().c_str(), Ability(ability_id)->name.c_str());
        Ability(ability_id)->Do(*this, team, size);
    }
    REMOVE_MODS(*this, mod_it->OnAction(), DEBUG("%s has %s expired\n", Name().c_str(), modifier->name.c_str()));
}

void Dino::CounterAttack(Dino team[], int size)
{
    if (Alive() && attacker && !stun && kind->counter_attack) {
        INFO("%s counter-attacks using %s!\n", Name().c_str(), kind->counter_attack->name.c_str());
        bool thrtnd = threatened;
        threatened = kind->counter_attack->Threatened(*this);
        kind->counter_attack->Do(*this, team, size);
        threatened = thrtnd;
    }
    attacker = nullptr;
}

void Dino::Impose(const Modifier *mod, Dino &author)
{
    mod->Impose(*this, &mods.emplace_back(mod));
    INFO("%s imposes %s to %s for %d turn(s)%s\n", author.Name().c_str(), mod->name.c_str(), Name().c_str(), mod->duration, mod->number ? strprintf(" %d attack(s)", mod->number).c_str() : "");
}

void Dino::Dispose(int type_flags, Dino &author)
{
    REMOVE_MODS(*this, mod_it->Type() & type_flags, INFO("%s disposes %s from %s\n", author.Name().c_str(), modifier->name.c_str(), Name().c_str()));
}

void Dino::PassTurn()
{
    REMOVE_MODS(*this, mod_it->OnEndOfTurn(), DEBUG("%s has %s expired\n", Name().c_str(), modifier->name.c_str()));
}

void Dino::DevourHeal()
{
    if (health == 0 || devour_heal == 0)
        return;
    devour_heal = HealAbsorb(devour_heal);
    Heal(devour_heal);
    WARNING("%s is [devour] healed by %d\n", Name().c_str(), devour_heal);
}

void Dino::DamageOverTime(Dino team[], int team_size)
{
    if (health == 0 || damage_over_time == 0)
        return;
    Hit(damage_over_time);
    WARNING("%s is damaged [over time] by %d\n", Name().c_str(), damage_over_time);
    if (!Alive()) {
        ERROR("%s dies!\n", Name().c_str());
        static modifiers::Revenge revenge;
        for (int i = 0; i < team_size; ++i)
            team[i].Impose(&revenge, *this);
    } else if (health == 0)
        INFO("%s is immune to HP changes.\n", Name().c_str());
}

std::string Dino::Name() const
{
    if (team != 0)
        return strprintf("%s#%d (+%d,*%d,>%d)", kind->name.c_str(), index, health, Damage(), Speed());
    return strprintf("%s (+%d,*%d,>%d)", kind->name.c_str(), health, Damage(), Speed());
}

void Dino::Revive()
{
    health = max_health = kind->health * LevelFactor[level] * BoostFactor[health_boost];
    for (int i = 0; i < (int)kind->ability[round].size(); ++i) {
        cooldown[i] = Ability(i)->delay;
    }
    INFO("%s is revived!\n", Name().c_str());
}

void Dino::Hit(int damage)
{
    if (damage > health)
        damage = health;
    health -= damage;
    total_health -= damage;
}

void Dino::Heal(int heal)
{
    if (heal > max_health - health)
        heal = max_health - health;
    health += heal;
    total_health += heal;
}

int Dino::Absorb(int damage)
{
    if (kind->flock == 1)
        return damage;
    auto it = upper_bound(flock_segment.rbegin(), flock_segment.rend(), health, greater<int>());
    if (it != flock_segment.rend() && health - *it < damage)
        return health - *it;
    return damage;
}

int Dino::HealAbsorb(int heal)
{
    if (kind->flock == 1)
        return heal;
    auto it = lower_bound(flock_segment.begin(), flock_segment.end(), health, less<int>());
    if (it != flock_segment.end() && *it - health < heal)
        return *it - health;
    return heal;
}

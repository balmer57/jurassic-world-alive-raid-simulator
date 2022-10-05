#include "modifiers.h"
#include "dino.h"
#include "utils.h"

using namespace std;
using namespace modifiers;

void Vulnerability::Impose(Dino &target, Mod *) const
{
    target.vulnerability += factor * (1 - target.kind[target.round].vulnerable_resistance);
}

void Vulnerability::Dispose(Dino &target, Mod *) const
{
    target.vulnerability -= factor * (1 - target.kind[target.round].vulnerable_resistance);
}

void Taunt::Impose(Dino &target, Mod *) const
{
    target.taunt = true;
}

void Taunt::Dispose(Dino &target, Mod *) const
{
    target.taunt = false;
}

void IncreasedCritChance::Impose(Dino &target, Mod *) const
{
    target.crit_chance_factor += factor;
}

void IncreasedCritChance::Dispose(Dino &target, Mod *) const
{
    target.crit_chance_factor -= factor;
}

void IncreasedDamage::Impose(Dino &target, Mod *) const
{
    target.damage_factor += factor;
}

void IncreasedDamage::Dispose(Dino &target, Mod *) const
{
    target.damage_factor -= factor;
}

void ReducedSpeed::Impose(Dino &target, Mod *) const
{
    target.speed_factor -= factor * (1 - target.kind[target.round].reduce_speed_resistance);
}

void ReducedSpeed::Dispose(Dino &target, Mod *) const
{
    target.speed_factor += factor * (1 - target.kind[target.round].reduce_speed_resistance);
}

void ReducedDamage::Impose(Dino &target, Mod *) const
{
    target.damage_factor -= factor * (1 - target.kind[target.round].reduced_damage_resistance);
}

void ReducedDamage::Dispose(Dino &target, Mod *) const
{
    target.damage_factor += factor * (1 - target.kind[target.round].reduced_damage_resistance);
}

void Dodge::Impose(Dino &target, Mod *) const
{
    target.dodge.insert(make_pair(chance, factor));
}

void Dodge::Dispose(Dino &target, Mod *) const
{
    target.dodge.erase(target.dodge.find(make_pair(chance, factor)));
}

void IncreasedSpeed::Impose(Dino &target, Mod *) const
{
    target.speed_factor += factor;
}

void IncreasedSpeed::Dispose(Dino &target, Mod *) const
{
    target.speed_factor -= factor;
}

void ReducedCritChance::Impose(Dino &target, Mod *) const
{
    target.crit_chance_factor -= factor * (1 - target.kind[target.round].crit_reduction_resistance);
}

void ReducedCritChance::Dispose(Dino &target, Mod *) const
{
    target.crit_chance_factor += factor * (1 - target.kind[target.round].crit_reduction_resistance);
}

void Shield::Impose(Dino &target, Mod *) const
{
    target.shield.insert(factor);
}

void Shield::Dispose(Dino &target, Mod *) const
{
    target.shield.erase(target.shield.find(factor));
}

void Revenge::Impose(Dino &target, Mod *) const
{
    ++target.revenge;
}

void Revenge::Dispose(Dino &target, Mod *) const
{
    --target.revenge;
}

void DevourHeal::Impose(Dino &target, Mod *mod) const
{
    mod->value = Round(target.last_damage * factor);
    target.devour_heal += mod->value;
}

void DevourHeal::Dispose(Dino &target, Mod *mod) const
{
    target.devour_heal -= mod->value;
}

void DamageOverTime::Impose(Dino &target, Mod *) const
{
    target.damage_over_time += Round(target.max_total_health * factor * (1 - target.kind[target.round].damage_over_time_resistance));
}

void DamageOverTime::Dispose(Dino &target, Mod *) const
{
    target.damage_over_time -= Round(target.max_total_health * factor * (1 - target.kind[target.round].damage_over_time_resistance));
}

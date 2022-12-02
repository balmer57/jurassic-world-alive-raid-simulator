#include "modifiers.h"
#include "dino.h"
#include "utils.h"

using namespace std;
using namespace modifiers;

void Vulnerability::Impose(Dino &target, Mod *) const
{
    target.vulnerability += factor * (1 - target.kind->vulnerable_resistance);
}

void Vulnerability::Dispose(Dino &target, Mod *) const
{
    target.vulnerability -= factor * (1 - target.kind->vulnerable_resistance);
}

void Taunt::Impose(Dino &target, Mod *) const
{
    target.taunt = true;
    ++target.n_positive_effects;
}

void Taunt::Dispose(Dino &target, Mod *) const
{
    target.taunt = false;
    --target.n_positive_effects;
}

void IncreasedCritChance::Impose(Dino &target, Mod *) const
{
    target.crit_chance_factor += factor;
    ++target.n_positive_effects;
}

void IncreasedCritChance::Dispose(Dino &target, Mod *) const
{
    target.crit_chance_factor -= factor;
    --target.n_positive_effects;
}

void IncreasedDamage::Impose(Dino &target, Mod *) const
{
    target.damage_factor += factor;
    ++target.n_positive_effects;
}

void IncreasedDamage::Dispose(Dino &target, Mod *) const
{
    target.damage_factor -= factor;
    --target.n_positive_effects;
}

void ReducedSpeed::Impose(Dino &target, Mod *) const
{
    target.speed_factor -= factor * (1 - target.kind->speed_reduction_resistance);
}

void ReducedSpeed::Dispose(Dino &target, Mod *) const
{
    target.speed_factor += factor * (1 - target.kind->speed_reduction_resistance);
}

void ReducedDamage::Impose(Dino &target, Mod *) const
{
    target.damage_factor -= factor * (1 - target.kind->damage_reduction_resistance);
}

void ReducedDamage::Dispose(Dino &target, Mod *) const
{
    target.damage_factor += factor * (1 - target.kind->damage_reduction_resistance);
}

void Dodge::Impose(Dino &target, Mod *) const
{
    target.dodge.insert(make_pair(chance, factor));
    ++target.n_positive_effects;
}

void Dodge::Dispose(Dino &target, Mod *) const
{
    target.dodge.erase(target.dodge.find(make_pair(chance, factor)));
    --target.n_positive_effects;
}

void IncreasedSpeed::Impose(Dino &target, Mod *) const
{
    target.speed_factor += factor;
    ++target.n_positive_effects;
}

void IncreasedSpeed::Dispose(Dino &target, Mod *) const
{
    target.speed_factor -= factor;
    --target.n_positive_effects;
}

void ReducedCritChance::Impose(Dino &target, Mod *) const
{
    target.crit_chance_factor -= factor * (1 - target.kind->crit_reduction_resistance);
}

void ReducedCritChance::Dispose(Dino &target, Mod *) const
{
    target.crit_chance_factor += factor * (1 - target.kind->crit_reduction_resistance);
}

void Shield::Impose(Dino &target, Mod *) const
{
    target.shield.insert(factor);
    ++target.n_positive_effects;
}

void Shield::Dispose(Dino &target, Mod *) const
{
    target.shield.erase(target.shield.find(factor));
    --target.n_positive_effects;
}

void Revenge::Impose(Dino &target, Mod *) const
{
    ++target.revenge;
}

void Revenge::Dispose(Dino &target, Mod *) const
{
    --target.revenge;
    target.revenge_ready = false;
}

void DevourHeal::Impose(Dino &target, Mod *mod) const
{
    mod->value = Round(target.last_damage * factor / duration);
    target.devour_heal += mod->value;
    ++target.n_positive_effects;
}

void DevourHeal::Dispose(Dino &target, Mod *mod) const
{
    target.devour_heal -= mod->value;
    --target.n_positive_effects;
}

void DamageOverTime::Impose(Dino &target, Mod *) const
{
    target.damage_over_time += Round(target.max_total_health * factor * (1 - target.kind->damage_over_time_resistance));
}

void DamageOverTime::Dispose(Dino &target, Mod *) const
{
    target.damage_over_time -= Round(target.max_total_health * factor * (1 - target.kind->damage_over_time_resistance));
}

void Stun::Impose(Dino &target, Mod *mod) const
{
    ++target.stun;
}

void Stun::Dispose(Dino &target, Mod *mod) const
{
    --target.stun;
}

void Cloak::Impose(Dino &target, Mod *mod) const
{
    target.dodge.insert(make_pair(dodge_chance, dodge_factor));
    target.cloak_factor.insert(attack_factor);
    ++target.n_positive_effects;
}

void Cloak::Dispose(Dino &target, Mod *mod) const
{
    target.dodge.erase(target.dodge.find(make_pair(dodge_chance, dodge_factor)));
    target.cloak_factor.erase(target.cloak_factor.find(attack_factor));
    --target.n_positive_effects;
}

void IncreasedArmor::Impose(Dino &target, Mod *) const
{
    target.armor += factor;
    ++target.n_positive_effects;
}

void IncreasedArmor::Dispose(Dino &target, Mod *) const
{
    target.armor -= factor;
    --target.n_positive_effects;
}

void ReducedArmor::Impose(Dino &target, Mod *) const
{
    target.armor -= factor * (1 - target.kind->armor_reduction_resistance);
}

void ReducedArmor::Dispose(Dino &target, Mod *) const
{
    target.armor += factor * (1 - target.kind->armor_reduction_resistance);
}

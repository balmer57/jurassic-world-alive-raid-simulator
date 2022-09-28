#include "modifiers.h"
#include "dino.h"

void Vulnerability::Impose(Dino &target) const
{
    target.vulnerability += factor * (1 - target.kind->vulnerable_resistance);
}

void Vulnerability::Dispose(Dino &target) const
{
    target.vulnerability -= factor * (1 - target.kind->vulnerable_resistance);
}

void Taunt::Impose(Dino &target) const
{
    target.taunt = true;
}

void Taunt::Dispose(Dino &target) const
{
    target.taunt = false;
}

void IncreasedCritChance::Impose(Dino &target) const
{
    target.crit_chance_factor += factor;
}

void IncreasedCritChance::Dispose(Dino &target) const
{
    target.crit_chance_factor -= factor;
}

void IncreasedDamage::Impose(Dino &target) const
{
    target.damage_factor += factor;
}

void IncreasedDamage::Dispose(Dino &target) const
{
    target.damage_factor -= factor;
}

void ReducedSpeed::Impose(Dino &target) const
{
    target.speed *= (1 - factor);
}

void ReducedSpeed::Dispose(Dino &target) const
{
    target.speed /= (1 - factor);
}

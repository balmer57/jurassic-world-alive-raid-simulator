#ifndef __JWA_CALC__ACTIONS__H__
#define __JWA_CALC__ACTIONS__H__

#include <vector>
#include <memory>
#include <initializer_list>

#include "modifiers.h"

struct Dino;

namespace actions
{

struct Action
{
    Action()
    {
    }
    virtual ~Action() {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const = 0;
};

enum Target
{
    TARGET_RANDOM = 0,
    TARGET_LOWEST_HP,
    TARGET_HIGHEST_HP,
    TARGET_LOWEST_DAMAGE,
    TARGET_HIGHEST_DAMAGE,
    TARGET_SLOWEST,
    TARGET_FASTEST,
    TARGET_LOWEST_HP_TEAMMATE,
    TARGET_ALL_OPPONENTS,
    TARGET_ATTACKER,
    TARGET_SELF,
    TARGET_TEAM,
};

struct ActionGroup
{
    int target;
    std::vector<std::unique_ptr<Action>> actions;
    ActionGroup(int _target, std::initializer_list<Action *> _actions)
        : target(_target)
        , actions(_actions.begin(), _actions.end())
    {
    }
    virtual ~ActionGroup() {}
    virtual void Do(Dino &self, Dino *team[], int size) const;
};

static const int GROUP = 1;
static const int PRECISE = 2;
static const int BYPASS_ARMOR = 4;

struct Attack : public Action
{
    double factor;
    int flags;
    Attack(double _factor, int _flags = 0)
        : factor(_factor)
        , flags(_flags)
    {
    }
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Heal : public Action
{
    double factor;
    int flags;
    Heal(double _factor, int _flags = 0)
        : factor(_factor)
        , flags(_flags)
    {
    }
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct ImposeVulnerability : public Action
{
    modifiers::Vulnerability vulnerability;
    ImposeVulnerability(double _factor, int _duration, int _number)
        : vulnerability(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Cleanse : public Action
{
    int flags;
    Cleanse(int _flags)
        : flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Remove : public Action
{
    int flags;
    Remove(int _flags)
        : flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Taunt : public Action
{
    modifiers::Taunt taunt;
    Taunt(int _duration)
        : taunt(_duration)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct IncreaseCritChance : public Action
{
    modifiers::IncreasedCritChance increased_crit_chance;
    IncreaseCritChance(double _factor, int _duration, int _number)
        : increased_crit_chance(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct IncreaseDamage : public Action
{
    modifiers::IncreasedDamage increased_damage;
    IncreaseDamage(double _factor, int _duration, int _number)
        : increased_damage(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct ReduceSpeed : public Action
{
    modifiers::ReducedSpeed reduced_speed;
    ReduceSpeed(double _factor, int _duration)
        : reduced_speed(_factor, _duration)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct ReduceDamage : public Action
{
    modifiers::ReducedDamage reduced_damage;
    ReduceDamage(double _factor, int _duration, int _number)
        : reduced_damage(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Dodge : public Action
{
    modifiers::Dodge dodge;
    Dodge(double _chance, double _factor, int _duration, int _number)
        : dodge(_chance, _factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct IncreaseSpeed : public Action
{
    modifiers::IncreasedSpeed increased_speed;
    IncreaseSpeed(double _factor, int _duration)
        : increased_speed(_factor, _duration)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct ReduceCritChance : public Action
{
    modifiers::ReducedCritChance reduced_crit_chance;
    ReduceCritChance(double _factor, int _duration, int _number)
        : reduced_crit_chance(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct Shield : public Action
{
    modifiers::Shield shield;
    Shield(double _factor, int _duration, int _number)
        : shield(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct DevourHeal : public Action
{
    modifiers::DevourHeal devour_heal;
    DevourHeal(double _factor, int _duration)
        : devour_heal(_factor, _duration)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

struct DamageOverTime : public Action
{
    modifiers::DamageOverTime damage_over_time;
    DamageOverTime(double _factor, int _duration)
        : damage_over_time(_factor, _duration)
    {}
    virtual void Do(Dino &self, Dino &target, Dino *team[], int size) const override;
};

} // namespace actions

#endif // __JWA_CALC__ACTIONS__H__

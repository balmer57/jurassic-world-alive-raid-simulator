#ifndef __JWA_CALC__ACTIONS__H__
#define __JWA_CALC__ACTIONS__H__

#include <vector>
#include <memory>
#include <initializer_list>

#include "modifiers.h"

struct Dino;

struct Action
{
    Action()
    {
    }
    virtual ~Action() {}
    virtual void Do(Dino &self, Dino &target) const = 0;
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
    TARGET_ALL_OPPONENTS,
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
    void Do(Dino &self, Dino &target) const;
};

struct ImposeVulnerability : public Action
{
    Vulnerability vulnerability;
    ImposeVulnerability(int _factor, int _duration, int _number)
        : vulnerability(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const;
};

struct Cleanse : public Action
{
    int flags;
    Cleanse(int _flags)
        : flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Remove : public Action
{
    int flags;
    Remove(int _flags)
        : flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ImposeTaunt : public Action
{
    Taunt taunt;
    ImposeTaunt(int _duration)
        : taunt(_duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseCritChance : public Action
{
    IncreasedCritChance increased_crit_chance;
    IncreaseCritChance(int _factor, int _duration, int _number)
        : increased_crit_chance(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseDamage : public Action
{
    IncreasedDamage increased_damage;
    IncreaseDamage(int _factor, int _duration, int _number)
        : increased_damage(_factor, _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ReduceSpeed : public Action
{
    ReducedSpeed reduced_speed;
    ReduceSpeed(int _factor, int _duration)
        : reduced_speed(_factor, _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

#endif // __JWA_CALC__ACTIONS__H__

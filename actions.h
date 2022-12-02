#ifndef __JWA_CALC__ACTIONS__H__
#define __JWA_CALC__ACTIONS__H__

#include <vector>
#include <memory>
#include <initializer_list>
#include <list>
#include <utility>

#include "modifiers.h"

struct Dino;

namespace actions
{

enum Target
{
    TARGET_INHERIT = -1,
    TARGET_RANDOM = 0,
    TARGET_LOWEST_HP,
    TARGET_HIGHEST_HP,
    TARGET_LOWEST_DAMAGE,
    TARGET_HIGHEST_DAMAGE,
    TARGET_SLOWEST,
    TARGET_FASTEST,
    TARGET_MOST_POSITIVE_EFFECTS,
    TARGET_LOWEST_HP_TEAMMATE,
    TARGET_ALL_OPPONENTS,
    TARGET_ATTACKER,
    TARGET_SELF,
    TARGET_TEAM,
    TARGET_LAST
};

struct Action
{
    int target;
    Action()
        : target(TARGET_INHERIT)
    {
    }
    virtual ~Action() {}
    virtual void Do(Dino &self, Dino &target) const = 0;
};

#define TargetRandom(...) std::move(actions::ActionGroupFunction(TARGET_RANDOM, __VA_ARGS__))
#define TargetLowestHP(...) std::move(actions::ActionGroupFunction(TARGET_LOWEST_HP, __VA_ARGS__))
#define TargetHighestHP(...) std::move(actions::ActionGroupFunction(TARGET_HIGHEST_HP, __VA_ARGS__))
#define TargetLowestDamage(...) std::move(actions::ActionGroupFunction(TARGET_LOWEST_DAMAGE, __VA_ARGS__))
#define TargetHighestDamage(...) std::move(actions::ActionGroupFunction(TARGET_HIGHEST_DAMAGE, __VA_ARGS__))
#define TargetSlowest(...) std::move(actions::ActionGroupFunction(TARGET_SLOWEST, __VA_ARGS__))
#define TargetFastest(...) std::move(actions::ActionGroupFunction(TARGET_FASTEST, __VA_ARGS__))
#define TargetMostPositiveEffects(...) std::move(actions::ActionGroupFunction(TARGET_MOST_POSITIVE_EFFECTS, __VA_ARGS__))
#define TargetLowestHPTeammate(...) std::move(actions::ActionGroupFunction(TARGET_LOWEST_HP_TEAMMATE, __VA_ARGS__))
#define TargetAllOpponents(...) std::move(actions::ActionGroupFunction(TARGET_ALL_OPPONENTS, __VA_ARGS__))
#define TargetAttacker(...) std::move(actions::ActionGroupFunction(TARGET_ATTACKER, __VA_ARGS__))
#define TargetSelf(...) std::move(actions::ActionGroupFunction(TARGET_SELF, __VA_ARGS__))
#define TargetTeam(...) std::move(actions::ActionGroupFunction(TARGET_TEAM, __VA_ARGS__))
#define TargetLast(...) std::move(actions::ActionGroupFunction(TARGET_LAST, __VA_ARGS__))

inline bool IsImmutableTarget(int target)
{
    return target == TARGET_ALL_OPPONENTS ||
           target == TARGET_ATTACKER ||
           target == TARGET_SELF ||
           target == TARGET_TEAM ||
           target == TARGET_LAST;
}

template<typename ...Args>
std::list<std::unique_ptr<Action>> ActionGroupFunction(int target, Args &&...args);

template<typename ...Args>
class ActionGroupClass;

template<typename ...Args>
class ActionGroupClass<std::list<std::unique_ptr<Action>>, Args...>
{
public:
    static std::list<std::unique_ptr<Action>> Make(int target, std::list<std::unique_ptr<Action>> &&actions, Args&&...args)
    {
        for (auto it = actions.begin(); it != actions.end(); ++it) {
            if ((*it)->target == TARGET_INHERIT) {
                (*it)->target = target;
                if (!IsImmutableTarget(target))
                    target = TARGET_LAST;
            }
        }
        std::list<std::unique_ptr<Action>> list(std::move(ActionGroupFunction(target, std::forward<Args>(args)...)));
        for (auto it = actions.rbegin(); it != actions.rend(); ++it) {
            list.push_front(std::move(*it));
        }
        return list;
    }
};

template<typename A, typename ...Args>
class ActionGroupClass<A, Args...>
{
public:
    static std::list<std::unique_ptr<Action>> Make(int target, A &&action, Args&&...args)
    {
        if (action.target == TARGET_INHERIT) {
            action.target = target;
            if (!IsImmutableTarget(target))
                target = TARGET_LAST;
        }
        std::list<std::unique_ptr<Action>> list(std::move(ActionGroupFunction(target, std::forward<Args>(args)...)));
        list.push_front(std::move(std::unique_ptr<A>(new A(std::forward<A&&>(action)))));
        return list;
    }
};

template<>
class ActionGroupClass<>
{
public:
    static std::list<std::unique_ptr<Action>> Make(int target)
    {
        return std::move(std::list<std::unique_ptr<Action>>());
    }
};

template<typename ...Args>
std::list<std::unique_ptr<Action>> ActionGroupFunction(int target, Args &&...args)
{
    return ActionGroupClass<Args...>::Make(target, std::forward<Args>(args)...);
}

static const int GROUP = 1 << 0;
static const int PRECISE = 1 << 1;
static const int BYPASS_ARMOR = 1 << 2;
static const int REND = 1 << 3;
static const int ALWAYS_CRITS = 1 << 4;

std::list<std::unique_ptr<Action>> Attack(double _factor, int _flags = 0);
std::list<std::unique_ptr<Action>> DevouringAttack(double _attack_factor, double _devour_factor, int _duration, int _flags = 0);
std::list<std::unique_ptr<Action>> Rend(double _factor, int _flags = 0);

struct PrepareAttack : public Action
{
    int flags;
    PrepareAttack(int _flags = 0)
        : flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct AttackAction : public Action
{
    double factor;
    int flags;
    AttackAction(double _factor, int _flags = 0)
        : factor(_factor)
        , flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Revenge : public Action
{
    modifiers::Revenge revenge;
    Revenge()
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

static const int FIXED = 1 << 3;

std::list<std::unique_ptr<Action>> Heal(double _factor, int _flags = 0);
std::list<std::unique_ptr<Action>> FixedHeal(double _factor, int _flags = 0);

struct HealAction : public Action
{
    double factor;
    int flags;
    HealAction(double _factor, int _flags)
        : factor(_factor)
        , flags(_flags)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Sacrifice : public Action
{
    double factor;
    Sacrifice(double _factor)
        : factor(_factor / 100.)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct RallyHeal : public Action
{
    double factor;
    RallyHeal(double _factor)
        : factor(_factor / 100.)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ImposeVulnerability : public Action
{
    modifiers::Vulnerability vulnerability;
    ImposeVulnerability(double _factor, int _duration, int _number)
        : vulnerability(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
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

std::list<std::unique_ptr<Action>> Taunt(int _duration);

struct TauntAction : public Action
{
    modifiers::Taunt taunt;
    TauntAction(int _duration)
        : taunt(_duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseCritChance : public Action
{
    modifiers::IncreasedCritChance increased_crit_chance;
    IncreaseCritChance(double _factor, int _duration, int _number)
        : increased_crit_chance(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseDamage : public Action
{
    modifiers::IncreasedDamage increased_damage;
    IncreaseDamage(double _factor, int _duration, int _number)
        : increased_damage(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ReduceSpeed : public Action
{
    modifiers::ReducedSpeed reduced_speed;
    ReduceSpeed(double _factor, int _duration)
        : reduced_speed(_factor / 100., _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ReduceDamage : public Action
{
    modifiers::ReducedDamage reduced_damage;
    ReduceDamage(double _factor, int _duration, int _number)
        : reduced_damage(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Dodge : public Action
{
    modifiers::Dodge dodge;
    Dodge(double _chance, double _factor, int _duration, int _number)
        : dodge(_chance / 100., _factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseSpeed : public Action
{
    modifiers::IncreasedSpeed increased_speed;
    IncreaseSpeed(double _factor, int _duration)
        : increased_speed(_factor / 100., _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ReduceCritChance : public Action
{
    modifiers::ReducedCritChance reduced_crit_chance;
    ReduceCritChance(double _factor, int _duration, int _number)
        : reduced_crit_chance(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Shield : public Action
{
    modifiers::Shield shield;
    Shield(double _factor, int _duration, int _number)
        : shield(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct DevourHeal : public Action
{
    modifiers::DevourHeal devour_heal;
    DevourHeal(double _factor, int _duration)
        : devour_heal(_factor / 100., _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct DamageOverTime : public Action
{
    modifiers::DamageOverTime damage_over_time;
    DamageOverTime(double _factor, int _duration)
        : damage_over_time(_factor / 100., _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Stun : public Action
{
    double factor;
    modifiers::Stun stun;
    Stun(double _factor, int _duration)
        : factor(_factor / 100.)
        , stun(_duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct Cloak : public Action
{
    modifiers::Cloak cloak;
    Cloak(double _attack_factor, double _dodge_chance, double _dodge_factor, int _duration)
        : cloak(_attack_factor, _dodge_chance / 100., _dodge_factor / 100., _duration)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct IncreaseArmor : public Action
{
    modifiers::IncreasedArmor increased_armor;
    IncreaseArmor(double _factor, int _duration, int _number)
        : increased_armor(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

struct ReduceArmor : public Action
{
    modifiers::ReducedArmor reduced_armor;
    ReduceArmor(double _factor, int _duration, int _number)
        : reduced_armor(_factor / 100., _duration, _number)
    {}
    virtual void Do(Dino &self, Dino &target) const override;
};

std::list<std::unique_ptr<Action>> UnableToSwap(int _duration);
std::list<std::unique_ptr<Action>> Swap();

} // namespace actions

#endif // __JWA_CALC__ACTIONS__H__

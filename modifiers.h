#ifndef __JWA_CALC__MODIFIERS__H__
#define __JWA_CALC__MODIFIERS__H__

#include <string>

struct Dino;

static const int REDUCED_DAMAGE = 1 << 0;
static const int DODGE = 1 << 1;
static const int CLOAK = 1 << 2;
static const int INCREASED_SPEED = 1 << 3;
static const int SHIELD = 1 << 4;
static const int TAUNT = 1 << 5;
static const int CRIT_CHANCE_REDUCTION = 1 << 6;
static const int VULNERABILITY = 1 << 7;
static const int INCREASED_CRIT_CHANCE = 1 << 8;
static const int INCREASED_DAMAGE = 1 << 9;
static const int REDUCED_SPEED = 1 << 10;
static const int DAMAGE_OVER_TIME = 1 << 11;
static const int REDUCED_CRIT_CHANCE = 1 << 12;
static const int REVENGE = 1 << 13;
static const int DEVOUR_HEAL = 1 << 14;

static const int NEGATIVE_EFFECTS = REDUCED_DAMAGE|CRIT_CHANCE_REDUCTION|VULNERABILITY|REDUCED_SPEED|DAMAGE_OVER_TIME|REDUCED_CRIT_CHANCE;
static const int POSITIVE_EFFECTS = DODGE|CLOAK|INCREASED_SPEED|SHIELD|TAUNT|INCREASED_CRIT_CHANCE|INCREASED_DAMAGE|DEVOUR_HEAL;

namespace modifiers
{

struct Mod;

struct Modifier
{
    const std::string name;
    int duration;
    int number;

    Modifier(const std::string &_name, int _duration, int _number = 0)
        : name(_name)
        , duration(_duration)
        , number(_number)
    {
    }
    virtual ~Modifier() {}
    virtual void Impose(Dino &target, Mod *mod) const = 0;
    virtual void Dispose(Dino &target, Mod *mod) const = 0;
    virtual int Type() const = 0;
    virtual bool OutgoingAttack(Mod *mod) const
    {
        return false;
    }
    virtual bool IncomingAttack(Mod *mod) const
    {
        return false;
    }
};

struct Mod
{
    const Modifier *modifier;
    int duration;
    int number;
    int value = 0;
    Mod(const Modifier *_modifier)
        : modifier(_modifier)
        , duration(_modifier->duration)
        , number(_modifier->number)
    {
    }
    ~Mod()
    {
    }
    bool OutgoingAttack()
    {
        return modifier->OutgoingAttack(this);
    }
    bool IncomingAttack()
    {
        return modifier->IncomingAttack(this);
    }
};

struct Vulnerability: public Modifier
{
    double factor;

    Vulnerability(double _factor, int _duration, int _number)
        : Modifier("vulnerability", _duration, _number)
        , factor(_factor / 100.)
    {
    }
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return VULNERABILITY;
    }
    virtual bool IncomingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct Taunt: public Modifier
{
    Taunt(int _duration)
        : Modifier("taunt", _duration)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return TAUNT;
    }
};

struct IncreasedCritChance: public Modifier
{
    double factor;
    IncreasedCritChance(double _factor, int _duration, int _number)
        : Modifier("increased crit chance", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return INCREASED_CRIT_CHANCE;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct IncreasedDamage: public Modifier
{
    double factor;
    IncreasedDamage(double _factor, int _duration, int _number)
        : Modifier("increased damage", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return INCREASED_DAMAGE;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct ReducedSpeed: public Modifier
{
    double factor;
    ReducedSpeed(double _factor, int _duration)
        : Modifier("reduced speed", _duration)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return REDUCED_SPEED;
    }
};

struct ReducedDamage: public Modifier
{
    double factor;
    ReducedDamage(double _factor, int _duration, int _number)
        : Modifier("reduced damage", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return REDUCED_DAMAGE;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct Dodge : public Modifier
{
    double chance;
    double factor;
    Dodge(double _chance, double _factor, int _duration, int _number)
        : Modifier("dodge", _duration, _number)
        , chance(_chance / 100.)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return DODGE;
    }
    virtual bool IncomingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return mod->number == 0;
    }
};

struct IncreasedSpeed: public Modifier
{
    double factor;
    IncreasedSpeed(double _factor, int _duration)
        : Modifier("increased speed", _duration)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return INCREASED_SPEED;
    }
};

struct ReducedCritChance: public Modifier
{
    double factor;
    ReducedCritChance(double _factor, int _duration, int _number)
        : Modifier("reduced crit chance", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return REDUCED_CRIT_CHANCE;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct Shield : public Modifier
{
    double factor;
    Shield(double _factor, int _duration, int _number)
        : Modifier("shield", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return SHIELD;
    }
    virtual bool IncomingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return mod->number == 0;
    }
};

struct Revenge : public Modifier
{
    Revenge()
        : Modifier("revenge", 1, 1)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return REVENGE;
    }
    virtual bool OutgoingAttack(Mod *mod) const override
    {
        return !--mod->number;
    }
};

struct DevourHeal : public Modifier
{
    double factor;
    DevourHeal(double _factor, int _duration)
        : Modifier("devour heal", _duration)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return DEVOUR_HEAL;
    }
};

struct DamageOverTime : public Modifier
{
    double factor;
    DamageOverTime(double _factor, int _duration)
        : Modifier("damage over time", _duration)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target, Mod *mod) const override;
    virtual void Dispose(Dino &target, Mod *mod) const override;
    virtual int Type() const override
    {
        return DAMAGE_OVER_TIME;
    }
};

} // namespace modifiers

#endif // __JWA_CALC__MODIFIERS__H__

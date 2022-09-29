#ifndef __JWA_CALC__MODIFIERS__H__
#define __JWA_CALC__MODIFIERS__H__

#include <string>

struct Dino;
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
    virtual void Impose(Dino &target) const = 0;
    virtual void Dispose(Dino &target) const = 0;
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
    Mod(const Modifier *_modifier)
        : modifier(_modifier)
        , duration(_modifier->duration)
        , number(_modifier->number)
    {}
    bool OutgoingAttack()
    {
        return modifier->OutgoingAttack(this);
    }
    bool IncomingAttack()
    {
        return modifier->IncomingAttack(this);
    }
};

static const int REDUCED_DAMAGE = 1 << 0;
static const int DODGE = 1 << 1;
static const int CLOAK = 1 << 2;
static const int INCRESED_SPEED = 1 << 3;
static const int SHIELD = 1 << 4;
static const int TAUNT = 1 << 5;
static const int CRIT_CHANCE_REDUCTION = 1 << 6;
static const int VULNERABILITY = 1 << 7;
static const int INCREASED_CRIT_CHANCE = 1 << 8;
static const int INCREASED_DAMAGE = 1 << 9;
static const int REDUCED_SPEED = 1 << 10;

struct Vulnerability: public Modifier
{
    double factor;

    Vulnerability(int _factor, int _duration, int _number)
        : Modifier("vulnerability", _duration, _number)
        , factor(_factor / 100.)
    {
    }
    virtual void Impose(Dino &target) const override;
    virtual void Dispose(Dino &target) const override;
    virtual int Type() const
    {
        return VULNERABILITY;
    }
};

struct Taunt: public Modifier
{
    Taunt(int _duration)
        : Modifier("taunt", _duration)
    {}
    virtual void Impose(Dino &target) const override;
    virtual void Dispose(Dino &target) const override;
    virtual int Type() const
    {
        return TAUNT;
    }
};

struct IncreasedCritChance: public Modifier
{
    double factor;
    IncreasedCritChance(int _factor, int _duration, int _number)
        : Modifier("increased crit chance", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target) const override;
    virtual void Dispose(Dino &target) const override;
    virtual int Type() const
    {
        return INCREASED_CRIT_CHANCE;
    }
    virtual bool OutgoingAttack(Mod *mod) const
    {
        return !--mod->number;
    }
};

struct IncreasedDamage: public Modifier
{
    double factor;
    IncreasedDamage(int _factor, int _duration, int _number)
        : Modifier("increased damage", _duration, _number)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target) const override;
    virtual void Dispose(Dino &target) const override;
    virtual int Type() const
    {
        return INCREASED_DAMAGE;
    }
    virtual bool OutgoingAttack(Mod *mod) const
    {
        return !--mod->number;
    }
};

struct ReducedSpeed: public Modifier
{
    double factor;
    ReducedSpeed(int _factor, int _duration)
        : Modifier("reduced speed", _duration)
        , factor(_factor / 100.)
    {}
    virtual void Impose(Dino &target) const override;
    virtual void Dispose(Dino &target) const override;
    virtual int Type() const
    {
        return REDUCED_SPEED;
    }
};

#endif // __JWA_CALC__MODIFIERS__H__

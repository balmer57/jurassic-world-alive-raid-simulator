#ifndef __JWA_CALC__DINO__H__
#define __JWA_CALC__DINO__H__

#include <vector>
#include <memory>
#include <string>
#include <list>
#include <initializer_list>
#include "strprintf.h"
#include "modifiers.h"
#include "actions.h"

struct ActionGroup;
struct Dino;

struct Ability
{
    int delay;
    int cooldown;
    bool priority;
    std::vector<std::unique_ptr<ActionGroup>> action_groups;

    Ability(int _delay, int _cooldown, bool _priority, std::initializer_list<ActionGroup *> _action_groups);
    bool Threatened(Dino &dino) const
    {
        return false;
    }
    bool Priority(Dino &dino) const
    {
        return priority;
    }
    void Do(Dino &self, Dino *team[], int size) const;
};

struct Attack;

struct DinoKind
{
    std::string name;
    int health;
    int damage;
    int speed;
    double armor;
    double crit;
    double crit_reduction_resistance;
    double damage_over_time_resistance;
    double reduced_damage_resistance;
    double rend_resistance;
    double reduce_speed_resistance;
    double stun_resistance;
    double taunt_resistance;
    double vulnerable_resistance;
    std::vector<std::unique_ptr<Ability>> ability;
    std::unique_ptr<Ability> counter_attack;

    DinoKind(const std::string &_name, int _health, int _damage, int _speed, int _armor, int _crit,
            double _crit_reduction_resistance,
            double _damage_over_time_resistance,
            double _reduced_damage_resistance,
            double _rend_resistance,
            double _reduce_speed_resistance,
            double _stun_resistance,
            double _taunt_resistance,
            double _vulnerable_resistance,
            std::initializer_list<Ability *> _ability, Ability *_counter_attack)
        : name(_name)
        , health(_health)
        , damage(_damage)
        , speed(_speed)
        , armor(_armor / 100.)
        , crit(_crit / 100.)
        , crit_reduction_resistance(_crit_reduction_resistance / 100.)
        , damage_over_time_resistance(_damage_over_time_resistance / 100.)
        , reduced_damage_resistance(_reduced_damage_resistance / 100.)
        , rend_resistance(_rend_resistance / 100.)
        , reduce_speed_resistance(_reduce_speed_resistance / 100.)
        , stun_resistance(_stun_resistance / 100.)
        , taunt_resistance(_taunt_resistance / 100.)
        , vulnerable_resistance(_vulnerable_resistance / 100.)
        , ability(_ability.begin(), _ability.end())
        , counter_attack(_counter_attack)
    {
    }
};

struct Modifier;

struct Dino
{
    std::string name;
    DinoKind *kind; // базовые параметры
    int rounds;
    int team; // команда (0 - босс, 1 - игроки)
    int index; // позиция в схеме
    int health; // текущее количество жизней
    int damage; // текущая атака
    int speed; // текущая скорость
    int ability_id = -1; // номер атаки
    bool priority = false; // приоритет в текущем ходу
    bool threatened = false; // угнетение в текущем ходу
    std::list<Mod> mods;
    double vulnerability = 0;
    double damage_factor = 1;
    double crit_chance_factor;
    double shields = 0;
    double armor;
    double dodge = 0;
    double dodge_factor = 0;
    bool taunt = false;
    int total_health = 0;
    int round = 0;

    Dino(int _team, int _index, DinoKind *_kind, int _rounds = 1)
        : name(strprintf("%s(%d)", _kind->name.c_str(), _index))
        , kind(_kind)
        , rounds(_rounds)
        , team(_team)
        , index(_index)
        , health(_kind->health)
        , damage(_kind->damage)
        , speed(_kind->speed)
        , crit_chance_factor(_kind->crit)
        , armor(_kind->armor)
    {
        for (int i = 0; i < rounds; ++i) {
            total_health += kind[i].health;
        }
    }

    int Speed() const
    {
        return priority * 1000 + speed;
    }

    void Prepare(int _ability_id);
    void Attack(Dino *team[], int size);
    void CounterAttack(Dino &target);
    void Impose(const Modifier *mod, Dino &author);
    int Dispose(int type_flags, Dino &author);
    double DamageFactor() const
    {
        if (damage_factor < 0)
            return 0;
        return damage_factor;
    }
    double CritChanceFactor() const
    {
        if (crit_chance_factor < 0)
            return 0;
        return crit_chance_factor;
    }
    bool Alive() const
    {
        return health > 0 || round + 1 < rounds;
    }
    void PassTurn();
};

#endif // __JWA_CALC__DINO__H__

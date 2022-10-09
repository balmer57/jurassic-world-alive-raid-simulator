#ifndef __JWA_CALC__DINO__H__
#define __JWA_CALC__DINO__H__

#include <vector>
#include <memory>
#include <string>
#include <list>
#include <initializer_list>
#include <functional>
#include <set>
#include <list>
#include "strprintf.h"
#include "modifiers.h"
#include "actions.h"
#include "utils.h"

struct Dino;

struct Ability
{
    std::string name;
    int delay;
    int cooldown;
    bool priority;
    std::list<std::unique_ptr<actions::Action>> actions;
    std::function<bool(Dino&)> threat_checker;
    std::unique_ptr<Ability> threatened_ability;

    Ability(const std::string &_name, int _delay, int _cooldown, bool _priority, std::initializer_list<std::list<std::unique_ptr<actions::Action>>> _action_lists, std::function<bool(Dino&)> _threat_checker = [](Dino&) { return false; }, Ability *_threatened_ability = nullptr)
        : name(_name)
        , delay(_delay)
        , cooldown(_cooldown)
        , priority(_priority)
        , actions()
        , threat_checker(std::move(_threat_checker))
        , threatened_ability(_threatened_ability)
    {
        for (auto list_it = _action_lists.begin(); list_it != _action_lists.end(); ++list_it) {
            for (auto action_it = const_cast<std::list<std::unique_ptr<actions::Action>>*>(&*list_it)->begin(); action_it != const_cast<std::list<std::unique_ptr<actions::Action>>*>(&*list_it)->end(); ++action_it) {
                actions.push_back(std::move(*action_it));
            }
        }
    }
    bool Threatened(Dino &dino) const
    {
        return threat_checker(dino);
    }
    bool Priority(Dino &dino) const;
    void Do(Dino &self, Dino *team[], int size) const;
};

static const int COMMON = 0;
static const int RARE = 1;
static const int EPIC = 2;
static const int LEGENDARY = 3;
static const int UNIQUE = 4;
static const int APEX = 5;

struct DinoKind
{
    std::string name;
    int rarity;
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

    DinoKind(const std::string &_name, int _rarity, int _health, int _damage, int _speed, int _armor, int _crit,
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
        , rarity(_rarity)
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

struct dodge_cmp : public std::binary_function<std::pair<double, double>, std::pair<double, double>, bool>
{
    constexpr bool operator()(const std::pair<double, double> &lhs, const std::pair<double, double> &rhs ) const
    {
        if (lhs.first * lhs.second > rhs.first * rhs.second)
            return true;
        if (lhs.first * lhs.second < rhs.first * rhs.second)
            return false;
        if (lhs.first > rhs.first)
            return true;
//        if (lhs.first < rhs.first)
//            return false;
        return false;
    }
};

struct Dino
{
    const DinoKind *kind; // базовые параметры
    int rounds;
    int team; // команда
    int index; // позиция в схеме
    int level;
    int health_boost;
    int damage_boost;
    int speed_boost;
    int max_health;
    int health; // текущее количество жизней
    int damage; // текущая атака
    int speed; // текущая скорость
    int ability_id = -1; // номер атаки
    bool priority = false; // приоритет в текущем ходу
    bool threatened = false; // угнетение в текущем ходу
    std::list<modifiers::Mod> mods;
    double vulnerability = 0;
    double damage_factor = 1;
    double speed_factor = 1;
    double crit_chance_factor;
    double armor;
    bool taunt = false;
    int total_health = 0;
    int max_total_health = 0;
    int round = 0;
    Dino *attacker = nullptr; // это норм
    int revenge = 0;
    int last_damage = 0;
    int devour_heal = 0;
    int damage_over_time = 0;
    std::multiset<double, std::greater<double>> shield{0};
    std::multiset<std::pair<double, double>, dodge_cmp> dodge{std::make_pair(0, 0)};
    int cooldown[4] = {};
    double prepared_damage_factor = 0;
    bool crit = false;
    bool killer = false;

    Dino(int _team, int _index, int _level, int _health_boost, int _damage_boost, int _speed_boost, const DinoKind *_kind, int _rounds = 1);

    int Damage() const
    {
        return Round(damage * damage_factor);
    }
    int Speed() const
    {
        return Round(speed * speed_factor);
    }
    bool Prepare(int ability_id);
    void Attack(Dino *team[], int team_size);
    void CounterAttack(Dino *team[], int team_size);
    void Impose(const modifiers::Modifier *mod, Dino &author);
    void Dispose(int type_flags, Dino &author);
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
    bool Taunt() const
    {
        return taunt;
    }
    void DevourHeal();
    void DamageOverTime(Dino *team[], int team_size);
    std::string Name() const;
    void Revive();
    double Shield() const
    {
        return *shield.begin();
    }
    double DodgeChance() const
    {
        return dodge.begin()->first;
    }
    double DodgeFactor() const
    {
        return dodge.begin()->second;
    }
    void Hit(int damage);
    void Heal(int heal);
};

#endif // __JWA_CALC__DINO__H__

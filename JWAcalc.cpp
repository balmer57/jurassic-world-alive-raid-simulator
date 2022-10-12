#include <cstdio>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <list>
#include <ctime>

#include "dino.h"
#include "actions.h"
#include "modifiers.h"
#include "logger.h"
#include "dinodex.h"

using namespace std;


bool SpeedCmp(const Dino &dino1, const Dino &dino2) {
    if (dino1.stun < dino2.stun)
        return true;
    if (dino1.stun > dino2.stun)
        return false;
    if (dino1.priority > dino2.priority)
        return true;
    if (dino1.priority < dino2.priority)
        return false;
    if (dino1.Speed() > dino2.Speed())
        return true;
    if (dino1.Speed() < dino2.Speed())
        return false;
    if (dino1.level > dino2.level)
        return true;
    if (dino1.level < dino2.level)
        return false;
    if (dino1.kind->rarity > dino2.kind->rarity)
        return true;
    if (dino1.kind->rarity < dino2.kind->rarity)
        return false;
    if (dino1.index < dino2.index)
        return true;
//    if (dino1.index > dino2.index)
//        return false;
    return false;
}

int Step(Dino team[], int team_size)
{
    int i;
    Dino *boss = team;
    Dino *dino[team_size];
    for (i = 0; i < team_size; ++i)
        dino[i] = &team[i];
    for (i = 0; i < team_size; ++i) {
        if (team[i].Alive())
            team[i].DevourHeal();
    }
    for (int j = 0; j < team_size; ++j) {
        sort(dino + j, dino + team_size, [](const Dino *dino1, const Dino *dino2) { return SpeedCmp(*dino1, *dino2); });
        if (!dino[j]->Alive())
            continue;
        dino[j]->Attack(team, team_size);
        for (i = 0; i < team_size; ++i) {
            team[i].CounterAttack(team, team_size);
        }
        for (i = 0; i < team_size; ++i) {
            if (team[i].team == 0)
                continue;
            if (team[i].Alive())
                break;
        }
        if (i == team_size)
            return -1;
        if (!boss->Alive())
            return 1;
    }
    for (i = 0; i < team_size; ++i) {
        if (team[i].Alive())
            team[i].DamageOverTime(team, team_size);
    }
    for (i = 0; i < team_size; ++i) {
        if (team[i].team == 0)
            continue;
        if (team[i].Alive())
            break;
    }
    if (i == team_size)
        return -1;
    if (!boss->Alive())
        return 1;
    for (i = 0; i < team_size; ++i) {
        team[i].PassTurn();
    }
    if (boss->health == 0) {
        ++boss->round;
        for (i = 0; i < team_size; ++i) {
            if (team[i].team != 0)
                continue;
            team[i].Revive();
            if (i != 0)
                actions::Remove(ALL_EFFECTS).Do(team[i], team[i]);
            else
                actions::Remove(REVENGE).Do(team[i], team[i]);
        }
    }
    return 0;
}

bool Check(Dino team[], int team_size, const vector<int> ability[], int n_turns)
{
    int round = 0, turn = 0;
    Dino *boss = team;
    for (int t = 0; t < n_turns; ++t) {
        if (round < boss->round + 1) {
            ++round;
            turn = 0;
            LOG("Round %d\n", round);
        }
        boss->Prepare(turn++ % (int)boss->kind[boss->round].ability.size());
        LOG("Turn %d\n", turn);
        for (int i = 1; i < team_size; ++i) {
            if (!team[i].Alive())
                continue;
            if (team[i].team == 1) { // Teammates
                if (!team[i].Prepare(ability[i-1][t]-1)) {
                    LOG("%s Can't use %s because of cooldown\n", team[i].Name().c_str(), team[i].kind[team[i].round].ability[ability[t][i]]->name.c_str());
                    return false;
                }
            } else { // Minions
                while (!team[i].Prepare(rand() % team[i].kind->ability.size()))
                    ;
            }
        }

        int result = Step(team, team_size);
        if (result == 0)
            continue;
        if (result == 1)
            LOG("Win!\n");
        else
            LOG("Defeat!\n");
        return result == 1;
    }
    LOG("You are out of turns!\n");
    return false;
}

int Chance(Dino team0[], int team_size, const vector<int> ability[], int n_turns)
{
    int result = 0;
    auto log = Logger::on;
    Logger::on = false;
    for (int i = 0; i < 100; ++i) {
        vector<Dino> team(team0, team0 + team_size);
        if (Check(team.data(), team_size, ability, n_turns))
            ++result;
    }
    Logger::on = log;
    return result;
}

int main()
{
    srand((unsigned)time(NULL));
    setbuf(stdout, NULL);
    Logger::on = true;

//    vector<int> ability[] = {
//        {2, 1},
//        {2, 1},
//        {3, 2},
//        {3, 2},
//    };
//    int n_turns = (int)ability[0].size();
//
//    Dino team[] = {
//        MeiolaniaBoss,
//        Dino(1, 1, 10, 0, 0, 0, &Irritator),
//        Dino(1, 2, 10, 0, 0, 0, &Irritator),
//        Dino(1, 3, 10, 0, 0, 0, &Albertosaurus),
//        Dino(1, 4, 10, 0, 0, 0, &Albertosaurus)
//    };
//    int team_size = sizeof(team) / sizeof(*team);

//    vector<int> ability[] = {
//        {2, 4, 1, 2, 1},
//        {2, 3, 4, 2, 4},
//        {3, 2, 4, 3, 4},
//        {1, 3, 4, 1, 3},
//    };
//    int n_turns = (int)ability[0].size();
//
//    Dino team[] = {
//        FukuimimusBoss,
//        Dino(1, 1, 20, 0, 0, 0, &Skoolasaurus),
//        Dino(1, 2, 20, 0, 0, 0, &Thylaconyx),
//        Dino(1, 3, 20, 0, 0, 0, &Rexy),
//        Dino(1, 4, 20, 0, 0, 0, &Rexy),
//        Dino(0, 5, 18, 9, 5, 3, &GroupShatteringMinion),
//        Dino(0, 6, 18, 7, 5, 6, &DecelerationMinion),
//    };
//    int team_size = sizeof(team) / sizeof(*team);

//    vector<int> ability[] = {
//        {2, 1, 3},
//        {4, 3, 4},
//        {4, 3, 4},
//        {2, 4, 2},
//    };
//    int n_turns = (int)ability[0].size();
//
//    Dino team[] = {
//        BrachiosaurusBoss,
//        Dino(1, 1, 11, 0, 0, 0, &Irritator),
//        Dino(1, 2, 11, 0, 0, 0, &Andrewtherium),
//        Dino(1, 3, 11, 0, 0, 0, &Andrewtherium),
//        Dino(1, 4, 11, 0, 0, 0, &Andrewtodon),
//    };
//    int team_size = sizeof(team) / sizeof(*team);

//    vector<int> ability[] = {
//        {2, 4, 3, 2},
//        {3, 2, 4, 3},
//        {3, 2, 4, 3},
//        {4, 2, 3, 4},
//    };
//    int n_turns = (int)ability[0].size();
//
//    Dino team[] = {
//        TroodoboaBoss,
//        Dino(1, 1, 20, 0, 0, 0, &Thylaconyx),
//        Dino(1, 2, 20, 0, 0, 0, &Rexy),
//        Dino(1, 3, 20, 0, 0, 0, &Rexy),
//        Dino(1, 4, 21, 0, 0, 0, &Allodrigues),
//        Dino(0, 5, 24, 4, 10, 10, &ShatteringMinion),
//        Dino(0, 6, 24, 10, 4, 10, &NullifyingMinion),
//    };
//    int team_size = sizeof(team) / sizeof(*team);

    vector<int> ability[] = {
        {1, 3, 2, 4},
        {2, 3, 4, 2},
        {3, 4, 2, 3},
        {1, 4, 3, 4},
    };
    int n_turns = (int)ability[0].size();

    Dino team[] = {
        GlyptocerasBoss,
        Dino(1, 1, 20, 0, 0, 0, &Thylaconyx),
        Dino(1, 2, 20, 0, 0, 0, &Thylaconyx),
        Dino(1, 3, 20, 0, 0, 0, &Rexy),
        Dino(1, 4, 20, 0, 0, 0, &Rexy),
        Dino(0, 5, 17, 7, 6, 1, &NullifyingMinion),
        Dino(0, 6, 17, 8, 3, 3, &DecelerationMinion),
    };
    int team_size = sizeof(team) / sizeof(*team);

    //Check(team, team_size, ability, n_turns);
    int chance = Chance(team, team_size, ability, n_turns);
    LOG("Chance: %d%%\n", chance);
    return 0;
}

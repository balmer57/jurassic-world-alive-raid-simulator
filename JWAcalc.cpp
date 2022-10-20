#include <cstdio>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <list>
#include <ctime>
#include <cstring>

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
        boss->turn = 0;
        for (i = 0; i < team_size; ++i) {
            if (team[i].team != 0)
                continue;
            team[i].Revive();
            if (i != 0)
                actions::Remove(ALL_EFFECTS).Do(team[i], team[i]);
            else
                actions::Remove(REVENGE).Do(team[i], team[i]);
        }
    } else {
        ++boss->turn;
    }
    return 0;
}

bool Check(Dino team[], int team_size, const vector<int> ability[], int n_turns)
{
    int round = 0;
    Dino *boss = team;
    for (int t = 0; t < n_turns; ++t) {
        if (round < boss->round + 1) {
            ++round;
            ERROR("Round %d\n", round);
        }
        ERROR("Turn %d\n", boss->turn+1);
        for (int i = 0; i < team_size; ++i) {
            if (!team[i].Alive())
                continue;
            if (i == 0)
                boss->Prepare(boss->turn % (int)boss->kind->ability[boss->round].size());
            else if (team[i].team == 1) { // Teammates
                int ability_id = ability[i-1][t]-1;
                if (!team[i].Prepare(ability_id)) {
                    ERROR("%s Can't use %s because of cooldown\n", team[i].Name().c_str(), team[i].Ability(ability_id)->name.c_str());
                    return false;
                }
            } else { // Minions
                while (!team[i].Prepare(rand() % team[i].kind->ability[team[i].round].size()))
                    ;
            }
            WARNING("%s chose %s\n", team[i].Name().c_str(), team[i].Ability(team[i].ability_id)->name.c_str());
        }

        int result = Step(team, team_size);
        if (result == 0)
            continue;
        if (result == 1)
            ERROR("Win!\n");
        else
            ERROR("Defeat!\n");
        return result == 1;
    }
    ERROR("You are out of turns!\n");
    return false;
}

int Chance(Dino team0[], int team_size, const vector<int> ability[], int n_turns, int n_checks = 1000)
{
    int result = 0;
    auto log = Logger::level;
    Logger::level = 0;
    for (int i = 0; i < n_checks; ++i) {
        vector<Dino> team(team0, team0 + team_size);
        if (Check(team.data(), team_size, ability, n_turns))
            ++result;
    }
    Logger::level = log;
    return 100 * result / n_checks;
}

//int FindAll(Dino boss[], int boss_size, Dino team[], int team_size, int max_turns)
//{
//    ;
//}
//
//int Find(Dino team[], int team_size, int max_turns, int turn = 0, int teammate_id = 0)
//{
//    if (teammate_id == 0) { // boss
//        Dino boss = *team;
//        team->Prepare(team->turn % (int)team->kind->ability[team->round].size());
//        int r = Find(team, team_size, max_turns, turn, teammate_id + 1);
//        *team = boss;
//        return r;
//    } else if (team[teammate_id] == 1) { // teammate
//        if (!team[teammate_id].Alive())
//            return Find(team, team_size, max_turns, turn, teammate_id + 1);
//        for (int i = 0; i < (int)team[teammate_id].kind->ability[team[teammate_id].round].size(); ++i) {
//            if (!team[teammate_id].Prepare(i))
//                continue;
//            int r = Find(
//        }
//    }
//}

int Input(vector<Dino> &team, vector<vector<int>> &ability)
{
    int team_size, n_turns;
    char boss[32];
    if (scanf("%s", boss) != 1)
        return 1;
    if (scanf("%d%d%d", &team_size, &n_turns, &Logger::level) != 3)
        return 1;
    auto boss_it = BossDex.find(boss);
    if (boss_it == BossDex.end()) {
        ERROR("Unable to find %s boss\n", boss);
        return 1;
    }
    team.push_back(boss_it->second[0]);
    for (int i = 0; i < team_size; ++i) {
        char dino[32];
        int level, health_boost, damage_boost, speed_boost;
        if (scanf("%s%d%d%d%d", dino, &level, &health_boost, &damage_boost, &speed_boost) != 5)
            return 1;
        auto dino_it = DinoDex.find(dino);
        if (dino_it == DinoDex.end()) {
            ERROR("Unable to find %s\n", dino);
            return 1;
        }
        team.push_back(Dino(1, i+1, level, health_boost, damage_boost, speed_boost, dino_it->second));
    }
    for (int i = 1; i < (int)boss_it->second.size(); ++i)
        team.push_back(boss_it->second[i]);
    for (int i = 0; i < team_size; ++i) {
        ability.emplace_back(n_turns);
        for (int j = 0; j < n_turns; ++j) {
            if (scanf("%d", &ability[i][j]) != 1)
                return 1;
        }
    }
    return 0;
}

int CheckInput()
{
    vector<vector<int>> ability;
    vector<Dino> team;
    if (Input(team, ability) != 0) {
        ERROR("Input error!\n");
        return 1;
    }
    Check(team.data(), (int)team.size(), ability.data(), (int)ability[0].size());
    return 0;
}

int ChanceInput()
{
    vector<vector<int>> ability;
    vector<Dino> team;
    Input(team, ability);
    int chance = Chance(team.data(), (int)team.size(), ability.data(), (int)ability[0].size());
    LOG("Chance: %d%%\n", chance);
    return 0;
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    setbuf(stdout, NULL);

    if (argc >= 2)
        freopen(argv[1], "r", stdin);

    char command[32];
    scanf("%s", command);
    if (strcasecmp(command, "check") == 0)
        return CheckInput();
    else if(strcasecmp(command, "chance") == 0)
        return ChanceInput();
    else
        ERROR("Unknown command \"%s\"\n", command);
    return 0;
}

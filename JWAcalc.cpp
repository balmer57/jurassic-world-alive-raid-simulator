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
#include <getopt.h>
#include <cctype>

#include "dino.h"
#include "actions.h"
#include "modifiers.h"
#include "logger.h"
#include "dex.h"

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
    for (int j = 0; j < team_size; ++j) {
        for (i = team_size - 1; i - 1 >= j; --i) { // Oh, yeah, this is bubble sort :)
            if (SpeedCmp(*dino[i], *dino[i-1]))
                swap(dino[i-1], dino[i]);
        }
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
        if (team[i].Alive())
            team[i].DevourHeal();
    }
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

std::string GetLine()
{
    std::string line;
    while(true) {
        int c = getchar();
        if (c == '\n')
            return line;
        line.push_back(c);
    }
}

int Input(int argc, char *argv[], vector<Dino> &team, vector<vector<int>> &ability)
{
    while (true) {
        static struct option long_options[] = {
            {"loglevel", required_argument, nullptr, 'l'},
            {0, 0, 0, 0}
        };
        int option_index;

        switch (getopt_long(argc, argv, "l:", long_options, &option_index)) {
        case -1:
            break;
        case 'l':
            if (sscanf(optarg, "%d", &Logger::level) != 1) {
                printf("--loglevel takes a number from 0 to 4\n");
                return -1;
            }
            continue;
        case '?':
            return -1;
        }
        break;
    }
    int team_size, n_turns;
    char end[2];
    char boss[32];
    team.clear();
    ability.clear();
    if (sscanf(GetLine().c_str(), "%s%1s", boss, end) != 1)
        return 1;
    auto boss_it = BossDex.find(boss);
    if (boss_it == BossDex.end()) {
        LOG("Unable to find %s boss\n", boss);
        return 1;
    }
    team.push_back(boss_it->second[0]);
    if (sscanf(GetLine().c_str(), "%d%d%1s", &team_size, &n_turns, end) != 2)
        return 2;
    for (int i = 0; i < team_size; ++i) {
        char dino[32];
        int level, health_boost, damage_boost, speed_boost;
        if (sscanf(GetLine().c_str(), "%s%d%d%d%d%1s", dino, &level, &health_boost, &damage_boost, &speed_boost, end) != 5)
            return 3+i;
        auto dino_it = DinoDex.find(dino);
        if (dino_it == DinoDex.end()) {
            LOG("Unable to find %s\n", dino);
            return 3+i;
        }
        team.push_back(Dino(1, i+1, level, health_boost, damage_boost, speed_boost, dino_it->second));
    }
    for (int i = 1; i < (int)boss_it->second.size(); ++i)
        team.push_back(boss_it->second[i]);
    for (int i = 0; i < team_size; ++i) {
        ability.emplace_back(n_turns);
        int offset = 0, n;
        auto line = GetLine();
        for (int j = 0; j < n_turns; ++j) {
            if (sscanf(line.c_str() + offset, "%d%n", &ability[i][j], &n) != 1)
                return 3+team_size+i;
            offset += n;
        }
        if (sscanf(line.c_str() + offset, "%1s", end) == 1)
            return 3+team_size+i;
    }
    return 0;
}

int CheckInput(int argc, char *argv[])
{
    vector<vector<int>> ability;
    vector<Dino> team;
    if (int line = Input(argc, argv, team, ability)) {
        LOG("Input error in line %d!\n", line);
        return -1;
    }
    Check(team.data(), (int)team.size(), ability.data(), (int)ability[0].size());
    return 0;
}

int ChanceInput(int argc, char *argv[])
{
    vector<vector<int>> ability;
    vector<Dino> team;
    if (int line = Input(argc, argv, team, ability)) {
        LOG("Input error in line %d!\n", line);
        return -1;
    }
    int chance = Chance(team.data(), (int)team.size(), ability.data(), (int)ability[0].size());
    LOG("Chance: %d%%\n", chance);
    return 0;
}

int Help()
{
    if (optarg != nullptr && (strcmp(optarg, "check") == 0 || strcmp(optarg, "chance") == 0)) {
        printf(R"--(Usage: JWAcalc --%s [file] --loglevel <loglevel>

Options:
        -l, --loglevel <loglevel>   Change the default log level to <loglevel>. It can be a number from 0 to 4.

Check a strategy from input or <file> if specified. The strategy has the following format:
        <boss_name>
        <n_teammates> <n_turns>
        <teammate_1_name> <teammate_1_level> <teammate_1_health_boost> <teammate_1_damage_boost> <teammate_1_speep_boost>
        ...
        <teammate_N_name> <teammate_N_level> <teammate_N_health_boost> <teammate_N_damage_boost> <teammate_N_speep_boost>
        <teammate_1_turn_1_move> ... <teammate_1_turn_M_move>
        ...
        <teammate_N_turn_1_move> ... <teammate_N_turn_M_move>
        )--", optarg);
    } else {
        printf(R"--(Usage: JWAcalc <options>

Options:
        -h, --help [command]    this help;
        --check [file]          check a strategy from input or <file> if specified;
        --chance [file]         calculate a chance of winning using a strategy from input or <file> if specified;
        -l, --list              print a list of available bosses and dinos.
        )--");
    }
    return 0;
}

int List()
{
    printf("Bossdex:\n");
    for (auto it = BossDex.begin(); it != BossDex.end(); ++it)
        printf("  %s\n", it->first.c_str());
    printf("\n");
    printf("Dinodex:\n");
    for (auto it = DinoDex.begin(); it != DinoDex.end(); ++it)
        printf("  %s\n", it->first.c_str());
    return 0;
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
#ifdef DEBUG
    setbuf(stdout, NULL);
#endif

    while (true) {
        static struct option long_options[] = {
            {"check", optional_argument, nullptr, 'c'},
            {"chance", optional_argument, nullptr, 'p'},
            {"help", optional_argument, nullptr, 'h'},
            {"list", no_argument, nullptr, 'l'},
            {0, 0, 0, 0}
        };
        int option_index;

        switch (getopt_long(argc, argv, "h::l", long_options, &option_index)) {
        case -1:
            return 0;
        case 'c':
            if(optarg == nullptr && argv[optind] != nullptr && argv[optind][0] != '-')
                optarg = argv[optind++];
            if (optarg)
                freopen(optarg, "r", stdin);
            return CheckInput(argc, argv);
        case 'p':
            if(optarg == nullptr && argv[optind] != nullptr && argv[optind][0] != '-')
                optarg = argv[optind++];
            if (optarg)
                freopen(optarg, "r", stdin);
            return ChanceInput(argc, argv);
        case '?':
        case 'h':
            if(optarg == nullptr && argv[optind] != nullptr && argv[optind][0] != '-')
                optarg = argv[optind++];
            return Help();
        case 'l':
            return List();
        }
    }
    return 0;
}

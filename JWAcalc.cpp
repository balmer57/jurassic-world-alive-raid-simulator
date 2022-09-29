#include <cstdio>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <string>
#include <list>

#include "dino.h"
#include "actions.h"
#include "modifiers.h"
#include "logger.h"
#include "dinodex.h"

using namespace std;


bool SpeedCmp(const Dino &dino1, const Dino &dino2) {
    return dino1.Speed() > dino2.Speed() || (dino1.Speed() == dino2.Speed() && dino1.index < dino2.index);
}

struct State
{
    Dino boss, teammate[4];
};

int Step(Dino boss[], int boss_size, Dino team[], int team_size, int ability[])
{
    int i;
    Dino *dino[] = {boss, &team[0], &team[1], &team[2], &team[3]};
    int dino_size = sizeof(dino) / sizeof(*dino);
    if (boss->health == 0) {
        Logger::Log("Round %d\n", boss->round + 1);
        boss->health = boss->kind[boss->round].health;
    }
    // TODO: devour heal
//        for (i = 0; i < (int)dino.size(); ++i) {
//            dino->DevourHeal();
//        }
    for (i = 0; i < dino_size; ++i) {
        dino[i]->Prepare(ability[i]);
    }

    for (int j = 0; j < dino_size; ++j) {
        sort(dino + j, dino + dino_size, [](const Dino *dino1, const Dino *dino2) { return SpeedCmp(*dino1, *dino2); });
        dino[j]->Attack(dino, dino_size);
        for (i = 0; i < team_size; ++i) {
            if (team[i].Alive())
                break;
        }
        if (i == team_size) {
            printf("Defeat!\n");
            return -1;
        }
        if (!boss->Alive()) {
            printf("Win!\n");
            return 1;
        }
    }
    // TODO: dot
//        for (i = 0; i < (int)dino.size(); ++i) {
//            dino->DoT();
//        }
    for (i = 0; i < team_size; ++i) {
        if (team[i].Alive())
            break;
    }
    if (i == team_size) {
        printf("Defeat!\n");
        return -1;
    }
    if (!boss->Alive()) {
        printf("Win!\n");
        return 1;
    }
    for (i = 0; i < dino_size; ++i) {
        dino[i]->PassTurn();
    }
    if (boss->health == 0)
        ++boss->round;
    return 0;
}

int main()
{
    setbuf(stdout, NULL);

    int ability[][5] = {
        {0, 1, 1, 2, 2},
        {0, 0, 0, 1, 1},
    };
    int n_turns = sizeof(ability) / sizeof(*ability);

    Dino boss(0, 0, MeiolaniaBoss, sizeof(MeiolaniaBoss) / sizeof(*MeiolaniaBoss));
    boss.health = 0;
    Dino team[] = {
        Dino(1, 1, &Irritator),
        Dino(1, 2, &Irritator),
        Dino(1, 3, &Albertosaurus),
        Dino(1, 4, &Albertosaurus)
    };
    int team_size = sizeof(team) / sizeof(*team);
    for (int turn = 0; turn < n_turns; ++turn) {
        int result = Step(&boss, 1, team, team_size, ability[turn]);
        if (result != 0)
            break;
    }
    return 0;
}

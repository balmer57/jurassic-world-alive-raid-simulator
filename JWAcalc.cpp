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

    DinoKind meiolania_boss[] = {
        DinoKind("Meiolania boss #1", 3973, 342, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
            new Ability(0, 0, false, {
                new ActionGroup(TARGET_ALL_OPPONENTS, {
                    new Attack(1, GROUP),
                    new ImposeVulnerability(50, 1, 2)
                })
            }),
            new Ability(0, 1, false, {
                new ActionGroup(TARGET_SELF, {
                    new Cleanse(REDUCED_DAMAGE)
                }),
                new ActionGroup(TARGET_FASTEST, {
                    new Remove(DODGE | CLOAK | INCRESED_SPEED),
                    new Attack(1.5),
                    new ImposeVulnerability(50, 2, 2)
                })
            }),
            new Ability(2, 1, false, {
                new ActionGroup(TARGET_HIGHEST_HP, {
                    new Attack(3, PRECISE)
                }),
                new ActionGroup(TARGET_SELF, {
                    new ImposeTaunt(1)
                })
            })
        }, nullptr),
        DinoKind("Meiolania boss #2", 3973, 342, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
            new Ability(0, 1, false, {
                new ActionGroup(TARGET_HIGHEST_HP, {
                    new Attack(1.5),
                    new ImposeVulnerability(50, 2, 2)
                })
            }),
            new Ability(0, 0, false, {
                new ActionGroup(TARGET_SELF, {
                    new Cleanse(REDUCED_DAMAGE)
                }),
                new ActionGroup(TARGET_ALL_OPPONENTS, {
                    new ReduceSpeed(50, 2),
                    new Attack(1, PRECISE),
                    new ImposeVulnerability(50, 2, 1)
                })
            }),
            new Ability(0, 0, false, {
                new ActionGroup(TARGET_ALL_OPPONENTS, {
                    new Attack(3, PRECISE)
                })
            })
        }, nullptr),
    };

    DinoKind irritator("Irritator", 2061, 458, 126, 0, 30, 0, 0, 0, 0, 100, 0, 0, 100, {
        new Ability(0, 0, false, {
            new ActionGroup(TARGET_LOWEST_HP, {
                new Remove(SHIELD | TAUNT),
                new Attack(1, BYPASS_ARMOR)
            })
        }),
        new Ability(0, 2, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(CRIT_CHANCE_REDUCTION | REDUCED_DAMAGE),
                new IncreaseCritChance(30, 4, 2),
                new IncreaseDamage(50, 4, 2)
            })
        }),
        new Ability(1, 2, true, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
                new IncreaseDamage(50, 2, 1)
            })
        })
    }, nullptr);

    DinoKind albertosaurus("Albertosaurus", 1992, 801, 106, 0, 30, 100, 50, 0, 0, 100, 0, 0, 25, {
        new Ability(0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(VULNERABILITY)
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new Remove(SHIELD | TAUNT),
                new Attack(1, BYPASS_ARMOR)
            })
        }),
        new Ability(1, 1, true, {
            new ActionGroup(TARGET_LOWEST_HP, {
                new Remove(SHIELD | TAUNT),
                new Attack(1.5, BYPASS_ARMOR)
            })
        }),
        new Ability(0, 1, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(VULNERABILITY)
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new Remove(SHIELD | TAUNT),
                new Attack(1.5, BYPASS_ARMOR)
            })
        })
    }, nullptr);

    int ability[][5] = {
        {0, 1, 1, 2, 2},
        {0, 0, 0, 1, 1},
    };
    int n_turns = sizeof(ability) / sizeof(*ability);

    Dino boss(0, 0, meiolania_boss, 2);
    boss.health = 0;
    Dino team[] = {
        Dino(1, 1, &irritator),
        Dino(1, 2, &irritator),
        Dino(1, 3, &albertosaurus),
        Dino(1, 4, &albertosaurus)
    };
    int team_size = sizeof(team) / sizeof(*team);
    for (int turn = 0; turn < n_turns; ++turn) {
        int result = Step(&boss, 1, team, team_size, ability[turn]);
        if (result != 0)
            break;
    }
    return 0;
}

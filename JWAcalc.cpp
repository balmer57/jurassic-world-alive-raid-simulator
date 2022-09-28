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

using namespace std;


bool SpeedCmp(const Dino &dino1, const Dino &dino2) {
    return dino1.Speed() < dino2.Speed() || (dino1.Speed() == dino2.Speed() && dino1.index < dino2.index);
}

struct State
{
    Dino boss, teammate[4];
};

int Step(Dino *dino[], int dino_size, int ability[])
{
    int i;
    Dino &boss = *dino[0];
    Dino *teammate[] = {dino[1], dino[2], dino[3], dino[4]};
    int teammate_size = 4;
    if (boss.health == 0) {
        printf("Round %d\n", boss.round + 1);
        boss.health = boss.kind[boss.round].health;
    }
    // TODO: devour heal
//        for (i = 0; i < (int)dino.size(); ++i) {
//            dino->DevourHeal();
//        }
    for (i = 0; i < dino_size; ++i) {
        dino[i]->Prepare(ability[i]);
    }

    for (int size = dino_size; dino_size > 0; --dino_size) {
        sort(dino, dino + size, [](const Dino *dino1, const Dino *dino2) { return SpeedCmp(*dino1, *dino2); });
        Dino &curr_dino = *dino[size-1];
        curr_dino.Attack(dino, dino_size);
        if (!boss.Alive()) {
            printf("Win!\n");
            return 1;
        }
        for (i = 0; i < teammate_size; ++i) {
            if (teammate[i]->Alive())
                break;
        }
        if (i == teammate_size) {
            printf("Defeat!\n");
            return -1;
        }
    }
    // TODO: dot
//        for (i = 0; i < (int)dino.size(); ++i) {
//            dino->DoT();
//        }
    if (!boss.Alive()) {
        printf("Win!\n");
        return 1;
    }
    for (i = 0; i < teammate_size; ++i) {
        if (teammate[i]->Alive())
            break;
    }
    if (i == teammate_size) {
        printf("Defeat!\n");
        return -1;
    }
    for (i = 0; i < dino_size; ++i) {
        for (auto mod_it = dino[i]->mods.begin(); mod_it != dino[i]->mods.end(); ) {
            if (mod_it->duration == 0)
                dino[i]->mods.erase(mod_it++);
            else
                --mod_it++->duration;
        }
    }
    if (boss.health == 0)
        ++boss.round;
    return 0;
}

int main()
{
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
                    new CleanseReducedDamage()
                }),
                new ActionGroup(TARGET_FASTEST, {
                    new RemoveDodge(),
                    new RemoveCloak(),
                    new RemoveIncresedSpeed(),
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
                    new CleanseReducedDamage()
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
                new BreakShields(),
                new RemoveTaunt(),
                new Attack(1, BYPASS_ARMOR)
            })
        }),
        new Ability(0, 2, false, {
            new ActionGroup(TARGET_TEAM, {
                new CleanseCritChanceReduction(),
                new CleanseReducedDamage(),
                new IncreaseCritChance(30, 4, 2),
                new IncreaseDamage(50, 4, 2)
            })
        }),
        new Ability(1, 2, true, {
            new ActionGroup(TARGET_TEAM, {
                new CleanseReducedDamage(),
                new CleanseCritChanceReduction(),
                new IncreaseDamage(50, 2, 1)
            })
        })
    }, nullptr);

    DinoKind albertosaurus("Albertosaurus", 1992, 801, 106, 0, 30, 100, 50, 0, 0, 100, 0, 0, 25, {
        new Ability(0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new CleanseVulnerable()
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new BreakShields(),
                new RemoveTaunt(),
                new Attack(1, BYPASS_ARMOR)
            })
        }),
        new Ability(1, 1, true, {
            new ActionGroup(TARGET_LOWEST_HP, {
                new BreakShields(),
                new RemoveTaunt(),
                new Attack(1.5, BYPASS_ARMOR)
            })
        }),
        new Ability(0, 1, false, {
            new ActionGroup(TARGET_SELF, {
                new CleanseVulnerable()
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new BreakShields(),
                new RemoveTaunt(),
                new Attack(1.5, BYPASS_ARMOR)
            })
        })
    }, nullptr);

    int ability[][5] = {
        {0, 1, 1, 2, 2},
        {0, 0, 0, 1, 1},
    };

    Dino boss(0, 0, meiolania_boss, 2);
    boss.health = 0;
    Dino teammate[] = {
        Dino(1, 1, &irritator),
        Dino(1, 2, &irritator),
        Dino(1, 3, &albertosaurus),
        Dino(1, 4, &albertosaurus)
    };
    //int teammate_size = sizeof(teammate) / sizeof(*teammate);
    Dino *dino[] = {&boss, &teammate[0], &teammate[1], &teammate[2], &teammate[3]};
    int dino_size = sizeof(dino) / sizeof(*dino);
    for (int turn = 0; turn < 10; ++turn) {
        int result = Step(dino, dino_size, ability[turn]);
        if (result != 0)
            break;
    }
    return 0;
}

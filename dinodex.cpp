#include "dinodex.h"
#include "actions.h"
#include "modifiers.h"

using namespace actions;

#define DECLARE_BOSS(name, level, health_boost, damage_boost, speed_boost) Dino name(0, 0, level, health_boost, damage_boost, speed_boost, name##Kind, sizeof(name##Kind) / sizeof(*name##Kind))

//
// boss dex
//

DinoKind MeiolaniaBossKind[] = {
    DinoKind("Meiolania boss #1", RARE, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
        new Ability("Steady Group Vulnerability Strike", 0, 0, false, {
            ActionGroup(TARGET_ALL_OPPONENTS,
                Attack(1, GROUP),
                ImposeVulnerability(50, 1, 2)
            )
        }),
        new Ability("Resilient Impact", 0, 1, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(REDUCED_DAMAGE)
            ),
            ActionGroup(TARGET_FASTEST,
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Devastation", 2, 1, false, {
            ActionGroup(TARGET_HIGHEST_HP,
                Attack(3, PRECISE)
            ),
            ActionGroup(TARGET_SELF,
                Taunt(1)
            )
        })
    }, nullptr),
    DinoKind("Meiolania boss #2", RARE, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
        new Ability("Vulnerability Impact", 0, 1, false, {
            ActionGroup(TARGET_HIGHEST_HP,
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Group Superior Vulnerability", 0, 0, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(REDUCED_DAMAGE)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceSpeed(50, 2),
                Attack(1, PRECISE|GROUP),
                ImposeVulnerability(50, 2, 1)
            )
        }),
        new Ability("Group Devastation", 0, 0, false, {
            ActionGroup(TARGET_ALL_OPPONENTS,
                Attack(3, PRECISE|GROUP)
            )
        })
    }, nullptr),
};

DECLARE_BOSS(MeiolaniaBoss, 8, 0, 0, 0);

DinoKind FukuimimusBossKind[] = {
    DinoKind("Fukuimimus boss #1", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_SELF,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_TEAM,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            ActionGroup(TARGET_SELF,
                Taunt(2)
            )
        })),
        new Ability("Protective Strike", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(NEGATIVE_EFFECTS),
                IncreaseSpeed(10, 2)
            ),
            ActionGroup(TARGET_LOWEST_HP_TEAMMATE,
                Heal(2.)
            ),
            ActionGroup(TARGET_LOWEST_HP,
                Attack(1.)
            )
        }),
        new Ability("Random Cunning Rampage", 0, 0, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(DAMAGE_OVER_TIME)
            ),
            ActionGroup(TARGET_RANDOM,
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                ReduceCritChance(100, 1, 2),
                ReduceDamage(50, 1, 2),
                Attack(2.)
            )
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            IncreaseDamage(5, 3, 3)
        ),
        ActionGroup(TARGET_TEAM,
            IncreaseDamage(5, 3, 3)
        )
    })),
    DinoKind("Fukuimimus boss #2", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_SELF,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_TEAM,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            ActionGroup(TARGET_SELF,
                Taunt(2)
            )
        })),
        new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(DAMAGE_OVER_TIME)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(DAMAGE_OVER_TIME)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        })),
        new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_RANDOM,
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2., GROUP),
                ImposeVulnerability(50, 2, 2)
            )
        }))
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            IncreaseDamage(5, 3, 3)
        ),
        ActionGroup(TARGET_TEAM,
            IncreaseDamage(5, 3, 3)
        )
    })),
    DinoKind("Fukuimimus boss #3", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_SELF,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            ActionGroup(TARGET_SELF,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                ReduceDamage(50, 2, 4)
            ),
            ActionGroup(TARGET_TEAM,
                Dodge(100, 200./3, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            ActionGroup(TARGET_SELF,
                Taunt(2)
            )
        })),
        new Ability("Protective Strike", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(NEGATIVE_EFFECTS),
                IncreaseSpeed(10, 2)
            ),
            ActionGroup(TARGET_LOWEST_HP_TEAMMATE,
                Heal(2.)
            ),
            ActionGroup(TARGET_LOWEST_HP,
                Attack(1.)
            )
        }),
        new Ability("Revenge Cunning Impact", 0, 0, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(DAMAGE_OVER_TIME)
            ),
            ActionGroup(TARGET_RANDOM,
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(1.5)
            ),
            ActionGroup(TARGET_SELF,
                Dodge(75, 200./3, 2, 4),
                Taunt(2)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Revenge Cunning Impact", 0, 0, false, {
            ActionGroup(TARGET_TEAM,
                Cleanse(NEGATIVE_EFFECTS)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                Remove(SHIELD),
                Attack(1.5, BYPASS_ARMOR|GROUP)
            ),
            ActionGroup(TARGET_SELF,
                Dodge(75, 200./3, 3, 4),
                Taunt(2)
            )
        })),
        new Ability("Determined Group Rampage", 0, 0, false, {
            ActionGroup(TARGET_SELF,
                Cleanse(REDUCED_DAMAGE | DAMAGE_OVER_TIME)
            ),
            ActionGroup(TARGET_ALL_OPPONENTS,
                Remove(INCREASED_SPEED | INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., PRECISE|GROUP),
                ImposeVulnerability(50, 2, 1),
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2)
            )
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            IncreaseDamage(5, 3, 3)
        ),
        ActionGroup(TARGET_TEAM,
            IncreaseDamage(5, 3, 3)
        )
    }))
};

DECLARE_BOSS(FukuimimusBoss, 19, 7, 7, 5);

//
// minion dex
//

DinoKind GroupShatteringMinion("Group Shattering Minion", RARE, 3600, 1000, 122, 0, 30, 0, 0, 0, 0, 0, 100, 0, 0, {
    new Ability("Group Defense Shattering Strike", 0, 0, false, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(SHIELD),
            Attack(1., BYPASS_ARMOR|GROUP)
       )
    }),
    new Ability("Group Ferocity", 0, 2, true, {
        ActionGroup(TARGET_TEAM,
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            IncreaseDamage(50, 2, 2)
        )
    }),
    new Ability("Group Shattering Impact", 0, 0, false, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR|GROUP)
        )
    })
}, nullptr);

DinoKind DecelerationMinion("Deceleration Minion", COMMON, 4050, 1000, 112, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Shielded Decelerating Strike", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            Shield(50, 1, 4)
        ),
        ActionGroup(TARGET_LOWEST_HP,
            ReduceSpeed(50, 2),
            Attack(1., PRECISE)
        )
    }),
    new Ability("Group Decelerating Strike", 0, 2, false, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            ReduceSpeed(50, 2),
            Attack(1., GROUP)
        )
    })
}, new Ability("Decelerating Counter", 0, 0, false, {
    ActionGroup(TARGET_ATTACKER,
        ReduceSpeed(50, 1),
        Attack(1.)
    )
}));

//
// dino dex
//

DinoKind Albertosaurus("Albertosaurus", RARE, 4350, 1750, 106, 0, 30, 100, 50, 0, 0, 100, 0, 0, 25, {
    new Ability("Fierce Strike", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        ),
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1, BYPASS_ARMOR)
        )
    }),
    new Ability("Killer Instinct", 1, 1, true, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    }),
    new Ability("Fierce Impact", 0, 1, false, {
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        ),
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind Irritator("Irritator", RARE, 4500, 1000, 126, 0, 30, 0, 0, 0, 0, 100, 0, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1, BYPASS_ARMOR)
        )
    }),
    new Ability("Ready To Crush", 0, 2, false, {
        ActionGroup(TARGET_TEAM,
            Cleanse(CRIT_CHANCE_REDUCTION | REDUCED_DAMAGE),
            IncreaseCritChance(30, 4, 2),
            IncreaseDamage(50, 4, 2)
        )
    }),
    new Ability("Group Takedown", 1, 2, true, {
        ActionGroup(TARGET_TEAM,
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            IncreaseDamage(50, 2, 1)
        )
    })
}, nullptr);

DinoKind Rexy("Rexy", LEGENDARY, 4950, 1850, 106, 0, 45, 0, 75, 0, 75, 100, 75, 0, 100, {
    new Ability("Alert Fierce Strike", 0, 0, false, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR|GROUP)
        ),
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        )
    }, [](Dino &self) { return self.health <= self.max_health * 0.5; }, new Ability("Alert Fierce Strike", 0, 0, false, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        ),
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        )
    })),
    new Ability("Defense Shattering Revenge", 0, 1, false, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        ),
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        )
    }, [](Dino &self) { return self.revenge; }, new Ability("Defense Shattering Revenge", 0, 1, false, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR|GROUP)
        ),
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        )
    })),
    new Ability("Dominant Roar", 0, 2, true, {
        ActionGroup(TARGET_TEAM,
            IncreaseDamage(50, 2, 2)
        ),
        ActionGroup(TARGET_ALL_OPPONENTS,
            Attack(1., GROUP)
        ),
        ActionGroup(TARGET_TEAM,
            IncreaseSpeed(25, 1)
        )
    }),
    new Ability("Fierce Devouring Rampage", 1, 1, false, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(2., BYPASS_ARMOR)
        ),
        ActionGroup(TARGET_SELF,
            DevourHeal(60, 4),
            Cleanse(VULNERABILITY)
        )
    })
}, nullptr);

DinoKind Skoolasaurus("Skoolasaurus", LEGENDARY, 4500, 1000, 124, 30, 5, 0, 0, 0, 0, 100, 75, 0, 50, {
    new Ability("Resilient Strike", 0, 0, false, {
        ActionGroup(TARGET_SELF,
            Cleanse(REDUCED_DAMAGE)
        ),
        ActionGroup(TARGET_LOWEST_HP,
            Remove(DODGE | CLOAK | INCREASED_SPEED),
            Attack(1.),
            ImposeVulnerability(50, 2, 2)
        )
    }),
    new Ability("Tip The Scales", 0, 1, true, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(POSITIVE_EFFECTS)
        ),
        ActionGroup(TARGET_TEAM,
            Cleanse(NEGATIVE_EFFECTS)
        )
    }),
    new Ability("Group Distraction", 0, 2, true, {
        ActionGroup(TARGET_ALL_OPPONENTS,
            ReduceDamage(50, 2, 3)
        )
    }),
    new Ability("Group Taunting Shields Strike", 0, 1, false, {
        ActionGroup(TARGET_TEAM,
            Shield(50, 2, 2)
        ),
        ActionGroup(TARGET_SELF,
            Taunt(1)
        ),
        ActionGroup(TARGET_LOWEST_HP,
            Attack(1.)
        )
    })
}, nullptr);

DinoKind Thylaconyx("Thylaconyx", LEGENDARY, 4800, 1250, 122, 0, 25, 0, 25, 0, 75, 100, 100, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        ActionGroup(TARGET_LOWEST_HP,
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Crushing Prowl", 0, 2, true, {
        ActionGroup(TARGET_SELF,
            Cleanse(NEGATIVE_EFFECTS),
            IncreaseCritChance(75, 2, 2),
            Dodge(75, 200./3, 1, 2)
        ),
        ActionGroup(TARGET_TEAM,
            IncreaseDamage(50, 4, 2),
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION)
        )
    }),
    new Ability("Devouring Wound", 0, 1, false, {
        ActionGroup(TARGET_HIGHEST_HP,
            Remove(SHIELD),
            Attack(1.5, BYPASS_ARMOR),
            DamageOverTime(20, 2)
        ),
        ActionGroup(TARGET_SELF,
            DevourHeal(60, 4)
        ),
    }),
    new Ability("Skirmish", 1, 1, false, {
        ActionGroup(TARGET_SELF,
            Cleanse(VULNERABILITY)
        ),
        ActionGroup(TARGET_ALL_OPPONENTS,
            Remove(SHIELD | TAUNT),
            Attack(2., BYPASS_ARMOR|GROUP)
        )
    })
}, new Ability("Defense Shattering Counter-Attack", 0, 0, false, {
    ActionGroup(TARGET_ATTACKER,
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    )
}));

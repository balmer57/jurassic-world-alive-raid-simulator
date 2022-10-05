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
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new Attack(1, GROUP),
                new ImposeVulnerability(50, 1, 2)
            })
        }),
        new Ability("Resilient Impact", 0, 1, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(REDUCED_DAMAGE)
            }),
            new ActionGroup(TARGET_FASTEST, {
                new Remove(DODGE | CLOAK | INCREASED_SPEED),
                new Attack(1.5),
                new ImposeVulnerability(50, 2, 2)
            })
        }),
        new Ability("Devastation", 2, 1, false, {
            new ActionGroup(TARGET_HIGHEST_HP, {
                new Attack(3, PRECISE)
            }),
            new ActionGroup(TARGET_SELF, {
                new Taunt(1)
            })
        })
    }, nullptr),
    DinoKind("Meiolania boss #2", RARE, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
        new Ability("Vulnerability Impact", 0, 1, false, {
            new ActionGroup(TARGET_HIGHEST_HP, {
                new Attack(1.5),
                new ImposeVulnerability(50, 2, 2)
            })
        }),
        new Ability("Group Superior Vulnerability", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(REDUCED_DAMAGE)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceSpeed(50, 2),
                new Attack(1, PRECISE|GROUP),
                new ImposeVulnerability(50, 2, 1)
            })
        }),
        new Ability("Group Devastation", 0, 0, false, {
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new Attack(3, PRECISE|GROUP)
            })
        })
    }, nullptr),
};

DECLARE_BOSS(MeiolaniaBoss, 8, 0, 0, 0);

DinoKind FukuimimusBossKind[] = {
    DinoKind("Fukuimimus boss #1", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_SELF, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2),
                new Taunt(2)
            })
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_TEAM, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2)
            }),
            new ActionGroup(TARGET_SELF, {
                new Taunt(2)
            })
        })),
        new Ability("Protective Strike", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(NEGATIVE_EFFECTS),
                new IncreaseSpeed(10, 2)
            }),
            new ActionGroup(TARGET_LOWEST_HP_TEAMMATE, {
                new Heal(2.)
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new Attack(1.)
            })
        }),
        new Ability("Random Cunning Rampage", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(DAMAGE_OVER_TIME)
            }),
            new ActionGroup(TARGET_RANDOM, {
                new Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                new ReduceCritChance(100, 1, 2),
                new ReduceDamage(50, 1, 2),
                new Attack(2.)
            })
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        new ActionGroup(TARGET_SELF, {
            new IncreaseDamage(5, 3, 3)
        }),
        new ActionGroup(TARGET_TEAM, {
            new IncreaseDamage(5, 3, 3)
        })
    })),
    DinoKind("Fukuimimus boss #2", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_SELF, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2),
                new Taunt(2)
            })
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_TEAM, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2)
            }),
            new ActionGroup(TARGET_SELF, {
                new Taunt(2)
            })
        })),
        new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(DAMAGE_OVER_TIME)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 1, 2),
                new ReduceCritChance(100, 1, 2),
                new Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                new Attack(2., GROUP)
            })
        }, [](Dino &self) { return self.revenge; }, new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(DAMAGE_OVER_TIME)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 1, 2),
                new ReduceCritChance(100, 1, 2),
                new Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                new Attack(2., GROUP)
            })
        })),
        new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_RANDOM, {
                new Remove(DODGE | CLOAK | INCREASED_SPEED),
                new Attack(2.),
                new ImposeVulnerability(50, 2, 2)
            })
        }, [](Dino &self) { return self.revenge; }, new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new Remove(DODGE | CLOAK | INCREASED_SPEED),
                new Attack(2., GROUP),
                new ImposeVulnerability(50, 2, 2)
            })
        }))
    }, new Ability("Ferocious Feathers", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new IncreaseDamage(5, 3, 3)
            }),
            new ActionGroup(TARGET_TEAM, {
                new IncreaseDamage(5, 3, 3)
            })
    })),
    DinoKind("Fukuimimus boss #3", LEGENDARY, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_SELF, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2),
                new Taunt(2)
            })
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new ReduceDamage(50, 2, 4)
            }),
            new ActionGroup(TARGET_TEAM, {
                new Dodge(100, 200./3, 1, 4),
                new IncreaseSpeed(10, 2)
            }),
            new ActionGroup(TARGET_SELF, {
                new Taunt(2)
            })
        })),
        new Ability("Protective Strike", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(NEGATIVE_EFFECTS),
                new IncreaseSpeed(10, 2)
            }),
            new ActionGroup(TARGET_LOWEST_HP_TEAMMATE, {
                new Heal(2.)
            }),
            new ActionGroup(TARGET_LOWEST_HP, {
                new Attack(1.)
            })
        }),
        new Ability("Revenge Cunning Impact", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(DAMAGE_OVER_TIME)
            }),
            new ActionGroup(TARGET_RANDOM, {
                new ReduceDamage(50, 1, 2),
                new ReduceCritChance(100, 1, 2),
                new Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                new Attack(1.5)
            }),
            new ActionGroup(TARGET_SELF, {
                new Dodge(75, 200./3, 2, 4),
                new Taunt(2)
            })
        }, [](Dino &self) { return self.revenge; }, new Ability("Revenge Cunning Impact", 0, 0, false, {
            new ActionGroup(TARGET_TEAM, {
                new Cleanse(NEGATIVE_EFFECTS)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new Remove(SHIELD),
                new Attack(1.5, BYPASS_ARMOR|GROUP)
            }),
            new ActionGroup(TARGET_SELF, {
                new Dodge(75, 200./3, 3, 4),
                new Taunt(2)
            })
        })),
        new Ability("Determined Group Rampage", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new Cleanse(REDUCED_DAMAGE | DAMAGE_OVER_TIME)
            }),
            new ActionGroup(TARGET_ALL_OPPONENTS, {
                new Remove(INCREASED_SPEED | INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                new Attack(2., PRECISE|GROUP),
                new ImposeVulnerability(50, 2, 1),
                new ReduceDamage(50, 1, 2),
                new ReduceCritChance(100, 1, 2)
            })
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
            new ActionGroup(TARGET_SELF, {
                new IncreaseDamage(5, 3, 3)
            }),
            new ActionGroup(TARGET_TEAM, {
                new IncreaseDamage(5, 3, 3)
            })
    }))
};

DECLARE_BOSS(FukuimimusBoss, 19, 7, 7, 5);

//
// minion dex
//

DinoKind GroupShatteringMinion("Group Shattering Minion", RARE, 3600, 1000, 122, 0, 30, 0, 0, 0, 0, 0, 100, 0, 0, {
    new Ability("Group Defense Shattering Strike", 0, 0, false, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(SHIELD),
            new Attack(1., BYPASS_ARMOR|GROUP)
        })
    }),
    new Ability("Group Ferocity", 0, 2, true, {
        new ActionGroup(TARGET_TEAM, {
            new Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            new IncreaseDamage(50, 2, 2)
        })
    }),
    new Ability("Group Shattering Impact", 0, 0, false, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(SHIELD | TAUNT),
            new Attack(1.5, BYPASS_ARMOR|GROUP)
        })
    })
}, nullptr);

DinoKind DecelerationMinion("Deceleration Minion", COMMON, 4050, 1000, 112, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Shielded Decelerating Strike", 0, 0, false, {
        new ActionGroup(TARGET_SELF, {
            new Shield(50, 1, 4)
        }),
        new ActionGroup(TARGET_LOWEST_HP, {
            new ReduceSpeed(50, 2),
            new Attack(1., PRECISE)
        })
    }),
    new Ability("Group Decelerating Strike", 0, 2, false, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new ReduceSpeed(50, 2),
            new Attack(1., GROUP)
        })
    })
}, new Ability("Decelerating Counter", 0, 0, false, {
    new ActionGroup(TARGET_ATTACKER, {
        new ReduceSpeed(50, 1),
        new Attack(1.)
    })
}));

//
// dino dex
//

DinoKind Albertosaurus("Albertosaurus", RARE, 4350, 1750, 106, 0, 30, 100, 50, 0, 0, 100, 0, 0, 25, {
    new Ability("Fierce Strike", 0, 0, false, {
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        }),
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1, BYPASS_ARMOR)
        })
    }),
    new Ability("Killer Instinct", 1, 1, true, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1.5, BYPASS_ARMOR)
        })
    }),
    new Ability("Fierce Impact", 0, 1, false, {
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        }),
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1.5, BYPASS_ARMOR)
        })
    })
}, nullptr);

DinoKind Irritator("Irritator", RARE, 4500, 1000, 126, 0, 30, 0, 0, 0, 0, 100, 0, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1, BYPASS_ARMOR)
        })
    }),
    new Ability("Ready To Crush", 0, 2, false, {
        new ActionGroup(TARGET_TEAM, {
            new Cleanse(CRIT_CHANCE_REDUCTION | REDUCED_DAMAGE),
            new IncreaseCritChance(30, 4, 2),
            new IncreaseDamage(50, 4, 2)
        })
    }),
    new Ability("Group Takedown", 1, 2, true, {
        new ActionGroup(TARGET_TEAM, {
            new Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            new IncreaseDamage(50, 2, 1)
        })
    })
}, nullptr);

DinoKind Rexy("Rexy", LEGENDARY, 4950, 1850, 106, 0, 45, 0, 75, 0, 75, 100, 75, 0, 100, {
    new Ability("Alert Fierce Strike", 0, 0, false, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(SHIELD | TAUNT),
            new Attack(1., BYPASS_ARMOR|GROUP)
        }),
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        })
    }, [](Dino &self) { return self.health <= self.max_health * 0.5; }, new Ability("Alert Fierce Strike", 0, 0, false, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1., BYPASS_ARMOR)
        }),
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        })
    })),
    new Ability("Defense Shattering Revenge", 0, 1, false, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1.5, BYPASS_ARMOR)
        }),
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        })
    }, [](Dino &self) { return self.revenge; }, new Ability("Defense Shattering Revenge", 0, 1, false, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(SHIELD | TAUNT),
            new Attack(1.5, BYPASS_ARMOR|GROUP)
        }),
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        })
    })),
    new Ability("Dominant Roar", 0, 2, true, {
        new ActionGroup(TARGET_TEAM, {
            new IncreaseDamage(50, 2, 2),
        }),
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Attack(1., GROUP)
        }),
        new ActionGroup(TARGET_TEAM, {
            new IncreaseSpeed(25, 1)
        })
    }),
    new Ability("Fierce Devouring Rampage", 1, 1, false, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(2., BYPASS_ARMOR)
        }),
        new ActionGroup(TARGET_SELF, {
            new DevourHeal(60, 4),
            new Cleanse(VULNERABILITY)
        })
    })
}, nullptr);

DinoKind Skoolasaurus("Skoolasaurus", LEGENDARY, 4500, 1000, 124, 30, 5, 0, 0, 0, 0, 100, 75, 0, 50, {
    new Ability("Resilient Strike", 0, 0, false, {
        new ActionGroup(TARGET_SELF, {
            new Cleanse(REDUCED_DAMAGE)
        }),
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(DODGE | CLOAK | INCREASED_SPEED),
            new Attack(1.),
            new ImposeVulnerability(50, 2, 2)
        })
    }),
    new Ability("Tip The Scales", 0, 1, true, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(POSITIVE_EFFECTS)
        }),
        new ActionGroup(TARGET_TEAM, {
            new Cleanse(NEGATIVE_EFFECTS)
        })
    }),
    new Ability("Group Distraction", 0, 2, true, {
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new ReduceDamage(50, 2, 3)
        })
    }),
    new Ability("Group Taunting Shields Strike", 0, 1, false, {
        new ActionGroup(TARGET_TEAM, {
            new Shield(50, 2, 2)
        }),
        new ActionGroup(TARGET_SELF, {
            new Taunt(1)
        }),
        new ActionGroup(TARGET_LOWEST_HP, {
            new Attack(1.)
        })
    })
}, nullptr);

DinoKind Thylaconyx("Thylaconyx", LEGENDARY, 4800, 1250, 122, 0, 25, 0, 25, 0, 75, 100, 100, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        new ActionGroup(TARGET_LOWEST_HP, {
            new Remove(SHIELD | TAUNT),
            new Attack(1., BYPASS_ARMOR)
        })
    }),
    new Ability("Crushing Prowl", 0, 2, true, {
        new ActionGroup(TARGET_SELF, {
            new Cleanse(NEGATIVE_EFFECTS),
            new IncreaseCritChance(75, 2, 2),
            new Dodge(75, 200./3, 1, 2)
        }),
        new ActionGroup(TARGET_TEAM, {
            new IncreaseDamage(50, 4, 2),
            new Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION)
        })
    }),
    new Ability("Devouring Wound", 0, 1, false, {
        new ActionGroup(TARGET_HIGHEST_HP, {
            new Remove(SHIELD),
            new Attack(1.5, BYPASS_ARMOR),
            new DamageOverTime(20, 2)
        }),
        new ActionGroup(TARGET_SELF, {
            new DevourHeal(60, 4)
        }),
    }),
    new Ability("Skirmish", 1, 1, false, {
        new ActionGroup(TARGET_SELF, {
            new Cleanse(VULNERABILITY)
        }),
        new ActionGroup(TARGET_ALL_OPPONENTS, {
            new Remove(SHIELD | TAUNT),
            new Attack(2., BYPASS_ARMOR|GROUP)
        })
    })
}, new Ability("Defense Shattering Counter-Attack", 0, 0, false, {
    new ActionGroup(TARGET_ATTACKER, {
        new Remove(SHIELD),
        new Attack(0.5, BYPASS_ARMOR)
    })
}));

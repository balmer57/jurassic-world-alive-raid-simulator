#include "dinodex.h"
#include "actions.h"
#include "modifiers.h"

using namespace actions;

#define DECLARE_BOSS(name, level, health_boost, damage_boost, speed_boost) Dino name(0, 0, level, health_boost, damage_boost, speed_boost, name##Kind, sizeof(name##Kind) / sizeof(*name##Kind))

//
// boss dex
//

DinoKind BrachiosaurusBossKind[] = {
    DinoKind("Brachiosaurus Boss #1", EPIC, 1, 24000, 1350, 109, 0, 15, 50, 85, 100, 80, 100, 100, 0, 50, {
        new Ability("Group Shield Strike", 0, 0, true, {
            TargetLowestHP(
                Attack(1.)
            ),
            TargetTeam(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Group Resilient Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Resilient Vulnerability Rampage", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        })
    }, nullptr),
    DinoKind("Brachiosaurus Boss #2", EPIC, 1, 24000, 1350, 109, 0, 15, 50, 85, 100, 80, 100, 100, 0, 50, {
        new Ability("Shielded Group Strike", 0, 0, true, {
            TargetAllOpponents(
                Attack(1.)
            ),
            TargetTeam(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Group Resilient Impact", 0, 0, true, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        })
    }, nullptr),
    DinoKind("Brachiosaurus Boss #3", EPIC, 1, 24000, 1350, 109, 0, 15, 50, 85, 100, 80, 100, 100, 0, 50, {
        new Ability("Group Shield Strike", 0, 0, true, {
            TargetLowestHP(
                Attack(1.)
            ),
            TargetTeam(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Boom", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 1)
            )
        }),
        new Ability("Shielded Resilient Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.),
                ImposeVulnerability(50, 2, 2)
            ),
            TargetSelf(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Resilient Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        })
    }, nullptr)
};

DECLARE_BOSS(BrachiosaurusBoss, 14, 0, 0, 0);

DinoKind MeiolaniaBossKind[] = {
    DinoKind("Meiolania boss #1", RARE, 1, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
        new Ability("Steady Group Vulnerability Strike", 0, 0, false, {
            TargetAllOpponents(
                Attack(1, GROUP),
                ImposeVulnerability(50, 1, 2)
            )
        }),
        new Ability("Resilient Impact", 0, 1, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Devastation", 2, 1, false, {
            TargetHighestHP(
                Attack(3, PRECISE)
            ),
            TargetSelf(
                Taunt(1)
            )
        })
    }, nullptr),
    DinoKind("Meiolania boss #2", RARE, 1, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
        new Ability("Vulnerability Impact", 0, 1, false, {
            TargetHighestHP(
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Group Superior Vulnerability", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                ReduceSpeed(50, 2),
                Attack(1, PRECISE|GROUP),
                ImposeVulnerability(50, 2, 1)
            )
        }),
        new Ability("Group Devastation", 0, 0, false, {
            TargetAllOpponents(
                Attack(3, PRECISE|GROUP)
            )
        })
    }, nullptr),
};

DECLARE_BOSS(MeiolaniaBoss, 8, 0, 0, 0);

DinoKind FukuimimusBossKind[] = {
    DinoKind("Fukuimimus boss #1", LEGENDARY, 1, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetSelf(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetTeam(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            TargetSelf(
                Taunt(2)
            )
        })),
        new Ability("Protective Strike", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS),
                IncreaseSpeed(10, 2)
            ),
            TargetLowestHPTeammate(
                Heal(2.)
            ),
            TargetLowestHP(
                Attack(1.)
            )
        }),
        new Ability("Random Cunning Rampage", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetRandom(
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                ReduceCritChance(100, 1, 2),
                ReduceDamage(50, 1, 2),
                Attack(2.)
            )
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        TargetSelf(
            IncreaseDamage(5, 3, 3)
        ),
        TargetTeam(
            IncreaseDamage(5, 3, 3)
        )
    })),
    DinoKind("Fukuimimus boss #2", LEGENDARY, 1, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetSelf(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetTeam(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            TargetSelf(
                Taunt(2)
            )
        })),
        new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Cunning Cleanse Revenge", 0, 0, false, {
            TargetTeam(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        })),
        new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetRandom(
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Resilient Cleanse Revenge", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2., GROUP),
                ImposeVulnerability(50, 2, 2)
            )
        }))
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        TargetSelf(
            IncreaseDamage(5, 3, 3)
        ),
        TargetTeam(
            IncreaseDamage(5, 3, 3)
        )
    })),
    DinoKind("Fukuimimus boss #3", LEGENDARY, 1, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
        new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetSelf(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2),
                Taunt(2)
            )
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, new Ability("Alert Mimic", 0, 0, true, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 2, 4)
            ),
            TargetTeam(
                Dodge(100, 67, 1, 4),
                IncreaseSpeed(10, 2)
            ),
            TargetSelf(
                Taunt(2)
            )
        })),
        new Ability("Protective Strike", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS),
                IncreaseSpeed(10, 2)
            ),
            TargetLowestHPTeammate(
                Heal(2.)
            ),
            TargetLowestHP(
                Attack(1.)
            )
        }),
        new Ability("Revenge Cunning Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetRandom(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(1.5)
            ),
            TargetSelf(
                Dodge(75, 67, 2, 4),
                Taunt(2)
            )
        }, [](Dino &self) { return self.revenge; }, new Ability("Revenge Cunning Impact", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                Remove(SHIELD),
                Attack(1.5, BYPASS_ARMOR|GROUP)
            ),
            TargetSelf(
                Dodge(75, 67, 3, 4),
                Taunt(2)
            )
        })),
        new Ability("Determined Group Rampage", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE | DAMAGE_OVER_TIME)
            ),
            TargetAllOpponents(
                Remove(INCREASED_SPEED | INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., PRECISE|GROUP),
                ImposeVulnerability(50, 2, 1),
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2)
            )
        })
    }, new Ability("Ferocious Feathers", 0, 0, false, {
        TargetSelf(
            IncreaseDamage(5, 3, 3)
        ),
        TargetTeam(
            IncreaseDamage(5, 3, 3)
        )
    }))
};

DECLARE_BOSS(FukuimimusBoss, 19, 7, 7, 5);

DinoKind TroodoboaBossKind[] = {
    DinoKind("Troodoboa Boss #1", UNIQUE, 1, 16666, 1300, 120, 0, 10, 0, 90, 60, 80, 75, 100, 100, 15, {
        new Ability("Instant Shielded Decelerating Strike", 0, 0, true, {
            TargetSelf(
                Shield(50, 1, 4)
            ),
            TargetHighestHP(
                Attack(1.),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Targeted Cleansing Strike", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetHighestDamage(
                Attack(1.)
            )
        }),
        new Ability("Group Ferocious Strike", 0, 0, false, {
            TargetTeam(
                IncreaseDamage(25, 2, 4)
            ),
            TargetHighestHP(
                Attack(1.)
            )
        })
    }, nullptr),
    DinoKind("Troodoboa Boss #2", UNIQUE, 1, 16666, 1300, 120, 0, 10, 0, 90, 60, 80, 75, 100, 100, 15, {
        new Ability("Instant Shielded Decelerating Strike", 0, 0, true, {
            TargetSelf(
                Shield(50, 1, 4)
            ),
            TargetHighestHP(
                Attack(1.),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Coiling Rampage", 0, 0, false, {
            TargetSelf(
                Shield(75, 3, 12)
            ),
            TargetAllOpponents(
                ReduceDamage(75, 2, 4)
            ),
            TargetHighestDamage(
                Attack(2.)
            )
        }),
        new Ability("Targeted Cleansing Impact", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetHighestDamage(
                Attack(1.5)
            )
        }),
        new Ability("Raking Piercing Strike", 0, 0, false, {
            TargetMostPositiveEffects(
                Remove(DODGE|CLOAK),
                Attack(1., BYPASS_ARMOR)
            )
        })
    }, nullptr),
    DinoKind("Troodoboa Boss #3", UNIQUE, 1, 16666, 1300, 120, 0, 10, 0, 90, 60, 80, 75, 100, 100, 15, {
        new Ability("Instant Shielded Decelerating Strike", 0, 0, true, {
            TargetSelf(
                Shield(50, 1, 4)
            ),
            TargetHighestHP(
                Attack(1.),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Coiling Rampage", 0, 0, false, {
            TargetSelf(
                Shield(75, 3, 12)
            ),
            TargetAllOpponents(
                ReduceDamage(75, 2, 4)
            ),
            TargetHighestDamage(
                Attack(2.)
            )
        }),
        new Ability("Targeted Cleansing Impact", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetHighestDamage(
                Attack(2.)
            )
        }),
        new Ability("Group Ferocious Impact", 0, 0, false, {
            TargetTeam(
                IncreaseDamage(50, 2, 4)
            ),
            TargetMostPositiveEffects(
                Remove(DODGE|CLOAK),
                Attack(1.5, BYPASS_ARMOR)
            )
        })
    }, nullptr)
};

DECLARE_BOSS(TroodoboaBoss, 25, 10, 10, 5);

DinoKind GlyptocerasBossKind[] = {
    DinoKind("Glyptoceras Boss #1", LEGENDARY, 1, 13000, 1350, 110, 15, 15, 25, 80, 75, 70, 50, 95, 0, 25, {
        new Ability("Primal Instant Charge", 0, 0, true, {
            TargetHighestDamage(
                Attack(1., BYPASS_ARMOR),
                Stun(75, 1)
            )
        }),
        new Ability("Resilient Group Impact", 0, 0, false, {
            TargetTeam(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Blind Rampage", 0, 0, false, {
            TargetSelf(
                IncreaseCritChance(100, 1, 0)
            ),
            TargetRandom(
                Attack(2.)
            )
        })
    }, nullptr),
    DinoKind("Glyptoceras Boss #2", LEGENDARY, 1, 13000, 1350, 110, 15, 15, 25, 80, 75, 70, 50, 95, 0, 25, {
        new Ability("Instant Defense Charge", 0, 0, true, {
            TargetHighestDamage(
                Attack(1.),
                Stun(75, 1)
            ),
            TargetSelf(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Resilient Group Strike", 0, 0, false, {
            TargetTeam(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Random Cunning Rampage", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetRandom(
                Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
                ReduceCritChance(100, 1, 2),
                ReduceDamage(50, 1, 2),
                Attack(2.)
            )
        }),
        new Ability("Critical Group Impact", 0, 0, false, {
            TargetSelf(
                IncreaseCritChance(100, 1, 0)
            ),
            TargetAllOpponents(
                Attack(1.5)
            )
        })
    }, nullptr),
    DinoKind("Glyptoceras Boss #3", LEGENDARY, 1, 13000, 1350, 110, 15, 15, 25, 80, 75, 70, 50, 95, 0, 25, {
        new Ability("Primal Instant Charge", 0, 0, true, {
            TargetHighestDamage(
                Attack(1., BYPASS_ARMOR),
                Stun(75, 1)
            )
        }),
        new Ability("Resilient Group Impact", 0, 0, false, {
            TargetTeam(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Instant Defense Charge", 0, 0, true, {
            TargetHighestDamage(
                Attack(1.),
                Stun(75, 1)
            ),
            TargetSelf(
                Shield(50, 2, 4)
            )
        }),
        new Ability("Bully Impact", 0, 0, false, {
            TargetSelf(
                IncreaseCritChance(100, 1, 0)
            ),
            TargetLowestHP(
                Attack(1.5)
            )
        })
    }, nullptr)
};

DECLARE_BOSS(GlyptocerasBoss, 19, 5, 3, 8);

DinoKind SmilonemysBossKind[] = {
    DinoKind("Smilonemys Boss #1", UNIQUE, 1, 20000, 1500, 127, 50, 5, 0, 80, 50, 80, 50, 100, 0, 50, {
        new Ability("Shielded Group Strike", 0, 0, false, {
            TargetSelf(
                Shield(50, 4, 4)
            ),
            TargetAllOpponents(
                Attack(1.)
            )
        }),
        new Ability("Primal Prowl", 0, 0, false, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS),
                Dodge(75, 67, 2, 4),
                IncreaseCritChance(50, 2, 2)
            )
        }),
        new Ability("Precise Pounce", 0, 0, false, {
            TargetLowestHP(
                Attack(2., PRECISE),
                ReduceDamage(50, 1, 2)
            )
        })
    }, nullptr),
    DinoKind("Smilonemys Boss #2", UNIQUE, 1, 20000, 1500, 127, 50, 5, 0, 80, 50, 80, 50, 100, 0, 50, {
        new Ability("Shielded Group Strike", 0, 0, false, {
            TargetSelf(
                Shield(50, 4, 4)
            ),
            TargetAllOpponents(
                Attack(1.)
            )
        }),
        new Ability("Prowling Shields", 0, 0, false, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS),
                Dodge(75, 67, 2, 4),
                IncreaseCritChance(50, 2, 2),
                Shield(50, 4, 4)
            )
        }),
        new Ability("Cautious Precise Pounce", 0, 0, false, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS),
                IncreaseSpeed(10, 3),
                Dodge(75, 67, 2, 4)
            ),
            TargetLowestHP(
                Attack(2., PRECISE),
                ReduceDamage(50, 1, 2)
            )
        }),
    }, nullptr)
};

DECLARE_BOSS(SmilonemysBoss, 22, 6, 9, 7);

//
// minion dex
//

DinoKind GroupShatteringMinion("Group Shattering Minion", RARE, 1, 3600, 1000, 122, 0, 30, 0, 0, 0, 0, 0, 100, 0, 0, {
    new Ability("Group Defense Shattering Strike", 0, 0, false, {
        TargetAllOpponents(
            Remove(SHIELD),
            Attack(1., BYPASS_ARMOR|GROUP)
        )
    }),
    new Ability("Group Ferocity", 0, 2, true, {
        TargetTeam(
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            IncreaseDamage(50, 2, 2)
        )
    }),
    new Ability("Group Shattering Impact", 0, 0, false, {
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR|GROUP)
        )
    })
}, nullptr);

DinoKind DecelerationMinion("Deceleration Minion", COMMON, 1, 4050, 1000, 112, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Shielded Decelerating Strike", 0, 0, false, {
        TargetSelf(
            Shield(50, 1, 4)
        ),
        TargetLowestHP(
            ReduceSpeed(50, 2),
            Attack(1., PRECISE)
        )
    }),
    new Ability("Group Decelerating Strike", 0, 2, false, {
        TargetAllOpponents(
            ReduceSpeed(50, 2),
            Attack(1., GROUP)
        )
    })
}, new Ability("Decelerating Counter", 0, 0, false, {
    TargetAttacker(
        ReduceSpeed(50, 1),
        Attack(1.)
    )
}));

DinoKind ShatteringMinion("Shattering Minion", RARE, 1, 4500, 1750, 103, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD|TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Defense Shattering Impact", 0, 1, false, {
        TargetLowestHP(
            Remove(SHIELD|TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    }),
    new Ability("Defense Shattering Rampage", 1, 1, false, {
        TargetLowestHP(
            Remove(SHIELD|TAUNT),
            Attack(2., BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind NullifyingMinion("Nullifying Minion", RARE, 1, 4500, 1100, 127, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Nullifying Strike", 0, 0, false, {
        TargetMostPositiveEffects(
            Remove(POSITIVE_EFFECTS),
            Attack(1.)
        )
    }),
    new Ability("Nullifying Impact", 0, 2, false, {
        TargetMostPositiveEffects(
            Remove(POSITIVE_EFFECTS),
            Attack(1.5)
        )
    }),
    new Ability("Group Distraction", 0, 2, true, {
        TargetAllOpponents(
            ReduceDamage(50, 2, 3)
        )
    })
}, nullptr);

DinoKind DistractionMinion("Distraction Minion", COMMON, 1, 3000, 1350, 129, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Distraction", 0, 0, false, {
        TargetHighestDamage(
            ReduceDamage(50, 1, 2),
            Attack(1.)
        )
    }),
    new Ability("Cunning Impact", 0, 1, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetHighestDamage(
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE)
        )
    })
}, nullptr);

DinoKind CounterAttackMinion("Counter-Attack Minion", RARE, 1, 4500, 1000, 104, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Resilient Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetLowestHP(
            Remove(DODGE|CLOAK|INCREASED_SPEED),
            Attack(1.),
            ImposeVulnerability(50, 2, 2)
        )
    }),
    new Ability("Group Taunting Shields", 0, 1, true, {
        TargetTeam(
            Shield(50, 2, 2)
        ),
        TargetSelf(
            Taunt(1)
        )
    }),
    new Ability("Cleansing Impact", 0, 2, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetLowestHP(
            Attack(1.5)
        )
    })
}, new Ability("Greater Rending Counter-Attack", 0, 0, false, {
    TargetAttacker(
        Remove(SHIELD),
        Rend(33, BYPASS_ARMOR)
    )
}));

//
// dino dex
//

DinoKind Albertosaurus("Albertosaurus", RARE, 1, 4350, 1750, 106, 0, 30, 100, 50, 0, 0, 100, 0, 0, 25, {
    new Ability("Fierce Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1, BYPASS_ARMOR)
        )
    }),
    new Ability("Killer Instinct", 1, 1, true, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    }),
    new Ability("Fierce Impact", 0, 1, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind Allodrigues("Allodrigues", UNIQUE, 3, 3300, 1750, 130, 0, 15, 0, 50, 75, 66, 100, 67, 0, 0, {
    new Ability("Fierce Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Protective Alert [2]", 0, 3, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetAllOpponents(
            ImposeVulnerability(50, 2, 4),
            ReduceDamage(50, 2, 4)
        )
    }, [](Dino &self) -> bool { return self.health <= 2 * self.max_health / 3; }, new Ability("Protective Alert [2]", 0, 3, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            RallyHeal(1./3)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 2, 4)
        )
    })),
    new Ability("Cunning Rampage", 1, 1, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetHighestDamage(
            Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
            ReduceCritChance(100, 1, 2),
            ReduceDamage(50, 1, 2),
            Attack(2.)
        )
    }),
    new Ability("Alert Peck", 0, 2, false, {
        TargetLowestHP(
            Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            Rend(60, BYPASS_ARMOR)
        )
    }, [](Dino &self) -> bool { return self.health <= self.max_health / 3; }, new Ability("Alert Peck", 1, 2, false, {
        TargetLowestHP(
            Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            Rend(60, BYPASS_ARMOR)
        )
    }))
}, nullptr);

DinoKind Andrewtherium("Andrewtherium", EPIC, 1, 3600, 1300, 119, 5, 25, 100, 0, 50, 0, 50, 50, 0, 50, {
    new Ability("Group Cleansing Strike", 0, 0, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    }),
    new Ability("Ferocious Strike", 0, 3, false, {
        TargetSelf(
            IncreaseDamage(50, 3, 6)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    }),
    new Ability("Group Warning Squeal", 0, 3, true, {
        TargetTeam(
            Shield(50, 2, 4),
            IncreaseCritChance(20, 2, 2),
            IncreaseDamage(25, 2, 4)
        ),
        TargetFastest(
            ReduceSpeed(50, 2)
        )
    }),
    new Ability("Rending Attack", 0, 1, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Rend(40, BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind Andrewtodon("Andrewtodon", EPIC, 1, 3450, 1300, 112, 15, 25, 0, 0, 0, 0, 100, 50, 0, 0, {
    new Ability("Fierce Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1, BYPASS_ARMOR)
        )
    }),
    new Ability("Armor Piercing Impact", 0, 1, false, {
        TargetLowestHP(
            Attack(1.5, BYPASS_ARMOR)
        )
    }),
    new Ability("Cleansing Impact", 0, 2, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetLowestHP(
            Attack(1.5)
        )
    }),
    new Ability("Rending Takedown", 1, 1, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Rend(60, BYPASS_ARMOR)
        )
    })
}, new Ability("Exposing Counter", 0, 0, false, {
    TargetAttacker(
        ImposeVulnerability(50, 1, 2)
    )
}));

DinoKind Indotaurus("Indotaurus", UNIQUE, 1, 4650, 1600, 106, 0, 20, 0, 0, 0, 34, 75, 50, 0, 50, {
    new Ability("Fierce Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD|TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Intimidating Impact", 0, 1, false, {
        TargetLowestHP(
            Remove(SHIELD),
            Attack(1.5, BYPASS_ARMOR),
            ImposeVulnerability(50, 1, 2)
        )
    }),
    new Ability("Cleansing Rampage", 1, 2, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            Attack(2.)
        )
    }),
    new Ability("Revenge Taunting Cloak", 0, 3, true, {
        TargetSelf(
            Cloak(2., 75, 67, 2),
            Taunt(1)
        )
    }, [](Dino &self) -> bool { return self.revenge; }, new Ability("Revenge Taunting Cloak", 0, 3, true, {
        TargetSelf(
            Cloak(2.5, 75, 67, 2),
            Taunt(1)
        )
    }))
}, new Ability("Greater Rending Counter-Attack", 0, 0, false, {
    TargetAttacker(
        Remove(SHIELD),
        Rend(33, BYPASS_ARMOR)
    )
}));

DinoKind Irritator("Irritator", RARE, 1, 4500, 1000, 126, 0, 30, 0, 0, 0, 0, 100, 0, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1, BYPASS_ARMOR)
        )
    }),
    new Ability("Ready To Crush", 0, 2, false, {
        TargetTeam(
            Cleanse(CRIT_CHANCE_REDUCTION | REDUCED_DAMAGE),
            IncreaseCritChance(30, 4, 2),
            IncreaseDamage(50, 4, 2)
        )
    }),
    new Ability("Group Takedown", 1, 2, true, {
        TargetTeam(
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION),
            IncreaseDamage(50, 2, 1)
        )
    })
}, nullptr);

DinoKind Rexy("Rexy", LEGENDARY, 1, 4950, 1850, 106, 0, 45, 0, 75, 0, 75, 100, 75, 0, 100, {
    new Ability("Alert Fierce Strike", 0, 0, false, {
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR|GROUP)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }, [](Dino &self) { return self.health <= self.max_health * 0.5; }, new Ability("Alert Fierce Strike", 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    })),
    new Ability("Defense Shattering Revenge", 0, 1, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }, [](Dino &self) { return self.revenge; }, new Ability("Defense Shattering Revenge", 0, 1, false, {
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR|GROUP)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    })),
    new Ability("Dominant Roar", 0, 2, true, {
        TargetTeam(
            IncreaseDamage(50, 2, 2)
        ),
        TargetAllOpponents(
            Attack(1., GROUP)
        ),
        TargetTeam(
            IncreaseSpeed(25, 1)
        )
    }),
    new Ability("Fierce Devouring Rampage", 1, 1, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(2., BYPASS_ARMOR)
        ),
        TargetSelf(
            DevourHeal(60, 4),
            Cleanse(VULNERABILITY)
        )
    })
}, nullptr);

DinoKind Skoolasaurus("Skoolasaurus", LEGENDARY, 1, 4500, 1000, 124, 30, 5, 0, 0, 0, 0, 100, 75, 0, 50, {
    new Ability("Resilient Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetLowestHP(
            Remove(DODGE | CLOAK | INCREASED_SPEED),
            Attack(1.),
            ImposeVulnerability(50, 2, 2)
        )
    }),
    new Ability("Tip The Scales", 0, 1, true, {
        TargetAllOpponents(
            Remove(POSITIVE_EFFECTS)
        ),
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS)
        )
    }),
    new Ability("Group Distraction", 0, 2, true, {
        TargetAllOpponents(
            ReduceDamage(50, 2, 3)
        )
    }),
    new Ability("Group Taunting Shields Strike", 0, 1, false, {
        TargetTeam(
            Shield(50, 2, 2)
        ),
        TargetSelf(
            Taunt(1)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    })
}, nullptr);

DinoKind Thylaconyx("Thylaconyx", LEGENDARY, 1, 4800, 1250, 122, 0, 25, 0, 25, 0, 75, 100, 100, 0, 100, {
    new Ability("Defense Shattering Strike", 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Crushing Prowl", 0, 2, true, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            IncreaseCritChance(75, 2, 2),
            Dodge(75, 67, 1, 2)
        ),
        TargetTeam(
            IncreaseDamage(50, 4, 2),
            Cleanse(REDUCED_DAMAGE | CRIT_CHANCE_REDUCTION)
        )
    }),
    new Ability("Devouring Wound", 0, 1, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Attack(1.5, BYPASS_ARMOR),
            DamageOverTime(20, 2)
        ),
        TargetSelf(
            DevourHeal(60, 4)
        ),
    }),
    new Ability("Skirmish", 1, 1, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(2., BYPASS_ARMOR|GROUP)
        )
    })
}, new Ability("Defense Shattering Counter-Attack", 0, 0, false, {
    TargetAttacker(
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    )
}));

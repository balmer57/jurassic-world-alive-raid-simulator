#include "dinodex.h"
#include "actions.h"
#include "modifiers.h"

using namespace actions;
using namespace std;

#define DECLARE_BOSS(name, level, health_boost, damage_boost, speed_boost) Dino name(0, 0, level, health_boost, damage_boost, speed_boost, name##Kind, sizeof(name##Kind) / sizeof(*name##Kind))

//
// boss dex
//

DinoKind BrachiosaurusBoss("Brachiosaurus Boss", EPIC, 1, 24000, 1350, 109, 0, 15, 50, 85, 100, 80, 100, 100, 0, 50, {
    { // Round 1
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
    }, { // Round 2
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
    }, { // Round 3
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
    }
}, nullptr);

DinoKind MeiolaniaBoss("Meiolania boss", RARE, 1, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 50, {
    { // Round 1
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
    }, { // Round 2
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
    }
}, nullptr);

DinoKind FukuimimusBoss("Fukuimimus boss", LEGENDARY, 1, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 15, {
    { // Round 1
        new ThreatenedAbility("Alert Mimic", 0, 0, true, {
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
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
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
        }),
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
    }, { // Round 2
        new ThreatenedAbility("Alert Mimic", 0, 0, true, {
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
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
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
        }),
        new RevengeAbility("Cunning Cleanse Revenge", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        }, 0, 0, false, {
            TargetTeam(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetAllOpponents(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
                Attack(2., GROUP)
            )
        }),
        new RevengeAbility("Resilient Cleanse Revenge", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetRandom(
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        }, 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                Remove(DODGE | CLOAK | INCREASED_SPEED),
                Attack(2., GROUP),
                ImposeVulnerability(50, 2, 2)
            )
        })
    }, { // Round 3
        new ThreatenedAbility("Alert Mimic", 0, 0, true, {
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
        }, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
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
        }),
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
        new RevengeAbility("Revenge Cunning Impact", 0, 0, false, {
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
        }, 0, 0, false, {
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
        }),
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
    }
}, new CounterAbility("Ferocious Feathers", {
    TargetSelf(
        IncreaseDamage(5, 3, 3)
    ),
    TargetTeam(
        IncreaseDamage(5, 3, 3)
    )
}));

DinoKind TroodoboaBoss("Troodoboa Boss", UNIQUE, 1, 16666, 1300, 120, 0, 10, 0, 90, 60, 80, 75, 100, 100, 15, {
    { // Round 1
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
    }, { // Round 2
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
    }, { // Round 3
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
    }
}, nullptr);

DinoKind GlyptocerasBoss("Glyptoceras Boss #1", LEGENDARY, 1, 13000, 1350, 110, 15, 15, 25, 80, 75, 70, 50, 95, 0, 25, {
    { // Round 1
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
    }, { // Round 2
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
    }, { // Round 3
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
    }
}, nullptr);

DinoKind SmilonemysBoss("Smilonemys Boss #1", UNIQUE, 1, 20000, 1500, 127, 50, 5, 0, 80, 50, 80, 50, 100, 0, 50, {
    { // Round 1
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
    }, { // Round 2
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
        })
    }
}, nullptr);

DinoKind MortemRexBoss("Mortem Rex Boss", APEX, 1, 25000, 2000, 108, 0, 40, 0, 80, 50, 80, 0, 100, 0, 50, {
    { // Round 1
        new Ability("Primal Tail Whip", 0, 0, false, {
            TargetAllOpponents(
                Remove(SHIELD),
                Attack(1., BYPASS_ARMOR)
            )
        }),
        new Ability("Defense Shattering Rampage", 0, 0, false, {
            TargetHighestHP(
                Remove(SHIELD),
                Attack(2., BYPASS_ARMOR)
            )
        }),
        new Ability("Cleansing Random Shattering Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetRandom(
                Remove(SHIELD),
                Attack(1., BYPASS_ARMOR)
            )
        })
    }, { // Round 2
        new Ability("Cleansing Primal Tail Whip", 0, 0, false, {
            TargetSelf(
                Cleanse(NEGATIVE_EFFECTS)
            ),
            TargetAllOpponents(
                Remove(SHIELD),
                Attack(1., BYPASS_ARMOR)
            )
        }),
        new Ability("Defense Shattering Rampage", 0, 0, false, {
            TargetHighestHP(
                Remove(SHIELD),
                Attack(2., BYPASS_ARMOR)
            )
        }),
        new Ability("Defense Shattering Impact", 0, 0, false, {
            TargetLowestHP(
                Remove(SHIELD),
                Attack(1.5, BYPASS_ARMOR)
            )
        })
    }
}, nullptr);

DinoKind ParasauthopsBoss("Parasauthops Boss", UNIQUE, 1, 14500, 1500, 112, 0, 20, 0, 70, 75, 80, 50, 100, 0, 35, {
    { // Round 1
        new Ability("Random Cunning Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetRandom(
                ReduceDamage(50, 1, 2),
                ReduceCritChance(100, 1, 2),
                Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
                Attack(1.5)
            )
        }),
        new RevengeAbility("Resilient Impact Revenge", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }, 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(1.5),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Emergency Regroup", 0, 0, true, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS),
                Heal(1.5),
                Shield(50, 2, 4)
            )
        }),
        new Ability("Fierce Cleansing Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR)
            )
        })
    }, { // Round 2
        new Ability("Group Fierce Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1.5, BYPASS_ARMOR)
            )
        }),
        new Ability("Emergency Regroup", 0, 0, true, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS),
                Heal(1.5),
                Shield(50, 2, 4)
            )
        }),
        new RevengeAbility("Revenge Group Cunning Strike", 0, 0, false, {
            TargetAllOpponents(
                Remove(INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
                ReduceDamage(50, 2, 3),
                Attack(1.5),
                ReduceCritChance(100, 2, 3)
            ),
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            )
        }, 0, 0, false, {
            TargetAllOpponents(
                Remove(INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
                ReduceDamage(50, 2, 3),
                Attack(1.),
                ReduceCritChance(100, 2, 3)
            ),
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
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
    }, { // Round 3
        new Ability("Regroup", 0, 0, false, {
            TargetTeam(
                Cleanse(NEGATIVE_EFFECTS),
                Heal(2.),
                Shield(50, 2, 4)
            )
        }),
        new RevengeAbility("Resilient Rampage Revenge", 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetFastest(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        }, 0, 0, false, {
            TargetSelf(
                Cleanse(REDUCED_DAMAGE)
            ),
            TargetAllOpponents(
                Remove(DODGE|CLOAK|INCREASED_SPEED),
                Attack(2.),
                ImposeVulnerability(50, 2, 2)
            )
        }),
        new Ability("Group Fierce Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1.5, BYPASS_ARMOR)
            )
        }),
        new Ability("Random Cunning Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(DAMAGE_OVER_TIME)
            ),
            TargetRandom(
                Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
                ReduceCritChance(100, 1, 2),
                ReduceDamage(50, 1, 2),
                Attack(1.)
            )
        })
    }
}, new CounterAbility("Power Heal", {
    TargetSelf(
        Heal(0.3)
    )
}));

DinoKind ImperatosuchusBoss("Imperatosuchus Boss", APEX, 1, 16000, 1450, 115, 15, 5, 75, 90, 75, 85, 80, 100, 0, 60, {
    { // Round 1
        new ThreatenedAbility("Alert Assist", 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                Shield(50, 2, 4)
            )
        }, [](Dino &self) -> bool { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                FixedHeal(10),
                IncreaseSpeed(30, 2),
                Shield(100, 2, 4)
            )
        }),
        new Ability("Group Fierce Decelerating Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Fierce Cleansing Impact", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT),
                Attack(1.5, BYPASS_ARMOR)
            )
        })
    }, { // Round 2
        new ThreatenedAbility("Alert Assist", 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                Shield(50, 2, 4)
            )
        }, [](Dino &self) -> bool { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                FixedHeal(10),
                IncreaseSpeed(30, 2),
                Shield(100, 2, 4)
            )
        }),
        new RevengeAbility("Infectious Revenge", 0, 0, false, {
            TargetFastest(
                ReduceSpeed(50, 2),
                Attack(1.5),
                DamageOverTime(15, 2)
            )
        }, 0, 0, false, {
            TargetAllOpponents(
                ReduceSpeed(75, 2),
                Attack(1.5),
                DamageOverTime(20, 2)
            )
        }),
        new Ability("Group Fierce Decelerating Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Fierce Decelerating Rampage", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT),
                Attack(2., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        })
    }, { // Round 3
        new ThreatenedAbility("Alert Assist", 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                Shield(50, 2, 4)
            )
        }, [](Dino &self) -> bool { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
            TargetSelf(
                Shield(100, 1, 4)
            ),
            TargetTeam(
                IncreaseDamage(50, 2, 2),
                FixedHeal(10),
                IncreaseSpeed(30, 2),
                Shield(100, 2, 4)
            )
        }),
        new RevengeAbility("Braking Revenge", 0, 0, false, {
            TargetFastest(
                ReduceSpeed(50, 2),
                Attack(2.),
                DamageOverTime(15, 2)
            )
        }, 0, 0, true, {
            TargetAllOpponents(
                ReduceSpeed(75, 2),
                Attack(2.),
                DamageOverTime(34, 2)
            )
        }),
        new RevengeAbility("Waning Revenge", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT),
                Attack(2., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        }, 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT)
            ),
            TargetAllOpponents(
                Attack(2., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Group Fierce Decelerating Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        })
    }
}, new CounterAbility("Counter Spike", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    ),
    TargetTeam(
        IncreaseDamage(10, 2, 2)
    )
}));

DinoKind AlacranixBoss("Alacranix Boss", APEX, 1, 15000, 1550, 116, 40, 20, 50, 100, 50, 90, 20, 100, 100, 15, {
    { // Round 1
        new Ability("Evasive Fierce Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetLowestHP(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR)
            ),
            TargetSelf(
                Dodge(75, 67, 2, 8)
            )
        }),
        new Ability("Group Fierce Decelerating Strike", 0, 0, false, {
            TargetSelf(
                Cleanse(VULNERABILITY)
            ),
            TargetAllOpponents(
                Remove(SHIELD|TAUNT),
                Attack(1., BYPASS_ARMOR),
                ReduceSpeed(50, 2)
            )
        }),
        new Ability("Enfeebling Raking Impact", 0, 0, false, {
            TargetMostPositiveEffects(
                Remove(DODGE|CLOAK),
                Attack(1.5, BYPASS_ARMOR)
            )
        }),
        new Ability("Piercing Destruction", 0, 0, true, {
            TargetMostPositiveEffects(
                Remove(POSITIVE_EFFECTS),
                Rend(100, BYPASS_ARMOR)
            )
        })
    }, { // Round 2
        new Ability("Evasive Piercing Impact", 0, 0, false, {
            TargetLowestHP(
                Remove(SHIELD),
                Attack(1.5, BYPASS_ARMOR)
            ),
            TargetSelf(
                Dodge(75, 67, 2, 8)
            )
        }),
        new Ability("Dispersed Decelerating Impact", 0, 0, false, {
            TargetAllOpponents(
                ReduceSpeed(50, 2),
                Attack(1.5)
            )
        }),
        new Ability("Piercing Destruction", 0, 0, true, {
            TargetMostPositiveEffects(
                Remove(POSITIVE_EFFECTS),
                Rend(100, BYPASS_ARMOR)
            )
        }),
        new Ability("Group Necrotic Strike", 0, 0, false, {
            TargetAllOpponents(
                Remove(POSITIVE_EFFECTS),
                Attack(1., BYPASS_ARMOR)
            ),
            TargetSelf(
                DevourHeal(50, 2)
            )
        })
    }, { // Round 3
        new Ability("Group Necrotic Strike", 0, 0, false, {
            TargetAllOpponents(
                Remove(POSITIVE_EFFECTS),
                Attack(1., BYPASS_ARMOR)
            ),
            TargetSelf(
                DevourHeal(50, 2)
            )
        }),
        new Ability("Piercing Destruction", 0, 0, true, {
            TargetMostPositiveEffects(
                Remove(POSITIVE_EFFECTS),
                Rend(100, BYPASS_ARMOR)
            )
        }),
        new Ability("Cold-Blooded Rampage", 0, 0, false, {
            TargetLowestHP(
                Attack(2., PRECISE)
            )
        })
    }
}, nullptr);

//
// minion dex
//

DinoKind EntelodonMinion("Group Shattering Minion", RARE, 1, 3600, 1000, 122, 0, 30, 0, 0, 0, 0, 0, 100, 0, 0, {
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

DinoKind MiragaiaMinion("Deceleration Minion", COMMON, 1, 4050, 1000, 112, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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
}, new CounterAbility("Decelerating Counter", {
    TargetAttacker(
        ReduceSpeed(50, 1),
        Attack(1.)
    )
}));

DinoKind GorgosaurusMinion("Shattering Minion", RARE, 1, 4500, 1750, 103, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, {
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

DinoKind KoolasuchusMinion("Nullifying Minion", RARE, 1, 4500, 1100, 127, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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

DinoKind MonolophosaurusMinion("Distraction Minion", COMMON, 1, 3000, 1350, 129, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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

DinoKind CarnotaurusMinion("Counter-Attack Minion", RARE, 1, 4500, 1000, 104, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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
}, new CounterAbility("Greater Rending Counter-Attack", {
    TargetAttacker(
        Remove(SHIELD),
        Rend(33, BYPASS_ARMOR)
    )
}));

DinoKind WuerhosaurusMinion("Deceleration Minion", RARE, 1, 4800, 1000, 115, 25, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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
    new Ability("Group Decelerating Rampage", 0, 2, false, {
        TargetAllOpponents(
            ReduceSpeed(50, 2),
            Attack(2.)
        )
    }),
    new Ability("Taunting Bellow", 0, 2, true, {
        TargetSelf(
            Shield(50, 1, 4),
            Taunt(1)
        ),
        TargetFastest(
            ReduceSpeed(50, 2)
        )
    })
}, nullptr);

DinoKind MajungasaurusMinion("Counter-Attack Minion", COMMON, 1, 3450, 1300, 105, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
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
    new Ability("Group Mock, Block And Sock", 0, 1, false, {
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
}, new CounterAbility("Armor Piercing Counter", {
    TargetAttacker(
        Attack(1., BYPASS_ARMOR)
    )
}));

DinoKind VelociraptorMinion("Damage Minion", COMMON, 1, 2500, 1500, 131, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Group Strike", 0, 0, false, {
        TargetAllOpponents(
            Attack(1.)
        )
    }),
    new Ability("High Pounce", 0, 1, false, {
        TargetHighestDamage(
            Attack(2.),
            ReduceDamage(50, 1, 2)
        )
    })
}, nullptr);

DinoKind SuchomimusMinion("Dot Minion", COMMON, 1, 3900, 900, 104, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, {
    new Ability("Group Wounding Strike", 0, 0, false, {
        TargetAllOpponents(
            Attack(1.),
            DamageOverTime(20, 2)
        )
    }),
    new Ability("Lethal Wound", 0, 2, false, {
        TargetHighestHP(
            Attack(1.),
            DamageOverTime(33, 3)
        )
    })
}, nullptr);

DinoKind GallimimusMinion("Dodge Minion", COMMON, 1, 2700, 1400, 130, 0, 5, 100, 100, 100, 0, 0, 100, 0, 0, {
    new Ability("Evasive Strike", 0, 0, false, {
        TargetSelf(
            Dodge(75, 67, 1, 1)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    }),
    new Ability("Instant Distraction", 0, 1, true, {
        TargetHighestDamage(
            ReduceDamage(100, 1, 2)
        )
    })
}, nullptr);

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
    new ThreatenedAbility("Protective Alert [2]", 0, 3, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetAllOpponents(
            ImposeVulnerability(50, 2, 4),
            ReduceDamage(50, 2, 4)
        )
    }, [](Dino &self) -> bool { return self.health <= 2 * self.max_health / 3; }, 0, 3, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            RallyHeal(1./3)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 2, 4)
        )
    }),
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
    new ThreatenedAbility("Alert Peck", 0, 2, false, {
        TargetLowestHP(
            Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            Rend(60, BYPASS_ARMOR)
        )
    }, [](Dino &self) -> bool { return self.health <= self.max_health / 3; }, 1, 2, false, {
        TargetLowestHP(
            Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            Rend(60, BYPASS_ARMOR)
        )
    })
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
}, new CounterAbility("Exposing Counter", {
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
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetHighestHP(
            Attack(2.)
        )
    }),
    new RevengeAbility("Revenge Taunting Cloak", 0, 3, true, {
        TargetSelf(
            Cloak(2., 75, 67, 2),
            Taunt(1)
        )
    }, 0, 3, true, {
        TargetSelf(
            Cloak(2.5, 75, 67, 2),
            Taunt(1)
        )
    })
}, new CounterAbility("Greater Rending Counter-Attack", {
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
    new ThreatenedAbility("Alert Fierce Strike", 0, 0, false, {
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR|GROUP)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }, [](Dino &self) { return self.health <= self.max_health * 0.5; }, 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }),
    new RevengeAbility("Defense Shattering Revenge", 0, 1, false, {
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }, 0, 1, false, {
        TargetAllOpponents(
            Remove(SHIELD | TAUNT),
            Attack(1.5, BYPASS_ARMOR|GROUP)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }),
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
}, new CounterAbility("Defense Shattering Counter-Attack", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    )
}));

DinoKind Thoradolosaur("Thoradolosaur", UNIQUE, 1, 4500, 1750, 105, 0, 30, 0, 75, 0, 0, 0, 50, 0, 50, {
    new Ability("Fierce Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetLowestHP(
            Remove(SHIELD | TAUNT),
            Attack(1., BYPASS_ARMOR)
        )
    }),
    new Ability("Cleansing Group Destroyer", 0, 1, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS)
        ),
        TargetAllOpponents(
            Remove(SHIELD|TAUNT),
            Attack(1.5, BYPASS_ARMOR)
        )
    }),
    new Ability("Fierce Rampage", 1, 1, false, {
        TargetSelf(
            Cleanse(VULNERABILITY)
        ),
        TargetHighestHP(
            Remove(SHIELD|TAUNT),
            Attack(2., BYPASS_ARMOR)
        )
    }),
    new Ability("Instant Charge", 1, 2, true, {
        TargetHighestDamage(
            Attack(1.),
            Stun(75, 1)
        )
    })
}, nullptr);

DinoKind Diloracheirus("Diloracheirus", UNIQUE, 1, 4470, 1650, 128, 0, 10, 0, 100, 0, 0, 0, 100, 0, 0, {
    new Ability("Tough Group Cunning Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
            Attack(1.)
        )
    }),
    new Ability("Accelerating Team Heal", 0, 2, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(1.),
            IncreaseSpeed(25, 1)
        )
    }),
    new Ability("Distracting Team Heal", 0, 2, true, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(2.)
        ),
        TargetHighestDamage(
            ReduceDamage(25, 2, 2)
        )
    }),
    new RevengeAbility("Revenge Cunning Rampage", 1, 1, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetHighestDamage(
            Remove(INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Attack(2.)
        )
    }, 0, 1, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetHighestDamage(
            Remove(INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Attack(2.)
        )
    })
}, new CounterAbility("Darting Counter", {
    TargetAttacker(
        Attack(1.)
    ),
    TargetSelf(
        IncreaseSpeed(25, 1)
    )
}));

DinoKind Poukandactylus("Poukandactylus", UNIQUE, 1, 4050, 1200, 127, 0, 15, 0, 0, 50, 0, 50, 100, 0, 50, {
    new Ability("Sideflap", 0, 0, true, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            Dodge(100, 67, 1, 2),
            IncreaseSpeed(10, 2),
            Taunt(1.)
        )
    }),
    new Ability("Distracting Impact", 0, 2, false, {
        TargetHighestDamage(
            ReduceDamage(50, 2, 4),
            Attack(1.5)
        )
    }),
    new Ability("Fearless Flap", 0, 2, false, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            Dodge(100, 67, 2, 2),
            IncreaseSpeed(10, 2)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 2, 2),
            Attack(1.)
        )
    }),
    new Ability("Group Instant Distraction", 0, 2, true, {
        TargetAllOpponents(
            ReduceDamage(100, 1, 2)
        )
    })
}, new CounterAbility("Defense Shattering Counter", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR)
    )
}));

DinoKind ThylosIntrepidus("Thylos Intrepidus", UNIQUE, 3, 3900, 1400, 120, 0, 40, 0, 50, 0, 33, 100, 0, 100, 0, {
    new Ability("Minor Rending Lockdown", 0, 0, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Rend(34, BYPASS_ARMOR),
            UnableToSwap(1)
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
    new Ability("Wounding Devouring Impact", 0, 2, false, {
        TargetLowestHP(
            Remove(SHIELD),
            Attack(1.5)
        ),
        TargetSelf(
            DevourHeal(60, 2)
        ),
        TargetLowestHP(
            Remove(TAUNT),
            DamageOverTime(20, 2)
        ),
        TargetSelf(
            Cleanse(VULNERABILITY)
        )
    }),
    new Ability("Rending Takedown", 1, 1, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Rend(60, BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind MarsupialLion("Marsupial Lion", RARE, 1, 4050, 1000, 117, 0, 40, 0, 0, 0, 0, 100, 0, 0, 50, {
    new Ability("Minor Rending Attack", 0, 0, false, {
        TargetLowestHP(
            Remove(SHIELD),
            Rend(34, BYPASS_ARMOR)
        )
    }),
    new Ability("Rending Takedown", 1, 1, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Rend(60, BYPASS_ARMOR)
        )
    }),
    new Ability("Prowl", 0, 0, true, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            Dodge(75, 67, 1, 2),
            IncreaseCritChance(50, 3, 2)
        )
    })
}, new CounterAbility("Medium Counter-Attack", {
    TargetAttacker(
        Attack(0.5)
    )
}));

DinoKind Parasauthops("Parasauthops", UNIQUE, 1, 4650, 1550, 109, 0, 15, 0, 75, 50, 0, 0, 33, 100, 0, {
    new Ability("Tough Group Cunning Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
            Attack(1.)
        )
    }),
    new ThreatenedAbility("Alert Instant Heal", 1, 2, true, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(1.5)
        )
    }, [](Dino &self) -> bool { return self.total_health <= self.max_total_health * 0.5; }, 1, 2, true, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(2.)
        )
    }),
    new Ability("Greater Group Heal", 0, 2, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(2.)
        )
    }),
    new RevengeAbility("Resilient Rampage Revenge", 1, 1, false, {
        TargetSelf(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetFastest(
            Remove(INCREASED_SPEED|CLOAK|DODGE),
            Attack(2.),
            ImposeVulnerability(50, 2, 2)
        )
    }, 1, 1, false, {
        TargetSelf(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetAllOpponents(
            Remove(INCREASED_SPEED|CLOAK|DODGE),
            Attack(2.),
            ImposeVulnerability(50, 2, 1)
        )
    })
}, new CounterAbility("Counter Power Heal", {
    TargetSelf(
        FixedHeal(6)
    )
}));

DinoKind Enteloceros("Enteloceros", LEGENDARY, 1, 4500, 1300, 126, 20, 10, 0, 0, 0, 50, 50, 100, 0, 100, {
    new Ability("Superiority Strike", 0, 0, false, {
        TargetSelf(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetFastest(
            ReduceSpeed(50, 1),
            Attack(1., PRECISE)
        )
    }),
    new Ability("Mutual Fury", 0, 1, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            IncreaseDamage(50, 3, 2),
            IncreaseSpeed(10, 2)
        ),
        TargetAllOpponents(
            IncreaseDamage(50, 2, 1)
        )
    }),
    new Ability("Dig In", 0, 2, true, {
        TargetSelf(
            Cleanse(NEGATIVE_EFFECTS),
            IncreaseSpeed(10, 2),
            Shield(50, 1, 8),
            Heal(1.)
        )
    }),
    new RevengeAbility("Group Revenge Shattering Rampage", 1, 2, false, {
        TargetHighestHP(
            Remove(SHIELD),
            Attack(2., BYPASS_ARMOR)
        )
    }, 1, 2, false, {
        TargetAllOpponents(
            Remove(SHIELD),
            Attack(2., BYPASS_ARMOR)
        )
    })
}, nullptr);

DinoKind Tuoramoloch("Tuoramoloch", UNIQUE, 1, 4200, 1500, 126, 0, 5, 0, 0, 50, 0, 100, 100, 0, 0, {
    new Ability("Group Superiority", 0, 0, false, {
        TargetTeam(
            Cleanse(REDUCED_DAMAGE)
        ),
        TargetFastest(
            ReduceSpeed(50, 1),
            Attack(1., PRECISE)
        )
    }),
    new Ability("Lesser Group Heal", 0, 2, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(1.)
        )
    }),
    new Ability("Group Acceleration", 0, 1, true, {
        TargetTeam(
            Cleanse(REDUCED_SPEED),
            IncreaseSpeed(50, 3)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    }),
    new Ability("Greater Emergency Heal", 0, 2, true, {
        TargetLowestHPTeammate(
            Cleanse(NEGATIVE_EFFECTS),
            Heal(2.)
        )
    })
}, nullptr);

DinoKind Troodoboa("Troodoboa", UNIQUE, 1, 3900, 1200, 117, 0, 10, 0, 100, 100, 0, 75, 75, 100, 0, {
    new Ability("Instant Decelerating Precision", 0, 0, true, {
        TargetSelf(
            Shield(50, 1, 4)
        ),
        TargetFastest(
            ReduceSpeed(50, 3),
            Attack(1., PRECISE)
        )
    }),
    new Ability("Group Cleansing Fatal Strike", 0, 3, false, {
        TargetTeam(
            Cleanse(NEGATIVE_EFFECTS),
            IncreaseDamage(50, 3, 6)
        ),
        TargetLowestHP(
            Attack(1.)
        )
    }),
    new Ability("Precise Distracting Impact", 0, 1, false, {
        TargetLowestHP(
            Attack(1.5, PRECISE),
            ReduceDamage(50, 1, 2)
        )
    }),
    new Ability("Group Cunning Rampage", 2, 1, false, {
        TargetSelf(
            Cleanse(DAMAGE_OVER_TIME)
        ),
        TargetAllOpponents(
            ReduceDamage(50, 1, 2),
            ReduceCritChance(100, 1, 2),
            Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
            Attack(2.)
        )
    })
}, new CounterAbility("Raking Counter-Attack", {
    TargetAttacker(
        Remove(CLOAK|DODGE),
        Attack(1., BYPASS_ARMOR)
    )
}));

std::map<std::string, std::vector<Dino>> BossDex = {
    make_pair<string, vector<Dino>>("Meiolania", {Dino(0, 0, 8, 0, 0, 0, &MeiolaniaBoss)}),
    make_pair<string, vector<Dino>>("Brachiosaurus", {Dino(0, 0, 14, 0, 0, 0, &BrachiosaurusBoss)}),
    make_pair<string, vector<Dino>>("Fukuimimus", {Dino(0, 0, 19, 7, 7, 5, &FukuimimusBoss), Dino(0, 5, 18, 9, 5, 3, &EntelodonMinion), Dino(0, 6, 18, 7, 5, 6, &MiragaiaMinion)}),
    make_pair<string, vector<Dino>>("Glyptoceras", {Dino(0, 0, 19, 5, 3, 8, &GlyptocerasBoss), Dino(0, 5, 17, 7, 6, 1, &KoolasuchusMinion), Dino(0, 6, 17, 8, 3, 3, &WuerhosaurusMinion)}),
    make_pair<string, vector<Dino>>("Troodoboa", {Dino(0, 0, 25, 10, 10, 5, &TroodoboaBoss), Dino(0, 5, 24, 4, 10, 10, &GorgosaurusMinion), Dino(0, 6, 24, 10, 4, 10, &KoolasuchusMinion)}),
    make_pair<string, vector<Dino>>("Smilonemys", {Dino(0, 0, 22, 6, 9, 7, &SmilonemysBoss), Dino(0, 5, 17, 7, 6, 1, &MonolophosaurusMinion), Dino(0, 6, 17, 8, 3, 3, &CarnotaurusMinion)}),
    make_pair<string, vector<Dino>>("Parasauthops", {Dino(0, 0, 24, 8, 8, 8, &ParasauthopsBoss), Dino(0, 5, 23, 9, 4, 10, &MajungasaurusMinion), Dino(0, 6, 23, 12, 3, 8, &SuchomimusMinion)}),
    make_pair<string, vector<Dino>>("MortemRex", {Dino(0, 0, 30, 15, 15, 0, &MortemRexBoss), Dino(0, 5, 29, 10, 10, 9, &MajungasaurusMinion), Dino(0, 6, 29, 4, 10, 15, &VelociraptorMinion)}),
    make_pair<string, vector<Dino>>("Imperatosuchus", {Dino(0, 0, 30, 10, 13, 7, &ImperatosuchusBoss), Dino(0, 5, 29, 8, 5, 10, &MajungasaurusMinion), Dino(0, 6, 29, 8, 2, 10, &KoolasuchusMinion)}),
    make_pair<string, vector<Dino>>("Alacranix", {Dino(0, 0, 30, 10, 14, 5, &AlacranixBoss), Dino(0, 5, 28, 5, 5, 18, &GallimimusMinion), Dino(0, 6, 28, 5, 13, 10, &SuchomimusMinion)}),
};

std::map<std::string, const DinoKind *> DinoDex = {
    make_pair("Albertosaurus", &Albertosaurus),
    make_pair("Allodrigues", &Allodrigues),
    make_pair("Andrewtherium", &Andrewtherium),
    make_pair("Andrewtodon", &Andrewtodon),
    make_pair("Diloracheirus", &Diloracheirus),
    make_pair("Enteloceros", &Enteloceros),
    make_pair("Indotaurus", &Indotaurus),
    make_pair("Irritator", &Irritator),
    make_pair("Parasauthops", &Parasauthops),
    make_pair("Poukandactylus", &Poukandactylus),
    make_pair("Rexy", &Rexy),
    make_pair("Skoolasaurus", &Skoolasaurus),
    make_pair("Thoradolosaur", &Thoradolosaur),
    make_pair("Thylaconyx", &Thylaconyx),
    make_pair("ThylosIntrepidus", &ThylosIntrepidus),
    make_pair("Troodoboa", &Troodoboa),
    make_pair("Tuoramoloch", &Tuoramoloch),
};

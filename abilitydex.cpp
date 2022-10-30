#include "abilitydex.h"
#include "actions.h"
#include "dino.h"

using namespace std;
using namespace actions;

namespace boss {

Ability Group_Shield_Strike("Group Shield Strike", 0, 0, true, {
    TargetLowestHP(
        Attack(1.)
    ),
    TargetTeam(
        Shield(50, 2, 4)
    )
});

Ability Group_Resilient_Strike("Group Resilient Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Resilient_Vulnerability_Rampage("Resilient Vulnerability Rampage", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetFastest(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(2.),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Shielded_Group_Strike_Brachiosaurus("Shielded Group Strike", 0, 0, true, {
    TargetAllOpponents(
        Attack(1.)
    ),
    TargetTeam(
        Shield(50, 2, 4)
    )
});

Ability Group_Resilient_Impact("Group Resilient Impact", 0, 0, true, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.5),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Boom("Boom", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(2.),
        ImposeVulnerability(50, 2, 1)
    )
});

Ability Shielded_Resilient_Strike("Shielded Resilient Strike", 0, 0, false, {
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
});

Ability Resilient_Impact("Resilient Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetFastest(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.5),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Steady_Group_Vulnerability_Strike("Steady Group Vulnerability Strike", 0, 0, false, {
    TargetAllOpponents(
        Attack(1, GROUP),
        ImposeVulnerability(50, 1, 2)
    )
});

Ability Devastation("Devastation", 2, 1, false, {
    TargetHighestHP(
        Attack(3, PRECISE)
    ),
    TargetSelf(
        Taunt(1)
    )
});

Ability Vulnerability_Impact("Vulnerability Impact", 0, 1, false, {
    TargetHighestHP(
        Attack(1.5),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Group_Superior_Vulnerability("Group Superior Vulnerability", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        ReduceSpeed(50, 2),
        Attack(1, PRECISE|GROUP),
        ImposeVulnerability(50, 2, 1)
    )
});

Ability Group_Devastation("Group Devastation", 0, 0, false, {
    TargetAllOpponents(
        Attack(3, PRECISE|GROUP)
    )
});

ThreatenedAbility Alert_Mimic("Alert Mimic", 0, 0, true, {
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
});

Ability Protective_Strike("Protective Strike", 0, 0, false, {
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
});

Ability Random_Cunning_Rampage("Random Cunning Rampage", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetRandom(
        Remove(INCREASED_CRIT_CHANCE | INCREASED_DAMAGE),
        ReduceCritChance(100, 1, 2),
        ReduceDamage(50, 1, 2),
        Attack(2.)
    )
});

RevengeAbility Cunning_Cleanse_Revenge("Cunning Cleanse Revenge", 0, 0, false, {
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
});

RevengeAbility Resilient_Cleanse_Revenge("Resilient Cleanse Revenge", 0, 0, false, {
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
});

RevengeAbility Revenge_Cunning_Impact("Revenge Cunning Impact", 0, 0, false, {
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
});

Ability Determined_Group_Rampage("Determined Group Rampage", 0, 0, false, {
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
});

CounterAbility Ferocious_Feathers("Ferocious Feathers", {
    TargetSelf(
        IncreaseDamage(5, 3, 3)
    ),
    TargetTeam(
        IncreaseDamage(5, 3, 3)
    )
});

Ability Instant_Shielded_Decelerating_Strike("Instant Shielded Decelerating Strike", 0, 0, true, {
    TargetSelf(
        Shield(50, 1, 4)
    ),
    TargetHighestHP(
        Attack(1.),
        ReduceSpeed(50, 2)
    )
});

Ability Targeted_Cleansing_Strike("Targeted Cleansing Strike", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetHighestDamage(
        Attack(1.)
    )
});

Ability Group_Ferocious_Strike("Group Ferocious Strike", 0, 0, false, {
    TargetTeam(
        IncreaseDamage(25, 2, 4)
    ),
    TargetHighestHP(
        Attack(1.)
    )
});

Ability Coiling_Rampage("Coiling Rampage", 0, 0, false, {
    TargetSelf(
        Shield(75, 3, 12)
    ),
    TargetAllOpponents(
        ReduceDamage(75, 2, 4)
    ),
    TargetHighestDamage(
        Attack(2.)
    )
});

Ability Targeted_Cleansing_Impact_1_5("Targeted Cleansing Impact", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetHighestDamage(
        Attack(1.5)
    )
});

Ability Raking_Piercing_Strike("Raking Piercing Strike", 0, 0, false, {
    TargetMostPositiveEffects(
        Remove(DODGE|CLOAK),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Targeted_Cleansing_Impact_2_0("Targeted Cleansing Impact", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetHighestDamage(
        Attack(1.5)
    )
});

Ability Group_Ferocious_Impact("Group Ferocious Impact", 0, 0, false, {
    TargetTeam(
        IncreaseDamage(50, 2, 4)
    ),
    TargetMostPositiveEffects(
        Remove(DODGE|CLOAK),
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Primal_Instant_Charge("Primal Instant Charge", 0, 0, true, {
    TargetHighestDamage(
        Attack(1., BYPASS_ARMOR),
        Stun(75, 1)
    )
});

Ability Resilient_Group_Impact("Resilient Group Impact", 0, 0, false, {
    TargetTeam(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.5),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Blind_Rampage("Blind Rampage", 0, 0, false, {
    TargetSelf(
        IncreaseCritChance(100, 1, 0)
    ),
    TargetRandom(
        Attack(2.)
    )
});

Ability Instant_Defense_Charge("Instant Defense Charge", 0, 0, true, {
    TargetHighestDamage(
        Attack(1.),
        Stun(75, 1)
    ),
    TargetSelf(
        Shield(50, 2, 4)
    )
});

Ability Resilient_Group_Strike("Resilient Group Strike", 0, 0, false, {
    TargetTeam(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetAllOpponents(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Critical_Group_Impact("Critical Group Impact", 0, 0, false, {
    TargetSelf(
        IncreaseCritChance(100, 1, 0)
    ),
    TargetAllOpponents(
        Attack(1.5)
    )
});

Ability Bully_Impact("Bully Impact", 0, 0, false, {
    TargetSelf(
        IncreaseCritChance(100, 1, 0)
    ),
    TargetLowestHP(
        Attack(1.5)
    )
});

Ability Shielded_Group_Strike_Smilonemys("Shielded Group Strike", 0, 0, false, {
    TargetSelf(
        Shield(50, 4, 4)
    ),
    TargetAllOpponents(
        Attack(1.)
    )
});

Ability Primal_Prowl("Primal Prowl", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(75, 67, 2, 4),
        IncreaseCritChance(50, 2, 2)
    )
});

Ability Precise_Pounce("Precise Pounce", 0, 0, false, {
    TargetLowestHP(
        Attack(2., PRECISE),
        ReduceDamage(50, 1, 2)
    )
});

Ability Prowling_Shields("Prowling Shields", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(75, 67, 2, 4),
        IncreaseCritChance(50, 2, 2),
        Shield(50, 4, 4)
    )
});

Ability Cautious_Precise_Pounce("Cautious Precise Pounce", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        IncreaseSpeed(10, 3),
        Dodge(75, 67, 2, 4)
    ),
    TargetLowestHP(
        Attack(2., PRECISE),
        ReduceDamage(50, 1, 2)
    )
});

Ability Primal_Tail_Whip("Primal Tail Whip", 0, 0, false, {
    TargetAllOpponents(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Defense_Shattering_Rampage("Defense Shattering Rampage", 0, 0, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Cleansing_Random_Shattering_Strike("Cleansing Random Shattering Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetRandom(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Cleansing_Primal_Tail_Whip("Cleansing Primal Tail Whip", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetAllOpponents(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Defense_Shattering_Impact("Defense Shattering Impact", 0, 0, false, {
    TargetLowestHP(
        Remove(SHIELD),
        Attack(1.5, BYPASS_ARMOR)
    )
});


Ability Random_Cunning_Impact("Random Cunning Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetRandom(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(1.5)
    )
});

RevengeAbility Resilient_Impact_Revenge("Resilient Impact Revenge", 0, 0, false, {
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
});

Ability Emergency_Regroup("Emergency Regroup", 0, 0, true, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(1.5),
        Shield(50, 2, 4)
    )
});

Ability Fierce_Cleansing_Strike("Fierce Cleansing Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetLowestHP(
        Remove(SHIELD|TAUNT),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Group_Fierce_Impact("Group Fierce Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetAllOpponents(
        Remove(SHIELD|TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

RevengeAbility Revenge_Group_Cunning_Strike("Revenge Group Cunning Strike", 0, 0, false, {
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
});

Ability Regroup("Regroup", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(2.),
        Shield(50, 2, 4)
    )
});

RevengeAbility Resilient_Rampage_Revenge("Resilient Rampage Revenge", 0, 0, false, {
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
});

Ability Random_Cunning_Strike("Random Cunning Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetRandom(
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        ReduceCritChance(100, 1, 2),
        ReduceDamage(50, 1, 2),
        Attack(1.)
    )
});

CounterAbility Power_Heal("Power Heal", {
    TargetSelf(
        Heal(0.3)
    )
});


ThreatenedAbility Alert_Assist("Alert Assist", 0, 0, true, {
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
});

Ability Group_Fierce_Decelerating_Strike("Group Fierce Decelerating Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetAllOpponents(
        Remove(SHIELD|TAUNT),
        Attack(1., BYPASS_ARMOR),
        ReduceSpeed(50, 2)
    )
});

Ability Fierce_Cleansing_Impact("Fierce Cleansing Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetLowestHP(
        Remove(SHIELD|TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

RevengeAbility Infectious_Revenge("Infectious Revenge", 0, 0, false, {
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
});

Ability Fierce_Decelerating_Rampage("Fierce Decelerating Rampage", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetLowestHP(
        Remove(SHIELD|TAUNT),
        Attack(2., BYPASS_ARMOR),
        ReduceSpeed(50, 2)
    )
});

RevengeAbility Braking_Revenge("Braking Revenge", 0, 0, false, {
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
});

RevengeAbility Waning_Revenge("Waning Revenge", 0, 0, false, {
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
});

CounterAbility Counter_Spike("Counter Spike", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    ),
    TargetTeam(
        IncreaseDamage(10, 2, 2)
    )
});


Ability Evasive_Fierce_Strike("Evasive Fierce Strike", 0, 0, false, {
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
});

Ability Enfeebling_Raking_Impact("Enfeebling Raking Impact", 0, 0, false, {
    TargetMostPositiveEffects(
        Remove(DODGE|CLOAK),
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Piercing_Destruction("Piercing Destruction", 0, 0, true, {
    TargetMostPositiveEffects(
        Remove(POSITIVE_EFFECTS),
        Rend(100, BYPASS_ARMOR)
    )
});

Ability Evasive_Piercing_Impact("Evasive Piercing Impact", 0, 0, false, {
    TargetLowestHP(
        Remove(SHIELD),
        Attack(1.5, BYPASS_ARMOR)
    ),
    TargetSelf(
        Dodge(75, 67, 2, 8)
    )
});

Ability Dispersed_Decelerating_Impact("Dispersed Decelerating Impact", 0, 0, false, {
    TargetAllOpponents(
        ReduceSpeed(50, 2),
        Attack(1.5)
    )
});

Ability Group_Necrotic_Strike("Group Necrotic Strike", 0, 0, false, {
    TargetAllOpponents(
        Remove(POSITIVE_EFFECTS),
        Attack(1., BYPASS_ARMOR)
    ),
    TargetSelf(
        DevourHeal(50, 2)
    )
});

Ability Cold_Blooded_Rampage("Cold-Blooded Rampage", 0, 0, false, {
    TargetLowestHP(
        Attack(2., PRECISE)
    )
});

Ability Daring_Group_Strike("Daring Group Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY | DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        Attack(1., BYPASS_ARMOR),
        ReduceDamage(50, 1, 2)
    )
});

RevengeAbility Revenge_Distracting_Rampage("Revenge Distracting Rampage", 0, 0, false, {
    TargetHighestDamage(
        Attack(2.),
        ReduceDamage(50, 2, 4)
    )
}, 0, 0, false, {
    TargetAllOpponents(
        Attack(2.),
        ReduceDamage(50, 2, 4)
    )
});

Ability Cleansing_Random_Impact("Cleansing Random Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetRandom(
        Attack(1.5)
    )
});

Ability Targeted_Cleansing_Impact("Targeted Cleansing Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetAllOpponents(
        Attack(1.5)
    )
});

RevengeAbility Slow_Piercing_Revenge("Slow Piercing Revenge", 0, 0, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Rend(40, BYPASS_ARMOR),
        ReduceSpeed(50, 2)
    )
}, 0, 0, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Rend(40, BYPASS_ARMOR),
        ReduceSpeed(50, 2)
    )
});

RevengeAbility Daring_Group_Revenge("Daring Group Revenge", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY|DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        Remove(TAUNT),
        Attack(1.5, BYPASS_ARMOR),
        ReduceDamage(50, 1, 2)
    )
}, 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY|DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        Remove(TAUNT),
        Attack(2, BYPASS_ARMOR),
        ReduceDamage(50, 1, 2)
    )
});

Ability Random_Daring_Rampage("Random Daring Rampage", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY|DAMAGE_OVER_TIME)
    ),
    TargetRandom(
        Attack(2., BYPASS_ARMOR),
        ReduceDamage(50, 1, 2)
    )
});

CounterAbility Counter_Vulnerability("Counter Vulnerability", {
    TargetAttacker(
        Attack(1.),
        ImposeVulnerability(50, 2, 1)
    )
});

Ability Group_Acceleration("Group Acceleration", 0, 1, true, {
    TargetTeam(
        Cleanse(REDUCED_SPEED),
        IncreaseSpeed(50, 3)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Random_Piercing_Rampage("Random Piercing Rampage", 0, 0, false, {
    TargetRandom(
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Stun_Pierce_And_Impact("Stun, Pierce And Impact", 0, 0, false, {
    TargetLowestHP(
        Attack(1.5, BYPASS_ARMOR),
        Stun(75, 1)
    )
});

Ability Cleansing_Random_Piercing_Rampage("Cleansing Random Piercing Rampage", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetRandom(
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Group_Cunning_Impact("Group Cunning Impact", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(1.5)
    )
});

Ability Squeeze_And_Strike("Squeeze And Strike", 0, 0, false, {
    TargetAllOpponents(
        Remove(POSITIVE_EFFECTS),
        Attack(1.)
    )
});

ThreatenedAbility Alert_Slither("Alert Slither", 0, 0, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(50, 67, 3, 4),
        IncreaseCritChance(50, 3, 3)
    ),
    TargetHighestDamage(
        ReduceDamage(50, 3, 6)
    )
}, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, 0, 0, true, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(75, 67, 3, 4),
        IncreaseCritChance(50, 3, 3)
    ),
    TargetHighestDamage(
        ReduceDamage(50, 3, 6)
    )
});

Ability Hard_Swallow("Hard Swallow", 0, 0, false, {
    TargetLowestHP(
        Attack(2.)
    ),
    TargetSelf(
        Heal(1.)
    )
});

Ability Venomous_Bite("Venomous Bite", 0, 0, true, {
    TargetHighestDamage(
        Attack(1.5, PRECISE),
        DamageOverTime(40, 2)
    )
});

Ability Total_Cleanse_And_Strike("Total Cleanse And Strike", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetAllOpponents(
        Attack(1.)
    )
});

ThreatenedCounterAbility Alert_Coil("Alert Coil", {
    TargetSelf(
            IncreaseDamage(5, 3, 3)
    )
}, [](Dino &self) { return self.total_health <= self.max_total_health * 0.5; }, {
    TargetSelf(
            IncreaseDamage(10, 3, 3)
    )
});

} // namespace boss

Ability Group_Defense_Shattering_Strike("Group Defense Shattering Strike", 0, 0, false, {
    TargetAllOpponents(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR|GROUP)
    )
});

Ability Group_Ferocity("Group Ferocity", 0, 2, true, {
    TargetTeam(
        Cleanse(REDUCED_DAMAGE | REDUCED_CRIT_CHANCE),
        IncreaseDamage(50, 2, 2)
    )
});

Ability Group_Shattering_Impact("Group Shattering Impact", 0, 0, false, {
    TargetAllOpponents(
        Remove(SHIELD | TAUNT),
        Attack(1.5, BYPASS_ARMOR|GROUP)
    )
});

Ability Shielded_Decelerating_Strike("Shielded Decelerating Strike", 0, 0, false, {
    TargetSelf(
        Shield(50, 1, 4)
    ),
    TargetLowestHP(
        ReduceSpeed(50, 2),
        Attack(1., PRECISE)
    )
});

Ability Group_Decelerating_Strike("Group Decelerating Strike", 0, 2, false, {
    TargetAllOpponents(
        ReduceSpeed(50, 2),
        Attack(1., GROUP)
    )
});

CounterAbility Decelerating_Counter("Decelerating Counter", {
    TargetAttacker(
        ReduceSpeed(50, 1),
        Attack(1.)
    )
});

Ability Defense_Shattering_Strike("Defense Shattering Strike", 0, 0, false, {
    TargetLowestHP(
        Remove(SHIELD|TAUNT),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Defense_Shattering_Impact("Defense Shattering Impact", 0, 1, false, {
    TargetLowestHP(
        Remove(SHIELD|TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Defense_Shattering_Rampage("Defense Shattering Rampage", 1, 1, false, {
    TargetHighestHP(
        Remove(SHIELD|TAUNT),
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Nullifying_Strike("Nullifying Strike", 0, 0, false, {
    TargetMostPositiveEffects(
        Remove(POSITIVE_EFFECTS),
        Attack(1.)
    )
});

Ability Nullifying_Impact("Nullifying Impact", 0, 2, false, {
    TargetMostPositiveEffects(
        Remove(POSITIVE_EFFECTS),
        Attack(1.5)
    )
});

Ability Group_Distraction("Group Distraction", 0, 2, true, {
    TargetAllOpponents(
        ReduceDamage(50, 2, 3)
    )
});

Ability Distraction("Distraction", 0, 0, false, {
    TargetHighestDamage(
        ReduceDamage(50, 1, 2),
        Attack(1.)
    )
});

Ability Cunning_Impact("Cunning Impact", 0, 1, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetHighestDamage(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE)
    )
});

Ability Resilient_Strike("Resilient Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetLowestHP(
        Remove(DODGE|CLOAK|INCREASED_SPEED),
        Attack(1.),
        ImposeVulnerability(50, 2, 2)
    )
});

Ability Group_Taunting_Shields("Group Taunting Shields", 0, 1, true, {
    TargetTeam(
        Shield(50, 2, 2)
    ),
    TargetSelf(
        Taunt(1)
    )
});

Ability Cleansing_Impact("Cleansing Impact", 0, 2, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetLowestHP(
        Attack(1.5)
    )
});

CounterAbility Greater_Rending_Counter_Attack("Greater Rending Counter-Attack", {
    TargetAttacker(
        Remove(SHIELD),
        Rend(33, BYPASS_ARMOR)
    )
});

Ability Group_Decelerating_Rampage("Group Decelerating Rampage", 0, 2, false, {
    TargetAllOpponents(
        ReduceSpeed(50, 2),
        Attack(2.)
    )
});

Ability Taunting_Bellow("Taunting Bellow", 0, 2, true, {
    TargetSelf(
        Shield(50, 1, 4),
        Taunt(1)
    ),
    TargetFastest(
        ReduceSpeed(50, 2)
    )
});

Ability Group_Mock_Block_And_Sock("Group Mock, Block And Sock", 0, 1, false, {
    TargetTeam(
        Shield(50, 2, 2)
    ),
    TargetSelf(
        Taunt(1)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

CounterAbility Armor_Piercing_Counter("Armor Piercing Counter", {
    TargetAttacker(
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Group_Strike("Group Strike", 0, 0, false, {
    TargetAllOpponents(
        Attack(1.)
    )
});

Ability High_Pounce("High Pounce", 0, 1, false, {
    TargetHighestDamage(
        Attack(2.),
        ReduceDamage(50, 1, 2)
    )
});

Ability Group_Wounding_Strike("Group Wounding Strike", 0, 0, false, {
    TargetAllOpponents(
        Attack(1.),
        DamageOverTime(20, 2)
    )
});

Ability Lethal_Wound("Lethal Wound", 0, 2, false, {
    TargetHighestHP(
        Attack(1.),
        DamageOverTime(33, 3)
    )
});

Ability Evasive_Strike("Evasive Strike", 0, 0, false, {
    TargetSelf(
        Dodge(75, 67, 1, 1)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Instant_Distraction("Instant Distraction", 0, 1, true, {
    TargetHighestDamage(
        ReduceDamage(100, 1, 2)
    )
});

Ability Taunting_Shields("Taunting Shields", 0, 0, false, {
    TargetLowestHP(
        Attack(1.)
    ),
    TargetSelf(
        Shield(50, 2, 4),
        Taunt(1)
    )
});

Ability Cunning_Strike("Cunning Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetLowestHP(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(1.)
    )
});

Ability Distracting_Impact("Distracting Impact", 0, 2, false, {
    TargetHighestDamage(
        ReduceDamage(50, 2, 4),
        Attack(1.5)
    )
});

Ability Cunning_Rampage("Cunning Rampage", 1, 1, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetHighestDamage(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(2.)
    )
});

Ability Group_Takedown("Group Takedown", 1, 2, true, {
    TargetTeam(
        Cleanse(REDUCED_DAMAGE|REDUCED_CRIT_CHANCE),
        IncreaseDamage(50, 2, 1)
    )
});

Ability Fierce_Strike("Fierce Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetLowestHP(
        Remove(SHIELD | TAUNT),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Killer_Instinct("Killer Instinct", 1, 1, true, {
    TargetLowestHP(
        Remove(SHIELD | TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Fierce_Impact("Fierce Impact", 0, 1, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetLowestHP(
        Remove(SHIELD | TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

ThreatenedAbility Protective_Alert_2("Protective Alert [2]", 0, 3, false, {
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
});

ThreatenedAbility Alert_Peck("Alert Peck", 0, 2, false, {
    TargetLowestHP(
        Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
        Rend(60, BYPASS_ARMOR)
    )
}, [](Dino &self) -> bool { return self.health <= self.max_health / 3; }, 1, 2, false, {
    TargetLowestHP(
        Remove(SHIELD|INCREASED_DAMAGE|INCREASED_CRIT_CHANCE),
        Rend(60, BYPASS_ARMOR)
    )
});

Ability Group_Cleansing_Strike("Group Cleansing Strike", 0, 0, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Ferocious_Strike("Ferocious Strike", 0, 3, false, {
    TargetSelf(
        IncreaseDamage(50, 3, 6)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Group_Warning_Squeal("Group Warning Squeal", 0, 3, true, {
    TargetTeam(
        Shield(50, 2, 4),
        IncreaseCritChance(20, 2, 2),
        IncreaseDamage(25, 2, 4)
    ),
    TargetFastest(
        ReduceSpeed(50, 2)
    )
});

Ability Rending_Attack("Rending Attack", 0, 1, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Rend(40, BYPASS_ARMOR)
    )
});

Ability Armor_Piercing_Impact("Armor Piercing Impact", 0, 1, false, {
    TargetLowestHP(
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Rending_Takedown("Rending Takedown", 1, 1, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Rend(60, BYPASS_ARMOR)
    )
});

CounterAbility Exposing_Counter("Exposing Counter", {
    TargetAttacker(
        ImposeVulnerability(50, 1, 2)
    )
});

Ability Intimidating_Impact("Intimidating Impact", 0, 1, false, {
    TargetLowestHP(
        Remove(SHIELD),
        Attack(1.5, BYPASS_ARMOR),
        ImposeVulnerability(50, 1, 2)
    )
});

Ability Cleansing_Rampage("Cleansing Rampage", 1, 2, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetHighestHP(
        Attack(2.)
    )
});

RevengeAbility Revenge_Taunting_Cloak("Revenge Taunting Cloak", 0, 3, true, {
    TargetSelf(
        Cloak(2., 75, 67, 2),
        Taunt(1)
    )
}, 0, 3, true, {
    TargetSelf(
        Cloak(2.5, 75, 67, 2),
        Taunt(1)
    )
});

Ability Ready_To_Crush("Ready To Crush", 0, 2, false, {
    TargetTeam(
        Cleanse(REDUCED_CRIT_CHANCE | REDUCED_DAMAGE),
        IncreaseCritChance(30, 4, 2),
        IncreaseDamage(50, 4, 2)
    )
});

ThreatenedAbility Alert_Fierce_Strike("Alert Fierce Strike", 0, 0, false, {
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
});

RevengeAbility Defense_Shattering_Revenge("Defense Shattering Revenge", 0, 1, false, {
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
});

Ability Dominant_Roar("Dominant Roar", 0, 2, true, {
    TargetTeam(
        IncreaseDamage(50, 2, 2)
    ),
    TargetAllOpponents(
        Attack(1., GROUP)
    ),
    TargetTeam(
        IncreaseSpeed(25, 1)
    )
});

Ability Fierce_Devouring_Rampage("Fierce Devouring Rampage", 1, 1, false, {
    TargetLowestHP(
        Remove(SHIELD | TAUNT),
        Attack(2., BYPASS_ARMOR)
    ),
    TargetSelf(
        DevourHeal(60, 4),
        Cleanse(VULNERABILITY)
    )
});

Ability Tip_The_Scales("Tip The Scales", 0, 1, true, {
    TargetAllOpponents(
        Remove(POSITIVE_EFFECTS)
    ),
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS)
    )
});

Ability Group_Taunting_Shields_Strike("Group Taunting Shields Strike", 0, 1, false, {
    TargetTeam(
        Shield(50, 2, 2)
    ),
    TargetSelf(
        Taunt(1)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Crushing_Prowl("Crushing Prowl", 0, 2, true, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        IncreaseCritChance(75, 2, 2),
        Dodge(75, 67, 1, 2)
    ),
    TargetTeam(
        IncreaseDamage(50, 4, 2),
        Cleanse(REDUCED_DAMAGE | REDUCED_CRIT_CHANCE)
    )
});

Ability Devouring_Wound("Devouring Wound", 0, 1, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Attack(1.5, BYPASS_ARMOR),
        DamageOverTime(20, 2)
    ),
    TargetSelf(
        DevourHeal(60, 4)
    ),
});

Ability Skirmish("Skirmish", 1, 1, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetAllOpponents(
        Remove(SHIELD | TAUNT),
        Attack(2., BYPASS_ARMOR|GROUP)
    )
});

CounterAbility Defense_Shattering_Counter_Attack("Defense Shattering Counter-Attack", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(0.5, BYPASS_ARMOR)
    )
});

Ability Cleansing_Group_Destroyer("Cleansing Group Destroyer", 0, 1, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS)
    ),
    TargetAllOpponents(
        Remove(SHIELD|TAUNT),
        Attack(1.5, BYPASS_ARMOR)
    )
});

Ability Fierce_Rampage("Fierce Rampage", 1, 1, false, {
    TargetSelf(
        Cleanse(VULNERABILITY)
    ),
    TargetHighestHP(
        Remove(SHIELD|TAUNT),
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Instant_Charge("Instant Charge", 1, 2, true, {
    TargetHighestDamage(
        Attack(1.),
        Stun(75, 1)
    )
});

Ability Tough_Group_Cunning_Strike("Tough Group Cunning Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(1.)
    )
});

Ability Accelerating_Team_Heal("Accelerating Team Heal", 0, 2, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(1.),
        IncreaseSpeed(25, 1)
    )
});

Ability Distracting_Team_Heal("Distracting Team Heal", 0, 2, true, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(2.)
    ),
    TargetHighestDamage(
        ReduceDamage(25, 2, 2)
    )
});

RevengeAbility Revenge_Cunning_Rampage("Revenge Cunning Rampage", 1, 1, false, {
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
});

CounterAbility Darting_Counter("Darting Counter", {
    TargetAttacker(
        Attack(1.)
    ),
    TargetSelf(
        IncreaseSpeed(25, 1)
    )
});

Ability Sideflap("Sideflap", 0, 0, true, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(100, 67, 1, 2),
        IncreaseSpeed(10, 2),
        Taunt(1.)
    )
});

Ability Fearless_Flap("Fearless Flap", 0, 2, false, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(100, 67, 2, 2),
        IncreaseSpeed(10, 2)
    ),
    TargetAllOpponents(
        ReduceDamage(50, 2, 2),
        Attack(1.)
    )
});

Ability Group_Instant_Distraction("Group Instant Distraction", 0, 2, true, {
    TargetAllOpponents(
        ReduceDamage(100, 1, 2)
    )
});

CounterAbility Defense_Shattering_Counter("Defense Shattering Counter", {
    TargetAttacker(
        Remove(SHIELD),
        Attack(1., BYPASS_ARMOR)
    )
});

Ability Minor_Rending_Lockdown("Minor Rending Lockdown", 0, 0, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Rend(34, BYPASS_ARMOR),
        UnableToSwap(1)
    )
});

Ability Wounding_Devouring_Impact("Wounding Devouring Impact", 0, 2, false, {
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
});

Ability Minor_Rending_Attack("Minor Rending Attack", 0, 0, false, {
    TargetLowestHP(
        Remove(SHIELD),
        Rend(34, BYPASS_ARMOR)
    )
});

Ability Prowl("Prowl", 0, 0, true, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        Dodge(75, 67, 1, 2),
        IncreaseCritChance(50, 3, 2)
    )
});

CounterAbility Medium_Counter_Attack("Medium Counter-Attack", {
    TargetAttacker(
        Attack(0.5)
    )
});

ThreatenedAbility Alert_Instant_Heal("Alert Instant Heal", 1, 2, true, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(1.5)
    )
}, [](Dino &self) -> bool { return self.total_health <= self.max_total_health * 0.5; }, 1, 2, true, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(2.)
    )
});

Ability Greater_Group_Heal("Greater Group Heal", 0, 2, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(2.)
    )
});

RevengeAbility Resilient_Rampage_Revenge("Resilient Rampage Revenge", 1, 1, false, {
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
});

CounterAbility Counter_Power_Heal("Counter Power Heal", {
    TargetSelf(
        FixedHeal(6)
    )
});

Ability Superiority_Strike("Superiority Strike", 0, 0, false, {
    TargetSelf(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetFastest(
        ReduceSpeed(50, 1),
        Attack(1., PRECISE)
    )
});

Ability Mutual_Fury("Mutual Fury", 0, 1, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        IncreaseDamage(50, 3, 2),
        IncreaseSpeed(10, 2)
    ),
    TargetAllOpponents(
        IncreaseDamage(50, 2, 1)
    )
});

Ability Dig_In("Dig In", 0, 2, true, {
    TargetSelf(
        Cleanse(NEGATIVE_EFFECTS),
        IncreaseSpeed(10, 2),
        Shield(50, 1, 8),
        Heal(1.)
    )
});

RevengeAbility Group_Revenge_Shattering_Rampage("Group Revenge Shattering Rampage", 1, 2, false, {
    TargetHighestHP(
        Remove(SHIELD),
        Attack(2., BYPASS_ARMOR)
    )
}, 1, 2, false, {
    TargetAllOpponents(
        Remove(SHIELD),
        Attack(2., BYPASS_ARMOR)
    )
});

Ability Group_Superiority("Group Superiority", 0, 0, false, {
    TargetTeam(
        Cleanse(REDUCED_DAMAGE)
    ),
    TargetFastest(
        ReduceSpeed(50, 1),
        Attack(1., PRECISE)
    )
});

Ability Lesser_Group_Heal("Lesser Group Heal", 0, 2, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(1.)
    )
});

Ability Group_Acceleration("Group Acceleration", 0, 1, true, {
    TargetTeam(
        Cleanse(REDUCED_SPEED),
        IncreaseSpeed(50, 3)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Greater_Emergency_Heal("Greater Emergency Heal", 0, 2, true, {
    TargetLowestHPTeammate(
        Cleanse(NEGATIVE_EFFECTS),
        Heal(2.)
    )
});

Ability Instant_Decelerating_Precision("Instant Decelerating Precision", 0, 0, true, {
    TargetSelf(
        Shield(50, 1, 4)
    ),
    TargetFastest(
        ReduceSpeed(50, 3),
        Attack(1., PRECISE)
    )
});

Ability Group_Cleansing_Fatal_Strike("Group Cleansing Fatal Strike", 0, 3, false, {
    TargetTeam(
        Cleanse(NEGATIVE_EFFECTS),
        IncreaseDamage(50, 3, 6)
    ),
    TargetLowestHP(
        Attack(1.)
    )
});

Ability Precise_Distracting_Impact("Precise Distracting Impact", 0, 1, false, {
    TargetLowestHP(
        Attack(1.5, PRECISE),
        ReduceDamage(50, 1, 2)
    )
});

Ability Group_Cunning_Rampage("Group Cunning Rampage", 2, 1, false, {
    TargetSelf(
        Cleanse(DAMAGE_OVER_TIME)
    ),
    TargetAllOpponents(
        ReduceDamage(50, 1, 2),
        ReduceCritChance(100, 1, 2),
        Remove(INCREASED_CRIT_CHANCE|INCREASED_DAMAGE),
        Attack(2.)
    )
});

CounterAbility Raking_Counter_Attack("Raking Counter-Attack", {
    TargetAttacker(
        Remove(CLOAK|DODGE),
        Attack(1., BYPASS_ARMOR)
    )
});

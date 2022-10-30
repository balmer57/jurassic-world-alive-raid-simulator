#include "dinodex.h"
#include "actions.h"
#include "modifiers.h"
#include "abilitydex.h"

using namespace actions;
using namespace std;

//
// boss dex
//

namespace boss {

DinoKind BrachiosaurusBoss("Brachiosaurus Boss", EPIC, 1, 24000, 1350, 109, 0, 15, 50, 85, 100, 80, 100, 100, 0, 0, 50, {
    { // Round 1
        &Group_Shield_Strike,
        &Group_Resilient_Strike,
        &Resilient_Vulnerability_Rampage
    }, { // Round 2
        &Shielded_Group_Strike_Brachiosaurus,
        &Group_Resilient_Impact
    }, { // Round 3
        &Group_Shield_Strike,
        &Boom,
        &Shielded_Resilient_Strike,
        &Resilient_Impact
    }
}, nullptr);

DinoKind MeiolaniaBoss("Meiolania boss", RARE, 1, 9500, 825, 105, 50, 5, 0, 70, 50, 70, 80, 100, 0, 0, 50, {
    { // Round 1
        &Steady_Group_Vulnerability_Strike,
        &Resilient_Impact,
        &Devastation
    }, { // Round 2
        &Vulnerability_Impact,
        &Group_Superior_Vulnerability,
        &Group_Devastation
    }
}, nullptr);

DinoKind FukuimimusBoss("Fukuimimus boss", LEGENDARY, 1, 15000, 1500, 123, 0, 25, 100, 90, 50, 85, 75, 95, 0, 0, 15, {
    { // Round 1
        &Alert_Mimic,
        &Protective_Strike,
        &Random_Cunning_Rampage
    }, { // Round 2
        &Alert_Mimic,
        &Cunning_Cleanse_Revenge,
        &Resilient_Cleanse_Revenge
    }, { // Round 3
        &Alert_Mimic,
        &Protective_Strike,
        &Revenge_Cunning_Impact,
        &Determined_Group_Rampage
    }
}, &Ferocious_Feathers);

DinoKind TroodoboaBoss("Troodoboa Boss", UNIQUE, 1, 16666, 1300, 120, 0, 10, 0, 90, 60, 80, 75, 100, 0, 100, 15, {
    { // Round 1
        &Instant_Shielded_Decelerating_Strike,
        &Targeted_Cleansing_Strike,
        &Group_Ferocious_Strike
    }, { // Round 2
        &Instant_Shielded_Decelerating_Strike,
        &Coiling_Rampage,
        &Targeted_Cleansing_Impact_1_5,
        &Raking_Piercing_Strike
    }, { // Round 3
        &Instant_Shielded_Decelerating_Strike,
        &Coiling_Rampage,
        &Targeted_Cleansing_Impact_2_0,
        &Group_Ferocious_Impact
    }
}, nullptr);

DinoKind GlyptocerasBoss("Glyptoceras Boss #1", LEGENDARY, 1, 13000, 1350, 110, 15, 15, 25, 80, 75, 70, 50, 95, 0, 0, 25, {
    { // Round 1
        &Primal_Instant_Charge,
        &Resilient_Group_Impact,
        &Blind_Rampage
    }, { // Round 2
        &Instant_Defense_Charge,
        &Resilient_Group_Strike,
        &Random_Cunning_Rampage,
        &Critical_Group_Impact
    }, { // Round 3
        &Primal_Instant_Charge,
        &Resilient_Group_Impact,
        &Instant_Defense_Charge,
        &Bully_Impact
    }
}, nullptr);

DinoKind SmilonemysBoss("Smilonemys Boss #1", UNIQUE, 1, 20000, 1500, 127, 50, 5, 0, 80, 50, 80, 50, 100, 0, 0, 50, {
    { // Round 1
        &Shielded_Group_Strike_Smilonemys,
        &Primal_Prowl,
        &Precise_Pounce
    }, { // Round 2
        &Shielded_Group_Strike_Smilonemys,
        &Prowling_Shields,
        &Cautious_Precise_Pounce
    }
}, nullptr);

DinoKind MortemRexBoss("Mortem Rex Boss", APEX, 1, 25000, 2000, 108, 0, 40, 0, 80, 50, 80, 0, 100, 0, 0, 50, {
    { // Round 1
        &Primal_Tail_Whip,
        &Defense_Shattering_Rampage,
        &Cleansing_Random_Shattering_Strike
    }, { // Round 2
        &Cleansing_Primal_Tail_Whip,
        &Defense_Shattering_Rampage,
        &Defense_Shattering_Impact
    }
}, nullptr);

DinoKind ParasauthopsBoss("Parasauthops Boss", UNIQUE, 1, 14500, 1500, 112, 0, 20, 0, 70, 75, 80, 50, 100, 0, 0, 35, {
    { // Round 1
        &Random_Cunning_Impact,
        &Resilient_Impact_Revenge,
        &Emergency_Regroup,
        &Fierce_Cleansing_Strike
    }, { // Round 2
        &Group_Fierce_Impact,
        &Emergency_Regroup,
        &Revenge_Group_Cunning_Strike,
        &Resilient_Vulnerability_Rampage
    }, { // Round 3
        &Regroup,
        &Resilient_Rampage_Revenge,
        &Group_Fierce_Impact,
        &Random_Cunning_Strike
    }
}, &Power_Heal);

DinoKind ImperatosuchusBoss("Imperatosuchus Boss", APEX, 1, 16000, 1450, 115, 15, 5, 75, 90, 75, 85, 80, 100, 0, 0, 60, {
    { // Round 1
        &Alert_Assist,
        &Group_Fierce_Decelerating_Strike,
        &Fierce_Cleansing_Impact
    }, { // Round 2
        &Alert_Assist,
        &Infectious_Revenge,
        &Group_Fierce_Decelerating_Strike,
        &Fierce_Decelerating_Rampage
    }, { // Round 3
        &Alert_Assist,
        &Braking_Revenge,
        &Waning_Revenge,
        &Group_Fierce_Decelerating_Strike
    }
}, &Counter_Spike);

DinoKind AlacranixBoss("Alacranix Boss", APEX, 1, 15000, 1550, 116, 40, 20, 50, 100, 50, 90, 20, 100, 0, 100, 15, {
    { // Round 1
        &Evasive_Fierce_Strike,
        &Group_Fierce_Decelerating_Strike,
        &Enfeebling_Raking_Impact,
        &Piercing_Destruction
    }, { // Round 2
        &Evasive_Piercing_Impact,
        &Dispersed_Decelerating_Impact,
        &Piercing_Destruction,
        &Group_Necrotic_Strike
    }, { // Round 3
        &Group_Necrotic_Strike,
        &Piercing_Destruction,
        &Cold_Blooded_Rampage
    }
}, nullptr);

DinoKind AndrewtopsBoss("Andrewtops Boss", UNIQUE, 1, 11000, 1350, 122, 15, 20, 0, 80, 45, 85, 50, 95, 0, 0, 40, {
    { // Round 1
        &Daring_Group_Strike,
        &Revenge_Distracting_Rampage,
        &Cleansing_Random_Impact
    }, { // Round 2
        &Targeted_Cleansing_Impact,
        &Slow_Piercing_Revenge,
        &Daring_Group_Revenge
    }, { // Round 3
        &Targeted_Cleansing_Impact,
        &Slow_Piercing_Revenge,
        &Revenge_Distracting_Rampage,
        &Random_Daring_Rampage
    }
}, &Counter_Vulnerability);

DinoKind CeramagnusBoss("Ceramagnus Boss", APEX, 1, 11500, 1600, 114, 30, 20, 50, 80, 50, 80, 100, 100, 0, 0, 0, {
    { // Round 1
        &Group_Acceleration,
        &Random_Piercing_Rampage,
        &Primal_Instant_Charge,
        &Random_Piercing_Rampage
    }, { // Round 2
        &Group_Acceleration,
        &Stun_Pierce_And_Impact,
        &Cleansing_Random_Piercing_Rampage,
        &Primal_Instant_Charge
    }, { // Round 3
        &Stun_Pierce_And_Impact,
        &Cleansing_Random_Piercing_Rampage,
        &Primal_Instant_Charge
    }
}, nullptr);

DinoKind HydraBoaBoss("Hydra Boa Boss", APEX, 1, 14000, 1500, 118, 10, 25, 75, 80, 80, 85, 75, 95, 0, 0, 35, {
    { // Round 1
        &Group_Cunning_Impact,
        &Squeeze_And_Strike,
        &Cold_Blooded_Rampage
    }, { // Round 2
        &Alert_Slither,
        &Squeeze_And_Strike,
        &Hard_Swallow
    }, { // Round 3
        &Alert_Slither,
        &Squeeze_And_Strike,
        &Venomous_Bite,
        &Total_Cleanse_And_Strike
    }
}, &Alert_Coil);

} // namespace boss

//
// minion dex
//

DinoKind EntelodonMinion("Group Shattering Minion", RARE, 1, 3600, 1000, 122, 0, 30, 0, 0, 0, 0, 0, 100, 0, 0, 0, {
    &Group_Defense_Shattering_Strike,
    &Group_Ferocity,
    &Group_Shattering_Impact
}, nullptr);

DinoKind MiragaiaMinion("Deceleration Minion", COMMON, 1, 4050, 1000, 112, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Shielded_Decelerating_Strike,
    &Group_Decelerating_Strike
}, &Decelerating_Counter);

DinoKind GorgosaurusMinion("Shattering Minion", RARE, 1, 4500, 1750, 103, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Defense_Shattering_Strike,
    &Defense_Shattering_Impact,
    &Defense_Shattering_Rampage
}, nullptr);

DinoKind KoolasuchusMinion("Nullifying Minion", RARE, 1, 4500, 1100, 127, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Nullifying_Strike,
    &Nullifying_Impact,
    &Group_Distraction
}, nullptr);

DinoKind MonolophosaurusMinion("Distraction Minion", COMMON, 1, 3000, 1350, 129, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Distraction,
    &Cunning_Impact
}, nullptr);

DinoKind CarnotaurusMinion("Counter-Attack Minion", RARE, 1, 4500, 1000, 104, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Resilient_Strike,
    &Group_Taunting_Shields,
    &Cleansing_Impact
}, &Greater_Rending_Counter_Attack);

DinoKind WuerhosaurusMinion("Deceleration Minion", RARE, 1, 4800, 1000, 115, 25, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Resilient_Strike,
    &Group_Decelerating_Rampage,
    &Taunting_Bellow
}, nullptr);

DinoKind MajungasaurusMinion("Counter-Attack Minion", COMMON, 1, 3450, 1300, 105, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Resilient_Strike,
    &Group_Mock_Block_And_Sock
}, &Armor_Piercing_Counter);

DinoKind VelociraptorMinion("Damage Minion", COMMON, 1, 2500, 1500, 131, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Group_Strike,
    &High_Pounce
}, nullptr);

DinoKind SuchomimusMinion("Dot Minion", COMMON, 1, 3900, 900, 104, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Group_Wounding_Strike,
    &Lethal_Wound
}, nullptr);

DinoKind GallimimusMinion("Dodge Minion", COMMON, 1, 2700, 1400, 130, 0, 5, 100, 100, 100, 0, 0, 100, 0, 0, 0, {
    &Evasive_Strike,
    &Instant_Distraction
}, nullptr);

DinoKind ScolosaurusMinion("Shield Minion", COMMON, 1, 5500, 1000, 110, 25, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Taunting_Shields,
    &Group_Taunting_Shields
}, nullptr);

DinoKind DilophosaurusMinion("Distraction Minion", RARE, 1, 3600, 1250, 129, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Cunning_Strike,
    &Distracting_Impact,
    &Cunning_Rampage
}, nullptr);

DinoKind BaryonyxMinion("Damage Increase Minion", EPIC, 1, 4200, 1300, 126, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, {
    &Defense_Shattering_Strike,
    &Group_Takedown,
    &Defense_Shattering_Rampage
}, nullptr);

//
// dino dex
//

DinoKind Albertosaurus("Albertosaurus", RARE, 1, 4350, 1750, 106, 0, 30, 100, 50, 0, 0, 100, 0, 100, 0, 25, {
    &Fierce_Strike,
    &Killer_Instinct,
    &Fierce_Impact
}, nullptr);

DinoKind Allodrigues("Allodrigues", UNIQUE, 3, 3300, 1750, 130, 0, 15, 0, 50, 75, 66, 100, 67, 100, 0, 0, {
    &Fierce_Strike,
    &Protective_Alert_2,
    &Cunning_Rampage,
    &Alert_Peck
}, nullptr);

DinoKind Andrewtherium("Andrewtherium", EPIC, 1, 3600, 1300, 119, 5, 25, 100, 0, 50, 0, 50, 50, 100, 0, 50, {
    &Group_Cleansing_Strike,
    &Ferocious_Strike,
    &Group_Warning_Squeal,
    &Rending_Attack
}, nullptr);

DinoKind Andrewtodon("Andrewtodon", EPIC, 1, 3450, 1300, 112, 15, 25, 0, 0, 0, 0, 100, 50, 0, 0, 0, {
    &Fierce_Strike,
    &Armor_Piercing_Impact,
    &Cleansing_Impact,
    &Rending_Takedown
}, &Exposing_Counter);

DinoKind Indotaurus("Indotaurus", UNIQUE, 1, 4650, 1600, 106, 0, 20, 0, 0, 0, 34, 75, 50, 67, 0, 50, {
    &Fierce_Strike,
    &Intimidating_Impact,
    &Cleansing_Rampage,
    &Revenge_Taunting_Cloak
}, &Greater_Rending_Counter_Attack);

DinoKind Irritator("Irritator", RARE, 1, 4500, 1000, 126, 0, 30, 0, 0, 0, 0, 100, 0, 0, 0, 100, {
    &Defense_Shattering_Strike,
    &Ready_To_Crush,
    &Group_Takedown
}, nullptr);

DinoKind Rexy("Rexy", LEGENDARY, 1, 4950, 1850, 106, 0, 45, 0, 75, 0, 75, 100, 75, 0, 0, 100, {
    &Alert_Fierce_Strike,
    &Defense_Shattering_Revenge,
    &Dominant_Roar,
    &Fierce_Devouring_Rampage
}, nullptr);

DinoKind Skoolasaurus("Skoolasaurus", LEGENDARY, 1, 4500, 1000, 124, 30, 5, 0, 0, 0, 0, 100, 75, 0, 0, 50, {
    &Resilient_Strike,
    &Tip_The_Scales,
    &Group_Distraction,
    &Group_Taunting_Shields_Strike
}, nullptr);

DinoKind Thylaconyx("Thylaconyx", LEGENDARY, 1, 4800, 1250, 122, 0, 25, 0, 25, 0, 75, 100, 100, 0, 0, 100, {
    &Defense_Shattering_Strike,
    &Crushing_Prowl,
    &Devouring_Wound,
    &Skirmish
}, &Defense_Shattering_Counter_Attack);

DinoKind Thoradolosaur("Thoradolosaur", UNIQUE, 1, 4500, 1750, 105, 0, 30, 0, 75, 0, 0, 0, 50, 100, 0, 50, {
    &Fierce_Strike,
    &Cleansing_Group_Destroyer,
    &Fierce_Rampage,
    &Instant_Charge
}, nullptr);

DinoKind Diloracheirus("Diloracheirus", UNIQUE, 1, 4470, 1650, 128, 0, 10, 0, 100, 0, 0, 0, 100, 0, 0, 0, {
    &Tough_Group_Cunning_Strike,
    &Accelerating_Team_Heal,
    &Distracting_Team_Heal,
    &Revenge_Cunning_Rampage
}, &Darting_Counter);

DinoKind Poukandactylus("Poukandactylus", UNIQUE, 1, 4050, 1200, 127, 0, 15, 0, 0, 50, 0, 50, 100, 75, 0, 50, {
    &Sideflap,
    &Distracting_Impact,
    &Fearless_Flap,
    &Group_Instant_Distraction
}, &Defense_Shattering_Counter);

DinoKind ThylosIntrepidus("Thylos Intrepidus", UNIQUE, 3, 3900, 1400, 120, 0, 40, 0, 50, 0, 33, 100, 0, 100, 100, 0, {
    &Minor_Rending_Lockdown,
    &Crushing_Prowl,
    &Wounding_Devouring_Impact,
    &Rending_Takedown
}, nullptr);

DinoKind MarsupialLion("Marsupial Lion", RARE, 1, 4050, 1000, 117, 0, 40, 0, 0, 0, 0, 100, 0, 0, 0, 50, {
    &Minor_Rending_Attack,
    &Rending_Takedown,
    &Prowl
}, &Medium_Counter_Attack);

DinoKind Parasauthops("Parasauthops", UNIQUE, 1, 4650, 1550, 109, 0, 15, 0, 75, 50, 0, 0, 33, 0, 100, 0, {
    &Tough_Group_Cunning_Strike,
    &Alert_Instant_Heal,
    &Greater_Group_Heal,
    &Resilient_Rampage_Revenge
}, &Counter_Power_Heal);

DinoKind Enteloceros("Enteloceros", LEGENDARY, 1, 4500, 1300, 126, 20, 10, 0, 0, 0, 50, 50, 100, 67, 0, 100, {
    &Superiority_Strike,
    &Mutual_Fury,
    &Dig_In,
    &Group_Revenge_Shattering_Rampage
}, nullptr);

DinoKind Tuoramoloch("Tuoramoloch", UNIQUE, 1, 4200, 1500, 126, 0, 5, 0, 0, 50, 0, 100, 100, 50, 0, 0, {
    &Group_Superiority,
    &Lesser_Group_Heal,
    &Group_Acceleration,
    &Greater_Emergency_Heal
}, nullptr);

DinoKind Troodoboa("Troodoboa", UNIQUE, 1, 3900, 1200, 117, 0, 10, 0, 100, 100, 0, 75, 75, 0, 100, 0, {
    &Instant_Decelerating_Precision,
    &Group_Cleansing_Fatal_Strike,
    &Precise_Distracting_Impact,
    &Group_Cunning_Rampage
}, &Raking_Counter_Attack);

using namespace boss;

std::map<std::string, std::vector<Dino>> BossDex = {
// Rare
    make_pair<string, vector<Dino>>("Meiolania", {Dino(0, 0, 8, 0, 0, 0, &MeiolaniaBoss)}),
// Epic
    make_pair<string, vector<Dino>>("Brachiosaurus", {Dino(0, 0, 14, 0, 0, 0, &BrachiosaurusBoss)}),
// Legendary
    make_pair<string, vector<Dino>>("Fukuimimus", {Dino(0, 0, 19, 7, 7, 5, &FukuimimusBoss), Dino(0, 5, 18, 9, 5, 3, &EntelodonMinion), Dino(0, 6, 18, 7, 5, 6, &MiragaiaMinion)}),
    make_pair<string, vector<Dino>>("Glyptoceras", {Dino(0, 0, 19, 5, 3, 8, &GlyptocerasBoss), Dino(0, 5, 17, 7, 6, 1, &KoolasuchusMinion), Dino(0, 6, 17, 8, 3, 3, &WuerhosaurusMinion)}),
// Unique
    make_pair<string, vector<Dino>>("Troodoboa", {Dino(0, 0, 25, 10, 10, 5, &TroodoboaBoss), Dino(0, 5, 24, 4, 10, 10, &GorgosaurusMinion), Dino(0, 6, 24, 10, 4, 10, &KoolasuchusMinion)}),
    make_pair<string, vector<Dino>>("Smilonemys", {Dino(0, 0, 22, 6, 9, 7, &SmilonemysBoss), Dino(0, 5, 17, 7, 6, 1, &MonolophosaurusMinion), Dino(0, 6, 17, 8, 3, 3, &CarnotaurusMinion)}),
    make_pair<string, vector<Dino>>("Parasauthops", {Dino(0, 0, 24, 8, 8, 8, &ParasauthopsBoss), Dino(0, 5, 23, 9, 4, 10, &MajungasaurusMinion), Dino(0, 6, 23, 12, 3, 8, &SuchomimusMinion)}),
    make_pair<string, vector<Dino>>("Andrewtops", {Dino(0, 0, 24, 8, 12, 4, &AndrewtopsBoss), Dino(0, 5, 23, 12, 7, 4, &ScolosaurusMinion), Dino(0, 6, 23, 9, 9, 6, &DilophosaurusMinion)}),
// Apex
    make_pair<string, vector<Dino>>("MortemRex", {Dino(0, 0, 30, 15, 15, 0, &MortemRexBoss), Dino(0, 5, 29, 10, 10, 9, &MajungasaurusMinion), Dino(0, 6, 29, 4, 10, 15, &VelociraptorMinion)}),
    make_pair<string, vector<Dino>>("Imperatosuchus", {Dino(0, 0, 30, 10, 13, 7, &ImperatosuchusBoss), Dino(0, 5, 29, 8, 5, 10, &MajungasaurusMinion), Dino(0, 6, 29, 8, 2, 10, &KoolasuchusMinion)}),
    make_pair<string, vector<Dino>>("Alacranix", {Dino(0, 0, 30, 10, 14, 5, &AlacranixBoss), Dino(0, 5, 28, 5, 5, 18, &GallimimusMinion), Dino(0, 6, 28, 5, 13, 10, &SuchomimusMinion)}),
    make_pair<string, vector<Dino>>("Ceramagnus", {Dino(0, 0, 30, 15, 15, 0, &CeramagnusBoss), Dino(0, 5, 29, 20, 8, 1, &KoolasuchusMinion), Dino(0, 6, 29, 9, 20, 0, &MiragaiaMinion)}),
    make_pair<string, vector<Dino>>("HydraBoa", {Dino(0, 0, 30, 10, 15, 5, &HydraBoaBoss), Dino(0, 5, 29, 10, 15, 4, &BaryonyxMinion), Dino(0, 6, 29, 15, 9, 5, &MajungasaurusMinion)}),
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

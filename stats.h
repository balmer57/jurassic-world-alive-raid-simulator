#ifndef JWA_SIMULATOR_STATS_H_
#define JWA_SIMULATOR_STATS_H_

#include <vector>

typedef enum {
	RESULT_OUT_OF_TURNS = -2,
	RESULT_DEFEAT = -1,
	RESULT_WIN = 1
} BattleResult;

class Stats
{
	static unsigned int win_count;
	static unsigned int defeat_count;
	static unsigned int out_of_turns_count;
	static std::vector< std::vector< std::vector<int> > > death_count;
	static std::vector< std::vector< std::vector<int> > > min_hp;
	static std::vector< std::vector<int> > turns_in_rounds;
	static unsigned int current_turn;
	static unsigned int current_turn_in_round;
	static unsigned int current_round;
	static std::vector<bool> was_killed_this_turn;
	static bool stats_inited;

public:
	static void Init(int team_size, int turns_count, int round_count);
	static int GetWinCount() {return win_count;}
	static int GetDefeatCount() {return defeat_count;}
	static int GetOutOfTurnsCount() {return out_of_turns_count;}
	static std::vector< std::vector<int> > GetMinHP(int i) {return min_hp[i];}
	static std::vector< std::vector<int> > GetDeaths(int i) {return death_count[i];}
	static std::vector<int> GetTurnCount(int i) {return turns_in_rounds[i];}

	static void ResetTurn();
	static void NextTurn();
	static void NextRound();
	static void RegisterHit(int target, int hp);
	static void RegisterResult(BattleResult result);
};


#endif /* JWA_SIMULATOR_STATS_H_ */

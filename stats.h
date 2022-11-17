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
	static int win_count;
	static int defeat_count;
	static int out_of_turns_count;
	static std::vector< std::vector<int> > death_count;
	static std::vector< std::vector<int> > min_hp;
	static int current_turn;
	static std::vector<bool> was_killed_this_turn;
public:
	static void Init(int team_size, int turns_count);
	static int GetWinCount() {return win_count;}
	static int GetDefeatCount() {return defeat_count;}
	static int GetOutOfTurnsCount() {return out_of_turns_count;}
	static std::vector< int > GetMinHP(int i) {return min_hp[i];}
	static std::vector<int> GetDeaths(int i) {return death_count[i];}

	static void ResetTurn();
	static void NextTurn();
	static void RegisterHit(int target, int hp);
	static void RegisterResult(BattleResult result);
};


#endif /* JWA_SIMULATOR_STATS_H_ */

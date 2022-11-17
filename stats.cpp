#include "stats.h"
#include <vector>

int Stats::current_turn = 0;
int Stats::current_turn_in_round = 0;
int Stats::current_round = 0;

int Stats::win_count = 0;
int Stats::defeat_count = 0;
int Stats::out_of_turns_count = 0;
std::vector<bool> Stats::was_killed_this_turn;
std::vector< std::vector<int> > Stats::min_hp;
std::vector< std::vector<int> > Stats::death_count;
std::vector<int> Stats::min_turns_count;
std::vector<int> Stats::max_turns_count;
bool Stats::stats_inited = false;

void Stats::RegisterResult(BattleResult result)
{
	if (stats_inited)
	{
		switch (result)
		{
			case RESULT_OUT_OF_TURNS:
				out_of_turns_count++;
				break;
			case RESULT_DEFEAT:
				defeat_count++;
				break;
			case RESULT_WIN:
				win_count++;
				break;
		}
		NextRound();
	}
}

void Stats::RegisterHit(int target, int hp)
{
	if (stats_inited)
	{
		if ((min_hp[target][current_turn] > hp) || (min_hp[target][current_turn] == -1))
		{
			min_hp[target][current_turn] = hp;
		}
		if ((hp == 0) && !was_killed_this_turn[target])
		{
			was_killed_this_turn[target] = true;
			death_count[target][current_turn]++;
		}
	}
}

void Stats::NextTurn()
{
	if (stats_inited)
	{
		current_turn++;
		current_turn_in_round++;
		for (unsigned int j = 0; j < was_killed_this_turn.size(); j++)
		{
			was_killed_this_turn[j] = false;
		}
	}
}

void Stats::NextRound()
{
	if (stats_inited)
	{
		if ((min_turns_count[current_round] > current_turn_in_round) || (min_turns_count[current_round] == -1))
		{
			min_turns_count[current_round] = current_turn_in_round;
		}
		if ((max_turns_count[current_round] < current_turn_in_round) || (max_turns_count[current_round] == -1))
		{
			max_turns_count[current_round] = current_turn_in_round;
		}
		current_round++;
		current_turn_in_round = 0;
	}
}

void Stats::ResetTurn()
{
	if (stats_inited)
	{
		current_round = 0;
		current_turn = 0;
		current_turn_in_round = 0;
		for (unsigned int j = 0; j < was_killed_this_turn.size(); j++)
		{
			was_killed_this_turn[j] = false;
		}
	}
}

void Stats::Init(int team_size, int turns_count, int round_count)
{
	stats_inited = true;
	win_count = 0;
	defeat_count = 0;
	out_of_turns_count = 0;
	current_turn = 0;

	was_killed_this_turn.resize(team_size);

	min_hp.resize(team_size);
	for (int i = 0; i < team_size; i++)
	{
		min_hp[i].resize(turns_count);
		for (int j = 0; j < turns_count; j++)
		{
			min_hp[i][j] = -1;
		}
	}

	death_count.resize(team_size);
	for (int i = 0; i < team_size; i++)
	{
		death_count[i].resize(turns_count);
	}

	min_turns_count.resize(round_count);
	max_turns_count.resize(round_count);
	for (int j = 0; j < round_count; j++)
	{
		min_turns_count[j] = -1;
		max_turns_count[j] = -1;
	}

}

#include "stats.h"
#include <vector>

unsigned int Stats::current_turn = 0;
unsigned int Stats::current_turn_in_round = 0;
unsigned int Stats::current_round = 0;

unsigned int Stats::win_count = 0;
unsigned int Stats::defeat_count = 0;
unsigned int Stats::out_of_turns_count = 0;
std::vector<bool> Stats::was_killed_this_turn;
std::vector< std::vector< std::vector<int> > > Stats::min_hp;
std::vector< std::vector< std::vector<int> > > Stats::death_count;
std::vector< std::vector<int> > Stats::turns_in_rounds;
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
		if (min_hp[target][current_round].size() <= current_turn_in_round)
		{
			for(unsigned int i = 0; i < min_hp.size(); i++)
			{
				min_hp[i][current_round].push_back(-1);
				death_count[i][current_round].push_back(0);
			}
		}

		if ((min_hp[target][current_round][current_turn_in_round] > hp) ||
			(min_hp[target][current_round][current_turn_in_round] == -1))
		{
			min_hp[target][current_round][current_turn_in_round] = hp;
		}
		if ((hp == 0) && !was_killed_this_turn[target])
		{
			was_killed_this_turn[target] = true;
			death_count[target][current_round][current_turn_in_round]++;
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
		if (turns_in_rounds[current_round].size() < current_turn_in_round)
		{
			turns_in_rounds[current_round].resize(current_turn_in_round);
		}

		// 'current_turn_in_round == 0' happens in out of turns case
		if (current_turn_in_round != 0)
		{
			turns_in_rounds[current_round][current_turn_in_round - 1]++;
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
		min_hp[i].resize(round_count);
	}

	death_count.resize(team_size);
	for (int i = 0; i < team_size; i++)
	{
		death_count[i].resize(round_count);
	}

	turns_in_rounds.resize(round_count);
}

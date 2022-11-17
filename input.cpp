#include "input.h"
#include <cstdio>
#include "dex.h"
#include "logger.h"
#include <string>
#include <cstring>
#include "expression.h"
#include "stdexcept"

using namespace std;

std::vector<int> Strategy::Next(const Dino team[], int team_size, int &offset) const
{
    while (offset < (int)instructions.size()) {
        auto &instruction = instructions[offset];
        if (!instruction.expression.get()) {
            offset = instruction.success;
            return instruction.abilities;
        } else if (instruction.expression->Calc(team, team_size)) {
            offset = instruction.success;
        } else {
            offset = instruction.failure;
        }
    }
    return {};
}

std::string GetLine()
{
    std::string line;
    while(true) {
        int c = getchar();
        if (c == '\n' || c == -1)
            return line;
        line.push_back(c);
    }
}

std::string GetIndent()
{
    std::string line;
    int c;
    while(true) {
        c = getchar();
        if (!isspace(c) || c == '\n' || c == -1)
            break;;
        line.push_back(c);
    }
    if (c != -1)
        ungetc(c, stdin);
    return line;
}

void UngetLine(const std::string &str)
{
    for (auto i = str.rbegin(); i != str.rend(); ++i)
        ungetc(*i, stdin);
}

Instruction ParseInstruction(int team_size, const char *line, int offset)
{
    Instruction instruction;
    int n, ability;
    for (int j = 0; j < team_size; ++j) {
        if (sscanf(line, "%d%n", &ability, &n) != 1)
            throw invalid_argument(strprintf("Expected a number near \"%.10s...\"", line));
        line += n;
        instruction.abilities.push_back(ability);
    }
    SkipWhite(line);
    if (*line != '\0')
        throw invalid_argument(strprintf("Invalid line format near \"%.10s...\"", line));
    instruction.success = offset+1;
    instruction.failure = offset+1;
    return std::move(instruction);
}

vector<Instruction> ParseBlock(int team_size, const string &indent, int offset);

vector<Instruction> ParseCondition(int team_size, const char *line, const string &indent, int offset)
{
    vector<Instruction> result;
    Instruction instruction;
    instruction.expression = std::move(ParseExpression(line));
    instruction.success = instruction.failure = ++offset;
    result.push_back(std::move(instruction));

    auto curr_indent = GetIndent();
    if (curr_indent.length() <= indent.length() || curr_indent.substr(0, indent.length()) != indent)
        throw invalid_argument("Invalid indent");
    UngetLine(curr_indent);

    auto success_block = ParseBlock(team_size, curr_indent, offset);
    offset += success_block.size();
    result.front().failure += success_block.size();
    for (auto it = success_block.begin(); it != success_block.end(); ++it)
        result.push_back(std::move(*it));

    curr_indent = GetIndent();
    if (curr_indent != indent) {
        UngetLine(indent);
        return std::move(result);
    }
    auto ch = getchar();
    if (ch != ':') {
        ungetc(ch, stdin);
        UngetLine(indent);
        return std::move(result);
    }

    auto curr_line = GetLine();
    if (*curr_line.c_str() == '?') {
        auto failure_block = std::move(ParseCondition(team_size, curr_line.c_str(), indent, offset));
        result.back().success += failure_block.size();
        result.back().failure += failure_block.size();
        for (auto it = failure_block.begin(); it != failure_block.end(); ++it)
            result.push_back(std::move(*it));
    } else {
        const char *curr_line_str = curr_line.c_str();
        SkipWhite(curr_line_str);
        if (*curr_line_str != '\0')
            throw invalid_argument(strprintf("Invalid line format near \"%.10s...\"", curr_line_str));
        auto curr_indent = GetIndent();
        if (curr_indent.length() <= indent.length() || curr_indent.substr(0, indent.length()) != indent)
            throw invalid_argument("Invalid indent");
        UngetLine(curr_indent);
        auto failure_block = std::move(ParseBlock(team_size, curr_indent, offset));
        result.back().success += failure_block.size();
        result.back().failure += failure_block.size();
        for (auto it = failure_block.begin(); it != failure_block.end(); ++it)
            result.push_back(std::move(*it));
    }
    return std::move(result);
}

vector<Instruction> ParseLine(int team_size, const string &indent, int offset)
{
    auto curr_indent = GetIndent();
    if (curr_indent != indent) {
        if (indent.substr(0, curr_indent.length()) != curr_indent)
            throw invalid_argument("Invalid indent");
        return {};
    }
    auto line = GetLine();
    if (*line.c_str() == '?') {
        return std::move(ParseCondition(team_size, line.c_str(), indent, offset));
    } else if (isdigit(*line.c_str())) {
        vector<Instruction> result;
        result.push_back(std::move(ParseInstruction(team_size, line.c_str(), offset)));
        return std::move(result);
    } else if (*line.c_str() == '\0' && indent == "") {
        return {};
    } else
        throw invalid_argument(strprintf("Invalid line format near \"%.10s...\"", line.c_str()));
}

vector<Instruction> ParseBlock(int team_size, const string &indent, int offset)
{
    vector<Instruction> result;
    while (true) {
        auto line = ParseLine(team_size, indent, offset);
        if (line.size() == 0)
            return std::move(result);
        offset += line.size();
        for (auto line_it = line.begin(); line_it != line.end(); ++line_it)
            result.push_back(std::move(*line_it));
    }
}

Strategy ParseStrategy(int team_size)
{
    Strategy strategy;
    strategy.instructions = std::move(ParseBlock(team_size, "", 0));
    return std::move(strategy);
}

int Input(std::vector<Dino> &team, Strategy &strategy)
{
    int team_size, n_turns;
    char end[2];
    char boss[32];
    team.clear();
    if (sscanf(GetLine().c_str(), "%s%1s", boss, end) != 1)
        return 1;
    auto boss_it = BossDex.find(boss);
    if (boss_it == BossDex.end()) {
        LOG("Unable to find %s boss\n", boss);
        return 1;
    }
    team.push_back(boss_it->second[0]);
    if (sscanf(GetLine().c_str(), "%d%d%1s", &team_size, &n_turns, end) != 2)
        return 2;
    for (int i = 0; i < team_size; ++i) {
        char dino[32];
        int level, health_boost, damage_boost, speed_boost;
        if (sscanf(GetLine().c_str(), "%s%d%d%d%d%1s", dino, &level, &health_boost, &damage_boost, &speed_boost, end) != 5)
            return 3+i;
        auto dino_it = DinoDex.find(dino);
        if (dino_it == DinoDex.end()) {
            LOG("Unable to find %s\n", dino);
            return 3+i;
        }
        team.push_back(Dino(1, i+1, level, health_boost, damage_boost, speed_boost, dino_it->second));
    }
    for (int i = 1; i < (int)boss_it->second.size(); ++i)
        team.push_back(boss_it->second[i]);
    if (n_turns != 0) {
        vector<vector<int>> ability;
        for (int i = 0; i < team_size; ++i) {
            ability.emplace_back(n_turns);
            int offset = 0, n;
            auto line = GetLine();
            for (int j = 0; j < n_turns; ++j) {
                if (sscanf(line.c_str() + offset, "%d%n", &ability[i][j], &n) != 1)
                    return 3+team_size+i;
                offset += n;
            }
            if (sscanf(line.c_str() + offset, "%1s", end) == 1)
                return 3+team_size+i;
        }
        strategy.instructions.clear();
        for (int i = 0; i < n_turns; ++i) {
            Instruction instruction;
            for (int j = 0; j < team_size; ++j)
                instruction.abilities.push_back(ability[j][i]);
            instruction.failure = i + 1;
            instruction.success = i + 1;
            strategy.instructions.push_back(std::move(instruction));
        }
    } else {
        try {
            strategy = std::move(ParseStrategy(team_size));
        } catch(std::exception &e) {
            LOG("Error: %s\n", e.what());
            return -1;
        }
    }
    return 0;
}

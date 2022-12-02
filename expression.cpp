#include "expression.h"
#include <cctype>
#include <stdexcept>
#include "strprintf.h"
#include <cstring>
#include <cstdio>
#include <map>
#include <functional>

using namespace std;

enum {
    NOP = 0,
    OR,
    AND,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    ADD,
    SUB,
    MLT,
    DIV,
    NOT,
    POS,
    NEG
};

string Operator[] = {
    "",
    "||",
    "&&",
    "<",
    "<=",
    ">",
    ">=",
    "==",
    "!=",
    "+",
    "-",
    "*",
    "/",
    "!",
    "+",
    "-",
};

map<string, function<int(const Dino &)>> Properties = {
    make_pair("health", [](const Dino &dino) -> int { return dino.health; }),
    make_pair("damage", [](const Dino &dino) -> int { return dino.Damage(); }),
    make_pair("speed", [](const Dino &dino) -> int { return dino.Speed(); }),
    make_pair("damage_factor", [](const Dino &dino) -> int { return dino.DamageFactor() * 100; }),
    make_pair("speed_factor", [](const Dino &dino) -> int { return dino.SpeedFactor() * 100; }),
    make_pair("shield", [](const Dino &dino) -> int { return dino.Shield() * 100; }),
    make_pair("dodge_chance", [](const Dino &dino) -> int { return dino.DodgeChance() * 100; }),
    make_pair("dodge_factor", [](const Dino &dino) -> int { return dino.DodgeFactor() * 100; }),
    make_pair("alive", [](const Dino &dino) -> int { return dino.Alive(); }),
    make_pair("cloak_factor", [](const Dino &dino) -> int { return dino.CloakFactor() * 100; }),
    make_pair("crit_chance", [](const Dino &dino) -> int { return dino.CritChanceFactor() * 100; }),
    make_pair("taunt", [](const Dino &dino) -> int { return dino.Taunt(); }),
    make_pair("max_health", [](const Dino &dino) -> int { return dino.max_health; }),
    make_pair("total_health", [](const Dino &dino) -> int { return dino.total_health; }),
    make_pair("max_total_health", [](const Dino &dino) -> int { return dino.max_total_health; }),
    make_pair("vulnerability", [](const Dino &dino) -> int { return dino.vulnerability * 100; }),
    make_pair("devour_heal", [](const Dino &dino) -> int { return dino.devour_heal; }),
    make_pair("damage_over_time", [](const Dino &dino) -> int { return dino.damage_over_time; }),
    make_pair("stun", [](const Dino &dino) -> int { return dino.stun != 0; }),
};

int Binary::Calc(const Dino team[], int team_size)
{
    switch (operation) {
    case OR:
        return op1->Calc(team, team_size) || op2->Calc(team, team_size);
    case AND:
        return op1->Calc(team, team_size) && op2->Calc(team, team_size);
    case LT:
        return op1->Calc(team, team_size) < op2->Calc(team, team_size);
    case LE:
        return op1->Calc(team, team_size) <= op2->Calc(team, team_size);
    case GT:
        return op1->Calc(team, team_size) > op2->Calc(team, team_size);
    case GE:
        return op1->Calc(team, team_size) >= op2->Calc(team, team_size);
    case EQ:
        return op1->Calc(team, team_size) == op2->Calc(team, team_size);
    case NE:
        return op1->Calc(team, team_size) != op2->Calc(team, team_size);
    case ADD:
        return op1->Calc(team, team_size) + op2->Calc(team, team_size);
    case SUB:
        return op1->Calc(team, team_size) - op2->Calc(team, team_size);
    case MLT:
        return op1->Calc(team, team_size) * op2->Calc(team, team_size);
    case DIV:
        return op1->Calc(team, team_size) / op2->Calc(team, team_size);
    default:
        return 0;
    }
}

int Unary::Calc(const Dino team[], int team_size)
{
    switch (operation) {
    case NOT:
        return !op->Calc(team, team_size);
    case POS:
        return +op->Calc(team, team_size);
    case NEG:
        return -op->Calc(team, team_size);
    default:
        return 0;
    }
}

int Const::Calc(const Dino team[], int team_size)
{
    return value;
}

int Property::Calc(const Dino team[], int team_size)
{
    if (index < 0 || team_size <= index)
        return 0;
    auto pr_it = Properties.find(name);
    if (pr_it == Properties.end())
        return 0;
    return pr_it->second(team[index]);
}

unique_ptr<Expression> ParseOr(const char *&line);

inline bool isvar(int ch)
{
    return isalnum(ch) || ch == '_';
}

unique_ptr<Expression> ParseConst(const char *&line)
{
    SkipWhite(line);
    if (isdigit(*line)) {
        int value, n;
        sscanf(line, "%d%n", &value, &n);
        line += n;
        return std::move(unique_ptr<Expression>(new Const(value)));
    } else if (isvar(*line)) {
        std::string name;
        while (isvar(*line))
            name.push_back(*line++);
        SkipWhite(line);
        if (*line != '[')
            throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
        ++line; // [
        SkipWhite(line);
        int index, n;
        if (sscanf(line, "%d%n", &index, &n) != 1)
            throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
        line += n;
        SkipWhite(line);
        if (*line != ']')
            throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
        ++line; // ]
        if (Properties.find(name) == Properties.end())
            throw invalid_argument(strprintf("Unknown property \"%s\"", name.c_str()));
        return std::move(unique_ptr<Expression>(new Property(name, index)));
    } else if (*line == '(') {
        ++line; // (
        unique_ptr<Expression> exp = std::move(ParseOr(line));
        SkipWhite(line);
        if (*line != ')')
            throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
        ++line; // )
        return exp;
    } else
        throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
}

unique_ptr<Expression> ParseUnary(const char *&line)
{
    SkipWhite(line);
    if (strncmp(line, Operator[NOT].c_str(), Operator[NOT].length()) == 0) {
        line += Operator[NOT].length();
        return std::move(unique_ptr<Expression>(new Unary(std::move(ParseUnary(line)), NOT)));
    } else if (strncmp(line, Operator[POS].c_str(), Operator[POS].length()) == 0) {
        line += Operator[POS].length();
        return std::move(unique_ptr<Expression>(new Unary(std::move(ParseUnary(line)), POS)));
    } else if (strncmp(line, Operator[NEG].c_str(), Operator[NEG].length()) == 0) {
        line += Operator[NEG].length();
        return std::move(unique_ptr<Expression>(new Unary(std::move(ParseUnary(line)), NEG)));
    } else
        return std::move(ParseConst(line));
}

unique_ptr<Expression> ParseMultiplication(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseUnary(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[MLT].c_str(), Operator[MLT].length()) == 0) {
            line += Operator[MLT].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseMultiplication(line)), MLT)));
        } else if (strncmp(line, Operator[DIV].c_str(), Operator[DIV].length()) == 0) {
            line += Operator[DIV].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseMultiplication(line)), DIV)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseAddition(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseMultiplication(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[ADD].c_str(), Operator[ADD].length()) == 0) {
            line += Operator[ADD].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseAddition(line)), ADD)));
        } else if (strncmp(line, Operator[SUB].c_str(), Operator[SUB].length()) == 0) {
            line += Operator[SUB].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseAddition(line)), SUB)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseComparision(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseAddition(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[LE].c_str(), Operator[LE].length()) == 0) {
            line += Operator[LE].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseComparision(line)), LE)));
        } else if (strncmp(line, Operator[LT].c_str(), Operator[LT].length()) == 0) {
            line += Operator[LT].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseComparision(line)), LT)));
        } else if (strncmp(line, Operator[GE].c_str(), Operator[GE].length()) == 0) {
            line += Operator[GE].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseComparision(line)), GE)));
        } else if (strncmp(line, Operator[GT].c_str(), Operator[GT].length()) == 0) {
            line += Operator[GT].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseComparision(line)), GT)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseEquation(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseComparision(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[EQ].c_str(), Operator[EQ].length()) == 0) {
            line += Operator[EQ].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseEquation(line)), EQ)));
        } else if (strncmp(line, Operator[NE].c_str(), Operator[NE].length()) == 0) {
            line += Operator[NE].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseEquation(line)), NE)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseAnd(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseEquation(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[AND].c_str(), Operator[AND].length()) == 0) {
            line += Operator[AND].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseAnd(line)), AND)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseOr(const char *&line)
{
    std::unique_ptr<Expression> op = std::move(ParseAnd(line));
    while (true) {
        SkipWhite(line);
        if (strncmp(line, Operator[OR].c_str(), Operator[OR].length()) == 0) {
            line += Operator[OR].length();
            op = std::move(unique_ptr<Expression>(new Binary(std::move(op), std::move(ParseOr(line)), OR)));
        } else
            return op;
    }
}

unique_ptr<Expression> ParseExpression(const char *line)
{
    SkipWhite(line);
    if (*line != '?')
        throw invalid_argument(strprintf("'?' expected near \"%.10s...\"", line));
    ++line; // ?
    std::unique_ptr exp = std::move(ParseOr(line));
    SkipWhite(line);
    if (*line != '\0')
        throw invalid_argument(strprintf("Malformed expression near \"%.10s...\"", line));
    return exp;
}

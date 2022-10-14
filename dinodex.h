#ifndef __DINODEX__H__
#define __DINODEX__H__

#include <map>
#include <string>
#include "dino.h"

extern std::map<std::string, std::vector<Dino>> BossDex;
extern std::map<std::string, const DinoKind *> DinoDex;

#endif // __DINODEX__H__

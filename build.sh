#!/usr/bin/env bash

g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o dex.o "dex.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o strprintf.o "strprintf.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o dino.o "dino.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o actions.o "actions.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o logger.o "logger.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o JWAcalc.o "JWAcalc.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o input.o "input.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o modifiers.o "modifiers.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o utils.o "utils.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o expression.o "expression.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o ability.o "ability.cpp" 
g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -o stats.o "stats.cpp" 
g++ -o JWAcalc JWAcalc.o ability.o actions.o dex.o dino.o expression.o input.o logger.o modifiers.o stats.o strprintf.o utils.o 

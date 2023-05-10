#!/bin/bash

#Program: Gnome Run Create
#Author: Joseph Eggers

echo "Link object files using the gcc Linker standard 2017"

clang++ -std=c++17 main.cc playerCharacter_/player.cc opponentCharacter_/opponent.cc game_element.cc game.cc cpputils/graphics/image.cc -o "Gnome Run"  -lm -lX11 -lpthread

echo "Built gnomeGame"

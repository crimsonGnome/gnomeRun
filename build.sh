#!/bin/bash

#Program: Gnome Run Create
#Author: Joseph Eggers

echo "Link object files using the gcc Linker standard 2017"
clang++ -std=c++17 -Wall main.cc playerCharacter_/player.cc opponent.cc game_element.cc game.cc cpputils/graphics/image.cc -o main  -lm -lX11 -lpthread

echo "Built gnomeGame"
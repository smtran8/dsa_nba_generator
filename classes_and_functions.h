#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


struct Player{
    string name;
    string team;
    string position;

    float ppg, apg, rpg, fg_pct, three_pm_pg, bpg;
    //Points, Assists, Rebounds, Field Goal Percentage, Three Pointers Made, Blocks - All per game
    float grade;
};

float compute_grade(Player& p);

// reads in data & returns vector of all players with all attributes we want
vector<Player> load_players(const string& filename); 

float guard_stof(const string& s);
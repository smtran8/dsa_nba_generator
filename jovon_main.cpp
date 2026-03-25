//
// Created by cladu on 3/25/2026.
//
#include "SplayTree.cpp"
#include "classes_and_functions.h"
int main() {
    SplayTree sg_tree;


    Player jordan;
    jordan.name = "Michael Jordan";
    jordan.team = "Bulls";
    jordan.position = "SG";
    jordan.ppg = 5.0f;
    jordan.apg = 5.0f;
    jordan.rpg = 5.0f;
    jordan.fg_pct = 5.0f;
    jordan.three_pm_pg = 5.0f;
    jordan.bpg = 5.0f;
    jordan.spg = 5.0f;

    jordan.grade = 5.0f;

    Player lebron;
    lebron.name = "lebron";
    lebron.team = "LAL";
    lebron.position = "SG";
    lebron.ppg = 5.0f;
    lebron.apg = 5.0f;
    lebron.rpg = 5.0f;
    lebron.fg_pct = 5.0f;
    lebron.three_pm_pg = 5.0f;
    lebron.bpg = 5.0f;
    lebron.spg = 5.0f;

    lebron.grade = 5.0f;

    vector<Player> players;
    players.push_back(jordan);
    players.push_back(lebron);

    sg_tree.playersIntoTree(players);

    return 0;
}
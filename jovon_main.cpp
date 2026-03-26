//
// Created by cladu on 3/25/2026.
//
#include "SplayTree.h"
#include "classes_and_functions.h"
#include <string>

using namespace std;
int main() {

    vector<Player> players = load_players("player_per_game.csv");

    TeamResult result = getTheTeam(players, "LAL");
    cout << result.pg.name << endl;
    cout << result.sg.name << endl;
    cout << result.sf.name << endl;
    cout << result.pf.name << endl;
    cout << result.c.name << endl;


    return 0;
}
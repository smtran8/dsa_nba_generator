//
// Created by cladu on 3/25/2026.
//
#include "SplayTree.h"
#include "classes_and_functions.h"
#include <string>

using namespace std;
int main() {

    vector<Player> players = load_players("player_per_game.csv");

    getTheTeam(players, "LAL");
    return 0;
}
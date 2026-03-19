#include <vector>
#include "classes_and_functions.h"
#include "max_heap.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    vector<Player> all_players = load_players("player_per_game.csv");
    build_different_team(all_players, "GSW");
    //cout << "Loaded " << all_players.size() << " data rows" << endl;
    //original data has 33280 rows, but after loading we have 25960 rows, so it was filtered by the constraint at least 10 minutes per game, and rows missing columns (Jack)
    return 0;
}
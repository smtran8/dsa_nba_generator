#include <vector>
#include "classes_and_functions.h"
#include "max_heap.h"
#include <iostream>
#include <string>
using namespace std;

//Issue: The heap will pick the players with THE BEST SEASON; so if a player plays crazily good in 1 season,
//but bad in other seasons, he is still likely to be picked
int main(){
    vector<Player> all_players = load_players("player_per_game.csv");
    build_different_team(all_players, "MIA");//1 player can be on the rosters of multiple teams; their scores can also be different per team
    //cout << "Loaded " << all_players.size() << " data rows" << endl;
    //original data has 33280 rows, but after loading we have 25960 rows, so it was filtered by the constraint at least 10 minutes per game, and rows missing columns (Jack)
    return 0;
}
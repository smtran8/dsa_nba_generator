#include <vector>
#include <string>
#include <unordered_map> //Better time complexity
#include "classes_and_functions.h"
#include "max_heap.h"
using namespace std;

void add_players(vector<Player>& players, string name, string team, string pos, float pts, float ast, float reb, float fg_pct, float three_pm, float blocks){
    Player p;
    p.name = name;
    p.team = team;  
    p.position = pos;
    p.ppg = pts;
    p.apg = ast;
    p.rpg = reb;
    p.fg_pct = fg_pct;
    p.three_pm_pg = three_pm;
    p.bpg = blocks;
    compute_grade(p);
    players.push_back(p);
}

void build_different_team(const vector<Player> &all_players, string team_code){
    unordered_map<string, Player> average_players;//Key is name, value is the actual Player object
    unordered_map<string, unordered_map<string, int>> position_counts; //Get this map to keep track of the most played positions for a player career
    //It is needed because for example, Kobe Bryant played mostly as a SG, but his last entries (last season) was a PF and our data picked up PF
    for (const auto& p : all_players) {
        if (p.team !=team_code) {
            continue;
        }
        if (average_players.find(p.name) == average_players.end()) {
            average_players[p.name] = p;//First time got the player => Insert them
        }else {//If see the players for 2+ times, take the sum of every stats
            average_players[p.name].ppg += p.ppg;
            average_players[p.name].apg += p.apg;
            average_players[p.name].rpg += p.rpg;
            average_players[p.name].fg_pct += p.fg_pct;
            average_players[p.name].three_pm_pg += p.three_pm_pg;
            average_players[p.name].bpg += p.bpg;
            average_players[p.name].spg += p.spg;
            average_players[p.name].season_count++;
        }
        position_counts[p.name][p.position]++; //We will take the most frequent positions
    }
    for (auto& pair : average_players) {
        string key_name = pair.first;
        Player& value_player = pair.second;

        value_player.ppg /= value_player.season_count;
        value_player.apg /= value_player.season_count;
        value_player.rpg /= value_player.season_count;
        value_player.fg_pct /= value_player.season_count;
        value_player.three_pm_pg /= value_player.season_count;
        value_player.spg /= value_player.season_count;
        value_player.bpg /= value_player.season_count;

        string best_position = "";//Keep the position with most counts
        int best_count = 0;

        for (auto& position_pair : position_counts[value_player.name]) {
            if (position_pair.second > best_count) {
                best_count = position_pair.second;
                best_position = position_pair.first;
            }
        }
        value_player.position = best_position;//Reset the position
        compute_grade(value_player);//Call compute grade again because the grades calculated in load_data is not equivalent any more
    }
    for (auto& pair: average_players) {
        Player& p = pair.second;
        if (p.name == "Dwyane Wade") {
            cout << p.name << "team " << p.team << "position " << p.position << "Grades: " << p.grade<< endl;
        }
    }
    MaxHeap pg_heap, sg_heap, sf_heap, pf_heap, c_heap;
    for (auto& pair : average_players){
        Player& p = pair.second;
        if (p.team == team_code){
            if (p.position == "PG"){
                pg_heap.insert(p);
            }
            else if (p.position == "SG"){
                sg_heap.insert(p);
            }
            else if (p.position == "SF"){
                sf_heap.insert(p);
            }
            else if (p.position == "PF"){
                pf_heap.insert(p);
            }
            else if (p.position == "C"){
                c_heap.insert(p);
            }
        }
    }
    cout << "Best Starting 5 for " << team_code << ":" << endl;
    cout << "PG: " << pg_heap.peek().name << " - Grades: " << pg_heap.peek().grade << endl;
    cout << "SG: " << sg_heap.peek().name << " - Grades: " << sg_heap.peek().grade << endl;
    cout << "SF: " << sf_heap.peek().name << " - Grades: " << sf_heap.peek().grade << endl;
    cout << "PF: " << pf_heap.peek().name << " - Grades: " << pf_heap.peek().grade << endl;
    cout << "C: " << c_heap.peek().name << " - Grades: " << c_heap.peek().grade << endl;
}
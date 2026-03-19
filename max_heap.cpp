#include <vector>
#include <string>
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
    MaxHeap pg_heap, sg_heap, sf_heap, pf_heap, c_heap;
    for (const auto& p : all_players){
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
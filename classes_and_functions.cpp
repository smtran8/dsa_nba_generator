#include "classes_and_functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


float compute_grade(Player& p){ //Rank players based on this final grade 
    float final_grade;
    if (p.position == "PG"){
        final_grade = (p.ppg * 0.3 + p.apg * 0.4 + p.three_pm_pg * 0.1 + p.fg_pct * 0.1 * 100 + p.rpg * 0.1);//fg_pct is a percent, so x 100 to get value
    }
    else if(p.position == "SG"){
        final_grade = (p.ppg * 0.4 + p.three_pm_pg * 0.2 + p.fg_pct * 0.2 * 100 + p.apg * 0.1 + p.bpg * 0.1);
    }
    else if(p.position == "SF"){
        final_grade = (p.ppg * 0.3 + p.rpg * 0.2 + p.three_pm_pg * 0.2 + p.bpg * 0.15 + p.apg * 0.15);
    }
    else if(p.position == "PF"){
        final_grade = (p.fg_pct * 0.4 * 100 + p.rpg * 0.3 + p.ppg * 0.1 + p.bpg * 0.1 + p.three_pm_pg * 0.1);
        //Really pay attention to this fg_pct => Check Jack's data handling => Jack uses decimal, so no problem
    }
    else if(p.position == "C"){
        final_grade = (p.rpg * 0.4 + p.bpg * 0.3 + p.fg_pct * 0.2 * 100 + p.ppg * 0.05 + p.apg * 0.05);
    }
    p.grade = final_grade;
    return final_grade;
}

float guard_stof(const string& s){//In case the data is empty, NA
    if(s.empty() || s == " "){
        return 0.0f;
    }
    try{
        return stof(s);
    }
    catch (const invalid_argument& e){
        return 0.0f;
    }
    catch (const out_of_range& e){
        return 0.0f;
    }
}

// reads in data & returns vector of all players with all attributes we want
vector<Player> load_players(const string& filename) {//We would use the data from the file player per game.csv
  vector<Player> players;
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    return players;
  }

  string line;
  getline(file, line);
  
  while (getline(file,line)) {
    stringstream ss(line);
    vector<string> row;
    string value;
    while (getline(ss, value, ',')) {
        row.push_back(value);
    }

    if (row.size()<32) {//The file has 32 columns
        continue;
    }
    //Filter out players who minutes play per game is less than 10 => Eliminate outliers that have 100% fg_pct but only played 1 game for example
    float mpg = guard_stof(row[9]);
    if (mpg < 10.0f){
        continue;
    }
    Player p;
    p.name=row[2];
    p.team=row[5];
    p.position=row[6];
    p.ppg=guard_stof(row[31]);
    p.apg=guard_stof(row[26]);
    p.rpg=guard_stof(row[25]);
    p.fg_pct=guard_stof(row[12]);
    p.three_pm_pg=guard_stof(row[13]);
    p.bpg=guard_stof(row[28]);
    compute_grade(p);
    players.push_back(p);
    }

   return players;
  }


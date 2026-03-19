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

float compute_grade(Player& p){ //Rank players based on this final grade 
    float final_grade;
    if (p.position == "PG"){
        final_grade = (p.ppg * 0.6 + p.apg * 0.2 + p.three_pm_pg * 0.2);
    }
    else if(p.position == "SG"){
        final_grade = (p.ppg * 0.6 + p.three_pm_pg * 0.4);
    }
    else if(p.position == "SF"){
        final_grade = (p.ppg * 0.6 + p.rpg * 0.4);
    }
    else if(p.position == "PF"){
        final_grade = (p.fg_pct * 0.6 * 100 + p.rpg * 0.4);//fg_pct is a percent, so x 100 to get value 
        //Really pay attention to this fg_pct => Check Jack's data handling => Jack uses decimal, so no problem
    }
    else if(p.position == "C"){
        final_grade = (p.rpg * 0.6 + p.bpg * 0.4);
    }
    p.grade = final_grade;
    return final_grade;
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
      if (row.size()<32) {
        continue;
       }
        Player p;
        p.name=row[2];
        p.team=row[5];
        p.position=row[6];
        p.ppg=stof(row[31]);
        p.apg=stof(row[26]);
        p.rpg=stof(row[25]);
        p.fg_pct=stof(row[12]);
        p.three_pm_pg=stof(row[13]);
        p.bpg=stof(row[28]);
        compute_grade(p);
        players.push_back(p);
        }
   return players;
  }


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

    float points, assists, rebounds, fg_pct, three_pm, blocks;
    //Points, Assists, Rebounds, Field Goal Percentage, Three Pointers Made, Blocks - All per game
    float grade;
};

float compute_grade(Player& p){ //Rank players based on this final grade 
    float final_grade;
    if (p.position == "PG"){
        final_grade = (p.points * 0.6 + p.assists * 0.2 + p.three_pm * 0.2);
    }
    else if(p.position == "SG"){
        final_grade = (p.points * 0.6 + p.three_pm * 0.4);
    }
    else if(p.position == "SF"){
        final_grade = (p.points * 0.6 + p.rebounds * 0.4);
    }
    else if(p.position == "PF"){
        final_grade = (p.fg_pct * 0.6 * 100 + p.rebounds * 0.4);//fg_pct is a percent, so x 100 to get value 
        //Really pay attention to this fg_pct => Check Jack's data handling
    }
    else if(p.position == "C"){
        final_grade = (p.rebounds * 0.6 + p.blocks * 0.4);
    }
    p.grade = final_grade;
    return final_grade;
}

// reads in data & returns vector of all players with all attributes we want
vector<Player> load_players(const string& filename) {
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
        p.points=stof(row[31]);
        p.assists=stof(row[26]);
        p.rebounds=stof(row[25]);
        p.fg_pct=stof(row[12]);
        p.three_pm=stof(row[13]);
        p.blocks=stof(row[28]);
        compute_grade(p);
        players.push_back(p);
        }
   return players;
  }


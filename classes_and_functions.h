#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Player{
    string name;
    string team;
    string position;

    float points, assists, rebounds, fg_pct, three_pm, blocks;
    //Points, Assists, Rebounds, Field Goal Percentage, Three Pointers Made, Blocks - All per game
    float grade;
};

float compute_grade(Player& p){
    float final_grade;
    if (p.position == "PG"){
        final_grade = (p.points * 0.6 + p.assists * 0.4);
    }
    else if(p.position == "SG"){
        final_grade = (p.points * 0.6 + p.three_pm * 0.4);
    }
    else if(p.position == "SF"){
        final_grade = (p.points * 0.6 + p.rebounds * 0.4);
    }
    else if(p.position == "PF"){
        final_grade = (p.fg_pct * 0.6 * 100 + p.rebounds * 0.4);//fg_pct is a percent, so x 100 to get value 
    }
    else if(p.position == "C"){
        final_grade = (p.rebounds * 0.6 + p.blocks * 0.4);
    }
    p.grade = final_grade;
    return final_grade;
}
#include <vector>
#include <SFML/Graphics.hpp>
#include "classes_and_functions.h"
#include "max_heap.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;


struct LogoButton {
    sf::Sprite sprite;
    string teamCode;
};
//Issue: The heap will pick the players with THE BEST SEASON; so if a player plays crazily good in 1 season,
//but bad in other seasons, he is still likely to be picked
int main(){
    vector<Player> players = load_players("player_per_game.csv");

    //1 player can be on the rosters of multiple teams; their scores can also be different per team
    //cout << "Loaded " << all_players.size() << " data rows" << endl;
    //original data has 33280 rows, but after loading we have 25960 rows, so it was filtered by the constraint at least 10 minutes per game, and rows missing columns (Jack)

    sf::RenderWindow window(sf::VideoMode(1000,700), "NBA");
    sf::Font font;
    font.loadFromFile("Roboto-VariableFont_wdth,wght.ttf");
    //title line 1
    sf::Text titleLine1;
    titleLine1.setFont(font);
    titleLine1.setString("Select An NBA Team!");
    titleLine1.setCharacterSize(36);
    titleLine1.setFillColor(sf::Color::White);
    // align center
    sf::FloatRect bounds1=titleLine1.getLocalBounds();
    titleLine1.setOrigin(bounds1.width/2,bounds1.height/2);
    titleLine1.setPosition(500,60);
    // title line 2
    sf::Text titleLine2;
    titleLine2.setFont(font);
    titleLine2.setString("Receive Best Player Per Position (All-Time)");
    titleLine2.setCharacterSize(36);
    titleLine2.setFillColor(sf::Color::White);
    // center
    sf::FloatRect bounds2=titleLine2.getLocalBounds();
    titleLine2.setOrigin(bounds2.width/2,bounds2.height/2);
    titleLine2.setPosition(500,110);
    // west text
    sf::Text westText;
    westText.setFont(font);
    westText.setString("West!");
    westText.setCharacterSize(36);
    westText.setFillColor(sf::Color(255,140,0)); //orange
    sf::FloatRect westBounds=westText.getLocalBounds();
    westText.setOrigin(westBounds.width/2,westBounds.height/2);
    westText.setPosition(250,160);
    // east text
    sf::Text eastText;
    eastText.setFont(font);
    eastText.setString("East!");
    eastText.setCharacterSize(36);
    eastText.setFillColor(sf::Color(255,140,0));
    sf::FloatRect eastBounds=eastText.getLocalBounds();
    eastText.setOrigin(eastBounds.width/2,eastBounds.height/2);
    eastText.setPosition(750,160);
    // load textures
    map<string,sf::Texture> textures; //easier texture access
    vector<string> teamCodes = {
        "DEN","MIN","OKC","POR","UTA",
        "GSW","LAC","LAL","PHO","SAC",
        "DAL","HOU","MEM","NOP","SAS",
        "BOS","BRK","NYK","PHI","TOR",
        "CHI","CLE","DET","IND","MIL",
        "ATL","CHA","MIA","ORL","WAS"
    };
    for (auto &code: teamCodes) {
        textures[code].loadFromFile("NBA/"+code+".png");
    }
    // create buttons by looping
    vector <LogoButton> buttons;
    float startY=200;
    float rowSpacing=120;
    float colSpacing=100;
    float westStartX=250-2*colSpacing;
    float eastStartX=750-2*colSpacing;

    // generate west team buttons
    string west[3][5] = {
    {"DEN", "MIN", "OKC", "POR", "UTA"},
    {"GSW", "LAC", "LAL", "PHO", "SAC"},
    {"DAL","HOU","MEM","NOP","SAS"}
    };
    for (int r=0;r<3;r++) {
        for (int c=0;c<5;c++) {
            LogoButton b;
            b.sprite.setTexture(textures[west[r][c]]);
            b.sprite.setScale(0.12f,0.12f);
            b.sprite.setPosition(westStartX+c*colSpacing,startY+r*rowSpacing);
            b.teamCode = west[r][c];
            buttons.push_back(b);
        }
    }
    // generate east team buttons
    string east[3][5] = {
        {"BOS","BRK","NYK","PHI","TOR"},
        {"CHI","CLE","DET","IND","MIL"},
        {"ATL","CHA","MIA","ORL","WAS"}
    };
    for (int r=0;r<3;r++) {
        for (int c=0;c<5;c++) {
            LogoButton b;
            b.sprite.setTexture(textures[east[r][c]]);
            b.sprite.setScale(0.12f,0.12f);
            b.sprite.setPosition(eastStartX+c*colSpacing, startY+r*rowSpacing);
            b.teamCode = east[r][c];
            buttons.push_back(b);
        }
    }

    //Back button
    sf::RectangleShape backButton(sf::Vector2f(120,50));
    backButton.setPosition(20,20);
    backButton.setFillColor(sf::Color::Red);

    sf::Text backText;
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setOrigin(backText.getLocalBounds().width/2,backText.getLocalBounds().height/2);
    backText.setPosition(80,45);

    bool showTeam=false;
    TeamResult team;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
            }
            if (event.type==sf::Event::MouseButtonPressed) {
                int x=event.mouseButton.x;
                int y=event.mouseButton.y;
                if (!showTeam) {
                    for (auto& b:buttons) {
                        if (b.sprite.getGlobalBounds().contains(x,y)) {
                        team=build_different_team(players,b.teamCode);
                        showTeam=true;
                        }
                    }
                }
                if (showTeam && backButton.getGlobalBounds().contains(x,y)) {
                    showTeam=false;
                }
            }
        }
        window.clear();
        //Menu
        if (!showTeam) {
            window.draw(titleLine1);
            window.draw(titleLine2);
            window.draw(westText);
            window.draw(eastText);
            for (auto& b:buttons) {
                window.draw(b.sprite);
            }
        }
        //View when you click on team
        else {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);

            text.setString("PG: " + team.pg.name);
            text.setPosition(400,200);
            window.draw(text);
            text.setString("SG: " + team.sg.name);
            text.setPosition(400,250);
            window.draw(text);
            text.setString("SF: " + team.sf.name);
            text.setPosition(400,300);
            window.draw(text);
            text.setString("PF: " + team.pf.name);
            text.setPosition(400,350);
            window.draw(text);
            text.setString("C: " + team.c.name);
            text.setPosition(400,400);
            window.draw(text);

            window.draw(backButton);
            window.draw(backText);
        }
        window.display();
    }

    return 0;
}
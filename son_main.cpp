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

    sf::RenderWindow window(sf::VideoMode(1400,900), "NBA");
    float windowWidth=window.getSize().x;
    //float windowHeight=window.getSize().y;
    sf::Font font;
    font.loadFromFile("Burkhan.otf");
    //title line 1
    sf::Text titleLine1;
    titleLine1.setFont(font);
    titleLine1.setString("Select An NBA Team!");
    titleLine1.setCharacterSize(75);
    titleLine1.setFillColor(sf::Color::Black);
    // align center
    sf::FloatRect bounds1=titleLine1.getLocalBounds();
    titleLine1.setOrigin(bounds1.left+bounds1.width/2,bounds1.top+bounds1.height/2);
    titleLine1.setPosition(windowWidth/2,50);
    // title line 2
    sf::Text titleLine2;
    titleLine2.setFont(font);
    titleLine2.setString("Receive Best Player Per Position (All-Time)");
    titleLine2.setCharacterSize(75);
    titleLine2.setFillColor(sf::Color::Black);
    // center
    sf::FloatRect bounds2=titleLine2.getLocalBounds();
    titleLine2.setOrigin(bounds2.left+bounds2.width/2,bounds2.top+bounds2.height/2);
    titleLine2.setPosition(windowWidth/2, 135);
    // west text
    sf::Text westText;
    westText.setFont(font);
    westText.setString("West!");
    westText.setCharacterSize(75);
    westText.setFillColor(sf::Color::Black);
    sf::FloatRect wBounds=westText.getLocalBounds();
    westText.setOrigin(wBounds.left+wBounds.width/2,wBounds.top+bounds2.height/2);
    westText.setPosition(350,245); // exact pos 25% of 1400 (x comp of window).
    // east text
    sf::Text eastText;
    eastText.setFont(font);
    eastText.setString("East!");
    eastText.setCharacterSize(75);
    eastText.setFillColor(sf::Color::Black);
    sf::FloatRect eBounds=eastText.getLocalBounds();
    eastText.setOrigin(eBounds.left+eBounds.width/2,eBounds.top+bounds2.height/2);
    eastText.setPosition(1050,245); // exact pos 75% of 1400
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
    float startY=300;
    float rowSpacing=180;
    float colSpacing=120;
    float westCenter=350;
    float eastCenter=1050;
    int cols=5;
    float totalWidth=(cols-1)*colSpacing;
    float westStartX=westCenter-totalWidth/2-50;
    float eastStartX=eastCenter-totalWidth/2 - 35;

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
            b.sprite.setScale(0.27f,0.27f);
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
            float x = eastStartX+c*colSpacing;
            float y = startY+r*rowSpacing;
            if (east[r][c]=="MIA") {
                b.sprite.setScale(0.55f,0.55f);
                x-=60;
                y-=60;
            }
            else {
                b.sprite.setScale(0.27f,0.27f);
            }
            b.sprite.setPosition(x,y);
            b.teamCode = east[r][c];
            buttons.push_back(b);
        }
    }

    //Back button
    sf::RectangleShape backButton(sf::Vector2f(150,80));
    backButton.setPosition(0,0);
    backButton.setFillColor(sf::Color::Red);

    sf::Text backText;
    backText.setFont(font);
    backText.setString("Back");
    backText.setColor(sf::Color::Black);
    backText.setCharacterSize(50);
    backText.setOrigin(backText.getLocalBounds().width/2,backText.getLocalBounds().height/2);
    backText.setPosition(75,25);

    sf::RectangleShape divider;
    divider.setSize(sf::Vector2f(4,540));
    divider.setPosition(705,245);
    divider.setFillColor(sf::Color::Black);

    bool showTeam=false;
    TeamResult team;
    string selectedTeam="";
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
                            // for line below, might need an if statement differentiating between heap or splay tree
                        team=build_different_team(players,b.teamCode);
                        selectedTeam=b.teamCode;
                        showTeam=true;
                        }
                    }
                }
                if (showTeam && backButton.getGlobalBounds().contains(x,y)) {
                    showTeam=false;
                }
            }
        }
        window.clear(sf::Color(255,140,0));
        //Menu
        if (!showTeam) {
            window.draw(titleLine1);
            window.draw(titleLine2);
            window.draw(westText);
            window.draw(eastText);
            window.draw(divider);
            for (auto& b:buttons) {
                window.draw(b.sprite);
            }
        }
        //View when you click on team
        else {
            sf::Text teamText;
            teamText.setFont(font);
            teamText.setString(selectedTeam);
            teamText.setCharacterSize(90);
            teamText.setFillColor(sf::Color::Black);
            sf::FloatRect tBounds=teamText.getLocalBounds();
            teamText.setOrigin(tBounds.left+tBounds.width/2,tBounds.top+tBounds.height/2);
            teamText.setPosition(windowWidth/2,120);
            sf::Sprite teamLogo;
            teamLogo.setTexture(textures[selectedTeam]);
            if (selectedTeam=="MIA") {
                teamLogo.setScale(1.0f,1.0f);
            }
            else {
                teamLogo.setScale(0.75f,0.75f);
            }
            teamLogo.setPosition(windowWidth*0.75,70);
            if (selectedTeam=="MIA") {
                teamLogo.setPosition(windowWidth*0.75-50,40);
            }
            window.draw(teamText);
            window.draw(teamLogo);

            //center align player text
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(64);
            text.setFillColor(sf::Color::Black);
            float centerX=windowWidth/2;
            float startY=250;
            float spacing=90;
            // pg
            text.setString("PG: " + team.pg.name);
            sf::FloatRect rec=text.getLocalBounds();
            text.setOrigin(rec.left+rec.width/2,rec.top+rec.height/2);
            text.setPosition(centerX,startY);
            window.draw(text);
            // sg
            text.setString("SG: " + team.sg.name);
            rec=text.getLocalBounds();
            text.setOrigin(rec.left+rec.width/2,rec.top+rec.height/2);
            text.setPosition(centerX,startY+spacing);
            window.draw(text);
            // sf
            text.setString("SF: " + team.sf.name);
            rec=text.getLocalBounds();
            text.setOrigin(rec.left+rec.width/2, rec.top+rec.height/2);
            text.setPosition(centerX,startY+2*spacing);
            window.draw(text);
            // pf
            text.setString("PF: " + team.pf.name);
            rec=text.getLocalBounds();
            text.setOrigin(rec.left+rec.width/2, rec.top+rec.height/2);
            text.setPosition(centerX,startY+3*spacing);
            window.draw(text);
            // c
            text.setString("C: " + team.c.name);
            rec=text.getLocalBounds();
            text.setOrigin(rec.left+rec.width/2, rec.top+rec.height/2);
            text.setPosition(centerX,startY+4*spacing);
            window.draw(text);

            window.draw(backButton);
            window.draw(backText);
        }
        window.display();
    }
    return 0;
}
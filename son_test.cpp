#include <vector>
#include "classes_and_functions.h"
#include "max_heap.h"
using namespace std;

int main(){
    //Try an example - Shooting Guards
    MaxHeap sg_heap;
    vector<Player> test_players;
    add_players(test_players, "Michael Jordan", "Chicago Bulls", "SG", 30.1, 5.3, 6.2, 0.497, 2.7, 0.8);
    add_players(test_players, "Kobe Bryant", "Los Angeles Lakers", "SG", 25.0, 4.7, 5.2, 0.447, 1.4, 0.5);
    add_players(test_players, "Dwyane Wade", "Miami Heat", "SG", 22.0, 5.4, 4.7, 0.473, 1.8, 0.8);
    add_players(test_players, "Clyde Drexler", "Portland Trail Blazers", "SG", 20.4, 6.1, 3.8, 0.470, 1.9, 0.7);
    add_players(test_players, "Allen Iverson", "Philadelphia 76ers", "SG", 26.7, 6.2, 3.7, 0.425, 1.9, 0.2);

    for(auto p : test_players){
        sg_heap.insert(p);
    }
    //cout << "Top Shooting Guards:" << sg_heap.peek().name << " Grades: " << sg_heap.peek().grade << endl;

    cout << "Top Shooting Guards:" << endl;
    vector<Player> top_sg = sg_heap.get_top_n(3);
    for (auto p : top_sg) {
        cout << p.name << " - Grade: " << p.grade << endl;
    }
    return 0;
}
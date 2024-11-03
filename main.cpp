#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include "Goat.h"
#include <random>
#include <string>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void find_goat_by_name(const list<Goat>& goats);
void count_goats_by_color(const list<Goat>& goats);
void display_goats_reversed(list<Goat> goats);
void shuffle_goats(list<Goat>& goats);
void remove_specific_goat(list<Goat>& goats);
void replace_goat_color(list<Goat>& goats);
void sort_goats_by_age(list<Goat>& goats);
void calculate_average_age();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Finding goat by name.\n";
                find_goat_by_name(trip);
                break;
            case 5:
                cout << "Counting goats by color.\n";
                count_goats_by_color(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find goat by name\n";
    cout << "[5] Count goats by color\n";
    cout << "[6] List all goats in reverse order\n";
    cout << "[7] Shuffle goats\n";
    cout << "[8] Remove a specific goat\n";
    cout << "[9] Replace goat color\n";
    cout << "[10] Sort goats by age and list\n";
    cout << "[11] Calculate average age of goats\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void find_goat_by_name(const list<Goat>& goats) {
    string name;
    cout << "Enter name to find: ";
    cin >> name;
    for (Goat g : goats) {
        if (g.get_name() == name)
            cout << "Found: " << g.get_name() << endl;
    }
}

void count_goats_by_color(const list<Goat>& goats) {
    string color;
    cout << "Enter color to count: ";
    cin >> color;
    int count = 0;
    for (Goat g : goats) {
        if (g.get_color() == color)
            count++;
    }
    cout << "Found " << count << " goats" << endl;
}

void display_goats_reversed(list<Goat> goats) {
    for (int i = goats.size() - 1; i >= 0; i--)
        cout << goats[i] << endl;
}

void shuffle_goats(list<Goat>& goats) {
    vector<Goat> temp(goats.begin(), goats.end());
    shuffle(temp.begin(), temp.end(), default_random_engine());
    goats = list<Goat>(temp.begin(), temp.end());
}

void sort_goats_by_age(list<Goat>& goats) {
    sort(goats.begin(), goats.end());
}

void remove_specific_goat(list<Goat>& goats) {
    string name;
    cout << "Enter name of goat to remove: ";
    cin >> name;
    goats.remove_if([&name](const Goat& g) { return g.get_name() == name; });
}

void replace_goat_color(list<Goat>& goats) {
    string oldColor, newColor;
    cout << "Enter current color: ";
    cin >> oldColor;
    cout << "Enter new color: ";
    cin >> newColor;
    for (Goat& goat : goats) {
        if (goat.get_color() == oldColor) 
            goat.set_color(newColor);
    }
}

void sort_goats_by_age(list<Goat>& goats) {
    sort(goats.begin(), goats.end());
}
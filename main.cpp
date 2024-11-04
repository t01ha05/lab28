#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <random>
#include <string>
#include "Goat.h"
using namespace std;

int main_menu();
void add_goat(list<Goat>& trip, string names[], string colors[]);
void delete_goat(list<Goat>& trip);
void display_trip(const list<Goat>& trip);
void find_goat_by_name(const list<Goat>& goats);
void count_goats_by_color(const list<Goat>& goats);
void display_goats_reversed(list<Goat> goats);
void shuffle_goats(list<Goat>& goats);
void remove_specific_goat(list<Goat>& goats);
void replace_goat_color(list<Goat>& goats);
void sort_goats_by_age(list<Goat>& goats);
void calculate_average_age(const list<Goat>& goats);

int main() {
    srand(time(0));
    string names[200];
    string colors[25];

    list<Goat> trip = {{"Billy", 5, "Black"}, {"Nanny", 3, "White"}, {"Kid", 1, "Brown"}};

    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                find_goat_by_name(trip);
                break;
            case 5:
                count_goats_by_color(trip);
                break;
            case 6:
                display_goats_reversed(trip);
                break;
            case 7:
                shuffle_goats(trip);
                break;
            case 8:
                remove_specific_goat(trip);
                break;
            case 9:
                replace_goat_color(trip);
                break;
            case 10:
                sort_goats_by_age(trip);
                break;
            case 11:
                calculate_average_age(trip);
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

void delete_goat(list<Goat>& trip) {
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }
    trip.pop_back();  // Just an example: removing the last goat
    cout << "Goat removed. Total goats now: " << trip.size() << endl;
}

void add_goat(list<Goat>& trip, string names[], string colors[]) {
    int age = rand() % 20;
    string name = names[rand() % 200];  // Assuming 200 names
    string color = colors[rand() % 25];  // Assuming 25 colors
    trip.push_back(Goat(name, age, color));
    cout << "Goat added. Total goats now: " << trip.size() << endl;
}

void display_trip(const list<Goat>& trip) {
    int i = 1;
    for (const Goat& goat : trip) {
        cout << i++ << ": " << goat.get_name() << " " 
             << goat.get_age() << " " << goat.get_color() << endl;
    }
}

void find_goat_by_name(const list<Goat>& goats) {
    string name;
    cout << "Enter name to find: ";
    cin >> name;
    auto it = find_if(goats.begin(), goats.end(), 
                     [&name](const Goat& g) { return g.get_name() == name; });
    if (it != goats.end()) {
        cout << "Goat found: " << it->get_name() << " " 
             << it->get_age() << " " << it->get_color() << endl;
    } else {
        cout << "Goat not found." << endl;
    }
}

void count_goats_by_color(const list<Goat>& goats) {
    string color;
    cout << "Enter color to count: ";
    cin >> color;
    int count = count_if(goats.begin(), goats.end(), 
                        [&color](const Goat& g) { return g.get_color() == color; });
    cout << "Number of goats with color " << color << ": " << count << endl;
}

void display_goats_reversed(list<Goat> goats) {
    goats.reverse();
    display_trip(goats);
}

void shuffle_goats(list<Goat>& goats) {
    vector<Goat> goatVec(goats.begin(), goats.end());
    shuffle(goatVec.begin(), goatVec.end(), default_random_engine(random_device()()));
    list<Goat> shuffledList(goatVec.begin(), goatVec.end());
    goats.swap(shuffledList);
    cout << "Goats shuffled." << endl;
}

void sort_goats_by_age(list<Goat>& goats) {
    goats.sort([](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
    cout << "Goats sorted by age." << endl;
}

void remove_specific_goat(list<Goat>& goats) {
    string name;
    cout << "Enter name of goat to remove: ";
    cin >> name;
    goats.remove_if([&name](const Goat& g) { return g.get_name() == name; });
    cout << "Goat removed if found. Total goats now: " << goats.size() << endl;
}

void replace_goat_color(list<Goat>& goats) {
    string oldColor, newColor;
    cout << "Enter current color: ";
    cin >> oldColor;
    cout << "Enter new color: ";
    cin >> newColor;
    for (Goat& goat : goats) {
        if (goat.get_color() == oldColor) goat.set_color(newColor);
    }
    cout << "Goat colors replaced from " << oldColor << " to " << newColor << "." << endl;
}

void calculate_average_age(const list<Goat>& goats) {
    if (goats.empty()) {
        cout << "No goats to calculate average age." << endl;
        return;
    }
    int totalAge = accumulate(goats.begin(), goats.end(), 0, 
        [](int sum, const Goat& g) { return sum + g.get_age(); });
    double averageAge = static_cast<double>(totalAge) / goats.size();
    cout << "Average age of goats: " << averageAge << endl;
}
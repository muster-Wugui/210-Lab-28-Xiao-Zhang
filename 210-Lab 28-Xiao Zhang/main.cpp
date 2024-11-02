// COMSC-210 | Lab 28 | Xiao Zhang
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include "Goat.h"
#include <algorithm>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void find_oldest(list<Goat> &trip); //A function to find and display the oldest goat.
void sort_age(list<Goat> &trip); // Sorts the goats by age
void count_color(list<Goat> &trip, string color); //Counts goats with a specific color
void find_youngest(list<Goat> &trip); // Finds and displays the youngest goat
void sort_name(list<Goat> &trip); // Sorts the goats by name
void uniquecolors(list<Goat> &trip); //Lists all the unique colors
void count_age(list<Goat> &trip, int age); //Counts goats above a certain age
void clear(list<Goat> &trip); //Clears the list

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
    int choice = main_menu();
        while (choice != 12) {
            switch (choice) {
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
                    cout<<"Finding the oldest GOAT\n";
                    find_oldest(trip);
                    break;
                case 5:
                    cout<<"Sorting the GOATs by age\n";
                    sort_age(trip);
                    break;
                case 6: {
                    cout<<"Counting the specific color.\n";
                    string color;
                    cout << "Enter color to count: ";
                    cin >> color;
                    count_color(trip, color);
                    break;
                }
                case 7:
                    cout<<"Finding the youngest GOAT\n";
                    find_youngest(trip);
                    break;
                case 8:
                    cout<<"Sorting the GOATs by name\n";
                    sort_name(trip);
                    break;
                case 9:
                    cout<<"listing the unique colors in GOAT\n";
                    uniquecolors(trip);
                    break;
                case 10: {
                    cout<<"Counting the GOATS above a certain age.\n";
                    int age;
                    cout << "Enter minimum age: ";
                    cin >> age;
                    count_age(trip, age);
                    break;
                }
                case 11:
                    cout<<"Erasing all the GOATs\n";
                    clear(trip);
                    break;
            }
            choice = main_menu();
        }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find oldest goat\n";
    cout << "[5] Sort by age\n";
    cout << "[6] Count by color\n";
    cout << "[7] Show youngest goat\n";
    cout << "[8] Sort by name\n";
    cout << "[9] List unique colors\n";
    cout << "[10] Count age above\n";
    cout << "[11] Clear trip\n";
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

void find_oldest(list<Goat> &trip) {
    if (trip.empty()) { // Check if the list is empty
        cout << "No goats in the trip.\n";
        return;
    }
    auto oldest = max_element(trip.begin(), trip.end(), [](Goat &a, Goat &b) { // Find the oldest goat using max_element with a custom comparator
        return a.get_age() < b.get_age();
    });
    cout << "Oldest goat: " << oldest->get_name() << " (" << oldest->get_age() << " years, " << oldest->get_color() << ")\n";
}

void sort_age(list<Goat> &trip) { // Sorts goats in the list by age in ascending order
    trip.sort([](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age(); // I use sort with a lambda function to sort goats by age
    });
    cout << "Goats sorted by age.\n";
    display_trip(trip);
}

void count_color(list<Goat> &trip, string color) {
    int count = count_if(trip.begin(), trip.end(), [&color](const Goat &g) {  // Use count_if to count goats with the specified color
        return g.get_color() == color;
    });
    cout << "Number of goats with color " << color << ": " << count << endl;
}

void find_youngest(list<Goat> &trip) {
    if (trip.empty()) { // Check if the list is empty
        cout << "No goats in the trip.\n";
        return;
    }
    auto youngest = min_element(trip.begin(), trip.end(), [](Goat &a, Goat &b) { // Find the youngest goat using min_element with a custom comparator
        return a.get_age() < b.get_age();
    });
    cout << "Youngest goat: " << youngest->get_name() << " (" << youngest->get_age() << " years, " << youngest->get_color() << ")\n";
}

void sort_name(list<Goat> &trip) { // Sorts goats in the list by name in alphabetical order
    trip.sort([](const Goat &a, const Goat &b) { // Use sort with a lambda function to sort goats by name
        return a.get_name() < b.get_name();
    });
    cout << "Goats sorted by name.\n";
    display_trip(trip);
}

void uniquecolors(list<Goat> &trip) {// Lists all unique colors of goats in the trip
    set<string> colors; //I used the property of the set which don't contain repeat elements
    for (const auto &goat : trip) {
        colors.insert(goat.get_color()); // Add each goat's color to the set
    }
    cout << "Unique colors: ";
    for (const auto &color : colors) { //Print out the unique colors found
        cout << color << " ";
    }
    cout << endl;
}

void count_age(list<Goat> &trip, int age) { // Counts and displays the number of goats older than a specified age
    int count = count_if(trip.begin(), trip.end(), [&age](const Goat &g) { // Use count_if to count goats older than the specified age
        return g.get_age() > age;
    });
    cout << "Number of goats older than " << age << ": " << count << endl;
}

void clear(list<Goat> &trip) {
    trip.clear(); // Remove all goats from the list
    cout << "All goats removed. Trip size: " << trip.size() << endl;
}

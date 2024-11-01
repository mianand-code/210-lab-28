// COMSC-210 | Lab 28 | Mira Anand
// Module 10, Lesson: std::map & STL Algorithms, Assignment: STL Algorithms
// IDE used: Visual Studio Code for Mac

#include <algorithm> // to use STL algorithm library
#include <cstdlib> // needed to generate a random number
#include <ctime> // needed to generate a random number
#include <fstream> // needed for file operations
#include "Goat.h" // references the Goat header file, which contains a complete class for Goat objects
#include <iostream>
#include <list> // needed to use std::list
#include <random> // to use default_random_engine() - for shuffling
#include <string>
using namespace std;

// declaration and initialization of const int variables
const int SZ_NAMES = 200; // represents array size for names, array can hold 200 names
const int SZ_COLORS = 25; // represents array size for colors, array can hold 25 colors

// function prototypes
int main_menu();
void add_goat(list<Goat> &trip, string [], string []);
void delete_goat(list<Goat> &trip);
void display_trip(list<Goat> trip);
void reverse_trip(list<Goat> &trip);
void find_goat(list<Goat> trip);
void any_of_goat(list<Goat> trip);

int select_goat(list<Goat> trip);

int main() 
{
    srand(time(0)); // needed as the first line in main() for randomization

    // code block to read & populate arrays for names
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    // code block to read & populate arrays for colors
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // code block to create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8; // declare and initialize a variable to hold the random trip size (8-15)
    list<Goat> trip; // creation of an std::list to hold Goat objects
    int age; // to hold the goat's age
    string name, color; // to hold the goat's name and color
    for (int i = 0; i < tripSize; i++) // creation of a for loop to populate the std::list with Goat objects
    {
        // defined in Goat.h
        age = rand() % (MAX_AGE + 1); // random generation of a age between 0 - 20 (MAX_AGE) and assigning it to "age"
        name = names[rand() % SZ_NAMES]; // random selection of a name within the "names" array and assigning it to "name"
        color = colors[rand() % SZ_COLORS]; // random selection of a color within the "colors" array and assigning it to "color"
        Goat tmp(name, age, color); // creation of a temp "tmp" Goat object with all 3 parameters
        trip.push_back(tmp); // using .push_back() member function, adds Goat object to the end of the list 
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu(); // main_menu() function call - displays GM3K1 menu, retrieves user's menu choice, assigns it to sel
    while (sel != 12) // creation of a while loop so that the user can continue to select menu options until they wish to quit program
    {
        switch (sel) // creation of a switch statement that handles cases of each numbered menu option based on sel
        {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors); // add_goat() function call, will add a Goat object (with its 3 parameters) to the container/std::list
                break;

            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip); // delete_goat() function call, will delete a Goat object from the container/std::list
                break;
                
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip); // display_trip() function call, will display the current list of Goat objects
                break;

            case 4:
                break;

            case 5:
                break;
            
            case 6:
                break;

            case 7:
                break;
            
            case 8:
                break;

            case 9:
                break;

            case 10:
                break;

            case 11:
                break;

            case 12:
                // option #12 is when user wants to quit
                cout << "Exiting program..." << endl;
                break;

            // user input validation for menu option # (has to be 1-12)
            // main_menu() function also handles user input validation, but it is good to include it here also for completeness
            default:
                cout << "Invalid selection.\n";
                break;
        }
        
        sel = main_menu(); // prompt the user to enter another selection
    }
    
    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
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

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
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
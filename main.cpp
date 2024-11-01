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
void any_of_goat_age(list<Goat> trip);
void shuffle_trip(list<Goat> &trip);
void fill_trip(list<Goat> &trip);
void accumulate_trip_age(list<Goat> trip);
void erase_goats_below_age(list<Goat> &trip);
void clear_trip(list<Goat> &trip);
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
                reverse_trip(trip); // reverse_trip() function call, will reverse the order of the Goat objects stored in the std::list
                break;

            case 5:
                find_goat(trip); // find_goat() function call, will allow the user to search for a Goat object by name
                break;
            
            case 6:
                any_of_goat_age(trip); // any_of_goat_age() function call, will allow the user to check if any of the Goat objects match/have a certain age
                break;

            case 7:
                shuffle_trip(trip); // shuffle_trip() function call, will shuffle the order of the Goat objects stored in the std::list, randomly
                break;
            
            case 8:
                fill_trip(trip); // fill_trip() function call, will fill/reset the 1st 3 Goat objects in the list to default values
                break;

            case 9:
                accumulate_trip_age(trip); // accumulate_trip_age() function call, will take the ages for all of the Goat objects and sum them up
                break;

            case 10:
                erase_goats_below_age(trip); // erase_goats_below_age() function call, will erase Goat objects that match/are of a certain age
                break;

            case 11:
                clear_trip(trip); // clear_trip() function call, will completely clear all of the Goat objects stored in the std::list
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

// int main_menu() function header
// DESCRIPTION: this function outputs a GM3K1 menu, obtains the user's choice for the menu option # they would like to select, validates it, and returns this choice to main()
// ARGUMENTS: no arguments/parameters
// RETURNS: int choice, which is the user input for the menu option # they would like to select
int main_menu() 
{
    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Reverse the goat trip" << endl;
    cout << "[5] Find a goat (by name)" << endl;
    cout << "[6] Check if any of the goats are of a certain age" << endl;
    cout << "[7] Shuffle the goat trip" << endl;
    cout << "[8] Fill/reset the 1st 3 goats in the trip to default values" << endl;
    cout << "[9] Accumulate/sum up all of the ages in the goat trip" << endl;
    cout << "[10] Erase/remove goats that are below a certain age" << endl;
    cout << "[11] Clear the goat trip" << endl;
    cout << "[12] Quit" << endl;
    cout << "Choice --> ";

    int choice; // to hold user's choice for menu option #
    cin >> choice;
    // input validation is performed, to ensure that the user does not input an invalid menu option #
    // if they input an invalid choice, they will be prompted again until they enter a valid choice
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }

    return choice; // return int choice to main()
}

// void add_goat(list<Goat> &trip, string nms[], string cls[]) function header
// DESCRIPTION: this function adds a new Goat object to the end of the list. Name, age, and color are all randomly selected and assigned to the Goat object
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// - string nms[], which is an array of names. A name will be randomly selected from this array
// - string cls[], which is an array of colors. A color will be randomly selected from this array
// RETURNS: nothing, void function
void add_goat(list<Goat> &trip, string nms[], string cls[]) 
{
    cout << "ADD A GOAT\n";
    int age = rand() % (MAX_AGE + 1); // random assignment of a age between 0 - 20 (MAX_AGE) and assigning it to "age"
    string nm = nms[rand() % SZ_NAMES]; // random selection of a name within the "nms" array and assigning it to "nm"
    string cl = cls[rand() % SZ_COLORS]; // random selection of a color within the "cls" array and assigning it to "cl"
    Goat tmp(nm, age, cl); // creation of a temp "tmp" Goat object with all 3 parameters
    trip.push_back(tmp); // using .push_back() member function, adds Goat object to the end of the list 
    cout << "Goat added. New trip size: " << trip.size() << endl; // using .size() member function, to display the new size of the trip
}

// void delete_goat(list<Goat> &trip) function header
// DESCRIPTION: this function deletes a user-chosen Goat object within the list
// - this function works hand-in-hand with the select_goat() function 
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void delete_goat(list<Goat> &trip) 
{
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip); // select_goat() function call, assigns user's choice of which Goat object (#) to delete to index
    // creation of an iterator using the C++ 11 "auto" keyword, since we cannot access objects by index
    auto it = trip.begin(); // using .begin() member function to start at the beginning of the list
    advance(it, index-1); // advance the iterator to the position of the Goat object we want to delete
    trip.erase(it); // using .erase() member function, to erase the Goat object at the position of the iterator
    cout << "Goat deleted. New trip size: " << trip.size() << endl; // using .size() member function, to display the new size of the trip
}

// void display_trip(list<Goat> trp) function header
// DESCRIPTION: this function neatly outputs the contents of the list
// ARGUMENTS: list<Goat> trp, which is a list of Goat objects
// RETURNS: nothing, void function
void display_trip(list<Goat> trp) 
{
    int i = 1; // to keep track of the # of goats in the list
    for (auto gt: trp) // using a C++ 11 range loop and "auto" keyword to output contents of the list
    // calling all getters to output names, ages, and colors for each Goat object
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

// void reverse_trip(list<Goat> &trip) function header
// DESCRIPTION: this function will reverse the order of the Goat objects stored in the std::list
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void reverse_trip(list<Goat> &trip)
{
    reverse(trip.begin(), trip.end()); // using the reverse member function to reverse the order of the std::list from beginning to end
    cout << "The order of the goat trip has been reversed:" << endl;
    display_trip(trip); // display_trip() function call to output the modified std::list
}

// void find_goat(list<Goat> trip) function header
// DESCRIPTION:
// ARGUMENTS: list<Goat> trip, which is a list of Goat objects
// RETURNS: nothing, void function
void find_goat(list<Goat> trip)
{

}

// int select_goat(list<Goat> trp) function header
// DESCRIPTION: this function will output the contents of the list, prompt the user to select a Goat object (#) they would like to delete from the list, and then return this choice
// - the user's choice is validated to ensure they do not select a # that is not within the range of the list size
// this function works hand-in-hand with the delete_goat() function, because delete_goat() requires SELECTION of a specific goat
// ARGUMENTS: list<Goat> trp, which is a list of Goat objects
// RETURNS: int input, which is the user input for the Goat object # they would like to delete
int select_goat(list<Goat> trp) 
{
    int input; // to hold user's choice for goat # they wish to select
    cout << "Make a selection:\n";
    display_trip(trp); // display_trip() function call, to display the current list of Goat objects for the user to select from
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) // using .size() member function - loop ensures that the user does not enter a number that is less/greater than the size of the list
    {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }

    return input; // return int input
}
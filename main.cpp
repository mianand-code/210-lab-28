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
#include <numeric> // to use accumulate
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
void increase_age_for_each(list<Goat> &trip);
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
    while (sel != 12) // creation of a while loop so that the user can continue to select menu options until they wish to quit program (option #12)
    {
        switch (sel) // creation of a switch statement that handles cases of each numbered menu option - based on sel
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
                increase_age_for_each(trip); // increase_age_for_each() function call, will increase the age by 1 for each Goat object
                break;
            
            case 8:
                fill_trip(trip); // fill_trip() function call, will fill/reset the 1st 3 Goat objects in the list to default values
                break;

            case 9:
                accumulate_trip_age(trip); // accumulate_trip_age() function call, will take the ages of all of the Goat objects and sum them up
                break;

            case 10:
                erase_goats_below_age(trip); // erase_goats_below_age() function call, will erase goats that are below a certain age
                break;

            case 11:
                clear_trip(trip); // clear_trip() function call, will completely clear all of the Goat objects stored in the std::list
                break;

            case 12:
                // option #12 is when user wants to quit
                break;

            // user input validation for menu option # (has to be 1-12)
            // main_menu() function also handles user input validation, but it is good to include it here also for completeness
            default:
                cout << "Invalid selection.\n";
                break;
        }
        
        sel = main_menu(); // prompt the user to enter another selection
    }

    cout << "Exiting program..." << endl; // option #12 was entered
    
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
    cout << "[7] Increase the age (by 1) for each goat" << endl;
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
    while (choice < 1 || choice > 12) 
    {
        cout << "Invalid, again --> ";
        cin >> choice;
    }

    return choice; // return int choice to main()
}

// void add_goat(list<Goat> &trip, string nms[], string cls[]) function header
// DESCRIPTION: this function adds a new Goat object to the end of the list. Name, age, and color are all randomly selected and assigned to the Goat object
// - the new trip size is displayed after adding a new object
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
    cout << "Goat added. New trip size: " << trip.size() << endl << endl; // using .size() member function, to display the new size of the trip
}

// void delete_goat(list<Goat> &trip) function header
// DESCRIPTION: this function deletes a user-chosen Goat object within the list
// - the new trip size is displayed after deleting an object
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
// DESCRIPTION: this function neatly outputs the contents of the std::list
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
    cout << endl;
}

// void reverse_trip(list<Goat> &trip) function header
// DESCRIPTION: this function will reverse the order of the Goat objects stored in the std::list
// - the modified std::list is then printed
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void reverse_trip(list<Goat> &trip)
{
    trip.reverse(); // using the reverse member function to reverse the order of the std::list
    cout << "The order of the goat trip has been reversed:" << endl;
    display_trip(trip); // display_trip() function call to output the modified std::list
}

// void find_goat(list<Goat> trip) function header
// DESCRIPTION: this function prompts the user to enter the name of a goat that they would like to find within the std::list
// - disclaimer: the user is informed that name entry is case sensitive, they should enter the goat's name exactly the way it is stored within the std::list
// - if the goat is found, the goat's age and color are also printed. The user is notified if the goat is not found
// - note: if there are duplicate names within the list, the name that comes first in the list will be the one whose data is printed
// ARGUMENTS: list<Goat> trip, which is a list of Goat objects
// RETURNS: nothing, void function
void find_goat(list<Goat> trip)
{
    string name; // to hold the name of the goat the user would like to find
    cin.ignore(); // needed after cin and before getline
    cout << "Enter the name of the goat you want to find (case sensitive): ";
    getline(cin, name);
    while (name.empty()) // user input validation, to ensure the field is not left blank
    {
        cout << "ERROR: Name field cannot remain blank. Please try again & enter a name: ";
        getline(cin, name);
    }

    // create an iterator
    // use the find_if member function to find the goat within the std::list
    // find_if will start at the beginning of the std::list and search until the end (trip.begin() and trip.end())
    // [name] is used to compare the user's input to each of the names of the Goat objects stored within the std::list
    // const Goat& g is a reference to a Goat object, const is used to signify that the original object should not be modified
    // return g.get_name() == name checks if the name entered by the user matches the name of a certain Goat object within the std::list
    auto it = find_if(trip.begin(), trip.end(), [name](const Goat& g){ return g.get_name() == name; });
    if (it != trip.end()) // if the iterator has not gone beyond the range of the std::list, we have found the goat
        cout << it->get_name() << " found with age " << it->get_age() << " and color " << it->get_color() << endl << endl; // call all getters to display info about goat
    else
        cout << name << " was not found." << endl << endl;
}

// void any_of_goat_age(list<Goat> trip) function header
// DESCRIPTION: this function checks if a specific age entered by the user matches any of the ages of the Goat objects stored in the std::list
// - "yes" or "no" will be printed, depending on whether a match/matches were found or not
// ARGUMENTS: list<Goat> trip, which is a list of Goat objects
// RETURNS: nothing, void function
void any_of_goat_age(list<Goat> trip)
{
    int age; // to hold the age the user would like to check for (to see if any Goat objects have this age)
    // creation of a do-while loop to ensure user input validation - prompt user until they enter a valid age (0-21)  
    // 21 is the max because our increase_age_for_each() function can increase the MAX_AGE (20) by 1
    do
    {
        cout << "Enter the goat's age you would like to check/search for (0-21): ";
        cin >> age;

        if (age < 0 || age > 21) 
            cout << "ERROR: Goat's age must be between 0-21. Please try again and enter a valid age." << endl;

    } while (age < 0 || age > 21);

    // create a bool named "hasAge"
    // use the any_of member function to check if any of the Goat objects within the std::list match the age that the user entered
    // any_of will start at the beginning of the std::list and search until the end (trip.begin() and trip.end())
    // [age] is used to compare the user's input to the ages of the Goat objects stored within the std::list
    // const Goat& g is a reference to a Goat object, const is used to signify that the original object should not be modified
    // return g.get_age() == age checks if the age entered by the user matches the age of a certain Goat object within the std::list. True or false is returned
    bool hasAge = any_of(trip.begin(), trip.end(), [age](const Goat& g){ return g.get_age() == age; });
    cout << "Is there a goat with age " << age << "? " << (hasAge ? "Yes" : "No") << endl << endl; // yes will be printed if a match/matches are found, otherwise no will be printed
}

// void increase_age_for_each(list<Goat> &trip)
// DESCRIPTION: this function will will increase the age (by 1) for each Goat object within the std::list
// - the modified std::list is then printed
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void increase_age_for_each(list<Goat> &trip)
{
    // use the for_each member function to increase the age of each goat by 1
    // for_each will start at the beginning of the std::list and continue to the end (trip.begin() and trip.end())
    // Goat& g is a reference to a Goat object
    // g.set_age(g.get_age() + 1) - gets the age of the Goat object, adds 1 to it, and sets this value as the new age
    for_each(trip.begin(), trip.end(), [](Goat& g){ g.set_age(g.get_age() + 1); });
    cout << "The age of each goat has been increased by 1:" << endl;
    display_trip(trip); // display_trip() function call to output the modified std::list
}

// void fill_trip(list<Goat> &trip) function header
// DESCRIPTION: this function takes a range of Goat objects (in this case, the 1st 3 goats) and fills them with set default values
// - this resets the values of the 1st 3 goats
// - the modified std::list is then printed
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void fill_trip(list<Goat> &trip)
{
    // using the fill member function to fill a range with a placeholder goat (resetting the first 3 to default values)
    // name & color will be set to "Unknown" and age will be set to 0
    fill(trip.begin(), next(trip.begin(), 3), Goat("Unknown", 0, "Unknown"));
    cout << "The first 3 Goat objects have been filled/reset to default values:" << endl;
    display_trip(trip); // display_trip() function call to output the modified std::list
}

// void accumulate_trip_age(list<Goat> trip) function header
// DESCRIPTION: this function takes the ages of all of the Goat objects, sums them up, and outputs the calculated total
// ARGUMENTS: list<Goat> trip, which is a list of Goat objects
// RETURNS: nothing, void function
void accumulate_trip_age(list<Goat> trip)
{
    // creation of an int variable named "totalAge"
    // use the accumulate member function to sum up the ages of all Goat objects within the std::list
    // accumulate will start at the beginning of the std::list and continue until the end (trip.begin() and trip.end())
    // the sum will start at 0
    // int sum will keep a running total of all the ages
    // const Goat& g is a reference to a Goat object, const is used to signify that the original object should not be modified
    // return sum + g.get_age() - the age of a single Goat object will be added to the sum we have accumulated so far
    int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g){ return sum + g.get_age(); });
    cout << "Total age (after summing up ages of all goats): " << totalAge << endl << endl;
}

// void erase_goats_below_age(list<Goat> &trip) function header
// DESCRIPTION: this function will erase all goats that are below a certain age (age is provided through user input)
// - the modified std::list is then printed
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void erase_goats_below_age(list<Goat> &trip)
{
    int age; // to hold the user's choice for age (this age will determine the Goat objects that are being erased)
    // creation of a do-while loop to ensure user input validation - prompt user until they enter a valid age (1-21) 
    // - 21 is the max because our increase_age_for_each() function can increase the MAX_AGE (20) by 1
    // - 1 is the minimum because an age below 1 is 0, which is still valid. But no goats have a negative age
    do
    {
        cout << "Enter a age. Any goats that are below this age will be erased from the list (1-21): ";
        cin >> age;

        if (age < 1 || age > 21) 
            cout << "ERROR: Goat's age must be between 1-21. Please try again and enter a valid age." << endl;

    } while (age < 1 || age > 21);

    // erase and remove_if member functions are used to erase goats below a certain age
    // starts at the beginning of the std::list and continues until the end (trip.begin() and trip.end())
    // [age] is used to compare the user's input to the ages of the Goat objects stored within the std::list
    // Goat& g is a reference to a Goat object
    // return g.get_age() < age checks if any of the Goat objects within the std::list are below the age that the user entered
    trip.erase(remove_if(trip.begin(), trip.end(), [age](Goat& g){ return g.get_age() < age; }), trip.end());
    cout << "All goats below the age " << age << " have been erased from the list." << endl;
    display_trip(trip); // display_trip() function call to output the modified std::list
}

// void clear_trip(list<Goat> &trip) function header
// DESCRIPTION: this function will completely clear all of the Goat objects stored in the std::list
// ARGUMENTS: list<Goat> &trip, which is a list of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void clear_trip(list<Goat> &trip)
{
    trip.clear(); // using clear member function to completely clear the std::list
    cout << "Trip cleared. New trip size: " << trip.size() << endl << endl; // using .size() member function, to display the new size of the trip
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

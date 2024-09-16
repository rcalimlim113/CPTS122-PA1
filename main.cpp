/*
ADVANTAGES/DISADVANTAGES LINKED LIST
ADVANTAGES/DISADVANTAGES ARRAY
*/

#include <iostream>
#include <string>
using namespace std;

#include "matchgame.hpp"

int main()
{
    linkedList <string, string> commandList;
    string comName, comDefinition;
    fstream infile("commands.csv");
    int size = commandList.populateList(infile, comName, comDefinition);

    string userName, newCommandToAdd, oldCommandTodelete;
    int selection;
    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        cout << "Your selection: ";
        cin >> selection;
        if (cin.fail()) // the input is not an integer
        {
            cout << "Your selection is invalid. Please select again." << endl;
            cout <<"=============================================================================" <<
            endl << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            switch (selection)
            {
                case 1: // Game Rules
                {
                    cout << "================================= Game Rule===================================" << endl;
                    cout << "To play the game, select \"2\" where you will be prompted for your name and number of questions.\n";
                    cout << "Each question presents a specific Linux command where you will be able to choose from 3 different options. Each correct answer yields a point.\n";
                    cout << "You can also add and delete commands as needed.\n";
                    cout << "================================= Game Rule===================================" << endl << endl;
                    break;
                }
                case 2: case 3: // 2. Play Game; 3. Load Previous Game
                {
                    cout << "Please enter your name: ";
                    cin >> userName;
                    break;
                }
                case 4: // Add Command
                {
                    cout << "To add a command to the library, please enter the command name that you would add: ";
                    cin >> newCommandToAdd;
                    break;
                }
                case 5: // Remove Command
                {
                    cout << "Please enter the name of the command that you would remove: ";
                    cin >> oldCommandTodelete;
                    break;
                }
                case 6: // Exit
                {
                    return 0;
                }
            } // end of switch(selection)
        } // end of else: check (cin.fail())
    } // end of while(true)
} // end of int main()
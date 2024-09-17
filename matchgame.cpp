#include "matchgame.hpp"

//rules function, prints the game rules when called from the main menu
void printRules()
{
	char anything = NULL;
	system("Clear");
	cout << "Welcome to Ryan's Linux Command Matching Game!\nThe rules are as follows:\nUpon selecting \"Play Game\" or \"Load Game\" you will be asked to enter your name.\nIf you have played before, entering the same name will bring up your old score for you to continue.\nOtherwise, the game will make a new profile for you.\nFor the game itself, you will first be asked how many questions you wish to answer.\nEach question will be a linux command, with three answers, one of which is correct.\nSelect correctly, +1 point. Incorrect? -1 point.\nThere are no upper or lower point limits.\n" << endl;
	cout << "Please enter any key to continue" << endl;
	cin >> anything;
	return;
}

//populate profiles function, pulls user profile data from profiles.csv and populates the player array
void populateUserProfiles(userProfile playerArray[])
{
	//string to store score
	string score;
	//count variable to travel through array
	int count = 0;
	fstream infile("profiles.csv");
	//limit the number of profiles to 100 (0-99), as the array is only 100 cells (prevent array overflow)
	while (!infile.eof() || count <= 99)
	{
		getline(infile, playerArray[count].username, ',');
		getline(infile, score);
		playerArray[count].score = stoi(score);
		count++;
	}
	if (count > 100)
	{
		cout <<"There are too many profiles in profiles.csv, only the first 100 were copied into the userProfile playerArray.";
	}
	infile.close();
}

//find user function, checks to see if the given name has a profile, and if so, returns it. otherwise, returns a profile with a NULL name field
userProfile findUser(userProfile playerArray[100], string name)
{
	//count variable to go through array
	int count = 0;
	//temp profile, set name to NULL
	userProfile tempProfile;
	tempProfile.username = "NULL";
	//check if that name is the first one
	if (playerArray[count].username == name)
	{
		tempProfile = playerArray[count];
		return tempProfile;
	}
	//go through array until name is found
	while (playerArray[count].username != name)
	{
		count++;
		//once its found set temp profile as that name's profile
		if (playerArray[count].username == name)
		{
			tempProfile = playerArray[count];
			return tempProfile;
		}
		//count = 100, this name is not in the profile array (100 cells, 0-99)
		if (count = 100)
		{
			cout << "This name is not stored already, you will make to start a new game (Main Menu Option 2).";
			return tempProfile;
		}
	}
	
	
	//return the profile
	return tempProfile;
}

//add command function, adds a new command to the linked list
void newCommand(linkedList<string,string> commandList)
{
	return;
}

//remove command function, deletes a command from the linked list
void deleteCommand(linkedList<string,string> commandList)
{
	return;
}

//run game function for new players, calls the HRunGame helper function to actually run the game
void runGame(linkedList<string,string> commandList, fstream& infile)
{
	return;
}

//overloaded run game function for returning players, calls the HRunGame helper function to actually run the game
void runGame(userProfile player)
{
	return;
}

//run game helper function, actually runs the game. is called by the runGame overloaded function which will decide new or returning player & feed corresponding arguments to this helper function
int HRunGame(node<string,string>* head, userProfile playerArray[], userProfile player, int index)
{
	return 0;
}

//save data function, runs when the game is exited to save the new command list & player data to their respective .csv files
void saveData(linkedList<string,string> commandList, userProfile playerArray[])
{
	return;
}

//overloaded ofstream << operator to make it work with the struct data type userProfile
ofstream& operator << (ofstream& lhs, userProfile& rhs)
{
	return lhs;
}

void gameMenu()
{
	//initializing my linked list, player array, command strings, the file stream, etc.
	linkedList <string, string> commandList;
	userProfile player;
	userProfile playerArray[100];
    string comName, comDefinition;
    fstream infile("commands.csv");
	//adding the commands and profiles from their .csvs to their linked list/array
	populateUserProfiles(playerArray);
    int size = commandList.populateList(infile, comName, comDefinition);

	//main menu selection stuff
    string selection;
    int option = 0;

	//testing the player array was populated correctly
	cout << playerArray[0].username<<endl;
	cout << playerArray[0].score <<endl;
	cout << playerArray[1].username<<endl;
	cout << playerArray[1].score <<endl;

	//double do-while loop to keep players in the menu/game until they exit
	do
	{
		do
		{
			cout << "Welcome to Ryan's Linux Command Matching Game!\n";
			cout << "Please select an option below\n";
			cout << "1 Game Rules\n2 Play Game\n3 Load Previous game\n4 Add Command\n5 Remove Command\n6 Exit Game\n";
			cout << "Enter your selection here:  ";
			cin >> selection;
			option = stoi(selection);
			if (option < 1 || option > 6)
			{
				cout << "\nThat is not a valid selection, please try again.\n";
			}
		} while (option < 1 || option > 6);

		switch (option)
		{

			case 1: //game rules
			{
				printRules();
				break;
			}
			case 2: //play game 
			{
				//play game with no player argument (new game)
				break;
			}
			case 3: //load previous game
			{
				string name;
				cout << "Please enter your name below:" << endl;
				cin >> name;
				userProfile player = findUser(playerArray, name);
				if (player.username == name)
				{
					cout << "The profile \"" << player.username << "\" has \"" << player.score << "\" points." << endl;
					//play game with player argument
					
				}
				if (player.username == "NULL")
				{
					cout << "The profile \"" << name << "\" does not exist. Please select option 2 for a new game." << endl;
				}
				break;
			}
			case 4: //add command
			{
				//newCommand(commandList);
				break;
			}
			case 5: //remove command
			{
				//deleteCommand(commandList);
				break;
			}
			case 6: //exit game
			{
				//save data to .csv files
				//saveData(commandList, playerArray);
				//this is how I break the double do-while loop
				option = 100;
				break;
			}

		}

		//if the exit option is slected, then the double do-while loop is broken
		if (option == 100)
		{
			return;
		}

	} while (option > 0 || option < 7);
}
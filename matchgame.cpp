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
int findUser(userProfile playerArray[100], string name)
{
	//temp profile, set name to NULL
	userProfile tempProfile;
	tempProfile.username = "NULL";
	//look through array with a for loop
	for (int i = 0; i < 100; i++)
	{
		//if the profile is found, return its location in the array
		if (playerArray[i].username == name)
		{
			return i;
		}
	}
	//return the profile
	return -1;
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
void runGame(node<string,string>* head, userProfile playerArray[100], int size)
{
	return;
}

//overloaded run game function for returning players, calls the HRunGame helper function to actually run the game
void runGame(node<string,string>* head, int arrayPosition, userProfile playerArray[100], int size)
{
	//variables to store new score and iterate through player array
	int newScore = 0, count =0;
	//run the game, get the new score
	newScore = HRunGame(head, playerArray[arrayPosition], size);
	cout << "Your current score is now: \"" << newScore << "\"" <<endl;
	playerArray[arrayPosition].score = newScore;
	return;
}

//run game helper function, actually runs the game. is called by the runGame overloaded function which will decide new or returning player & feed corresponding arguments to this helper function
int HRunGame(node<string,string>* head, userProfile player, int size)
{
	//3 index variables for the correct & incorrect answers, 1 int used to randomize the display order, and 1 used to store question count
	int goodIndex, badIndex1, badIndex2, printOrder, qCount, qAnswer;
	//array to store if a question has been asked yet
	int qAsked[size];
	//3 node pointers, 1 for each answer
	node<string,string>* pGood = head;
	node<string,string>* pBad1 = head;
	node<string,string>* pBad2 = head;
	//ask how many questions to have
	cout << "How many matching questions would you like? There are currently \"" << size << "\" questions total." << endl;
	cin >> qCount;
	//loop until that many questions are given
	for (int count = 0; count < qCount; count++)
	{
		//set answer order randomizer & player answer fields to 0 to start
		printOrder = 0;
		qAnswer = 0;
		//find 2 random bad answers
		badIndex1 = rand() % size;
		badIndex2 = rand() % size;
		//find a good answer that is different, and hasn't been picked before
		do 
		{
			goodIndex = rand() % size;
		} while(goodIndex == badIndex1 || goodIndex == badIndex2 || qAsked[goodIndex] == -1);
		//mark that question as picked for the rest of the game
		qAsked[goodIndex] = -1;
		//reset pointers to head each loop
		pGood = head;
		pBad1 = head;
		pBad2 = head;
		//set pointers to the correct nodes w/ for loops
		for (int i =0; i< goodIndex; i++)
		{
			pGood = pGood->pNext;
		}
		for (int i =0; i< badIndex1; i++)
		{
			pBad1 = pBad1->pNext;
		}
		for (int i =0; i< badIndex2; i++)
		{
			pBad2 = pBad2->pNext;
		}
		//randomize the order the answer are printed
		printOrder = rand() % 3 + 1;
		cout << "What is the definition of the command \"" << pGood->command << "\"?\n";
		//correct answer on top
		if (printOrder == 1)
		{
			cout << " 1) \"" << pGood->definition << "\"\n";
			cout << " 2) \"" << pBad1->definition << "\"\n";
			cout << " 3) \"" << pBad2->definition << "\"\n";			
		}
		//correct answer in the middle
		if (printOrder == 2)
		{
			cout << " 1) \"" << pBad1->definition << "\"\n";
			cout << " 2) \"" << pGood->definition << "\"\n";
			cout << " 3) \"" << pBad2->definition << "\"\n";	
		}
		//correct answer on the bottom
		if (printOrder == 3)
		{
			cout << " 1) \"" << pBad1->definition << "\"\n";
			cout << " 2) \"" << pBad2->definition << "\"\n";
			cout << " 3) \"" << pGood->definition << "\"\n";
		}
		//get their answer
		cout << "Please enter your selection below (1, 2, or 3):\n" << endl;
		cin >> qAnswer;
		//answer is correct
		if (qAnswer == printOrder)
		{
			cout <<"DING!! Correct!! 1 Point will be added to your score.\n";
			player.score++;
			cout <<"Your current score is now:\"" << player.score << "\" Points.\n";
			cout << "Please enter any key to continue" << endl;
			cin >> qAnswer;
		}
		//answer is incorrect
		else
		{
			cout <<"BZZZZT!! I'm sorry, that is incorrect. 1 Point will be deducted from your score.\n";
			player.score--;
			cout <<"Your current score is now:\"" << player.score << "\" Points.\n";
			cout << "Please enter any key to continue" << endl;
			cin >> qAnswer;
		}
	}
	return player.score;
}

//save data function, runs when the game is exited to save the new command list & player data to their respective .csv files
void saveData(node<string,string>* head, userProfile playerArray[])
{
	//opens commands.csv
	fstream outfilecommand("commands.csv");
	//temp node to traverse the linked list
	node<string,string>* pCur = head;
	//check file was opened correctly
	if (!outfilecommand)
	{
		cout << "Error opening commands.csv" << endl;
		return;
	} 
	//loop through list & output to file
	while (pCur!=nullptr)
	{
		outfilecommand << pCur->command << "," << pCur->definition << "\n";
		
		cout << pCur->command << "," << pCur->definition << "\n";
		pCur = pCur->pNext;
	}
	//close file & return
	outfilecommand.close();

	//opens profiles.csv
	fstream outfileprofile("profiles.csv");
	//check file was opened correctly
	if (!outfileprofile)
	{
		cout << "Error opening profiles.csv" << endl;
		return;
	} 
	//loop through array & output to file
	for (int i = 0; i < 100; i++)
	{
		outfileprofile << playerArray[i].username << "," << playerArray[i].score << "\n";
		cout << playerArray[i].username << "," << playerArray[i].score << "\n";
		//if the array still has cells to go, but they are empty, break the for loop(array has 100 cells, they might not all be full. dont want to loop a bunch unnecesarrily)
		if (playerArray[i].username == "")
		{
			i = 10000;
		}
	}
	//close file & return
	outfileprofile.close();

	//cout << "save data success";
	return;
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
	cout << playerArray[2].username<<endl;
	cout << playerArray[2].score <<endl;

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
				//get player name
				string name;
				cout << "Please enter your name below:" << endl;
				cin >> name;
				//see if this user exists and open the game, or send them back to the main menu
				int arrayPosition;
				arrayPosition = findUser(playerArray, name);
				if (playerArray[arrayPosition].username == name)
				{
					cout << "The profile \"" << playerArray[arrayPosition].username << "\" has \"" << playerArray[arrayPosition].score << "\" points." << endl;
					runGame(commandList.getHead(), arrayPosition, playerArray, size);
					break;
					
				}
				if (player.username == "NULL")
				{
					cout << "The profile \"" << name << "\" does not exist. Please select option 2 for a new game." << endl;
					break;
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
				saveData(commandList.getHead(), playerArray);
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
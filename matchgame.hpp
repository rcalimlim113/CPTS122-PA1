//guard code and my includes & using bits
#pragma once

#define MATCHGAME__H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdlib.h> 
#include <fstream>
#include <time.h>

using namespace std;
using std::string;
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::getline;
using std::stoi;

//user profile struct, stores name & score
struct userProfile
{
    string username;
    int score;
};

//node struct, stores 2 templates for the commands and definitions and a pointer to another node
template <typename C, typename D>
struct node
{
    C command;
    D definition;
    node* pNext;
};

//linked list class, stores the head and tail pointers of a singly linked list made of template nodes 
template <typename C, typename D>
class linkedList
{
    private:
        //pointers to head and tail nodes
        node<C,D> *head, *tail;

        //helper function to recursivly destroy the linked list
        void HDestroyList(node<C,D>*temp)
        {
            if (temp != nullptr)
            {
                HDestroyList(temp->pNext);
                delete temp;
            }
        }

        //helper function to destroy individual nodes without breaking the whole list
        void HDestroyNode(node<C,D>*temp)
        {
            node<C,D>* pCur = head;
            node<C,C>*pLast = head;

            //while loop to find the node to remove
            while (pCur!=nullptr && pCur!= temp)
            {
                pLast = pCur;
                pCur = pCur->pNext;
            }
            if (pCur == temp)
            {
                //delete the node, pLast maintains the list be storing the last node & the node after the deleted one
                pLast->pNext = pCur->pNext;
                delete pCur;
            }
            return;
        }

    public:

        //start with head and tail set to NULL
        linkedList()
        {
            head = NULL;
            tail = NULL;
        }

        //head getter 
        node<C,D>* getHead()
        {
            return head;
        }

        //tail getter
        node<C,D>* getTail()
        {
            return tail;
        }

        //new node function, takes 2 template arguyments for the command and it's definition, makes a node, and adds it to the list (insertAtFront is built in)
        void newNode(C command, D definition)
        {
            //make new node & store input data
            node<C,D>* temp = new node<C,D>;
            temp->command = command;
            temp->definition = definition;
            temp->pNext = NULL;

            //if linked list is empty, make the new node the head node 
            if(head == NULL)
            {
                //check temp was actually made
                if(temp != nullptr)
                {
                    head = temp;
                    tail = temp;
                }
            }
            //otherwise add the node to the end
            else
            {
                //check temp was actually made
                if(temp != nullptr)
                {
                    tail->pNext = temp;
                    tail = temp;
                }

            }
        }

        //remove node function, finds the selected node and calls the destroy node helper function to destroy it without breaking the list
        void removeNode(C command)
        {
            //make a temo node to hold head
            node<C,D>* temp = head;
            //check the list isnt empty
            while (temp != nullptr)
            {
                //if the command is head of the list
                if (head->command == command)
                {
                    head = head->pNext;
                    HDestroyNode(temp);
                    return;
                }
                //otherwise, find the command
                while (temp->command != command)
                {
                    temp = temp->pNext;
                }
                //once found, destroy it
                if (temp->command == command)
                {
                    HDestroyNode(temp);
                    return;
                }
            }
        }

        //destructor, calls the destroylist function
        ~linkedList()
        {
            this->destroyList();
        }
        
        //calls the destroy list helper function which recursively destroys the list starting from the head
        void destroyList()
        {
            HDestroyList(this->head);
        }

        //populator, fills the list out with the data input from the commands.csv input file stream. returns the size of the list
        int populateList(fstream& infile, C command, D definition)
        {
            int size = 0;
            while (!infile.eof())
            {
                //reads the command and defintion through getline with a "," delimiter
                getline(infile, command, ',');
                getline(infile, definition);

                //make a new node with the input data, increase size by 1
                this->newNode(command, definition);
                size++;
            }
            return size;
        }
};

//rules function, prints the game rules when called from the main menu
void printRules();

//populate profiles function, pulls user profile data from profiles.csv and populates the player array
void populateUserProfiles(userProfile playerArray[100]);

//find user function, checks to see if the given name has a profile, and if so, returns it. otherwise, returns a profile with a NULL name field
int findUser(userProfile playerArray[100], string name);

//add command function, adds a new command to the linked list
void newCommand(linkedList<string,string>& commandList);

//remove command function, deletes a command from the linked list
void deleteCommand(linkedList<string,string>& commandList);

//run game function for new players, calls the HRunGame helper function to actually run the game
void runGame(node<string,string>* head, userProfile playerArray[100], int size);

//overloaded run game function for returning players, calls the HRunGame helper function to actually run the game
void runGame(node<string,string>* head, int arrayPosition, userProfile playerArray[100], int size);

//run game helper function, actually runs the game. is called by the runGame overloaded function which will decide new or returning player & feed corresponding arguments to this helper function
int HRunGame(node<string,string>* head, userProfile player, int size);

//save data function, runs when the game is exited to save the new command list & player data to their respective .csv files
void saveData(node<string,string>* head, userProfile playerArray[100]);

//game wrapper function, actually runs the program
void gameMenu();
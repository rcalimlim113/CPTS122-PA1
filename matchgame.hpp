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
            //delete the node, pLast maintains the list be storing the last node & the node after the deleted one
            pLast->pNext = pCur->pNext;
            delete pCur;
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

        //new node function, takes 2 template arguyments for the command and it's definition, makes a node, and adds it to the list
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
                if(temp != nullptr)
                {
                    temp->pNext = head;
                    head = temp;
                }
            }
            //otherwise add the node to the end
            else
            {
                //list has 1 entry, the head. tail is null atm and must be populated
                if (head->pNext==nullptr)
                {
                    temp->pNext = tail;
                    tail = temp;
                    head->pNext = temp;
                }
                //there is a tail, make it point to the new node and then make the new node the tail
                else
                {
                    tail->pNext = temp;
                    tail = tail->pNext;
                }
            }
        }

        //remove node function, finds the selected node and calls the destroy node helper function to destroy it without breaking the list
        void removeNode(C command)
        {
            node<C,D>* temp = head;
            while (temp != nullptr)
            {
                if (temp->command != command)
                {
                    temp = temp->pNext;
                }
                else
                {
                    HDestroyNode(temp);
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

        int populateList(fstream& infile, C command, D definition)
        {
            int size = 0;
            while (!infile.eof())
            {
                getline(infile, command, ',');
                getline(infile, definition);

                this->newNode(command, definition);
                size++;
            }
            return size;
        }
};
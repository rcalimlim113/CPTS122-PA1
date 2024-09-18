//Ryan Calimlim, CPTS 223, PA1, Linux Command Matching Game

/*
ADVANTAGES/DISADVANTAGES LINKED LIST
Advantage:
Manipulating a node/linked list is very easy, I can pass pointers to it through functions and for most applications I can pass the whole list or just a pointer to the head and do what I need.
Disadvantage:
Finding the actual node I want to manipulate is very annoying. I have to go through the entire list before it, checking to see if it is the node I want.

ADVANTAGES/DISADVANTAGES ARRAY
Advantage:
Finding the cell I want to access is very easy. As long as I know which index I want, I just need to put that number in and I can access it instantly without passing through every previous cell.
Disadvantage:
Manipulating that array through functions is annoying. For most of my functions I have to pass in an arrayPosition int variable in addition to the array, and use both. For a linked list I can just pass a pointer to a node.
*/

//I looked at https://www.geeksforgeeks.org/cpp-program-for-selecting-a-random-node-from-a-singly-linked-list/?ref=oin_asr3 for help on randomizing which answers
//were asked for questions in the game. I didn't copy code but I used the same method

#include "matchgame.hpp"

int main()
{
   
    gameMenu(); 	

	return 0;

}
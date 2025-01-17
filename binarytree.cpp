binarytree.h                                                                                        0000771 0020221 0020221 00000001727 12417617034 012710  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstddef>
//#include <string>
#include "node.h"

//Author: Himanshu Sahay
class binarytree
{
    public:
        binarytree();
        ~binarytree();

        void insert(std::string item_id, int row, int col, int floor, int item_quantity);
        //void insert(std::string item_id, store_node *new_store);
        item_node *search(std::string item_id);
        void destroy_tree();
        void print_tree();
        // virtual ~binarytree();


    private:
        void destroy_tree(item_node *child);
        void insert(std::string item_id, int row, int col, int floor, int item_quantity, item_node *child);
        //void insert(std::string item_id, store_node *new_store, item_node *child);
        item_node *search(std::string item_id, item_node *child);
        void print_tree(item_node *currNode);

        item_node *root;

};



#endif // BINARYTREE_H
                                         globals.h                                                                                           0000771 0020221 0020221 00000002772 12417617107 012171  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay

#pragma once

#ifdef __MAIN__
    #define __EXTERN(type, name, value)     type name = value
#else
    #define __EXTERN(type, name, value)     extern type name;
#endif

#ifndef GLOBALS_H
#define GLOBALS_H

enum direction{North, NorthWest, West, SouthWest, South, SouthEast, East, NorthEast, Up, Down};
enum type{A1,Store,Elevator,Plain,Fork,Empty};

//Author: Himanshu Sahay
struct sqr
{
  int direction;
  int type; //type is S for store, E for elevator, T is for regular tiles, A for A1, and N for everything else (For now, unless more types used)
  int forkid; //ID for deducing which direction to take at a fork. 0 for tiles that aren't forks. 1/2/..and so on for tiles that are forks in the path
  //Fork ID = 0 and type = Empty clears the floor before we operate on it.
  int storeid; //if not store, id = 0. Else, ID ordered by store
};

//Author: Himanshu Sahay
struct coord
{
  int r;
  int c;
  int f;
};


__EXTERN(struct sqr, fl[17][17][2], {}); //initializeing the structure of arrays


//Robot structure and initialization of new robot

/*
struct robot
{
  // x, y and z cooridnates of each destination (store or A1 when exiting the mall)
  struct coord destination;
  int rnum;
  struct coord lloc; //last location of robot, used to call function in hsahay_main.c

};




void move(struct robot *rptr, int *tptr, int x, int y, int z); //function to move



void floormap(); //global function to initialize floor map
*/


#endif
      hsahay_main.cpp                                                                                     0000771 0020221 0020221 00000023127 12417635745 013367  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay

//#include "globals.h"
#include "mall.h"
#include <iostream>
#include <string>
#include "binarytree.h"

using namespace std;

//Author: Himanshu Sahay
int main()
{

  cout<<"Stage 1 starts here"<<endl;
  //STAGE 1 STARTS HERE
  /*

Robot has a class.
Start with robot object. One of the class members is an array of pointers to the robots.
move() is now a member function fo the robot and can be called as mallobject->robotobject[i]->move(*tptr,x,y,z);
Mall is wrapper class for everything in this program

go to //CHECK THIS in mall->cpp
Call floormap() as mallObject.floormap();

*/


// Had to rewrite program 4 to make it work since first submission of program 4 did not work
//Variable Definitions for the item input implementation - currently done for 1 robot
  int i, num_unique_items,num_items;
  std::string item_id;
  binarytree item_tree;
  item_node *item_s_result = NULL;

  Mall *mall = new Mall(); //declaring new Mall object. Mall is wrapper class for program

  //struct robot rb; //Declares new robot (extern given in header)
  //int endtime[9],starttime[9]; //start and end times of robot simulation
  // int j;
  int time = 0;
  int rnum; //Number of robots
  int storenum; //Number of stores
  int *tptr;
  tptr = &time;
  int snum[9]; //number of stores for each robot



  //struct robot *rptr;
  //rptr = &rb; //Pointer to current robot
  int xtemp,ytemp,ztemp;
  //int snum[24]; //array for number of stroes for each robot

  // First take number of robots from user. Then take number of stores that each robot will visit.
  // Finally, take coordinates of each store to be visited

  cout << "Welcome to Robomall!" << endl;
  mall->floormap(); //Show floor map for user

  cout << "Enter the number of robots that will enter RoboMall: " << endl;
  cin>>rnum;
  cout<<"Number of robots is "<<rnum<<endl;
  //mall->R[0]->starttime = 0; //Start time of first robot is 0 time units

  for(i=0;i<rnum;i++)
    {
      cout << "Enter number of stores for robot " << i+1 <<endl;
      cin>>storenum;
      mall->R[i]->checkIfInMall = true; //robot is in the mall now
      snum[i]=storenum; //Adds number of stores for current store into the array for number of stores for all robots
      //cout<<"\nNo. of stores = "<<snum[i]<<endl;
    }
    //varibles to use in loops
    int q = 0;
    int p = 0;

    for(q=0;q<rnum;q++) //loop for number of robots
      {
        cout<<"\nNow, processing robot "<<q+1<<endl;
        for(p=0;p<=snum[q];p++) //One extra iteration to make the robot go back to the A1 tile
        {
          cout<<"\nNo. of stores for this robot: "<<snum[q];

          if(p==0) //First pass for a robot, when it goes to it's first store
            {
              cout  << "\nEnter coordinates for the store robot " << q+1 << " will visit: " << endl;
              cin >>xtemp>>ytemp>>ztemp;
              struct coord storetemp = {xtemp,ytemp,ztemp}; //Store coordinates to be visited

			         mall->R[q]->destination = storetemp;

              cout << "Enter Number of Items for this Store: " << endl;
              cin >> num_unique_items;
              cout << "Store Location: " << xtemp << " " << ytemp << " " << ztemp  << "    Number of Items to be Read In: " << num_unique_items << endl;

              //cout << "destination: " << mall->R[i]->destination.r << mall->R[i]->destination.c << mall->R[i]->destination.f << endl;
              cout << "\nRobot " << q+1 << " begins at entry location A1 at time " << mall->R[q]->starttime << endl;
              mall->R[q]->move(tptr,8,16,0); //Tells robot to start on the first tile //goes to first store

              *tptr+= num_unique_items; //robot spends one time unit in store per unique item type;

              for(i = 0; i < num_unique_items ; i++)
                {
                  cout<<"Robot is at store. Enter items to deliver followed by their counts: \n";
                  cin >> item_id >> num_items;
                  //Search the Tree for the Item_Id
                  if((item_s_result = item_tree.search(item_id)) == NULL)
                    {
                      item_tree.insert(item_id, xtemp, ytemp,ztemp, num_items);
                    }
                    else{
                      item_s_result->store_list.insert(xtemp,ytemp,ztemp,num_items);
                      //Add the New Store Location to the Linked List
                    }
                  //If it returns null, then add a new ID to the tree
                  //Else get add an entry for the store on the ID's linked list
                  cout << "Item ID: " + item_id << "    Number of Items: " << num_items << endl;
                }
            //continue;
			         // cout << "Last location: " << rb.lloc.r << " " << rb.lloc.c << " " << rb.lloc.f << endl;
        }//end if


         else if(p==snum[q]) //Final pass for a robot, when it goes back to the A1 position, to end it's simulation
            {
              struct coord storetemp = {8,16,0}; //To go back to A1 tile
              mall->R[q]->destination = storetemp;


              cout << "\nNew location set to (" << mall->R[q]->lloc.r << "," << mall->R[q]->lloc.c << "," << mall->R[q]->lloc.f << ")";
              mall->R[q]->move(tptr,mall->R[q]->lloc.r,mall->R[q]->lloc.c,mall->R[q]->lloc.f);
              cout << "\nRobot " << q+1 << " exits simulation at position A1 at time " << *tptr << endl;
              mall->R[q]->endtime = *tptr; //End time is the time when the robot reaches back to A1

			       //cout << "Last location: " << rb.lloc.r << " " << rb.lloc.c << " " << rb.lloc.f << endl;

            }//end else if

         else //All other passes for the robot, when it travels between stores
            {
              cout << "\nEnter coordinates for the stores robot " << q+1 << " will visit: ";
              cin>>xtemp>>ytemp>>ztemp;
              struct coord storetemp = {xtemp,ytemp,ztemp}; //Store coordinates to be visited
              mall->R[q]->destination = storetemp;

              cout << "Enter Number of Items for this Store: " << endl;
              cin >> num_unique_items;
              cout << "Store Location: " <<xtemp << " " << ytemp << " " << ztemp << "    Number of Items to be Read In: " << num_unique_items << endl;


              mall->R[q]->move(tptr,mall->R[q]->lloc.r,mall->R[q]->lloc.c,mall->R[q]->lloc.f);
			        //cout << "Last location: " << rb.lloc.r << " " << rb.lloc.c << " " << rb.lloc.f << endl;

              *tptr+= num_unique_items; //robot spends one time unit in store per unique item type;

              for(i = 0; i < num_unique_items ; i++)
              {
                cout<<"Robot is at store. Enter items to deliver followed by their counts: \n";
                cin >> item_id >> num_items;
                //Search the Tree for the Item_Id
                if((item_s_result = item_tree.search(item_id)) == NULL)
                {

                item_tree.insert(item_id, xtemp, ytemp, ztemp, num_items);
                }
              else
              {
                item_s_result->store_list.insert(xtemp, ytemp, ztemp, num_items);
                //Add the New Store Location to the Linked List
              }
              //If it returns null, then add a new ID to the tree
              //Else get add an entry for the store on the ID's linked list
              cout << "Item ID: " + item_id << "    Number of Items: " << num_items << endl;
              }

          }//end else

        (*tptr)+=1;

        // p++; //update p value
        // cout<<"No. of stores: "<<snum[q]<<" value of p varibale now: "<<p<<endl;

      }//end while loop for stores

      //  mall->R[i]->starttime=(mall->R[i-1]->endtime)+1; //Sets start time of next robot as end time of previous robot + 1 time unit
      // q++; //update q value
      cout<<"Value of q variable now: "<<q<<endl;
  } // while loop for robots



  // //Printing summary
  //   cout << "Summary of robot movememnt in mall" << endl;
  //   for(i=0;i<rnum;i++)
  //   cout << "\nRobot " << 1+i << " starts at " << mall->R[i]->starttime << " time units and ends at " << mall->R[i]->endtime << " time units\n";


  //Now, print database after robot has finished dropping off items
  cout<<"Print database: "<<endl;
  item_tree.print_tree();

cout<<"\n Stage 1 ends here\n";
//STAGE 1 ENDS HERE
  cout<<endl<<endl<<endl;

// //Author of Stage 2: Marco Duran
// cout << "Stage 2 \n";
//
// 	EventList database;
// 	Shopper s;
// 	Queue itinerary;
// 	i = 0;
// 	int arr_time; // the relative arrival time of the ith shopper to the simulation
// 	int j_items; // is the number of unique items on the ith shopper's shopping list
// 	string item; // is the 2 digit ASCII code for the jth item on the shopping list
// 	int count; // is the quantity of item that the shopper wants to buy
// 	int shoppers; //number of shoppers that are in the mall
// 	Store store;
// 	cout <<"Insert the number of shoppers that will be in the robomall";
// 	cin >> shoppers;
//
//
// 	while( i < shoppers)
// {//runs the loop until the amount of shoppers is reached
// 	cout << "Insert the arrival time of shopper" << i+1 << endl;
// 	cin >> arr_time;
// 	cout << "\nInsert the number of items on the shopping list" << endl;
// 	cin >> j_items;
//
// 	for(int j = 0; j < j_items; j++)
// 	{
// 		cin >> item >> count;
// 		cout <<"[DEBUG] Item code: " << item << " " << "ItemCount: " << count;
// 		if(s.searchItem(database, store) == true)
// 		store = database.rootPtr->store;
//
// 		if(s.searchItem(database, store) == false){ //searches for the item in the database
// 			s.deleteItem(itinerary.headPtr, itinerary.tailPtr);//if not found it deletes the item from the queue
// 		}
// 		else{
// 			s.addStore(store, itinerary, database);
// 		}
// 	}
//
// }



return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                         linkedlist.cpp                                                                                      0000771 0020221 0020221 00000012615 12417617162 013241  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay


#include <iostream>
#include <iomanip>
#include "linkedlist.h"
//#include <string>

//Defining the namespace for printing and reading in data
using namespace std;

//Author: Himanshu Sahay
//Public Constructor
linkedlist::linkedlist(){
      root=NULL;
}

//Author: Himanshu Sahay
//Public Destructor for Garbage Collection
linkedlist::~linkedlist(){
    destroy_list();
}

//Author: Himanshu Sahay
//Private Destructor for emptying the tree
void linkedlist::destroy_list(store_node *nextNode){
  if(nextNode!=NULL)
  {
    destroy_list(nextNode->next_store); //Go down the whole left side removing the nodes
    delete nextNode;              //Remove the node
  }
}

//Author: Himanshu Sahay
//Private Destructor for Garbage Collection
void linkedlist::destroy_list(){
  destroy_list(root);
}

//Author: Himanshu Sahay
//Public Function for adding a store node to the inventory linked list
void linkedlist::insert(int row, int col, int floor, int item_quantity){
  if(root!=NULL){ //If the list is not empty
        store_node *newNode = new store_node;
        newNode->row = row;
        newNode->col = col;
        newNode->floor = floor;
        newNode->item_quantity = item_quantity;
        //
        store_node *currNode = root, *temp, *prev;

        if( search( row, col, floor) != NULL) { // If there is already an entry with the same coordinates, add to it
            //search( row, col, floor )->item_quantity += item_quantity;

            temp = root;
            while(temp != NULL){
                if((temp->row == row)&&(temp->col == col)&&(temp->floor == floor)){
                    if(temp == root){
                        root = temp->next_store;
                        insert(row, col, floor, temp->item_quantity+item_quantity);
                        delete temp;
                    }
                    else{
                        prev->next_store = temp->next_store;
                        insert(row, col, floor, temp->item_quantity+item_quantity);
                        delete temp;
                    }
                }
                else{
                    prev = temp;
                    temp = temp->next_store;
                }
            }



            /*
            while((currNode->next_store != NULL)) {
                if(!(row == currNode->next_store->row) && (col == currNode->next_store->col) && (floor == currNode->next_store->floor))){
                    currNode = currNode->next_store;
                }
            }
            if(currNode->next_store != NULL){
                temp  = currNode->next_store;
                currNode->next_store = currNode->next_store->next_store;
                insert(temp->row, temp->col, temp->floor, temp->item_quantity + item_quantity);
            }
            else{
                ;
                insert(row, col, floor, currNode->item_quantity + item_quantity);
            }

            delete temp;
            */
        }

        else if( item_quantity > root->item_quantity) {
                newNode->next_store = root;
                root = newNode;
        }
        else {


            //OLD CODE WITH NULL ERROR
            /*
            while( item_quantity < currNode->next_store->item_quantity ) {
                currNode = currNode->next_store;
            }
            */
            while((currNode->next_store != NULL) && (item_quantity < currNode->next_store->item_quantity )) {
                currNode = currNode->next_store;
            }
            newNode->next_store = currNode->next_store; // Insert the node between current node and the one after it
            currNode->next_store = newNode;

        }
  }
  else{           //The list is empty
    root = new store_node;
    root->row = row;
    root->col = col;
    root->floor = floor;
    root->item_quantity = item_quantity;
    root->next_store = NULL;
  }
}

//Author: Himanshu Sahay
//Public Function for Printing out the Tree
void linkedlist::print_list(){
    print_list(root);
}

//Author: Himanshu Sahay
//Private Function for Printing out the List
void linkedlist::print_list(store_node *storeNode){
    if(storeNode != NULL){
        cout << "Qty Available: " << storeNode->item_quantity << "     Store Location: (" << storeNode->row << ", " << storeNode->col << ", " << storeNode->floor << ")" << endl;
        //cout << "Item count: " << storeNode->item_quantity << " Row: " << storeNode->row << " Column: " << storeNode->col << " Floor: " << storeNode->floor << endl;
        print_list(storeNode->next_store);
    }

}

//Author: Himanshu Sahay
// Private function to return the item in the linked list of store nodes with the same coordinates  as a given node, if one exists
store_node *linkedlist::search( int row, int col, int floor ) {
        if( root == NULL) {
                return NULL; // Returns null if called on an empty linked list
        }

        else{
            store_node *currNode = root;
            while( currNode != NULL) { // Check each item in the list for a match
                if( (row == currNode->row) && (col == currNode->col) && (floor == currNode->floor)) {
                    return currNode;
                }
                currNode = currNode->next_store;
            }
            return NULL; // return NULL if a matching node is not found
        }
    }
                                                                                                                   linkedlist.h                                                                                        0000771 0020221 0020221 00000001512 12417617211 012673  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


//Include Statements
#include <cstddef>
//#include <string>
#include "store_node.h"

//Author: Himanshu Sahay
class linkedlist
{
       public:
        linkedlist();
        ~linkedlist();

        void insert(int row, int col, int floor, int item_quantity);
        //item_node *search(std::string item_id);
        void destroy_list();
        void print_list();
        //virtual ~linkedlist();


    private:
        void destroy_list(store_node *nextNode);
        //void insert(int row, int col, int floor, int item_quantity, store_node *storePtr);
        store_node *search(int row, int col, int floor);
        void print_list(store_node *currNode);

        store_node *root; //root of linked list
};


#endif // LINKEDLIST_H
                                                                                                                                                                                      Makefile                                                                                            0000771 0020221 0020221 00000000571 12417635544 012035  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 # Makefile

#Author: Himanshu Sahay
CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=hsahay_main.cpp motion.cpp mall.cpp linkedlist.cpp binarytree.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= prog5_stage1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
		rm *.o
                                                                                                                                       mall.cpp                                                                                            0000771 0020221 0020221 00000027437 12417632374 012036  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 // Author: Himanshu Sahay
#define __MAIN__
#include "globals.h"
#include "mall.h"

#include <iostream>
using namespace std;

//TO DO: ASSIGN STORE IDs LATER

//Author: Himanshu Sahay
Mall::Mall()
{
  for(int i = 0; i<9; i++)
  R[i] = new Robot(i+1);
floormap();

}

//Author: Himanshu Sahay
/*void printcurrent(Robot *R)
  {
    //struct sqr fl[FLOORSIDE][FLOORSIDE][FLOORNUM]; //initializing the structure of arrays (extern given in header)

    int i,j,k;
  for(k=0;k<2;k++)
  {
    cout<<"Floor "<<k+1<<endl;
    cout<<"-------------------------------------\n"; //Top border
    for(i=0;i<17;i++)
  { cout<<"| "; //Left side border
    for(j=0;j<17;j++)
      {

        if(i==(R->lloc).x && j==(R->lloc).y && k==(R->lloc).z)  //CHECK THIS
          {
            cout<<"* ";
          }
        else
          {
        //cout<<"(%d, %d, %d): type %d\n", i,j,0,(fl[i][j][0]).type);
        switch(fl[i][j][k].type)
        {
          case Empty: cout<<"  ";
          break;

          case A1: cout<<"A1";
          break;

          case Store: cout<<"S ";
          break;

          case Elevator: cout<<"E ";
          break;

          case Plain: cout<<"P ";
          break;

          case Fork: cout<<"F ";
          break;

          default: cout<<"!!";
        }
      }
    }

      cout<<"|\n"; //Right side border
    }
    cout<<"-------------------------------------\n"; //Bottom border
  }
}
*/

//Author: Himanshu Sahay
void Mall::floormap()
{
int i,j,k; //Arbitrary  variables to be used in for loops
//struct sqr fl[17][17][2]; //initializeing the structure of arrays (extern given in header)



//Assigning types to every tile

for(i=0;i<2;i++)
  {
    for(j=0;j<17;j++)
      {
        for(k=0;k<17;k++)
          {
            (fl[j][k][i]).type = Empty;
            (fl[j][k][i]).forkid = 0;
          }
      }
  }


// Set structs for stores
for(i=0;i<2;i++)
{
  (fl[4][4][i]).type = Store;
  (fl[4][6][i]).type = Store;
  (fl[4][10][i]).type = Store;
  (fl[4][12][i]).type = Store;
  (fl[6][4][i]).type = Store;
  (fl[6][12][i]).type = Store;
  (fl[10][4][i]).type = Store;
  (fl[12][6][i]).type = Store;
  (fl[12][10][i]).type = Store;
  (fl[10][12][i]).type = Store;
  (fl[12][4][i]).type = Store;
  (fl[12][12][i]).type = Store;

}

(fl[4][4][0]).direction = NorthWest;
(fl[4][6][0]).direction = East;
(fl[4][10][0]).direction = West;
(fl[4][12][0]).direction = NorthEast;
(fl[6][4][0]).direction = South;
(fl[6][12][0]).direction = South;
(fl[10][12][0]).direction = North;
(fl[10][4][0]).direction = North;
(fl[12][6][0]).direction = East;
(fl[12][10][0]).direction = West;
(fl[12][4][0]).direction = SouthWest;
(fl[12][12][0]).direction = SouthEast;


(fl[4][4][1]).direction = NorthWest;
(fl[4][6][1]).direction = East;
(fl[4][10][1]).direction = West;
(fl[4][12][1]).direction = NorthEast;
(fl[6][4][1]).direction = South;
(fl[6][12][1]).direction = South;
(fl[10][12][1]).direction = North;
(fl[10][4][1]).direction = North;
(fl[12][6][1]).direction = East;
(fl[12][10][1]).direction = West;
(fl[12][4][1]).direction = SouthWest;
(fl[12][12][1]).direction = SouthEast;



// Set structs for plain tiles
for(i=0;i<2;i++)
{
 for(j=6;j<=10;j++)
 {
 if(j!=8 && i!=0)
  (fl[0][j][i]).type=Plain; //Top 6 blocks

 if(j!=8 && i!=1)
  (fl[16][j][i]).type=Plain; //Bottom 6 blocks

 if(j!=8 && i!=0)
  (fl[j][0][i]).type=Plain; //Left 6 blocks

 if(j!=8) //8 16 0 is A1 and 8 16 1 is fork
  (fl[j][16][i]).type=Plain; //Right 6 blocks
 }


 for(j=0;j<17;j++)
 {
  if(j!=8 || j!=0 && i!=0 || j!=16 && i!=1)
   (fl[j][8][i]).type=Plain; //Middle long row - vertical

  if(j!=16 || j!=8 || j!=0 && i!=0)
   (fl[8][j][i]).type=Plain; //Middle long row - column
 }

  //Top left diagonal
 (fl[1][5][i]).type=Plain;
 (fl[2][4][i]).type=Plain;
 //(fl[3][3][i]).type=Plain;
 (fl[4][2][i]).type=Plain;
 (fl[5][1][i]).type=Plain;

(fl[0][6][0]).type = Plain;
(fl[0][7][0]).type = Plain;
(fl[0][9][0]).type = Plain;
(fl[0][10][0]).type = Plain;
(fl[6][0][0]).type = Plain;
(fl[7][0][0]).type = Plain;
(fl[9][0][0]).type = Plain;
(fl[10][0][0]).type = Plain;
(fl[16][6][1]).type = Plain;
(fl[16][7][1]).type = Plain;
(fl[16][9][1]).type = Plain;
(fl[16][10][1]).type = Plain;






 //Top right diagonal
 (fl[1][11][i]).type=Plain;
 (fl[2][12][i]).type=Plain;
 //(fl[3][13][i]).type=Plain;
 (fl[4][14][i]).type=Plain;
 (fl[5][15][i]).type=Plain;

 //Bottom left diagonal
 (fl[11][1][i]).type=Plain;
 (fl[12][2][i]).type=Plain;
 //(fl[13][3][i]).type=Plain;
 (fl[14][4][i]).type=Plain;
 (fl[15][5][i]).type=Plain;

 //Bottom right diagonal
 (fl[11][15][i]).type=Plain;
 (fl[12][14][i]).type=Plain;
 //(fl[13][13][i]).type=Plain;
 (fl[14][12][i]).type=Plain;
 (fl[15][11][i]).type=Plain;

}
 /*Assigning Directions*/


 //!!! - Do Tiles that do 2 directions (Currently they are coded on only 1 direction)
 //Update: There pdirections are changed ahead
 //Tiles going East only
 for(i=1;i<16;i++)
  {
     if(i!=0 || i!=8)
	 (fl[8][i][0]).direction = East;
  }

  for(i=6;i<10;i++)
    {

     (fl[0][i][1]).direction = East;
    }

  for(i=6;i<10;i++)
  {

    (fl[16][i][0]).direction = East;
  }

  //Tiles going North only
  for(i=10;i>6;i--)
  {//A1 goes only north as well
    (fl[i][16][0]).direction = North;
  }

  for(i=10;i>6;i--)
    {
	//no fork on this side on second floor
      (fl[i][0][1]).direction = North;
    }

  for(i=1;i<16;i++)
    {
		if(i!=8)
      (fl[i][8][1]).direction = North;
    }

  //Tiles going West only
  for(i=10;i>6;i--)
  {
	  if(i!=8)
    (fl[0][i][0]).direction = West;
  }

  for(i=1;i<16;i++)
    {
	if(i!=8)
      (fl[8][i][1]).direction = West;
    }
  for(i=10;i>6;i--)
    {
		if(i!=8)
      (fl[16][i][1]).direction = West;
    }

  //Tiles going South only
  for(i=1;i<16;i++)
   {
	if(i!=8)
     (fl[i][8][0]).direction = South;
   }

   for(i=6;i<10;i++)
   {
	   if(i!=8)
     (fl[i][0][0]).direction = South;
   }

   for(i=6;i<10;i++)
    {
		if(i!=8)
     (fl[i][16][1]).direction = South;
    }

  //Tiles going North East
  (fl[11][15][0]).direction=NorthEast;
  (fl[12][14][0]).direction=NorthEast;
  (fl[14][12][0]).direction=NorthEast;
  (fl[15][11][0]).direction=NorthEast;
  (fl[16][10][0]).direction=NorthEast;

  //Tiles going South West
  (fl[10][16][1]).direction=SouthWest;
  (fl[11][15][1]).direction=SouthWest;
  (fl[12][14][1]).direction=SouthWest;
  (fl[14][12][1]).direction=SouthWest;
  (fl[15][11][1]).direction=SouthWest;

  //Tiles going South East
  (fl[10][0][0]).direction=SouthEast;
  (fl[11][1][0]).direction=SouthEast;
  (fl[12][2][0]).direction=SouthEast;
  (fl[14][4][0]).direction=SouthEast;
  (fl[15][5][0]).direction=SouthEast;

  //Tiles going North West
  (fl[11][1][1]).direction=NorthWest;
  (fl[12][2][1]).direction=NorthWest;
  (fl[14][4][1]).direction=NorthWest;
  (fl[15][5][1]).direction=NorthWest;
  (fl[16][6][1]).direction=NorthWest;

  //Tiles going North West
  (fl[1][11][0]).direction=NorthWest;
  (fl[2][12][0]).direction=NorthWest;
  (fl[4][14][0]).direction=NorthWest;
  (fl[5][15][0]).direction=NorthWest;
  (fl[6][16][0]).direction=NorthWest;

  //Tiles going South East
  (fl[0][10][1]).direction=SouthEast;
  (fl[1][11][1]).direction=SouthEast;
  (fl[2][12][1]).direction=SouthEast;
  (fl[4][14][1]).direction=SouthEast;
  (fl[5][15][1]).direction=SouthEast;

  //Tiles going SouthWest
  (fl[0][6][0]).direction=SouthWest;
  (fl[1][5][0]).direction=SouthWest;
  (fl[2][4][0]).direction=SouthWest;
  (fl[4][2][0]).direction=SouthWest;
  (fl[5][1][0]).direction=SouthWest;


  //Tiles going North East
  (fl[1][5][1]).direction=NorthEast;
  (fl[2][4][1]).direction=NorthEast;
  (fl[4][2][1]).direction=NorthEast;
  (fl[5][1][1]).direction=NorthEast;
  (fl[6][0][1]).direction=NorthEast;


//-------------------------------------------------------------------------------

  (fl[8][8][0]).forkid = 0; //Elevator
  (fl[8][8][0]).type = Elevator;
  (fl[8][8][1]).type = Elevator;
  (fl[8][8][0]).forkid = 0; //Elevator

   // Set struct for A1 (entry tile)
(fl[8][16][0]).type =A1;

  // Assigning Fork IDs
  // Forks are positions where the robot can go in more than one direction, and it deicdes the direction based on the destination

  //First floor
  //Outer forks
  (fl[3][13][0]).forkid = 1;
  (fl[3][13][0]).type = Fork;
  (fl[0][8][0]).forkid = 2;
  (fl[0][8][0]).type = Fork;
  (fl[3][3][0]).forkid = 3;
  (fl[3][3][0]).type = Fork;
  (fl[8][0][0]).forkid = 4;
  (fl[8][0][0]).type = Fork;
  (fl[13][3][0]).forkid = 5;
  (fl[13][3][0]).type = Fork;
  (fl[13][13][0]).forkid = 6;
  (fl[13][13][0]).type = Fork;

  //Inner forks
  (fl[4][8][0]).forkid = 7;
  (fl[4][8][0]).type = Fork;
  (fl[12][8][0]).forkid = 8;
  (fl[12][8][0]).type = Fork;
  (fl[8][4][0]).forkid = 9;
  (fl[8][4][0]).type = Fork;
  (fl[8][12][0]).forkid = 10;
  (fl[8][12][0]).type = Fork;
  (fl[4][7][0]).forkid = 11;
  (fl[4][7][0]).type = Fork;
  (fl[4][9][0]).forkid = 12;
  (fl[4][9][0]).type = Fork;
  (fl[12][7][0]).forkid = 13;
  (fl[12][7][0]).type = Fork;
  (fl[12][9][0]).forkid = 14;
  (fl[12][9][0]).type = Fork;
  (fl[7][4][0]).forkid = 15;
  (fl[7][4][0]).type = Fork;
  (fl[9][4][0]).forkid = 16;
  (fl[9][4][0]).type = Fork;
  (fl[7][12][0]).forkid = 17;
  (fl[7][12][0]).type = Fork;
  (fl[9][12][0]).forkid = 18;
  (fl[9][12][0]).type = Fork;

  //Second floor
  //Outer forks
  (fl[3][13][1]).forkid = 19;
  (fl[3][13][1]).type = Fork;
  (fl[3][3][1]).forkid = 20;
  (fl[3][3][1]).type = Fork;
  (fl[13][3][1]).forkid = 21;
  (fl[13][3][1]).type = Fork;
  (fl[16][8][1]).forkid = 22;
  (fl[16][8][1]).type = Fork;
  (fl[13][13][1]).forkid = 23;
  (fl[13][13][1]).type = Fork;
  (fl[8][16][1]).forkid = 24;
  (fl[8][16][1]).type = Fork;

  //Inner forks
  (fl[4][8][1]).forkid = 25;
  (fl[4][8][1]).type = Fork;
  (fl[12][8][1]).forkid = 26;
  (fl[12][8][1]).type = Fork;
  (fl[8][4][1]).forkid = 27;
  (fl[8][4][1]).type = Fork;
  (fl[8][12][1]).forkid = 28;
  (fl[8][12][1]).type = Fork;
  (fl[4][7][1]).forkid = 29;
  (fl[4][7][1]).type = Fork;
  (fl[4][9][1]).forkid = 30;
  (fl[4][9][1]).type = Fork;
  (fl[12][7][1]).forkid = 31;
  (fl[12][7][1]).type = Fork;
  (fl[12][9][1]).forkid = 32;
  (fl[12][9][1]).type = Fork;
  (fl[7][4][1]).forkid = 33;
  (fl[7][4][1]).type = Fork;
  (fl[9][4][1]).forkid = 34;
  (fl[9][4][1]).type = Fork;
  (fl[7][12][1]).forkid = 35;
  (fl[7][12][1]).type = Fork;
  (fl[9][12][1]).forkid = 36;
  (fl[9][12][1]).type = Fork;



  //Printing first floor
  cout<<"First Floor\n";
  cout<<"-------------------------------------\n"; //Top border
  for(i=0;i<17;i++)
    { cout<<"| "; //Left side border
      for(j=0;j<17;j++)
        {
          //printf("(%d, %d, %d): type %d\n", i,j,0,(fl[i][j][0]).type);
          switch(fl[i][j][0].type)
          {
            case Empty: cout<<"  ";
            break;

            case A1: cout<<"A1";
            break;

            case Store: cout<<"S ";
            break;

            case Elevator: cout<<"E ";
            break;

            case Plain: cout<<"P ";
            break;

            case Fork: cout<<"F ";
            break;

            default: cout<<"!!!";
          }
        }

        cout<<"|\n"; //Right side border
    }
    cout<<"-------------------------------------\n"; //Bottom border

  //Printing first floor
  cout<<"Second Floor\n";
  cout<<"-------------------------------------\n"; //Top border
  for(i=0;i<17;i++)
    { cout<<"| "; //Left side border
      for(j=0;j<17;j++)
        {
          //printf("(%d, %d, %d): type %d\n", i,j,0,(fl[i][j][0]).type);
          switch(fl[i][j][1].type)
          {
            case Empty: cout<<"  ";
            break;

            case A1: cout<<"A1";
            break;

            case Store: cout<<"S ";
            break;

            case Elevator: cout<<"E ";
            break;

            case Plain: cout<<"P ";
            break;

            case Fork: cout<<"F ";
            break;

            default: cout<<"!!!";
          }
        }

        cout<<"|\n"; //Right side border
    }
    cout<<"-------------------------------------\n"; //Bottom border

}
                                                                                                                                                                                                                                 mall.h                                                                                              0000771 0020221 0020221 00000000670 12417617433 011470  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //motion.h
//Author: Himanshu Sahay
#ifndef MALL_H
#define MALL_H
#include "robot.h"

//Author: Himanshu Sahay
class Mall //Mall is wrapper class for robot and floor
{
  public:
    void floormap(); //sets the mall floor
    //void printcurrent(Robot *R);
    Mall(); //default constructor
    ~Mall();
    //struct sqr fl[17][17][2]; //every tile on the floor
    Robot *R[9]; //array of pointers to robots


};

#endif
                                                                        motion.cpp                                                                                          0000771 0020221 0020221 00000047523 12417616577 012423  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 
#include "globals.h"
#include "mall.h"

//Author: Himanshu Sahay
#include <iostream>
using namespace std;

//Author: Himanshu Sahay
Robot::Robot(int robotnum) //constructor
{
	destination.r = -1;
	destination.c = -1;
	destination.f = -1; //invalid destination
	lloc.r = -1; //invalid last location
	lloc.c = -1;
	lloc.f = -1;
	rnum = robotnum;
	checkIfInMall =false; //set to true when robot enters mall
}

//Author: Himanshu Sahay
void Robot::move(int *tptr, int x, int y, int z) //Inputs current square postion
{

	if(checkIfInMall == true)
	{
//	cout << "Time: "<< *tptr << endl;

	//struct sqr fl[FLOORSIDE][FLOORSIDE][FLOORNUM]; //initializeing the structure of arrays (extern given in header)

  /*Enter mall at A1 on first floor.
    Goes north.
    Checks at every tile if it is a fork. If tile is not a fork, the robot keeps going.
    If the current tile is a fork, it checks what is the best path to take in order to reach the destination
    If the current coordinates match destination coordinates, it says that you have reached the desired store and moves on to the next store.

  */


//cout<<"1st destination show inside move function: "<<(rptr->destination).r<<" "<<(rptr->destination).c<<" "<<(rptr->destination).f<<endl;

//Initializes variables with coordinates of store that the robot is going to
int xtarget=destination.r;
int ytarget=destination.c;
int ztarget=destination.f;

/*Stores current location as last location at each step.
If store is reached, last locaion of previous iteration is used so that the robot can move back out of the store*/
if((fl[x][y][z]).type!=Store)
  {
  	//cout<<"Printing inside last location if statement: Last location: "<<x<<" "<<y<<" "<<z<<" and "<<temp.r<<" "<<temp.c<<" "<<temp.f<<endl;
  lloc.r = x;
	lloc.c = y;
	lloc.f = z;
  }

//cout<<"Last location: %d,%d,%d\n",(rptr->lloc).r,(rptr->lloc).c,(rptr->lloc).f);
cout<<"Time "<<(*tptr)<<"\tLocation ("<<x<<","<<y<<","<<z<<")\n";

//---------------------------------------------------------------------------------------------
  //Debug statements
  //cout<<"Position: %d %d %d\n",x,y,z);
  //cout<<"Direction: %d\n",fl[x][y][z].direction);

//Switches over robot type to facilitate robot movement
  switch((fl[x][y][z]).type)
  {
    case A1:
		cout<<"Type is: A1"<<endl;

    if(*tptr%25==0) //Prints current floor map every 5 time units
      {
		  cout<<"Time is: "<<*tptr;
        //cout<<"Current floor map\n\n";
        //Printing current floor map
        	//printcurrent(x,y,z);
      }
    if(x==xtarget && y==ytarget && z==ztarget)
      {
        return; //Ends robot movement and returns time taken in journey
      }

    else
      {
        *tptr+=1; //Time is incremented at each step by 1 unit
        move(tptr,x-1,y,z);
      }

    break;

    case Plain:
		cout<<"Plain tile"<<endl;
    if(*tptr%25==0) //Prints current floor map every 5 time units
      {
        ////cout<<"Current floor map\n";
        //Printing current floor map
      //printcurrent(x,y,z);
      }
    {
      *tptr+=1; //Time is incremented at each step by 1 unit
      switch((fl[x][y][z]).direction)
        {
          case North: //North
          x--;
          move(tptr,x,y,z);
          break;

          case NorthWest: //NorthWest
          x--;
          y--;
          move(tptr,x,y,z);
          break;

          case West: //West
          y--;
          move(tptr,x,y,z);
          break;

          case SouthWest: //SouthWest
          x++;
          y--;
          move(tptr,x,y,z);
          break;

          case South: //South
          x++;
          move(tptr,x,y,z);
          break;

          case SouthEast: //SouthEast
          x++;
          y++;
          move(tptr,x,y,z);
          break;

          case East: //East
          y++;
          move(tptr,x,y,z);
          break;

          case NorthEast: //NorthEast
          x--;
          y++;
          move(tptr,x,y,z);
          break;

          default: break;
        }
      }
      break;

      case Store: //Switch over direction to move form store

      if(*tptr%25==0) //Prints current floor map every 5 time units
        {
          //cout<<"Current floor map\n";
          //Printing current floor map
        //printcurrent(x,y,z);
        }
        cout<<"\nRobot reached store ("<<x<<","<<y<<","<<z<<") at time "<<*tptr<<endl;

        *tptr+=1; //Time is incremented by 1 unit extra for stores

		if(ztarget==1)
          {
            *tptr+=1; //Spends 1 time unit more on a second floor store than on a first floor store
          }
          return; //Returns from function if destination reached.

      break;

  //WORK ON ELEVATOR
      case Elevator:

      if(*tptr%25==0) //Prints current floor map every 5 time units
        {
          //cout<<"Current floor map\n";
          //Printing current floor map
      //  printcurrent(x,y,z);
        }

    if(ztarget==0) //Checks if target floor is first floor
      {
        if(z==1) //Checks if robot is currently on the second floor
          {
            cout<<"\nRobot got on the elevator at time: "<<*tptr<<endl;
            cout<<"\nRobot got off the elevator at time: "<<*tptr+3<<endl;
            z--;
          *tptr+=4; //3 time units in the elevator and 1 time unit to get off the elevator
        if(xtarget>10 && ytarget>5)
          {
            x++;
            move(tptr,x,y,z);
          }
        else
          {
            y++;
            move(tptr,x,y,z);
          }
        }
        else //Robot is already on the first floor and destination is also on first floor
          {
              if(xtarget>10 && ytarget>5)
                {
                  x++;
                  move(tptr,x,y,z);
                }
              else
                {
                  y++;
                  move(tptr,x,y,z);
                }
          }
        }
      else //Target floor is the second floor
      {
        if(z==0) //Checks if robot is currently on the first floor
      {
        z=1;
        cout<<"\nRobot got on the elevator at time: "<<*tptr<<endl;
        cout<<"\nRobot got off the elevator at time: "<<*tptr+3<<endl;
        *tptr+=4; //3 time units in the elevator and 1 time unit to get off the elevator
        if(xtarget<11 && ytarget<5)
          {
            y--;
            move(tptr,x,y,z);
          }
        else
          {
            x--;
            move(tptr,x,y,z);
          }
        }
      else //Robot is already on the seond floor and destination is also on the second floor
      {
        if(xtarget<11 && ytarget<5)
          {
            y--;
            move(tptr,x,y,z);
          }
        else
          {
            x--;
            move(tptr,x,y,z);
          }
        }

      }
      *tptr+=1; //Time is incremented at each step by 1 unit
      break; //Universal break for entire case Elevator:

        case Fork:

        if(*tptr%25==0) //Prints current floor map every 5 time units
          {
            //cout<<"Current floor map\n";
            //Printing current floor map
        //  printcurrent(x,y,z);
          }
        *tptr+=1; //Time is incremented at each step by 1 unit
        cout<<"\nRobot has reached fork "<<fl[x][y][z].forkid<<endl;

        switch(fl[x][y][z].forkid)
        {
          case 1:
            if(xtarget==4 && ytarget==12 && ztarget==0)
              {
                x++;
                y--;
                move(tptr,x,y,z); //Goes to store
              }
            else

              {
                x--;
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 2:

            if(ytarget<6 && ztarget==0) //Destination store has y<6
              {
                y--;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 3:
            if(xtarget==4 && ytarget==4 && ztarget==0)
              {
                x++;
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 4:
            if(!((xtarget==12 && ytarget==4 && ztarget==0)||(xtarget==12 && ytarget==12 && ztarget==0)))
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 5:
            if(xtarget==12 && ytarget==4 && ztarget==0)
              {
                x--;
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 6:
            if(xtarget==12 && ytarget==12 && ztarget==0)
              {
                x--;
                y--;
                move(tptr,x,y,z);
              }
            else
              {
                x--;
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 7:
            if(xtarget==4 && ytarget==6 && ztarget==0)
              {
                y--;
                move(tptr,x,y,z); //Goes to left store
              }
            else if(xtarget==4 && ytarget==10 && ztarget==0)
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 8:
            if(xtarget==12 && ytarget==6 && ztarget==0)
              {
                y--;
                move(tptr,x,y,z);
              }
            else if(xtarget==12 && ytarget==10 && ztarget==0)
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 9:
            if(xtarget==6 && ytarget==4 && ztarget==0)
              {
                x--;
                move(tptr,x,y,z);
              }
            else if(xtarget==10 && ytarget==4 && ztarget==0)
              {
                x++;
                move(tptr,x,y,z);
              }
            else
              {
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 10:
            if(xtarget==6 && ytarget==12 && ztarget==0)
              {
                x--;
                move(tptr,x,y,z);
              }
            else if(xtarget==10 && ytarget==12 && ztarget==0)
              {
                x++;
                move(tptr,x,y,z);
              }
            else
              {
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 11:
            if(xtarget==4 && ytarget==6 && ztarget==0)
              {
                y--;
                move(tptr,x,y,z);
              }
            else
              {
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 12:
            if(xtarget==4 && ytarget==10 && ztarget==0)
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 13:
            if(xtarget==12 && ytarget==6 && ztarget==0)
              {
                y--;
                move(tptr,x,y,z);
              }
            else
              {
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 14:
            if(xtarget==12 && ytarget==10 && ztarget==0)
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 15:
            if(xtarget==6 && ytarget==4 && ztarget==0)
              {
                x--;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 16:
            if(xtarget==10 && ytarget==4 && ztarget==0)
              {
                x++;
                move(tptr,x,y,z);
              }
            else
              {
                x--;
                move(tptr,x,y,z);
              }
            break;

          case 17:
            if(xtarget==6 && ytarget==12 && ztarget==0)
              {
                x--;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                move(tptr,x,y,z);
              }
            break;

          case 18:
            if(xtarget==10 && ytarget==12 && ztarget==0)
              {
                x++;
                move(tptr,x,y,z);
              }
            else
              {
                x--;
                move(tptr,x,y,z);
              }
            break;

          case 19:
            if(xtarget==4 && ytarget==12 && ztarget==1)
              {
                x++;
                y--;
                move(tptr,x,y,z);
              }
            else
              {
                x++;
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 20:
            if(xtarget==4 && ytarget==4 && ztarget==1)
              {
                x++;
                y++;
                move(tptr,x,y,z);
              }
            else //floor 1 case included
              {
                x--;
                y++;
                move(tptr,x,y,z);
              }
            break;

          case 21:
            if(xtarget==12 && ytarget==4 && ztarget==1)
              {
                x--;
                y++;
                move(tptr,x,y,z);
              }
            else //floor 1 case included
             {
               x--;
               y--;
               move(tptr,x,y,z);
             }
            break;

          case 22:
            if((xtarget==12 && ytarget==4 && ztarget==1)||(xtarget==4 && ytarget==4 && ztarget==1))
              {
                y--;
                move(tptr,x,y,z);
              }
            else //floor 1 case included
              {
                x--;
                move(tptr,x,y,z);
              }
            break;

          case 23:
            if(xtarget==12 && ytarget==12 && ztarget==1)
              {
                x--;
                y--;
                move(tptr,x,y,z);
              }
            else //floor 1 case included
              {
                x++;
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 24:
            if(xtarget>10 && ztarget==1)
              {
                x++;
                move(tptr,x,y,z);
              }
            else //floor 1 case included
              {
                y--;
                move(tptr,x,y,z);
              }
            break;

          case 25:
            if(xtarget==4 && ytarget==6 && ztarget==1)
              {
                y--;
                move(tptr,x,y,z);
              }
            else if(xtarget==4 && ytarget==10 && ztarget==1)
              {
                y++;
                move(tptr,x,y,z);
              }
            else
              {
                x--;
                move(tptr,x,y,z);
              }
            break;

          case 26:

              if(xtarget==12 && ytarget==6 && ztarget==1)
                {
                  y--;
                  move(tptr,x,y,z);
                }
              else if(xtarget==12 && ytarget==10 && ztarget==1)
                {
                  y++;
                  move(tptr,x,y,z);
                }
              else
                {
                  x--;
                  move(tptr,x,y,z);
                }
              break;

            case 27:
                if(xtarget==6 && ytarget==4 && ztarget==1)
                  {
                    x--;
                    move(tptr,x,y,z);
                  }
                else if(xtarget==10 && ytarget==4 && ztarget==1)
                  {
                    x++;
                    move(tptr,x,y,z);
                  }
                else
                  {
                    y--;
                    move(tptr,x,y,z);
                  }
                break;

              case 28:

                  if(xtarget==6 && ytarget==12 && ztarget==1)
                    {
                      x--;
                      move(tptr,x,y,z);
                    }
                  else if(xtarget==10 && ytarget==12 && ztarget==1)
                    {
                      x++;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      y--;
                      move(tptr,x,y,z);
                    }
                  break;

                case 29:
                  if(xtarget==4 && ytarget==6 && ztarget==1)
                    {
                      y--;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      y++;
                      move(tptr,x,y,z);
                    }
                  break;

                case 30:
                  if(xtarget==4 && ytarget==10 && ztarget==1)
                    {
                      y++;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      y--;
                      move(tptr,x,y,z);
                    }
                  break;

                case 31:
                  if(xtarget==12 && ytarget==6 && ztarget==1)
                    {
                      y--;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      y++;
                      move(tptr,x,y,z);
                    }
                  break;

                case 32:
                  if(xtarget==12 && ytarget==10 && ztarget==1)
                    {
                      y++;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      y--;
                      move(tptr,x,y,z);
                    }
                  break;
                case 33:
                  if(xtarget==6 && ytarget==4 && ztarget==1)
                    {
                      x--;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      x++;
                      move(tptr,x,y,z);
                    }
                  break;

                case 34:
                  if(xtarget==10 && ytarget==4 && ztarget==1)
                    {
                      x++;;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      x--;
                      move(tptr,x,y,z);
                    }
                  break;

                case 35:
                  if(xtarget==6 && ytarget==12 && ztarget==1)
                    {
                      x--;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      x++;
                      move(tptr,x,y,z);
                    }
                  break;

                case 36:
                  if(xtarget==10 && ytarget==12 && ztarget==1)
                    {
                      x++;
                      move(tptr,x,y,z);
                    }
                  else
                    {
                      x--;
                      move(tptr,x,y,z);
                    }
                  break;

          default: cout<<"ERROR! ERROR! ERROR!"<<endl;
        }
      break;

    case Empty: cout<<"CASE EMPTY"<<endl;
    break;

    default: cout<<"INVALID TILE"<<endl; //for both default and Empty

  	}
	}
}
                                                                                                                                                                             node.h                                                                                              0000771 0020221 0020221 00000001150 12417616634 011464  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay
#ifndef NODE_H
#define NODE_H

#include <string>
#include "linkedlist.h"

//Author: Himanshu Sahay
//This Struct is used to hold the information held in the binary tree
struct item_node{
    std::string item_id;     //The Unique ID of Item, which the tree is ordered on
    linkedlist store_list;       //Pointer to the Start of the linked list which describes the locations of the item and quantity
    item_node *left;         //Pointer to the left child of the node in the tree
    item_node *right;        //Pointer to the right child of the node in the tree
};

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                        prog5_stage1                                                                                        0000771 0020221 0020221 00000114037 12417635702 012617  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 ELF          >    �@     @       �u          @ 8  @         @       @ @     @ @     �      �                           @      @                                          @       @     �f      �f                     p       p`      p`           �)                    Pp      Pp`     Pp`     �      �                         @     @                            P�td   L[      L[@     L[@     �      �             Q�td                                                  /lib64/ld-linux-x86-64.so.2          GNU           	                   � 1          r��jn!��	�CyIk�                        D              
      3                     �              "                                                    =                     �             �       �                     �             �      d             �      �             O       �             x       W             ^       �             |       W             �      b             �      V              D       �             1      u              J      	                    �             �       >                   �                     �                                 �       �                                  c       �     s`           �   "  �@     �             @     )       �    @t`           `      @     �       libstdc++.so.6 __gmon_start__ _Jv_RegisterClasses _ZNSsC1Ev _ZdlPv _ZNSs6appendEPKcm _ZNSsD1Ev __gxx_personality_v0 _ZNSirsERi _ZNSsaSERKSs _ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw _ZNSolsEi _ZNKSs4sizeEv _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_ _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_ _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc _Znwm _ZNSt8ios_base4InitC1Ev _ZNSsC1ERKSs _ZNSs7reserveEm _ZSt3cin _ZNSt8ios_base4InitD1Ev _ZNKSs7compareERKSs _ZSt4cout _ZNSolsEPFRSoS_E _ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St8_SetfillIS3_E _ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RSbIS4_S5_T1_E _ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E _ZNSolsEPFRSt8ios_baseS0_E _ZNSs6appendERKSs libm.so.6 libgcc_s.so.1 _Unwind_Resume libc.so.6 __cxa_atexit __libc_start_main GCC_3.0 GLIBC_2.2.5 CXXABI_1.3 GLIBCXX_3.4                                            0         P&y   v        M         ui	   ~                  ӯk   �     t)�   �      r`                    s`                   @t`                   0r`                   8r`                   @r`                   Hr`                   Pr`                   Xr`                   `r`        	           hr`        
           pr`                   xr`                   �r`                   �r`                   �r`                   �r`                   �r`                   �r`                   �r`                   �r`                   �r`                   �r`                    �r`                   �r`                   �r`                   �r`                   �r`                   �r`                    s`                   H����  �z  �G  H����5Je  �%Le  @ �%Je  h    ������%Be  h   ������%:e  h   ������%2e  h   �����%*e  h   �����%"e  h   �����%e  h   �����%e  h   �p����%
e  h   �`����%e  h	   �P����%�d  h
   �@����%�d  h   �0����%�d  h   � ����%�d  h   �����%�d  h   � ����%�d  h   ������%�d  h   ������%�d  h   ������%�d  h   ������%�d  h   �����%�d  h   �����%�d  h   �����%�d  h   �����%�d  h   �p����%�d  h   �`����%�d  h   �P����%zd  h   �@���1�I��^H��H���PTI���S@ H���S@ H���@ �������H��H�Ic  H��t��H��Ð������������UH��SH���=hf   uD�@p` H-8p` H��H�X�H�Df  H9�vH��H�4f  ��8p` H�&f  H9�w��"f  H��[�� UH�=�`   H��t�    H��t�Hp` I���A���Ð�UH��H���}��u��}�u'�}���  u�\u` ������T@ �    ��@ ������ÐUH����  �   �����ÐUH��H��H�}��\u` ������UH��SH���  ��T@ �@t` ����H�Ǿ @ �����H��`��������H��P����v:  H�E�    �H   �����H��8���H��8����a4  H��8���H�E�ǅL���    H��L���H�EྼT@ �@t` �8���H��@����&H��(���H��(���H��8�������H��(����  � @ H��@����H���H�}���$  ��T@ �@t` �����H�Ǿ @ �#���H��H���� s` ������H�����H����U@ �@t` ����H�ǋ�H��������H�Ǿ @ ������E�    �m�Ẽ���L����(U@ �@t` �h���H�ǋ�L�������H�Ǿ @ ����H��D���� s` �|����E�H�U�H�H��� �E̋�D���H���������E���H���9E�|��E�    �E�    �E�    ��
  �E����P����JU@ �@t` �����H�ǋ�P����(���H�Ǿ @ �����E�    �[
  �E�H����������T����hU@ �@t` ����H�ǋ�T���������}� �T  �E����X�����U@ �@t` �[���H�ǋ�X�������H�Ǿ�U@ �@���H�Ǿ @ ����H��@���� s` �b���H��H��<����S���H��H��8����D���Hǅ ���    ǅ(���    ��@����� �����<�����$�����8�����(����E�H�U�H�H��H�� ���H�B��(����B��U@ �@t` ����H�Ǿ @ �����H��l���� s` ������l�����\�����8�����`�����<�����d�����@�����h�����U@ �@t` �>���H�ǋ�h�������H�Ǿ�U@ �#���H�ǋ�d����u���H�Ǿ�U@ ����H�ǋ�`����Z���H�Ǿ V@ �����H�ǋ�\����?���H�Ǿ @ �"����E�H�U�H�H�@ ��l����E����p����$V@ �@t` ����H�ǋ�p��������H�Ǿ0V@ ����H�ǋ�l��������H�Ǿ @ �����E�H�U�H�H�<�H�u�A�    �   �   �)  H�E����l����H�E���E�    ��  �XV@ �@t` ����H��`���� s` ����H��H��h����6���H��`���H��p�������H��p���H��P����J7  H�E�H�}� ��w���H��p���������&H��(���H��(���H��p�������H��(����  ��w��� ��   ��h�����x�����8�����|�����<�����������@���������H��`���H�}�����H�u�H��P���D��x���D��|����������������u:  H�}��,����KH��(���H��(���H�}�����H��(����n  ��h�����8�����<�����@���H�}�H��A����1  ��h���������H�}�H��`�����V@ ��  H�u��@t` �����H�Ǿ�V@ ����H�ǋ����������H�Ǿ @ ����H�}������#H��(���H��(���H�}��f���H��(�����  �E���l���9E������  �E�H��������;E���  ǅ���   ǅ���   ǅ���    �E�H�U�H�H��H�����H�B������B�E�H�U�H�H�@�������E�H�U�H�H�@�������E�H�U�H�H�@��������V@ �@t` �}���H�ǋ����������H�Ǿ�V@ �b���H�ǋ���������H�Ǿ�V@ �G���H�ǋ���������H�Ǿ�V@ �,����E�H�U�H�H�H�E�H�U�H�H��D�H�E�H�U�H�H�x�E�H�U�H�H��H�u�A��D�ɉ�H���  H�E�� �������E���������$V@ �@t` ����H�ǋ���������H�Ǿ�V@ ����H�ǋ����������H�Ǿ @ ������E�H�U�H�H��H�E�� �B$��  �E���������W@ �@t` �G���H�ǋ���������H�Ǿ�U@ �,���H��@���� s` �[���H��H��<����L���H��H��8����=���Hǅ ���    ǅ���    ��@����� �����<����������8���������E�H�U�H�H��H�� ���H�B������B��U@ �@t` ����H�Ǿ @ �����H��l���� s` ������l�����������8�����������<�����������@�����������U@ �@t` �7���H�ǋ���������H�Ǿ�U@ ����H�ǋ������n���H�Ǿ�U@ ����H�ǋ������S���H�Ǿ V@ �����H�ǋ������8���H�Ǿ @ �����E�H�U�H�H�H�E�H�U�H�H��D�H�E�H�U�H�H�x�E�H�U�H�H��H�u�A��D�ɉ�H���]  H�E����l����H�E���E�    ��  �XV@ �@t` �J���H��`���� s` �I���H��H��h����j���H��`���H�}������H�u�H��P����1  H�E�H�}� ������H�}������#H��(���H��(���H�}������H��(����S  ������ ��   ��h�����������8�����������<�����������@���������H��`���H�}��O���H�u�H��P���D������D�������������������4  H�}��l����KH��(���H��(���H�}��S���H��(����  ��h�����8�����<�����@���H�}�H��A���,  ��h���������H�}�H��`�����V@ �  H�u��@t` � ���H�Ǿ�V@ �����H�ǋ���������H�Ǿ @ �����H�}������#H��(���H��(���H�}�����H��(����  �E���l���9E�����H�E�� �PH�E���E��E�H��������;E�������9W@ �@t` �0���H�ǋu�����H�Ǿ @ �h����E���H���9E������SW@ �@t` �����H�Ǿ @ �9���H��P����0  �dW@ �@t` ������ @ �@t` ����H�Ǿ @ ����H�Ǿ @ �����H�Ǿ @ �����ǅ����    H��P����4  �#H��(���H��(���H��P����p4  H��(����!H��`����q�����������4����-H��(���H��(���H��`����I���H��(���H��(���������4���H���  [��UH��H�}�H�E�H������H�E�    �H�}��H��H��H���ÐUH��SH��8H�}�H�u�H�U�H�}�����H�E�H�}������H�}��2���H��Hu�H�}�����H�}�H�U�H�u������H�}�H�u��4����H�E�H�]�H�}�����H�]�H�}������H�E�H��8[�ÐUH��H�}��u�H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�U��E�BH�E��  ��UH��H�}��u�H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�U��E�BH�E��  ��UH��H���}��u��}�u'�}���  u�`u` ������T@ �    �l@ �-����ÐUH����  �   �����ÐUH��H��H�}��`u` ������UH��SH��HH�}�H�u؉UԉM�D�E�H�E�� ���|  H�E��@�E�H�E��@�E�H�E��@�E�EԋUЋu�Hc�Hc�H��H��H�H�Hc�H�H�H�����u` ��tH�U��EԉBH�U��EЉBH�U��ẺBH�E؋��W@ �@t` �m���H�ǉ������H�Ǿ�W@ �V���H�ǋu�����H�Ǿ�W@ �>���H�ǋu�����H�Ǿ�W@ �&���H�ǋu��{���H�Ǿ�W@ �����EԋUЋu�Hc�Hc�H��H��H�H�Hc�H�H�H�����u` �E��}��@  �E�H��xX@ �ྗW@ �@t` ����H�Ǿ @ �����H�E؋�E���Q�E�����������)É]��E���E���    Љ�)U��}� uH�E؋��W@ �@t` �T���H�ǉ������E�;E�u�E�;E�u�E�;E�u�  H�E؋ �PH�E؉�Uԃ��E̋M�H�u�H�}�A��������  ��W@ �@t` �����H�Ǿ @ �1���H�E؋ �PH�E؉�EԋUЋu�Hc�Hc�H��H��H�H�Hc�H�H�H�����u` �Eă}��   �E�H�ŨX@ ���m��E̋MЋU�H�u�H�}�A���P�����  �m��m��E̋MЋU�H�u�H�}�A���*�����  �m��E̋MЋU�H�u�H�}�A�������  �E��m��E̋MЋU�H�u�H�}�A��������  �E��E̋MЋU�H�u�H�}�A��������a  �E��E��E̋MЋU�H�u�H�}�A�������;  �E��E̋MЋU�H�u�H�}�A���x����  �m��E��E̋MЋU�H�u�H�}�A���R�����  H�E؋��W@ �@t` �T���H�ǋu�����H�Ǿ�W@ �<���H�ǋu�����H�Ǿ�W@ �$���H�ǋu��y���H�Ǿ�W@ ����H�ǉ��b���H�Ǿ @ �E���H�E؋ �PH�E؉�}��f  H�E؋ �PH�E؉�R  �}� �  �}���   H�E؋��W@ �@t` ����H�ǉ������H�Ǿ @ �����H�E؋ �X�X@ �@t` �p���H�ǉ������H�Ǿ @ �����m�H�E؋ �PH�E؉�}�
~(�}�~"�E��E̋MЋU�H�u�H�}�A�������  �E��E̋MЋU�H�u�H�}�A��������]  �}�
~(�}�~"�E��E̋MЋU�H�u�H�}�A�������/  �E��E̋MЋU�H�u�H�}�A�������  �}� ��   �E�   H�E؋��W@ �@t` ����H�ǉ������H�Ǿ @ ����H�E؋ �X�X@ �@t` �Q���H�ǉ�����H�Ǿ @ ����H�E؋ �PH�E؉�}�
%�}��m��E̋MЋU�H�u�H�}�A��������g�m��E̋MЋU�H�u�H�}�A��������H�}�
%�}��m��E̋MЋU�H�u�H�}�A��������m��E̋MЋU�H�u�H�}�A���}���H�E؋ �PH�E؉�  H�E؋ �PH�E؉�EԋUЋu�Hc�Hc�H��H��H�H�Hc�H�H�H�����u` �.X@ �@t` �8���H�ǉ�����H�Ǿ @ �q����EԋUЋu�Hc�Hc�H��H��H�H�Hc�H�H�H�����u` �Eȃ}�$�  �E�H���X@ ���}�u2�}�u,�}� u&�E��m��E̋MЋU�H�u�H�}�A�������*  �m��m��E̋MЋU�H�u�H�}�A���c����  �}�(�}� u"�m��E̋MЋU�H�u�H�}�A���5�����  �E��E̋MЋU�H�u�H�}�A�������  �}�u2�}�u,�}� u&�E��E��E̋MЋU�H�u�H�}�A��������|  �E��m��E̋MЋU�H�u�H�}�A�������V  �}�u�}�u�}� t4�}�u�}�u�}� t"�E��E̋MЋU�H�u�H�}�A���o����  �E��E̋MЋU�H�u�H�}�A���M�����  �}�u2�}�u,�}� u&�m��E��E̋MЋU�H�u�H�}�A�������  �E��E��E̋MЋU�H�u�H�}�A��������  �}�u2�}�u,�}� u&�m��m��E̋MЋU�H�u�H�}�A�������X  �m��E��E̋MЋU�H�u�H�}�A�������2  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A���]�����  �}�u.�}�
u(�}� u"�E��E̋MЋU�H�u�H�}�A���)�����  �E��E̋MЋU�H�u�H�}�A�������  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A��������t  �}�u.�}�
u(�}� u"�E��E̋MЋU�H�u�H�}�A�������@  �E��E̋MЋU�H�u�H�}�A���}����  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A���I�����
  �}�
u.�}�u(�}� u"�E��E̋MЋU�H�u�H�}�A�������
  �E��E̋MЋU�H�u�H�}�A��������
  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A�������`
  �}�
u.�}�u(�}� u"�E��E̋MЋU�H�u�H�}�A�������,
  �E��E̋MЋU�H�u�H�}�A���i����

  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A���5�����	  �E��E̋MЋU�H�u�H�}�A�������	  �}�u.�}�
u(�}� u"�E��E̋MЋU�H�u�H�}�A��������	  �m��E̋MЋU�H�u�H�}�A�������^	  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A�������*	  �E��E̋MЋU�H�u�H�}�A���g����	  �}�u.�}�
u(�}� u"�E��E̋MЋU�H�u�H�}�A���3�����  �m��E̋MЋU�H�u�H�}�A�������  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A��������~  �E��E̋MЋU�H�u�H�}�A�������\  �}�
u.�}�u(�}� u"�E��E̋MЋU�H�u�H�}�A�������(  �m��E̋MЋU�H�u�H�}�A���e����  �}�u.�}�u(�}� u"�m��E̋MЋU�H�u�H�}�A���1�����  �E��E̋MЋU�H�u�H�}�A�������  �}�
u.�}�u(�}� u"�E��E̋MЋU�H�u�H�}�A��������|  �m��E̋MЋU�H�u�H�}�A�������Z  �}�u2�}�u,�}�u&�E��m��E̋MЋU�H�u�H�}�A�������"  �E��E��E̋MЋU�H�u�H�}�A���[�����  �}�u2�}�u,�}�u&�E��E��E̋MЋU�H�u�H�}�A���#�����  �m��E��E̋MЋU�H�u�H�}�A��������  �}�u2�}�u,�}�u&�m��E��E̋MЋU�H�u�H�}�A��������f  �m��m��E̋MЋU�H�u�H�}�A�������@  �}�u�}�u�}�t�}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A���Y�����  �m��E̋MЋU�H�u�H�}�A���7�����  �}�u2�}�u,�}�u&�m��m��E̋MЋU�H�u�H�}�A��������  �E��m��E̋MЋU�H�u�H�}�A��������z  �}�
~(�}�u"�E��E̋MЋU�H�u�H�}�A�������L  �m��E̋MЋU�H�u�H�}�A�������*  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A���U�����  �}�u.�}�
u(�}�u"�E��E̋MЋU�H�u�H�}�A���!�����  �m��E̋MЋU�H�u�H�}�A��������  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A��������l  �}�u.�}�
u(�}�u"�E��E̋MЋU�H�u�H�}�A�������8  �m��E̋MЋU�H�u�H�}�A���u����  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A���A�����  �}�
u.�}�u(�}�u"�E��E̋MЋU�H�u�H�}�A�������  �m��E̋MЋU�H�u�H�}�A��������  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A�������X  �}�
u.�}�u(�}�u"�E��E̋MЋU�H�u�H�}�A�������$  �m��E̋MЋU�H�u�H�}�A���a����  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A���-�����  �E��E̋MЋU�H�u�H�}�A�������  �}�u.�}�
u(�}�u"�E��E̋MЋU�H�u�H�}�A��������x  �m��E̋MЋU�H�u�H�}�A�������V  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A�������"  �E��E̋MЋU�H�u�H�}�A���_����   �}�u.�}�
u(�}�u"�E��E̋MЋU�H�u�H�}�A���+�����  �m��E̋MЋU�H�u�H�}�A���	����  �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A��������v  �E��E̋MЋU�H�u�H�}�A�������T  �}�
u.�}�u(�}�u"�E��E̋MЋU�H�u�H�}�A�������   �m��E̋MЋU�H�u�H�}�A���]�����   �}�u.�}�u(�}�u"�m��E̋MЋU�H�u�H�}�A���)�����   �E��E̋MЋU�H�u�H�}�A�������   �}�
u+�}�u%�}�u�E��E̋MЋU�H�u�H�}�A��������w�m��E̋MЋU�H�u�H�}�A�������X�GX@ �@t` ����H�Ǿ @ �����:�\X@ �@t` ����H�Ǿ @ �������gX@ �@t` ����H�Ǿ @ �����H��H[�Ð��UH��H���}��u��}�u'�}���  u���` �������T@ �    ��5@ �����ÐUH����  �   �����ÐUH��H��H�}����` �������UH��H�� H�}��E�    �   �E�    �}�E�    �j�E��U��u�Hc�Hc�H��H��H�H�Hc�H�H�H��ǀ�u`    �E��U��u�Hc�Hc�H��H��H�H�Hc�H�H�H��ǀ�u`     �E��}�~��E��}��y����E��}��b����E�    ��   �E�H�H��ǀ�~`    �E�H�H��ǀ�~`    �E�H�H��ǀD`    �E�H�H��ǀ�`    �E�H�H��ǀĂ`    �E�H�H��ǀă`    �E�H�H��ǀD�`    �E�H�H��ǀď`    �E�H�H��ǀD�`    �E�H�H��ǀD�`    �E�H�H��ǀ��`    �E�H�H��ǀ��`    �E��}������"G     �XG     ��G     �H     �:K     �0L     ��T      ��S      �X     ��X     ��W     ��X     ��F     ��F     �fG     ��G     ��J     ��K     �>T      �4S      ��W     � X     �VW     �LX     �E�    �  �E�   �   �}�t%�}� t�E��U�H�Hc�H�H�H��ǀ�u`    �}�t%�}�t�E��U�H�Hc�H�H�H��ǀ��`    �}�t/�}� t)�E��U�H�Hc�H�H��H��H�H�H��ǀ�u`    �}�t)�E��U�H�Hc�H�H��H��H�H�H��ǀ�w`    �E��}�
�8����E�    �   �}�u�}� t�}� u�}�t/�}�t)�E��U�H�Hc�H�H��H��H�H�H��ǀ�v`    �}�u�}�u�}� t%�}� t�E��U�H�Hc�H�H�H��ǀ��`    �E��}��t����E�H�H��ǀDx`    �E�H�H��ǀDz`    �E�H�H��ǀD~`    �E�H�H��ǀD�`    �2<     �H<     �~<     ��<     �
H     � J     �VN     �lP     ��]     �^     �>^     �T^     �E�H�H��ǀy`    �E�H�H��ǀD{`    �E�H�H��ǀ�`    �E�H�H��ǀ�`    �E�H�H��ǀ�`    �E�H�H��ǀD�`    �E�H�H��ǀē`    �E�H�H��ǀ�`    �E�H�H��ǀĎ`    �E�H�H��ǀĐ`    �E�H�H��ǀĔ`    �E�H�H��ǀĖ`    �E��}�������E�   �#�}� u�}�t�E�H�H��ǀ��`    �E��}�~��E�   ��E�H�H��ǀ�u`    �E��}�	~��E�   ��E�H�H��ǀ��`    �E��}�	~��E�
   �!�E�H�H��H��H��H�ǀ�w`     �m��}���E�
   �!�E�H�H��H��H��H�ǀ�u`     �m��}���E�   �'�}�t�E�H�H��H��H��H�ǀ�v`     �E��}�~��E�
   ��}�t�E�H�H��ǀ�u`    �m��}���E�   ��}�t�E�H�H��ǀ��`    �E��}�~��E�
   ��}�t�E�H�H��ǀ��`    �m��}���E�   �'�}�t�E�H�H��H��H��H�ǀ�v`    �E��}�~��E�   �'�}�t�E�H�H��H��H��H�ǀ�u`    �E��}�	~��E�   �'�}�t�E�H�H��H��H��H�ǀ�w`    �E��}�	~��
Q     � S     ��V     ��X     ��Z     ��N     ��P     ��R     ��V     ��X     ��L     ��N     �Q     ��U     ��W     ��N     ��P     �pU     ��W     ��Y     ��:     ��<     �.A     �dC     ��E     � 8     �V:     ��<     �A     �8C     �^7     �T9     �J;     �@?     �6A     �<9     �2;     �(?     �A     �C     �BH      �4H     �:H     �$H      �I      �>     �>     ��6     ��6     ��<     ��<     ��F     ��F     ��Q     ��Q     ��R     ��R     �?     �
?     �P     ��O     ��F  	   ��F     ��G  
   ��G     ��>     ��>     ��>     ��>     ��O     �rO     ��O     ��O     �XD     �JD     ��H     �vH     �0E     �"E     �\I     �NI     ��<     ��<     �d;     �V;     ��P     ��P     �|W     �nW     ��Q     ��Q     �TG     �FG     ��=     ��=     ��N     ��N     ��E     ��E     ��F     �vF     �P=     �B=     �|=     �n=     �(N     �N     �TN      �FN     � C  !   ��B     �,G  "   �G     ��C  #   ��C     �H  $   ��G     �Z@ �@t` �S���� Z@ �@t` �D����E�    ��   �GZ@ �@t` �)����E�    �   �E�U�Hc�Hc�H��H��H�H�H�����u` �E��}�ws�E�H��xZ@ ��JZ@ �@t` ������d�MZ@ �@t` ������S�PZ@ �@t` �����B�SZ@ �@t` �����1�VZ@ �@t` ����� �YZ@ �@t` ������\Z@ �@t` �o����E��}��D����`Z@ �@t` �R����E��}������ Z@ �@t` �5����cZ@ �@t` �&���� Z@ �@t` �����E�    ��   �GZ@ �@t` ������E�    �   �E�U�Hc�Hc�H��H��H�H�H�����u` �E�}�ws�E�H�ŨZ@ ��JZ@ �@t` �����d�MZ@ �@t` �����S�PZ@ �@t` �����B�SZ@ �@t` �u����1�VZ@ �@t` �d���� �YZ@ �@t` �S�����\Z@ �@t` �B����E��}��D����`Z@ �@t` �%����E��}������ Z@ �@t` ������UH��SH��8H�}��E�    �W�E�EԿ(   �`���H�E؋u��H�}������H�U�HcE�H�M�H�E��H�E�H�]�H�}�����H�]�H�}��)����}�~�H�}�����H��8[�ÐUH��SH��8H�}��E�    �W�E�EԿ(   �����H�E؋u��H�}��a���H�U�HcE�H�M�H�E��H�E�H�]�H�}�����H�]�H�}������}�~�H�}�����H��8[�Ð��UH��H�}�H�E�H�     �ÐUH��H�}�H�E�H�     �ÐUH��H�}�u�U��M�H�E�H� H��u
H�E�    �UH�E�H� H�E��9H�E�� ;E�u"H�E��@;E�uH�E��@;E�u
H�E�H�E��H�E�H�@H�E�H�}� u�H�E�    H�E���UH��H���}��u��}�u'�}���  u���` �������T@ �    ��F@ ������ÐUH����  �   �����ÐUH��H��H�}����` �������UH��AVAUATSH��H�}�H�u�H�}� ��   H�E�D�`H�E�D�hH�E�D�0H�EЋX��Z@ �@t` ����H�ǉ������H�Ǿ�Z@ �|���H��D�������H�Ǿ�Z@ �d���H��D������H�Ǿ�Z@ �L���H��D������H�Ǿ[@ �4���H�Ǿ @ �w���H�E�H�pH�}��4���H��[A\A]A^�ÐUH��H��H�}�H�E�H�0H�}��
�����UH��H��@H�}؉uԉUЉM�D�E�H�E�H� H����  �   �7���H�E�H�U��EԉH�U��EЉBH�U��ẺBH�U��EȉBH�E�H� H�E�M̋UЋu�H�}�����H��������   H�E�H� H�E���   H�E�� ;E���   H�E��@;E���   H�E��@;E���   H�E�H� H;E�u9H�E�H�PH�E�H�H�E��@EȋM̋UЋu�H�}�A�������H�}��N����NH�E�H�PH�E�H�PH�E��@EȋM̋UЋu�H�}�A�������H�}������H�E�H�E�H�E�H�@H�E�H�}� �2�����   H�E�H� �@;E�}+H�E�H�H�E�H�PH�U�H�E�H��   H�E�H�@H�E�H�E�H�@H��tH�E�H�@�@;E��H�E�H�PH�E�H�PH�U�H�E�H�B�V�   ����H��H�E�H�H�E�H��EԉH�E�H��EЉBH�E�H��ẺBH�E�H��EȉBH�E�H� H�@    �ÐUH��H��H�}�H�u�H�}� tH�E�H�pH�}������H�}�������ÐUH��H��H�}�H�E�H�0H�}�������UH��H��H�}�H�}�������ÐUH��H��H�}�H�}������Ð��UH��H�}�H�E�H�     �ÐUH��H�}�H�E�H�     �ÐUH��H���}��u��}�u'�}���  u���` �y�����T@ �    ��J@ �����ÐUH����  �   �����ÐUH��H��H�}����` ������UH��SH��XH�}�H�u�H�U�H�}� ��   H�u�H�}��'���������tH�E�H�E���   H�u�H�}���������tRH�E�H�XH�u�H�}������H�u�H�}�H������H�E�H�}��+����xH�E�H�]�H�}�����H�]�H�}��{���H�E�H�XH�u�H�}�����H�u�H�}�H���2���H�E�H�}�������&H�E�H�]�H�}������H�]�H�}��)���H�E�    H�E�H��X[��UH��SH��8H�}�H�u�H�E�H�H�u�H�}��1���H�u�H�}�H������H��H�}��e���H�]��H�E�H�]�H�}��N���H�]�H�}�����H�E�H��8[��UH��AUATSH��H�}�H�u�H�}� ��   H�E�H�pH�}������L�eؿ   �  A�ſ    �  �þ[@ �@t` ����H�ǉ�����H��D���t���H�Ǿ�R@ �G���H��L������H�Ǿ @ �����H�}�H���j����[@ �@t` �c���H�Ǿ @ ����H�E�H�pH�}��/���H��[A\A]��UH��H��H�}�H�E�H�0H�}�������UH��SH��xH�}�H�u��U��M�D�E�D�M�H�uH�}�谿�������  H�EH�@H��tlH�EH�XH�u�H�}�蓿���E��U��M��u�H�}�L�U�H�$A��A�Љ�H��L���|���H�}�诿����  H�E�H�]�H�}�虿��H�]�H�}�������    ����H�E�H�}��  H�EH�U�H�PH�EH�@H��H�u��տ��H�EH�@H�x�E��M��U��u�A���+���H�EH�@H�@    H�EH�@H�@    �H  H�E�H�]�H�}��O���H�]�H�}��b���H�uH�}�腾���������  H�EH�@H��tlH�EH�XH�u�H�}��f����E��U��M��u�H�}�L�U�H�$A��A�Љ�H��L���O���H�}�肾���   H�E�H�]�H�}��l���H�]�H�}��Ͼ���    赾��H�E�H�}��  H�EH�U�H�PH�EH�@H��H�u�訾��H�EH�@H�x�E��M��U��u�A�������H�EH�@H�@    H�EH�@H�@    �H�E�H�]�H�}��%���H�]�H�}��8���H��x[�ÐUH��SH��XH�}�H�uЉỦM�D�E�D�M�H�E�H� H��tkH�E�H�H�u�H�}��1����E��UċMȋu�H�}�L�U�H�$A��A�Љ�H��L������H�}��M����   H�E�H�]�H�}��7���H�]�H�}�蚽���    耽��H�E�H�}��[  H�E�H�U�H�H�E�H� H��H�u��u���H�E�H� H�x�E��MċUȋu�A�������H�E�H� H�@    H�E�H� H�@    �H�E�H�]�H�}������H�]�H�}�����H��X[�ÐUH��H�� H�}�H�u�H�}� tCH�E�H�pH�}������H�E�H�pH�}������H�E�H�E�H�}� tH�}���  H�}�膻����UH��H��H�}�H�E�H�0H�}�������UH��H��H�}�H�}�������ÐUH��H��H�}�H�}������ÐUH��}��u��U��E�!���UH��}��u��U��E�	���UH��H��H�}��u�H�E��8�u��������H�E��H�E��ÐUH��H��H�}��u�H�E��8�u�������H�E��H�E��ÐUH��}��E�����UH��H�� H�}�u�U�H�E�@�E��}��������H�}�H�������u��}��4�����H�}�H���M����E���UH��H��H�}�H�}���   ��   ����H�E��ÐUH��}�E�E��E���UH��@�}��E�E��E��ÐUH��SH��H�}�H�}��ҹ��H�}�H�������H�E�H�]�H�}�肺��H�]�H�}�����H��[��UH��SH��H�}�H�}�H�������H�E�H�E�H�}��C����&H�E�H�]�H�E�H�E�H�}��(���H�]�H�}�苺��H��[�Ð������    �    L�d$�L�l$�L�%/  L�t$�L�|$�I��H�\$�H�l$�H��8A��I�������H�  I)�I��M��t1�H�ÐH��L��L��D���H��I9�u�H�\$H�l$L�d$L�l$ L�t$(L�|$0H��8Ð����UH��S�(p` H��H��  H���tD  H����H�H���u�H��[�Ð�H���O���H���                Stage 1 starts here Welcome to Robomall!        Enter the number of robots that will enter RoboMall:  Number of robots is       Enter number of stores for robot  
Now, processing robot        
No. of stores for this robot:  
Enter coordinates for the store robot   will visit:    Enter Number of Items for this Store:  Store Location:              Number of Items to be Read In:  
Robot       begins at entry location A1 at time    Robot is at store. Enter items to deliver followed by their counts: 
 Item ID:      Number of Items:  
New location set to ( , )         exits simulation at position A1 at time        
Enter coordinates for the stores robot  Value of q variable now:  Print database:  
 Stage 1 ends here
        Time  	Location ( , )
 Type is: A1 Time is:  Plain tile 
Robot reached store ( ) at time        
Robot got on the elevator at time:     
Robot got off the elevator at time:  
Robot has reached fork  ERROR! ERROR! ERROR! CASE EMPTY INVALID TILE     � @     7#@     �#@     �!@     &@     �4@     "@     9"@     _"@     �"@     �"@     �"@     �"@     #@     �4@     �&@     &'@     v'@     �'@     <(@     �(@     �(@     �)@     *@     �*@      +@     v+@     �+@     ",@     x,@     �,@     $-@     z-@     �-@     ..@     �.@     �.@     R/@     �/@      0@     �0@     1@     �1@     (2@     ~2@     �2@     *3@     �3@     �3@     ,4@     �4@     First Floor
    -------------------------------------
 |     A1 S  E  P  F  !!! |
 Second Floor
        �B@     �B@     �B@      C@     C@     �B@     �C@     D@     D@     -D@     >D@     �C@     Qty Available:       Store Location: ( ,  )     ITEM ID:        --------------------------------------------------  ;�  ;   ���  Z���$  p���D  �����  N���d  ~����  ����  l���  ����$  
���D   ���d  8����  �����  &����  <���  T���$  N���D  ����d  X����  n����  �����  ���  D���$  Z���D  r���d  L����  j����  �����  �����  ����  ���,  (���l  >����  T����  �����  ����  ����,  ����L  >���l  ����  8����  �����  ����4	  @���T	  ^���t	  v����	  ����l  �����  �����  �����  ����  ���  n���,  ����L  �����  �����  ���	  d����	  t����	         zPLR x@ �     $   h@ =       A�C      D   �@        A�C      d   �@        A�C      �   �@ /       A�C      �   �@ �   \e@ A�CE�   �   �@ �  le@ A�CH�       zPR x@ �       $   X@ `    A�C          D   �@ `    A�C          d   @ =    A�C          �   V@     A�C          �   l@     A�C          �   �@ �   A�CE�           zPLR x@ �     $   45@ =       A�C      D   r5@        A�C      d   �5@        A�C      �   �5@ �      A�C      �   �D@ �   	f@ A�CE�   �   E@ �   f@ A�CE�       zPR x@ �       $   �E@     A�C          D   �E@     A�C          d   �E@ �    A�C          �   RF@ =    A�C          �   �F@     A�C          �   �F@     A�C       $   �   �F@ �    A�CK����           �G@     A�C          ,  �G@ 9   A�C          L  �I@ 3    A�C          l  $J@     A�C          �  BJ@     A�C          �  ZJ@     A�C              zPLR x@ �     $   �Q@        A�C      D   �Q@        A�C      d   R@ +       A�C      �   .R@ +       A�C      �   ZR@        A�C      �   hR@ R       A�C      �   �R@ %       A�C        �R@        A�C      $  tJ@        A�C      D  �J@        A�C      d  �R@        A�C      �  �J@ =       A�C      �  �J@        A�C      �  �J@        A�C      �  K@   )f@ A�CE�     L@ p   Pf@ A�CE�$   $  �L@ �       A�CI���       L  fM@        A�C      l  S@ J   df@ A�CE�   �  �M@ {  tf@ A�CE�   �   P@ /  �f@ A�CE�   �  RS@ Z   �f@ A�CE�   �  0Q@ \       A�C        �Q@        A�C      ,  �Q@        A�C      L  �Q@        A�C          zR x�        ����           $   4   �����    J��Q��Q@��          ��&  /3d }  ���  ;� M� `� ��� �	�
 �
� �� �� �� �&� �-� �� ��� �� �� �� �� �� �&� �-� �� ��� �� �  �  ��!  4O h  ��!  4O h  ��#(D  w� �  �  �� �  �  ��   0G <  `  ��  % >  ��:'2  � �  �  �� ��  �� �  �  �� �e  ��:  ex n  �  �� �b  ��- &  N                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ���������@     V@     r5@     �F@     �J@             ��������                                     &             0             M             �@            �T@     ���o    @@            �@            x@     
       �                                          r`            �                           0
@            �	@            H       	              ���o    x	@     ���o           ���o    2	@                                                                                                             Pp`                     �@     �@     @     @     &@     6@     F@     V@     f@     v@     �@     �@     �@     �@     �@     �@     �@     �@     @     @     &@     6@     F@     V@     f@     v@     �@          GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)  .symtab .strtab .shstrtab .interp .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .text .fini .rodata .eh_frame_hdr .eh_frame .gcc_except_table .ctors .dtors .jcr .dynamic .got .got.plt .data .bss .comment                                                                                  @                                          #             @                                          1   ���o       @@     @      8                             ;             x@     x                                C             �@     �      �                             K   ���o       2	@     2	      B                            X   ���o       x	@     x	      p                            g             �	@     �	      H                            q             0
@     0
      �                          {             �@     �                                    v             �@     �      �                            �             �@     �      �E                             �             �T@     �T                                    �             �T@     �T      �                             �             L[@     L[      �                             �             0]@     0]      ,                             �             \e@     \e      �                             �              p`      p      8                              �             8p`     8p                                    �             Hp`     Hp                                    �             Pp`     Pp      �                           �             r`     r                                   �             r`     r      �                             �             s`     s                                    �              s`     s      �&                              �                      s      �                                                   �t      �                                                    X}               J                 	                      p�      �                                                            @                   @                   @@                   x@                   �@                   2	@                   x	@                   �	@                  	 0
@                  
 �@                   �@                   �@                   �T@                   �T@                   L[@                   0]@                   \e@                    p`                   8p`                   Hp`                   Pp`                   r`                   r`                   s`                    s`                                        �@                 ��                      p`             *     8p`             8     Hp`             E     Pu`            S     Xu`            b     �@             x     @@                 ��                �     0p`             �     Xe@             �     Hp`             �     PT@             �    ��                �     �@            �     h@     =           \u`                �@            '   ��                2    V@            �     @     =           `u`                l@            K   ��                T    r5@            �     45@     =           ��`                �5@            b   ��                q    �F@            �     RF@     =           ��`                �F@            �   ��                �    �J@            �     �J@     =           ��`                �J@            �     p`             �     p`             �   r`             �     p`                  p`             "     p`             3     p`             F   Pp`             O     s`             Z     s`           p             
      �  "  hR@     R       �    E@     �       �                    �    �E@     �       �             "          �E@            "    �S@            2    �@             9  "  �Q@            S                      b                      v                    �             �       �  "  RS@     Z       �    �@     `       �    �T@             �                    �             �                   �      ,    �J@            @  "  R@     +       [             O       |             x       �             ^       �             |       �    �I@     3           X@     `                    �      T    �F@     �       ~    �T@            �             �      �             D       �    s`             	    �G@            '     P@     /      E    �u`      $      H    �L@     �       p  "  ZR@            �  "  �R@            �    �M@     {      �  "  �@     /       �    fM@                �E@            &    �5@     �      :    @t`           Q    �Q@            e   �T@             r  "  .R@     +       �   @p`             �    �S@     �       �  "  S@     J       �    0Q@     \       �    �D@     �       �   ��s`             �    BJ@                         1      l    �@     �      �  "  �@     �       �  "  �R@     %       �             J      �    �Q@            	    $J@            '	   ����`             ,	                    J	  "  �R@            U	    L@     p       o	    K@           �	      @     )       �	    �Q@            �	    tJ@            
   ��s`             
     @     �      ,
    �G@     9      H
             �       [
  "  �Q@            u
                   �
                    �
                    �
             �       �
                    ;             c       �    �@     �      �   
 �@             �    ZJ@             call_gmon_start crtstuff.c __CTOR_LIST__ __DTOR_LIST__ __JCR_LIST__ dtor_idx.6147 completed.6145 __do_global_dtors_aux frame_dummy __CTOR_END__ __FRAME_END__ __JCR_END__ __do_global_ctors_aux hsahay_main.cpp _GLOBAL__I_main _Z41__static_initialization_and_destruction_0ii _ZSt8__ioinit __tcf_0 motion.cpp _GLOBAL__I__ZN5RobotC2Ei mall.cpp _GLOBAL__I_fl linkedlist.cpp _GLOBAL__I__ZN10linkedlistC2Ev binarytree.cpp _GLOBAL__I__ZN10binarytreeC2Ev __preinit_array_start __fini_array_end _GLOBAL_OFFSET_TABLE_ __preinit_array_end __fini_array_start __init_array_end __init_array_start _DYNAMIC data_start _ZSt3cin@@GLIBCXX_3.4 _ZNSs6appendEPKcm@@GLIBCXX_3.4 _ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_ _ZN4MallC2Ev _ZNSsC1Ev@@GLIBCXX_3.4 _ZN10linkedlist6searchEiii _ZNSolsEi@@GLIBCXX_3.4 _ZN10linkedlistC1Ev __libc_csu_fini _start _ZStorSt13_Ios_FmtflagsS_ __gmon_start__ _Jv_RegisterClasses _ZdlPv@@GLIBCXX_3.4 _ZNSs7reserveEm@@GLIBCXX_3.4 _ZN9item_nodeD1Ev _ZN5RobotC1Ei _fini _ZNKSs4sizeEv@@GLIBCXX_3.4 _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4 __libc_start_main@@GLIBC_2.2.5 _ZN10binarytreeC1Ev _ZStoRRSt13_Ios_FmtflagsS_ _ZNKSs7compareERKSs@@GLIBCXX_3.4 _ZNSsC1ERKSs@@GLIBCXX_3.4 __cxa_atexit@@GLIBC_2.2.5 _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4 _ZN10linkedlist12destroy_listEP10store_node _ZN5RobotC2Ei _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4 _ZN10linkedlist10print_listEP10store_node _IO_stdin_used _ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RSbIS4_S5_T1_E@@GLIBCXX_3.4 _ZNSsD1Ev@@GLIBCXX_3.4 __data_start _ZN10linkedlist10print_listEv _ZN10binarytree6insertESsiiii fl _ZN10binarytree10print_treeEP9item_node _ZStcoSt13_Ios_Fmtflags _ZSt7setfillIcESt8_SetfillIT_ES1_ _ZN10binarytree6insertESsiiiiP9item_node _ZNSt11char_traitsIcE6lengthEPKc _ZN10binarytree10print_treeEv _ZN10linkedlistC2Ev _ZN4Mall8floormapEv _ZSt4cout@@GLIBCXX_3.4 _ZN10binarytreeD2Ev __dso_handle _ZStaNRSt13_Ios_FmtflagsS_ __DTOR_END__ __libc_csu_init _ZN9item_nodeC1Ev _ZN10binarytree12destroy_treeEP9item_node _ZN4MallC1Ev __bss_start _ZN10linkedlistD1Ev _ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E@@GLIBCXX_3.4 _ZN5Robot4moveEPiiii _ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_ _ZSt5rightRSt8ios_base _ZNSirsERi@@GLIBCXX_3.4 _ZN10binarytree12destroy_treeEv _ZN10linkedlist12destroy_listEv _end _ZNSolsEPFRSoS_E@@GLIBCXX_3.4 _ZSt4setwi _ZN10binarytree6searchESs _ZN10binarytree6searchESsP9item_node _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4 _ZN10binarytreeD1Ev _ZN10binarytreeC2Ev _edata __gxx_personality_v0@@CXXABI_1.3 _ZN10linkedlist6insertEiiii _Znwm@@GLIBCXX_3.4 _ZStanSt13_Ios_FmtflagsS_ _Unwind_Resume@@GCC_3.0 _ZNSsaSERKSs@@GLIBCXX_3.4 _ZNSolsEPFRSt8ios_baseS0_E@@GLIBCXX_3.4 _ZNSs6appendERKSs@@GLIBCXX_3.4 _ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw@@GLIBCXX_3.4 _ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St8_SetfillIS3_E@@GLIBCXX_3.4 main _init _ZN10linkedlistD2Ev                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  README.txt                                                                                          0000771 0020221 0020221 00000007265 12417640213 012067  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 README for Program 5 

Team: Himanshu Sahay and Marco Duran
CS2303 A04

Language: C++

The program is split is 2 parts, Stage 1 and Stage 2. Stage 1 was done by Himanshu Sahay and Stage 2 by Marco Duran

--------------------------------
NOTE: There is a driver function for thr almost working Stage 1 and one for Stage 2. They have been implemented separately, but only Stage 1 gives an output and works to the level it has been implemented.

All the code for Stage 1 is in the tar and the code for Stage 2 is in the tar in a seprate folder called Stage2
--------------------------------------


Stage 1: Author: Himanshu Sahay

The executable file for Stage 1 is prog5_stage1

The program is implemented as such:

- There is a class Robot for the robots that deliver goods to stores. 
- There is a wrapper class Mall which contains pointers to robots and the floor map of the mall.
- There is a function motion.cpp while includes robot.h. It has the constructor for robot and the function to move a robot. 
- A robot moves step by step and calls the move function in motion.cpp recursively.
- The first call to the move function is made in hsahay_main.cpp where it is called when a store location is given to it. 
- The robot deliveries database is built via a binary tree for the items and a linked list of stores at each item (node of the binary tree)
- Once a robot reahces a store, it is asked to input the items for that store. These instructions are given via on screen commands. 
- The database is updated at each instance of a robot going to a store. 

How this works: 
- The main function takes user input (on screen commands).
- It asks for number of robots, number of stores for each robot, number of unique items, item codes and their counts.
- Calls are made to the move function. The item database is also updated.
- Finally, the program ends after printing the item database. 

The Makefile contains all the compiler commands to compile, link and load (by creating .o files) and then execute.

What doesn't work in Stage 1:
- The robots currently do not come off of an event list. Only 1 robot is in the mall at any given time. I did not have enough time to implement this in the program.
- The tie breaker for stores when inputted into the list for an item is also not implemented. It's a quick add, but I ran short of time.

Thanks you and I hope this helps in the grading oof Stage 1 of the program.

Sincerely,
Himanshu Sahay

--------------------------------------------------------------------

Stage 2: Author: Marco Duran

The executable file for stage 2 is prog5_stage2

Phase 2 of the program does not actually work but all of code for the event list and the queue do work, and the prgoram takes user input. 
 
I ended up making a seperate driver function to at least have the shopper take in the inputs that were specified.

I created a class for the shopper which contains all of the functions. 

I wrote functions for the shopper for having it add a store to the shoppers itinerary queue from the item that was on the shoppers wish list.
 
I had a function for updating the shoppers list when a store was found in the mall, I also had a function for deleting an item if there was not enough of an item in the store.
 
I dont have a variable for time with regards to the shopper, and therefore the queue will not work for the shopper, but it will work for the robot. 

The shopper cannot move at all, it can only take in some of the data.

I could not do anything with regards to multiple shoppers arriving in a store at the same time so no tie breaker was even created for that case. 

Hope this helps.
Marco Duran
-----------------------------------------------
                                                                                                                                                                                                                                                                                                                                           robot.h                                                                                             0000771 0020221 0020221 00000001341 12417616705 011665  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Authot: Himanshu Sahay

#include "globals.h"

#ifndef ROBOT_H
#define ROBOT_H

//Author: Himanshu Sahay
class Robot
{
  public:
  bool checkIfInMall; //set to true when robot enters mall. Only move robot if this is true.
  struct coord destination;
  struct coord lloc; //last location - to get out of store
  int rnum; //robot number - only for printing purposes in main


  // Store num didn't work int snum; //max number of stores per robot = 24


  int starttime; //start and end times of robot simulation
  int endtime;
  Robot(int robotnum); //constructor
  ~Robot(); //destructor
  //function to move robot
  void move(int *tptr, int x, int y, int z); //takes in x,y,z location and takes in pointer to the location

};


#endif
                                                                                                                                                                                                                                                                                               store_node.h                                                                                        0000771 0020221 0020221 00000001126 12417616747 012710  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 //Author: Himanshu Sahay
#ifndef STORE_NODE_H
#define STORE_NODE_H

#include <string>
//#include "linkedlist.h"


//Author: Himanshu Sahay
//This Struct is used to hold the information held in the linked list
struct store_node{
    int row;                 //Row of the Store
    int col;                 //Column of the Store
    int floor;               //Floor of the Store
    int item_quantity;       //An integer representing the quantity of the specific item at the given store
    store_node *next_store;  //A pointer to the next store_node in the linked list
};

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                          Stage2/                                                                                             0002771 0020221 0020221 00000000000 12417640075 011511  5                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 Stage2/queue.cpp                                                                                    0000771 0020221 0020221 00000002310 12417623103 013327  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*
 *Source file for the queue processes for the shoppers
 *Author: Marco
 *This code was a c++ implementation from program 3 with a bit of abstraction
 * 
 */

#include "queue.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Queue::Queue(){
	headPtr = NULL;
	tailPtr = NULL;
}

void Queue::enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, QueueData value){
	cout<<"Enqueue"<<endl;
	QueueNodePtr newPtr = new QueueNode;//pointer to a new queuenode

	if(newPtr != NULL){
		newPtr->data = value;
		newPtr->nextnode = NULL;

		if(isEmpty(*headPtr)){
			*headPtr = newPtr;
			*tailPtr = newPtr;
		}
		else{
			(*tailPtr)->nextnode = newPtr;
			*tailPtr = newPtr;
		}
	}
	else{
		cout<<value.process_id<<" event (process) not inserted. No memory available."<<endl;
	}
}

QueueData Queue::dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr){
	QueueData value;
	QueueNodePtr tempPtr;

	value = (*headPtr)->data;
	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextnode;

	//if queue is empty
	if(*headPtr == NULL){
		*tailPtr = NULL;
	}
	delete tempPtr;
	return value;
}//end dequeue

int Queue::isEmpty(QueueNodePtr headPtr){
	return headPtr == NULL;
}
                                                                                                                                                                                                                                                                                                                        Stage2/eventlist.cpp                                                                                0000771 0020221 0020221 00000014313 12417622405 014232  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*
Source File for the event list
Author Marco Duran
Taken from previous program 3 and converted into c++
*/

#include "events.h"
#include <string>
#include <iostream>
using namespace std;

EventList::EventList()
{
  //Constructor with no arguments
  //Initializes head and tail node
  rootPtr = NULL;
}

//destructor to empty the linked list
EventList::~EventList()
{
  //Destructor
  if(!(rootPtr == NULL))

    { //if the list is not empty...
     cout << "\nI am destroying your nodes ... \n";

     EventNode *currentPtr = rootPtr;
     EventNode *tempPtr;

     while(currentPtr != 0)
       {//deletes the remaining nodes
          tempPtr = currentPtr;
          cout << "Destroyed store: " << tempPtr->store.coor.x << " " << tempPtr->store.coor.y << " " << tempPtr->store.coor.z << endl;
          currentPtr = currentPtr->nextnode; //moves to next node in list
          delete tempPtr;
       } //ends the while loop

      } // ends the if statement
    cout << "All of your nodes have been destroyed!\n\n";
}


//public version of print_list function
void EventList::print_list()
{
  print_list(rootPtr); //calls private version of the function
}

//private version of print_list function
void EventList::print_list(EventNode *rootPtr)
{
  //The list is empty?
  if(rootPtr == NULL)
    {
      cout<< "The list is empty."<<endl;
      return;
    }
  else
    {
      cout<<"For store ("<<(rootPtr->store).coor.x<<", "<<(rootPtr->store).coor.y<<", "<<(rootPtr->store).coor.z<<") the item count is "<<(rootPtr->store).item_count<<".\n";
      print_list(rootPtr->nextnode); //calls function recursively with next store on the list
    }
}


//add_list function ot add store to the linked list in the appropriate position
  void EventList::add_list(Store str)
  {

    if(rootPtr != NULL) //list is not empty
    {
    EventNodePtr newNode = new EventNode;//allocates memory for a new node

    //Now, give store information to the new node
    (newNode->store).coor.x = str.coor.x;
    (newNode->store).coor.y = str.coor.y;
    (newNode->store).coor.z = str.coor.z;
    (newNode->store).item_count = str.item_count;

    EventNode *currentPtr = rootPtr; //initialize currentPtr to the global rootPtr for use in this function
    EventNode *tempPtr, *previousPtr; //to use

    //if store is found in linkedlist
    if(search_in_list(str)== 1)
    {
    tempPtr = rootPtr;

    //loop to find correct location in list
    while(tempPtr!=NULL)
      {
          //if previous record exists
          if(((tempPtr->store).coor.x == str.coor.x) && ((tempPtr->store).coor.y == str.coor.y) && ((tempPtr->store).coor.z == str.coor.z))
            {
              if(tempPtr == rootPtr)
                { //checks positions from rootPtr and forward
                  rootPtr = tempPtr->nextnode; //shifts root pointer of linked list by 1 position so that incoming information can be put into current root position
                  str.item_count+= (tempPtr->store).item_count; //increment item count of the store
                  add_list(str); //insert store with incremented item count
                  delete tempPtr; //delete earlier instance of the store
                }
              else
                { //checks positions going backwards from rootPtr
                  previousPtr->nextnode = tempPtr->nextnode;
                  str.item_count+= (tempPtr->store).item_count; //increment item count of the store
                  add_list(str); //insert store with incremented item count
                  delete tempPtr; //delete earlier instance of the store
                }
            }
          else
            {
              //shifting by one position to move along the list
              previousPtr = tempPtr;
              tempPtr = tempPtr->nextnode;
            }
          }
      }
    else if(str.item_count < (rootPtr->store).item_count) //store is not found and item count of store is less than item count of the store that of the root of the list
      {
        //First, check position to insert store at
        while( (currentPtr->nextnode != NULL) && (str.item_count < (currentPtr->store).item_count) )
          {
              currentPtr = currentPtr->nextnode;
          }

        //Now, insert store at the correct position found
          newNode->nextnode = currentPtr->nextnode;
          currentPtr->nextnode = newNode;
      }
    else //store is not found and item count of store is more than item count of the store that of the root of the list
      {
        newNode->nextnode = rootPtr; //insert store at root position
        rootPtr = newNode; //Now, this new node is the root
      }
  }

  else //list is empty
  {
    //insert the new node as root of the linked list
    rootPtr = new EventNode;
    (rootPtr->store).coor.x = str.coor.x;
    (rootPtr->store).coor.y = str.coor.y;
    (rootPtr->store).coor.z = str.coor.z;
    (rootPtr->store).item_count = str.item_count;
  }

}

int EventList::search_in_list(Store str)
{
  if(rootPtr == NULL)
    {
      return 0; //list is empty
    }

  else
    {
      EventNode *currentPtr = rootPtr;
      while(rootPtr!=NULL)
        {
          //if currentPtr has same coordinates as store
          if( (str.coor.x == (currentPtr->store).coor.x) && (str.coor.y == (currentPtr->store).coor.y) && (str.coor.z == (currentPtr->store).coor.z))
            return 1; //indicates that store is found

          currentPtr = currentPtr->nextnode; //move along the while loop by going to the next position

        }

      return 0; //store not found in list
      }
  }

  Store EventList::getStore(EventNodePtr rootPtr, EventNodePtr currPtr){
    EventNodePtr newPtr;
    newPtr = new EventNode;

    if((currPtr->store).item_count < (newPtr->store).item_count){//if the number of items in the store are less than the next store
      currPtr = currPtr->nextnode; //go to the next store
      getStore(newPtr, currPtr); //recursivley finds the store with the biggest item count
    }

    Store destination = currPtr->store;//sets the destination of the shopper to the current store
    delete newPtr;
    return destination; //returns the store value
  }
                                                                                                                                                                                                                                                                                                                     Stage2/main.cpp                                                                                     0000771 0020221 0020221 00000003247 12417632575 013156  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*
Author Marco Duran
Driver file for how the shopper should run in phase 2 of the simulation
*Note not all of this code runs correctly but i believe that the logic behind it is correct
there is also no sense of time in this driver function
*/

#include <cstdlib>
#include <iostream>
#include "events.h"
#include "queue.h"
#include "shopper.h"

using namespace std;

int main()
{
	EventList database;
	Shopper s;
	Queue itinerary;
	int i = 0;
	int arr_time; // the relative arrival time of the ith shopper to the simulation
	int j_items; // is the number of unique items on the ith shopper's shopping list
	string item; // is the 2 digit ASCII code for the jth item on the shopping list
	int count; // is the quantity of item that the shopper wants to buy
	int shoppers; //number of shoppers that are in the mall
	Store store;
	cout <<"Insert the number of shoppers that will be in the robomall";
	cin >> shoppers;


	while( i < shoppers){//runs the loop until the amount of shoppers is reached
	cout << "Insert the arrival time of shopper" << i+1 << endl;
	cin >> arr_time;
	cout << "\nInsert the number of items on the shopping list" << endl;
	cin >> j_items;

	for(int j = 0; j < j_items; j++){
		cin >> item >> count;
		cout <<"[DEBUG] Item code: " << item << " " << "ItemCount: " << count;
		if(s.searchItem(database, store) == true)
		store = database.rootPtr->store;

		if(s.searchItem(database, store) == false){ //searches for the item in the database
			s.deleteItem(itinerary.headPtr, itinerary.tailPtr);//if not found it deletes the item from the queue
		}
		else{
			s.addStore(store, itinerary, database);
		}
	}

	}



return 0;
}
                                                                                                                                                                                                                                                                                                                                                         Stage2/shopper.h                                                                                    0000771 0020221 0020221 00000001502 12417631442 013337  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*Header file for the shopper
Author Marco Duran 
*/
#include "events.h"
#include "queue.h"
#include <string>

class Shopper {

      public :
	  Queue itinerary;//the shopper's itinerary
      void addStore(Store store, Queue itinerary, EventList database);//the store is put into the traveling route of the shopper
      QueueNodePtr deleteItem(QueueNodePtr *headPtr, QueueNodePtr *tailPtr); //deletes the item from the shopping list and cancels the route to that store
      void move(int *tptr, int x, int y, int z);
      bool searchItem(EventList database, Store newStore);//searches the database to return a store with the largest quantity of that item
      private:
      EventList updateList(EventList shopping_list, Store newStore);//updates the shopping list if the item has or has not been found
};


                                                                                                                                                                                              Stage2/shopper.cpp                                                                                  0000771 0020221 0020221 00000060076 12417631642 013707  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*
Source file for the Shopper class, contains all the functions that are in the Shopper class
Author: Marco Duran and Himanshu Sahay
*/


#include <cstdlib>
#include <iostream>
#include <string>
#include "shopper.h"
#include "events.h"
#include "queue.h"


//Author: Marco Duran
//public version of search function
bool Shopper::searchItem(EventList database, Store newStore){ // if the store in the database is the same as the store that the shopper is looking for return true
  if(database.rootPtr->store.coor.x == newStore.coor.x && database.rootPtr->store.coor.y == newStore.coor.y && database.rootPtr->store.coor.z == newStore.coor.z ){ //if the store that is inserted is in the database return true
	  return true;
  }
  else
	  return false;//if not it returns false
}

//Author: Marco Duran
EventList Shopper::updateList(EventList shopping_list, Store newStore){//updates the shopping list once a added
	shopping_list.add_list(newStore);
	return shopping_list;
}

//Author: Marco Duran
void Shopper::addStore(Store store, Queue itinerary, EventList database){//adds a store coordinate to the itinerary if the shoppers item fits the criteria of the one in the mall

	if(store.item_count <= database.rootPtr->store.item_count){
    	 // itinerary.enqueue(itinerary.headPtr, itinerary.tailPtr, (itinerary.headPtr) );//has to reach the queuedata for a store
      }

}
//Author: Marco Duran
QueueNodePtr Shopper::deleteItem(QueueNodePtr *headPtr, QueueNodePtr *tailPtr){//deletes an item from the itinerary
     QueueNodePtr tempPtr;

     tempPtr = *headPtr;
     *headPtr = (*headPtr)->nextnode;//points to the next node
     if(*headPtr == NULL) *tailPtr = NULL;//deletes the item

     return tempPtr;
}

//Author: Himanshu Sahay 
//Cannot correctly implement this with the shopper
void Shopper::move(int *tptr, int x, int y, int z){//moves the shopper throughout the robomall

//   if(checkIfInMall == true)
//   {
// //  cout << "Time: "<< *tptr << endl;

//   //struct sqr fl[FLOORSIDE][FLOORSIDE][FLOORNUM]; //initializeing the structure of arrays (extern given in header)

//   /*Enter mall at A1 on first floor.
//     Goes north.
//     Checks at every tile if it is a fork. If tile is not a fork, the robot keeps going.
//     If the current tile is a fork, it checks what is the best path to take in order to reach the destination
//     If the current coordinates match destination coordinates, it says that you have reached the desired store and moves on to the next store.

//   */


// //cout<<"1st destination show inside move function: "<<(rptr->destination).r<<" "<<(rptr->destination).c<<" "<<(rptr->destination).f<<endl;

// //Initializes variables with coordinates of store that the robot is going to
// int xtarget=destination.x;
// int ytarget=destination.y;
// int ztarget=destination.z;

// /*Stores current location as last location at each step.
// If store is reached, last locaion of previous iteration is used so that the robot can move back out of the store*/
// if((fl[x][y][z]).type!=Store)
//   {
//     //cout<<"Printing inside last location if statement: Last location: "<<x<<" "<<y<<" "<<z<<" and "<<temp.r<<" "<<temp.c<<" "<<temp.f<<endl;
//   lloc.x = x;
//   lloc.y = y;
//   lloc.z = z;
//   }

// //cout<<"Last location: %d,%d,%d\n",(rptr->lloc).r,(rptr->lloc).c,(rptr->lloc).f);
// cout<<"Time "<<(*tptr)<<"\tLocation ("<<x<<","<<y<<","<<z<<")\n";

// //---------------------------------------------------------------------------------------------
//   //Debug statements
//   //cout<<"Position: %d %d %d\n",x,y,z);
//   //cout<<"Direction: %d\n",fl[x][y][z].direction);

// //Switches over robot type to facilitate robot movement
//   switch((fl[x][y][z]).type)
//   {
//     case A1:
//     cout<<"Type is: A1"<<endl;

//     if(*tptr%25==0) //Prints current floor map every 5 time units
//       {
//       cout<<"Time is: "<<*tptr;
//         //cout<<"Current floor map\n\n";
//         //Printing current floor map
//           //printcurrent(x,y,z);
//       }
//     if(x==xtarget && y==ytarget && z==ztarget)
//       {
//         return; //Ends robot movement and returns time taken in journey
//       }

//     else
//       {
//         *tptr+=1; //Time is incremented at each step by 1 unit
//         move(tptr,x-1,y,z);
//       }

//     break;

//     case Plain:
//     cout<<"Plain tile"<<endl;
//     if(*tptr%25==0) //Prints current floor map every 5 time units
//       {
//         ////cout<<"Current floor map\n";
//         //Printing current floor map
//       //printcurrent(x,y,z);
//       }
//     {
//       *tptr+=1; //Time is incremented at each step by 1 unit
//       switch((fl[x][y][z]).direction)
//         {
//           case North: //North
//           x--;
//           move(tptr,x,y,z);
//           break;

//           case NorthWest: //NorthWest
//           x--;
//           y--;
//           move(tptr,x,y,z);
//           break;

//           case West: //West
//           y--;
//           move(tptr,x,y,z);
//           break;

//           case SouthWest: //SouthWest
//           x++;
//           y--;
//           move(tptr,x,y,z);
//           break;

//           case South: //South
//           x++;
//           move(tptr,x,y,z);
//           break;

//           case SouthEast: //SouthEast
//           x++;
//           y++;
//           move(tptr,x,y,z);
//           break;

//           case East: //East
//           y++;
//           move(tptr,x,y,z);
//           break;

//           case NorthEast: //NorthEast
//           x--;
//           y++;
//           move(tptr,x,y,z);
//           break;

//           default: break;
//         }
//       }
//       break;

//       case Store: //Switch over direction to move form store

//       if(*tptr%25==0) //Prints current floor map every 5 time units
//         {
//           //cout<<"Current floor map\n";
//           //Printing current floor map
//         //printcurrent(x,y,z);
//         }
//         cout<<"\nRobot reached store ("<<x<<","<<y<<","<<z<<") at time "<<*tptr<<endl;

//         *tptr+=1; //Time is incremented by 1 unit extra for stores

//     if(ztarget==1)
//           {
//             *tptr+=1; //Spends 1 time unit more on a second floor store than on a first floor store
//           }
//           return; //Returns from function if destination reached.

//       break;

//   //WORK ON ELEVATOR
//       case Elevator:

//       if(*tptr%25==0) //Prints current floor map every 5 time units
//         {
//           //cout<<"Current floor map\n";
//           //Printing current floor map
//       //  printcurrent(x,y,z);
//         }

//     if(ztarget==0) //Checks if target floor is first floor
//       {
//         if(z==1) //Checks if robot is currently on the second floor
//           {
//             cout<<"\nRobot got on the elevator at time: "<<*tptr<<endl;
//             cout<<"\nRobot got off the elevator at time: "<<*tptr+3<<endl;
//             z--;
//           *tptr+=4; //3 time units in the elevator and 1 time unit to get off the elevator
//         if(xtarget>10 && ytarget>5)
//           {
//             x++;
//             move(tptr,x,y,z);
//           }
//         else
//           {
//             y++;
//             move(tptr,x,y,z);
//           }
//         }
//         else //Robot is already on the first floor and destination is also on first floor
//           {
//               if(xtarget>10 && ytarget>5)
//                 {
//                   x++;
//                   move(tptr,x,y,z);
//                 }
//               else
//                 {
//                   y++;
//                   move(tptr,x,y,z);
//                 }
//           }
//         }
//       else //Target floor is the second floor
//       {
//         if(z==0) //Checks if robot is currently on the first floor
//       {
//         z=1;
//         cout<<"\nRobot got on the elevator at time: "<<*tptr<<endl;
//         cout<<"\nRobot got off the elevator at time: "<<*tptr+3<<endl;
//         *tptr+=4; //3 time units in the elevator and 1 time unit to get off the elevator
//         if(xtarget<11 && ytarget<5)
//           {
//             y--;
//             move(tptr,x,y,z);
//           }
//         else
//           {
//             x--;
//             move(tptr,x,y,z);
//           }
//         }
//       else //Robot is already on the seond floor and destination is also on the second floor
//       {
//         if(xtarget<11 && ytarget<5)
//           {
//             y--;
//             move(tptr,x,y,z);
//           }
//         else
//           {
//             x--;
//             move(tptr,x,y,z);
//           }
//         }

//       }
//       *tptr+=1; //Time is incremented at each step by 1 unit
//       break; //Universal break for entire case Elevator:

//         case Fork:

//         if(*tptr%25==0) //Prints current floor map every 5 time units
//           {
//             //cout<<"Current floor map\n";
//             //Printing current floor map
//         //  printcurrent(x,y,z);
//           }
//         *tptr+=1; //Time is incremented at each step by 1 unit
//         cout<<"\nRobot has reached fork "<<fl[x][y][z].forkid<<endl;

//         switch(fl[x][y][z].forkid)
//         {
//           case 1:
//             if(xtarget==4 && ytarget==12 && ztarget==0)
//               {
//                 x++;
//                 y--;
//                 move(tptr,x,y,z); //Goes to store
//               }
//             else

//               {
//                 x--;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 2:

//             if(ytarget<6 && ztarget==0) //Destination store has y<6
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 3:
//             if(xtarget==4 && ytarget==4 && ztarget==0)
//               {
//                 x++;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 4:
//             if(!((xtarget==12 && ytarget==4 && ztarget==0)||(xtarget==12 && ytarget==12 && ztarget==0)))
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 5:
//             if(xtarget==12 && ytarget==4 && ztarget==0)
//               {
//                 x--;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 6:
//             if(xtarget==12 && ytarget==12 && ztarget==0)
//               {
//                 x--;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x--;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 7:
//             if(xtarget==4 && ytarget==6 && ztarget==0)
//               {
//                 y--;
//                 move(tptr,x,y,z); //Goes to left store
//               }
//             else if(xtarget==4 && ytarget==10 && ztarget==0)
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 8:
//             if(xtarget==12 && ytarget==6 && ztarget==0)
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else if(xtarget==12 && ytarget==10 && ztarget==0)
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 9:
//             if(xtarget==6 && ytarget==4 && ztarget==0)
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             else if(xtarget==10 && ytarget==4 && ztarget==0)
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 10:
//             if(xtarget==6 && ytarget==12 && ztarget==0)
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             else if(xtarget==10 && ytarget==12 && ztarget==0)
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 11:
//             if(xtarget==4 && ytarget==6 && ztarget==0)
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 12:
//             if(xtarget==4 && ytarget==10 && ztarget==0)
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 13:
//             if(xtarget==12 && ytarget==6 && ztarget==0)
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 14:
//             if(xtarget==12 && ytarget==10 && ztarget==0)
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 15:
//             if(xtarget==6 && ytarget==4 && ztarget==0)
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 16:
//             if(xtarget==10 && ytarget==4 && ztarget==0)
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 17:
//             if(xtarget==6 && ytarget==12 && ztarget==0)
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 18:
//             if(xtarget==10 && ytarget==12 && ztarget==0)
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 19:
//             if(xtarget==4 && ytarget==12 && ztarget==1)
//               {
//                 x++;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x++;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 20:
//             if(xtarget==4 && ytarget==4 && ztarget==1)
//               {
//                 x++;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else //floor 1 case included
//               {
//                 x--;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 21:
//             if(xtarget==12 && ytarget==4 && ztarget==1)
//               {
//                 x--;
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else //floor 1 case included
//              {
//                x--;
//                y--;
//                move(tptr,x,y,z);
//              }
//             break;

//           case 22:
//             if((xtarget==12 && ytarget==4 && ztarget==1)||(xtarget==4 && ytarget==4 && ztarget==1))
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else //floor 1 case included
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 23:
//             if(xtarget==12 && ytarget==12 && ztarget==1)
//               {
//                 x--;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else //floor 1 case included
//               {
//                 x++;
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 24:
//             if(xtarget>10 && ztarget==1)
//               {
//                 x++;
//                 move(tptr,x,y,z);
//               }
//             else //floor 1 case included
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 25:
//             if(xtarget==4 && ytarget==6 && ztarget==1)
//               {
//                 y--;
//                 move(tptr,x,y,z);
//               }
//             else if(xtarget==4 && ytarget==10 && ztarget==1)
//               {
//                 y++;
//                 move(tptr,x,y,z);
//               }
//             else
//               {
//                 x--;
//                 move(tptr,x,y,z);
//               }
//             break;

//           case 26:

//               if(xtarget==12 && ytarget==6 && ztarget==1)
//                 {
//                   y--;
//                   move(tptr,x,y,z);
//                 }
//               else if(xtarget==12 && ytarget==10 && ztarget==1)
//                 {
//                   y++;
//                   move(tptr,x,y,z);
//                 }
//               else
//                 {
//                   x--;
//                   move(tptr,x,y,z);
//                 }
//               break;

//             case 27:
//                 if(xtarget==6 && ytarget==4 && ztarget==1)
//                   {
//                     x--;
//                     move(tptr,x,y,z);
//                   }
//                 else if(xtarget==10 && ytarget==4 && ztarget==1)
//                   {
//                     x++;
//                     move(tptr,x,y,z);
//                   }
//                 else
//                   {
//                     y--;
//                     move(tptr,x,y,z);
//                   }
//                 break;

//               case 28:

//                   if(xtarget==6 && ytarget==12 && ztarget==1)
//                     {
//                       x--;
//                       move(tptr,x,y,z);
//                     }
//                   else if(xtarget==10 && ytarget==12 && ztarget==1)
//                     {
//                       x++;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       y--;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 29:
//                   if(xtarget==4 && ytarget==6 && ztarget==1)
//                     {
//                       y--;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       y++;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 30:
//                   if(xtarget==4 && ytarget==10 && ztarget==1)
//                     {
//                       y++;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       y--;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 31:
//                   if(xtarget==12 && ytarget==6 && ztarget==1)
//                     {
//                       y--;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       y++;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 32:
//                   if(xtarget==12 && ytarget==10 && ztarget==1)
//                     {
//                       y++;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       y--;
//                       move(tptr,x,y,z);
//                     }
//                   break;
//                 case 33:
//                   if(xtarget==6 && ytarget==4 && ztarget==1)
//                     {
//                       x--;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       x++;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 34:
//                   if(xtarget==10 && ytarget==4 && ztarget==1)
//                     {
//                       x++;;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       x--;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 35:
//                   if(xtarget==6 && ytarget==12 && ztarget==1)
//                     {
//                       x--;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       x++;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//                 case 36:
//                   if(xtarget==10 && ytarget==12 && ztarget==1)
//                     {
//                       x++;
//                       move(tptr,x,y,z);
//                     }
//                   else
//                     {
//                       x--;
//                       move(tptr,x,y,z);
//                     }
//                   break;

//           default: cout<<"ERROR! ERROR! ERROR!"<<endl;
//         }
//       break;

//     case Empty: cout<<"CASE EMPTY"<<endl;
//     break;

//     default: cout<<"INVALID TILE"<<endl; //for both default and Empty

//     }
 // }
}



                                                                                                                                                                                                                                                                                                                                                                                                                                                                  Stage2/Makefile                                                                                     0000771 0020221 0020221 00000000775 12417640034 013156  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 ## Start of Makefile

all:prog5_stage2

prog5_stage2: main.o eventlist.o queue.o shopper.o events.h queue.h shopper.h 
	g++ -o Prog5 main.o eventlist.o queue.o shopper.o 

main.o: main.cpp events.h queue.h shopper.h
	g++ -Wall -c main.cpp

eventlist.o: eventlist.cpp events.h
	g++ -Wall -c eventlist.cpp

queue.o: queue.cpp queue.h
	g++ -Wall -c queue.cpp

shopper.o: shopper.cpp shopper.h events.h queue.h 
	g++ -Wall -c shopper.cpp
	

clean:
	rm *.o prog5_stage2

## End of Makefile
   Stage2/events.h                                                                                     0000771 0020221 0020221 00000003500 12417622542 013164  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*header file for the event list for the shopper 
  Author:Marco Duran
  Abstracted from the Linked List header file from program 3
*/

#include <cstddef>
#include <string>

using namespace std;
#ifndef EVENTS_H
#define EVENTS_H



//creates a struct that represents a tree node

class Coordinate{
  public: int x,y,z;

};

class Store {
  public:
  Coordinate coor;
  int item_count; //count of items
};

struct eventnode //Node of linkedlist
{
  Store store; // data for the node

  struct eventnode *nextnode; //pointer to the next node
}; //end class Node

typedef struct eventnode EventNode; //alias for struct Node
typedef struct eventnode* EventNodePtr;

class EventList
{
private:

  //int get_next_node(Node* nodePtr);
  void print_list(EventNodePtr currentPtr);
  void destroy_list(EventNodePtr nextstore); //used to destroy list, called in destructor
  int search_in_list(Store str); //searches for store in list and returns 1 if found, 0 if not found
  Store getStore(EventNodePtr rootPtr, EventNodePtr currPtr);//gets the largest store in the event list and adds it to the shoppers itinerary

public:
  //Constructor
  EventList();
/*
  //Constructors with a given value of a list node
  LinkedList(Store str);
*/
  //Destructor
  ~EventList();

  //Traverse list and print each node
  void print_list();

  //adds a store to the list
  void add_list(Store str);


  void destroy_list();
  EventNode *rootPtr; //pointers to head and tail nodes
};
struct TreeNode{
  string item;//basic node that contains all the information of the student
  struct TreeNode *left;//pointer to the left side of the tree
  struct TreeNode *right;//pointer to the right side of the tree
  EventList ll; //linked list of stores associated with item

}; //ends struct of treenode

#endif
                                                                                                                                                                                                Stage2/queue.h                                                                                      0000771 0020221 0020221 00000003074 12417624035 013011  0                                                                                                    ustar   hsahay                          hsahay                                                                                                                                                                                                                 /*
Author: Marco Duran
Header file for the queue
Abstracted from Program 3
*/

#include <string>
#include <iostream>
#include <cstddef>
#include "events.h"
using namespace std;

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct queuenode QueueNode;//synonym for queuenode
typedef QueueNode *QueueNodePtr;//synonym for a *queuenode
typedef struct queuedata QueueData; //synonym for queuedata

struct queuedata{//data that is found in a node
  int process_id;
  float arrival_time;
  float rr_time;
  float fcfs_time;
  float start_time;
  float completion_time_rr;
  float completion_time_fcfs;
  Store store;
};

struct queuenode{//objects that are found in a queue
  struct queuenode *nextnode;//points to the next node
  struct queuedata data;//all the data stated above

};

class Queue{//this is a class for the queue process contains all of the functions necessary to build this data structure
public:
  Queue();//constructor
  void add_event(QueueNodePtr *qPtr,  QueueData value); //adds an event to the queue
  QueueNodePtr get_nextqueue(QueueNodePtr *qPtr); //pulls up the next node and deletes the previous one
  int isEmpty(QueueNodePtr headPtr); //checks to see if the node is empty by either returning 0 or 1
  QueueData dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);//removes a node from the queue
  void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, QueueData value);//puts a node into the queue


  QueueNodePtr *headPtr; //this is a pointer to the head or front of the queue
  QueueNodePtr *tailPtr; //this is a pointer to the tail or back of the queue
};

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
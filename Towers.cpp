//Tim Fullagar
//Towers of Hanoi
//UH REU summer 2013
//Purpose: To test that the formula provided by Paul K. Stockmeyer will give the minimum number of moves to solve a 4 node Towers of Hanoi
//puzzle with a variable number of disks. As long as the formula holds then we will start adding nodes up to 20 and see if a pattern emerges for a generalized Towers of Hanoi
//puzzle with a variable number of nodes above 4.

#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

const int SOURCE = 0;
const int DESTINATION = 3;

//Function:    Orig
//Precondition:  Requires "disks" to be defined and filled, requires "nodes" to be defined and 
//				 filled, and requires "orig" to be defined
//Postcondition: Splits the incoming "disks" variable at the optimized value, sends the split off
//				 to a nother function for solving with recursion, then takes the other part and 
//				 uses the 2^n-1 formula to solve it. Finally it adds the result from the recursion
//				 function to the result from the 2^n-1 formula twice to account for the initial 
//				 split, and putting it back
//Returns:	 	 Returns the minimum number of moves to solve a 4 peg puzzle with n disks according
//				 to Paul K. Stockmeyer
double Orig(int disks, int nodes[]);

//Function: 	 Recursion
//Precondition:  Requires all variables to be declared and initialized
//Postcondition: Recieves the "split" potion of the stack for solving using all 4 pegs, records the 
//				 number of moves for use later, uses the vector for the intermediate pegs
//Returns:	 	 The minimum number of moves to solve a 4 peg puzzle using recursion
double Recursion(int nodes[], double moves, int split, int source, int dest, vector <int>& free_peg);

//Function:	 	 Top_disk
//Precondition:  Requires "nodes" to be declared and filled
//Postcondition: Takes one disk from nodes[0] and moves it to nodes[3]
//Returns: 		 None
void Top_disk(int nodes[], int source, int dest);

int main()
{
	int disks;
	int counter = 1;
	double orig; 
	ofstream outfile;
	outfile.open("results.txt");
		
	cout << "Welcome to the Towers of Hanoi caluculation program.\n";
	cout << "You will be asked to provide a number of disks, then the program will calculate the\n"; 
	cout <<	" number of moves required to solve a 4 node puzzle with that number of disks using\n";
	cout << " the split formulation provided by Paul K. Stockmeyer and print the results to the\n";
	cout << " screen and a file.\n"; 
	cout << endl;
	
	cout << "Please enter a number greater than 0 of disks you wish to use as an integer.\n";
	cin >> disks;
	
	//While the input for "disks" is not greater than 0, ask the user to re-enter the value
	while(disks <= 0)
	{
		cout << "Please enter an integer that is greater than 0.\n";
		cin >> disks;
	}
	
	//Declaring an array for the nodes then putting the input number in node 0 
	int nodes[4] = {0};
	nodes[SOURCE] = disks;
	
	orig = Orig(disks, nodes);
		
	cout << "The number of moves for " << disks << " disks using the presumed optimal split is ";
	cout << "approximately: " << setprecision(5) << orig << endl;
	outfile << "The number of moves for " << disks << " disks using the presumed optimal split is ";
	outfile << "approximately: " << setprecision(5) << orig << endl;
		
	outfile.close();
	return 0;
}

double Orig(int disks, int nodes[])
{
	int split1 = sqrt(2*(disks));
	int other1 = disks - split1;
	double moves = 0.00;
	vector<int> free_peg(2);
	double result1, result2, result3, totres = 0.00;
	
	//***This needs to change, do something with recursion here***
	result1 = /*pow(2.00, sqrt(2*(split1)))*(sqrt(split1) -1) + 1;*/ Recursion(nodes, moves, split1, SOURCE, DESTINATION, free_peg);
	
	//This part should be ok
	result2 = pow(2.00, other1) - 1;
	
	//For testing
	result3 = pow(2.00, sqrt(2*(disks)))*(sqrt(disks) -1) + 1;
	cout << endl << result3 << endl;
	
	totres = 2*(result1) + result2;
	
	return totres;
}


 double Recursion(int nodes[], double moves, int split, int source, int dest, vector<int>& free_peg)
     {
         int p, middle;
 
         if (split == 1)
         {
             moves++;
             //Move to top disk from the source to the destination
             Top_disk(nodes, source, dest);
         }
 
         else
         {
             moves++;
 
             if(free_peg.size() >= 2)
                 p = split/2;
             else
                 p = split - 1;
 
             //Move top "p" disks from peg 1 to peg i
             middle = free_peg.back();
             free_peg.pop_back();
             free_peg.push_back(dest);
             Recursion(nodes, moves, p, source, middle, free_peg);
 
             //Move "n - p " disks from peg 1 to another peg
             free_peg.pop_back();
             Recursion(nodes, moves, split - p, source, dest, free_peg);
 
             //Move p from current peg to the final peg
             free_peg.push_back(source);
             Recursion(nodes, moves, p, middle, dest, free_peg);
         }
		return moves;
     }

     void Top_disk(int nodes[], int source, int dest)
     {
     	nodes[source] - 1;
     	nodes[dest] + 1;
     }

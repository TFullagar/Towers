//Tim Fullagar
//Towers of Hanoi
//UH REU summer 2013
//Purpose: To test that the formula provided by Paul K. Stockmeyer will give the minimum number of 
//  	   moves to solve a 4 node Towers of Hanoi puzzle with a variable number of disks. As long
//		   as the formula holds then we will start adding nodes up to 20 and see if a pattern emerges
//		   for a generalized Towers of Hanoi puzzle with a variable number of nodes above 4.

#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>
using namespace std;

//Function: 	 Orig
//Precondition:  Requires "disks" to be defined and filled, requires "m4" to be defined,
//				 and requires "orig" to be defined
//Postcondition: Splits the incoming "disks" variable at the optimized value, sends the split 
//				 off to another function for solving with recursion, then takes the other part
//				 and uses the 2^n-1 formula to solve it. Finally it adds the result from the recursion
//				 function to the result from the 2^n-1 formula twice to account for the initial split,
//				 and putting it back
//Returns:	 	 Returns the minimum number of moves to solve a 4 peg puzzle with n disks according to
//				 Paul K. Stockmeyer
double Orig(int disks, int m4[], bool ansm4[], ofstream &outfile);

//Function: 	 Recursion
//Precondition:  Requires all variables to be declared and initialized
//Postcondition: Recieves the "split" potion of the stack for solving using all 4 pegs with the formula
//				 provided by Paul K. Stockmeyer, records the number of moves for use later
//Returns:	 	 The minimum number of moves to solve a 4 peg puzzle using recursion
double Split(int m4[], int split1, double split, bool ansm4[]);

int main()
{
	int disks;
	int counter = 1;
	double orig; 
	ofstream outfile;
	outfile.open("results.txt");
		
	cout << "Welcome to the Towers of Hanoi caluculation program.\n";
	cout << "You will be asked to provide a number of disks, then the program will calculate the";
	cout << " number of moves required to solve a 4 node puzzle with that number of disks using";
	cout << " the formula provided by Paul K. Stockmeyer and print the results to the screen and";
	cout << " a file.\n"; 
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
	int m4[disks];

	//Declaring a boolean array pf 100000 so every block can be initialized to false
	bool ansm4[100000] = {false};
		
	orig = Orig(disks, m4, ansm4, outfile);
		
	cout << "The number of moves for " << disks << " disks using the presumed optimal split is ";
	cout << "approximately: " << setprecision(5) << orig << endl;
	outfile << "The number of moves for " << disks << " disks using the presumed optimal split is ";
	outfile << "approximately: " << setprecision(5) << orig << endl;
	
	outfile.close();
	return 0;
}

double Orig(int disks, int m4[], bool ansm4[], ofstream &outfile)
{
	int split1;
	double split = sqrt(2*(disks));
	int other1;
	double result1, result2, result3, totres = 0.00;

	//For rounding purposes
	split1 = (split*10.0 + .5)/10.0;
	other1 = disks - split1;

	//cout << endl << split << endl;

	if(!ansm4[split1-1])
	{
		//Getting the result for the split using all 4 pegs
		result1 = Split(m4, split1, split, ansm4);
	}
	else
		result1 = m4[split1-1];
	
	//Getting the result for the rest using 3 pegs
	result2 = pow(2.00, other1) - 1;
	
	//For testing
	result3 = pow(2.00, sqrt(2*(disks)))*(sqrt(disks) -1) + 1;
	cout << endl << result3 << endl;

	//Checking results
	outfile << "Result 3: " << result3 << endl;
	cout << endl << result1 << endl;
	outfile << endl << "Result 1: " << result1 << endl;
	cout << endl << result2 << endl;
	outfile << endl << "Result 2: " << result2 << endl;
	
	//Getting the total result by add the first result to the second result twice
	totres = 2.0*(result1) + result2;
	
	return totres;
}

 double Split(int m4[],int split1, double split, bool ansm4[])
     {
         double moves;
         m4[split1-1] = pow(2.00, sqrt(2*(split)))*(sqrt(split)-1)+1;
         moves = m4[split1-1];
         ansm4[split1-1] = true;

         return moves;
     }

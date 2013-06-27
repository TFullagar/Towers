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
#include<climits>
using namespace std;

//Function: 	 Orig
//Precondition:  Requires "disks" to be defined and filled, requires "m4" to be declared,
//				 and requires "orig" to be declared
//Postcondition: If the number of disks is 4 or less the function uses 2(n)-1 to fill the array, 
//				 if not it calls Towers to use an optimal spliting method, updates a boolean value
//				 to determine which print statement is used in main()
//Returns:	 	 Returns the minimum number of moves to solve a 4 peg puzzle with n disks according to
//				 Paul K. Stockmeyer
int Orig(int disks, bool &ppart);

//Function:		 Towers
//Precondition:  Requires "disks" to be declared and initialized and requires "m4[]" to be declared 
//Postcondition: Splits the stack of disks at every value and tests to see whush split gives the 
//				 lowest value and then places that value in an array
//Returns:		 NONE
void Towers(int disks, int m4[], int counter);

int main()
{
	bool ppart = false;
	int disks;
	int orig; 
	double optimal;
	ofstream outfile;
	outfile.open("results.txt");
		
	cout << "Welcome to the Towers of Hanoi caluculation program.\n";
	cout << "You will be asked to provide a number of disks, then the program will calculate the";
	cout << " number of moves required to solve a 4 node puzzle with that number of disks and";
	cout << " compairing to the result given bythe formula provided by Paul K. Stockmeyer,";
	cout << " and print the results to the screen and a file.\n"; 
	cout << endl;
	
	cout << "Please enter a number greater than 0 of disks you wish to use as an integer.\n";
	cin >> disks;
	
	//While the input for "disks" is not greater than 0, ask the user to re-enter the value
	while(disks <= 0)
	{
		cout << "Please enter an integer that is greater than 0.\n";
		cin >> disks;
	}
	
	orig = Orig(disks, ppart);
	optimal = pow(2.00, sqrt(2*(disks)))*(sqrt(disks) -1) + 1;
		
	if(!ppart)
	{	
		cout << "The number of moves for " << disks << " disks using a spliting method is ";
		cout << "\napproximately: " << orig << endl;
		cout << "For comparison, the presumed optimal split formula given by Paul K. Stockmeyer ";
		cout << "gives: " << optimal << endl;
		outfile << "The number of moves for " << disks << " disks using a spliting method is ";
		outfile << "\napproximately: " << orig << endl;
		outfile << "For comparison, the presumed optimal split formula given by Paul K. Stockmeyer ";
		outfile << "gives: " << optimal << endl;
	}
	else
	{
		cout << "The number of moves for " << disks << " disks, which is less than or equal to the number ";
		cout << "\nof pegs is: " << orig << endl;
		cout << "For comparison, the presumed optimal split formula given by Paul K. Stockmeyer ";
		cout << "\ngives: " << optimal << endl;
		outfile << "The number of moves for " << disks << " disks, which is less than or equal to the number ";
		outfile << "\nof pegs is: " << orig << endl;
		outfile << "For comparison, the presumed optimal split formula given by Paul K. Stockmeyer ";
		outfile << "\ngives: " << optimal << endl;
	}
	
	outfile.close();
	return 0;
}

int Orig(int disks, bool &ppart)
{
	//Declaring an array for the disks of a definate size and initilizing to 0
	int m4[101] = {0};
	int totres;
	
	if(disks <= 4)
	{
		for(int x = 0; x < disks; x++)
		{
			m4[x] = 2*(x+1)-1;
		}
		//Using for testing*********************
		cout << "The array is: ";
		for (int g = 0; g < disks; g++)
		{
			cout<<m4[g]<<" ";
		}
		cout<<endl;
		//*************************************
		ppart = true;
	}

	else
	{
		for(int i = 0; i < disks; i++)
			Towers(disks, m4, i);

		//Using for testing*********************
		cout << "The array is: ";
		for (int y = 0; y < disks; y++)
		{
			cout<<m4[y]<<" ";
		}
		cout<<endl;
		//*************************************
		ppart = false;
	}
	return totres = m4[disks - 1];
}


void Towers(int disks, int m4[], int counter)
{
	int split;
   	int split_res;
   	int remaining;
 	int remaining_res;
 	int result;
 	int smallest_so_far = INT_MAX;

	//Setting up the first 4 positions in the array
	if(counter == 0)
		m4[counter] = 1;
	if(counter == 1)
		m4[counter] = 3;
	if(counter == 2)
		m4[counter] = 5;
	if(counter == 3)
		m4[counter] = 7;

	//If the above fo loop is at greater than 3
	if(counter > 3)
	{
		for(int j = 4; j <= counter; j++)
		{
			split = 1;
			for(int a = 0; a <= counter; a++)
			{
				if(split < counter)
				{
					remaining = (counter+1) - split;
					split_res = m4[split - 1];

					remaining_res = pow(2.00, remaining) - 1;
					result = 2*(split_res) + remaining_res;

					//Only update "smallest_so_far" if "result" is lower
					if(result <= smallest_so_far)
						smallest_so_far = result;
					//**********FOR TESTING*************
					//cout << endl << smallest_so_far << endl;
					//**********************************
					//Updating "Split"
					split++;
				}
			}
		}
		//Setting the array at counter to "smallest_so_far"
		m4[counter] = smallest_so_far;
	}

}

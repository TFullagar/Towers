//Tim Fullagar
//Towers of Hanoi
//UH REU summer 2013
//Purpose: To test that the formula provided by Paul K. Stockmeyer will give the minimum number of 
//  	   moves to solve a 4 node Towers of Hanoi puzzle with a variable number of disks. As long
//		   as the formula holds then we will start adding nodes up to 20 and see if a pattern emerges
//		   for a generalized Towers of Hanoi puzzle with a variable number of nodes above 4.

//#include <cstring>
#include <iostream>
#include <cmath>
#include <fstream>
#include <climits>
//#include<cctype>
using namespace std;

//Function: 	 Orig
//Precondition:  Requires "disks" to be defined and filled, "arr1[]" and "arr2[]" to be declared,
//				 "pegs" to be declacred and initialized, "ppart" to be declared and initialized, 
//				 and "orig" to be declared
//Postcondition: If the number of disks is 4 or less the function uses 2(n)-1 to fill both arrays, 
//				 if not it calls Towers to use an optimal spliting method, updates a boolean value
//				 to determine which print statement is used in main() and uses the streams to print
//				 to 2 different files
//Returns:	 	 Returns the minimum number of moves to solve the puzzle with n disks
int Orig(int disks, int arr1[], int arr2[], int pegs, bool &ppart, ofstream &fout, ofstream &outfile);

//Function:		 Towers_sm
//Precondition:  Requires "disks" to be declared and initialized, "arr1[]" and "arr2[]" to be 
//				 declared, and "counter" from Orig() to be declared and initialized
//Postcondition: Splits the stack of disks at every value and tests to see which split gives the 
//				 lowest value and then places that value in an array
//Returns:		 NONE
void Towers_sm(int disks, int arr1[], int arr2[], int counter, int pegs);

//Function:		 Towers_lg
//Precondition:  Requires "disks", "pegs", and "ppart" to be declared and filled, requires "arr1[]" 
//				 and "arr2[]" to be declred and recieves the infile, outfile, and fout streams
//Postcondition: The function determines if the program is on an even iteration and uses that info
//				 to determine whih array to fill. If the number of disks is less than or equal to 
//				 the number of pegs the function uses 2(n)-1 to fill both arrays, if not the function
//				 fills arr1[] with the last inforation written by the "fout" stream and uses that 
//				 array to fill arr2[], which is then written to a file for later use
//Returns:		 Returns the minimum number of moves to solve the puzzle with n disks
int Towers_lg(int disks, int pegs, int arr1[], int arr2[], bool &ppart, ifstream &infile, ofstream & outfile, ofstream &fout);

int main()
{
	int count;
	bool ppart = false;
	int disks;
	int pegs;
	int orig; 
	int m;
	int n;
	int diskssofar;
	char yesno = 'Y';
	ofstream outfile;
	ifstream infile;
	ofstream fout;
	fout.open("array.txt");
	infile.open("array.txt");
	outfile.open("results.txt");
		
	cout << "Welcome to the Towers of Hanoi caluculation program.\n";
	cout << "You will be asked to provide a number of disks and pegs, then the program will then";
	cout << " calculate the number of moves required to solve a puzzle with that number of disks";
	cout << " for 4 pegs, then 5 pegs and so on up to the number of pegs entered. The program will";
	cout << " print the results to the screen and a file.";
	cout << endl;

	while(yesno == 'Y' || yesno == 'y')
	{
		//Initializing here so count and disks so far will reset when doing the program again
		count = 4;
		diskssofar = 1;

		cout << "Please enter an integer greater than 0 for the disks you wish to use.\n";
		cin >> disks;

		cout << "Please enter an integer 4 or greater for the nuber of pegs you wish to use .\n";
		cin >> pegs;

		//Using to check that the input values are indeed integers
		n = (10*disks)%10;
		m = (10*pegs)%10;
		
		//While the input for "disks" is not greater than 0 and is not an integer, ask the user to 
		//re-enter the value
		while(disks < 0 && n != 0)
		{
			cout << "Please enter an integer that is greater than 0.\n";
			cin >> disks;
		}

		//Declaring the arrays of size "disks"
		int arr1[disks];
		int arr2[disks];

		//While the input for "pegs" is not greater than 3 and is not an integer, ask the user re-enter
		//the value.
		while(pegs < 4 && m != 0)
		{
			cout << "Please enter an integer that is equal to or greater than 4.\n";
			cin >> pegs;
		}

		// //Setting the array's to 0
		// memset(arr1, 0, disks);
		// memset(arr2, 0, disks);

		while(diskssofar <= disks)
		{
			if(count <= 5)
				orig = Orig(disks, arr1, arr2, count, ppart, fout, outfile);

			else if(count > 5 && count <= pegs)
				orig = Towers_lg(disks, count, arr1, arr2, ppart, infile, outfile, fout);
							
			if(!ppart && count <= pegs)
			{	
				cout << "The number of moves for " << disks << " disks and " << count << " pegs using";
				cout << " \na spliting method is approximately: " << orig << endl << endl;
				outfile << "The number of moves for " << disks << " disks and " << count << " pegs using";
				outfile << " \na spliting method is approximately: " << orig << endl << endl;
			}
			else if (ppart && count <= pegs)
			{
				cout << "The number of moves for " << disks << " disks and " << count << " pegs, in which ";
				cout << "\nthe number of disks in equal to or less than the number of pegs is: " << orig << endl;
				cout << endl;
				outfile << "The number of moves for " << disks << " disks and " << count << " pegs, in which ";
				outfile << "\nthe number of disks in equal to or less than the number of pegs is: " << orig << endl;
				outfile << endl;
			}
			count++;
			diskssofar++;
		}
		//Asking the user if they would like to use the program again
		cout << "Would you like to go again? Please enter 'y' or 'Y' for yes and 'n' or 'N' for \nno." << endl;
		cin >> yesno;

		while(yesno != 'Y' && yesno != 'y' && yesno != 'N' && yesno != 'n')
		{
			cout << "Please enter 'y or 'Y' for yes and 'n' or 'N' for no." << endl;
			cin >> yesno;
		}
	}
	fout.close();
	infile.close();
	outfile.close();
	return 0;
}

int Orig(int disks, int arr1[], int arr2[], int pegs,  bool &ppart, ofstream &fout, ofstream &outfile)
{
	int totres;
		
	if(disks < 4)
	{
		for(int x = 0; x < disks; x++)
		{
			arr1[x] = 2*(x+1)-1;
			arr2[x] = 2*(x+1)-1;
		}
		
		cout << "The array is: ";
		outfile << "The array is: ";
		if(pegs == 4)
		{
			for (int g = 0; g < disks; g++)
			{
				cout << arr1[g] << " ";
				outfile << arr1[g] << " ";
			}
			cout << endl;
			outfile << endl;
		}
		else
		{
			for (int g = 0; g < disks; g++)
			{
				cout << arr2[g] << " ";
				outfile << arr2[g] << " ";
				fout << arr2[g] << " ";
			}
			cout << endl;
			outfile << endl;
		}
		ppart = true;
		fout.clear();
		fout.seekp(0);
	}

	else
	{
		for(int i = 0; i < disks; i++)
			Towers_sm(disks, arr1, arr2, i, pegs);
		
		cout << "The array is: ";
		outfile << "The array is: ";
		if(pegs == 4)
		{
			for (int y = 0; y < disks; y++)
			{
				cout << arr1[y] << " ";
				outfile << arr1[y] << " ";
			}
			cout << endl;
			outfile << endl;
		}
		else
		{
			for (int y = 0; y < disks; y++)
			{
				cout << arr2[y] << " ";
				outfile << arr2[y] << " ";
				fout << arr2[y] << " ";
			}
			cout << endl;
			outfile << endl;
		}
		ppart = false;
		fout.clear();
		fout.seekp(0);
	}

	if(pegs == 4)
		return totres = arr1[disks - 1];
	else
		return totres = arr2[disks - 1];

}

void Towers_sm(int disks, int arr1[], int arr2[], int counter, int pegs)
{
	int split;
   	int split_res;
   	int remaining;
 	int remaining_res;
 	int result;
 	int smallest_so_far = INT_MAX;

 	if(pegs == 4)
 	{
	 	//Setting up the first 4 positions in the array
		if(counter == 0)
			arr1[counter] = 1;
		if(counter == 1)
			arr1[counter] = 3;
		if(counter == 2)
			arr1[counter] = 5;
		if(counter == 3)
			arr1[counter] = 7;

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
						split_res = arr1[split - 1];

						remaining_res = pow(2.00, remaining) - 1;
						result = 2*(split_res) + remaining_res;

						//Only update "smallest_so_far" if "result" is lower
						if(result <= smallest_so_far)
							smallest_so_far = result;
					}
					//Updating "split"
					split++;
				}
			}
			//Setting the array at counter to "smallest_so_far"
			arr1[counter] = smallest_so_far;
		}
	}

	else 
	{
		//Setting up the first 4 positions in the array
		if(counter == 0)
			arr2[counter] = 1;
		if(counter == 1)
			arr2[counter] = 3;
		if(counter == 2)
			arr2[counter] = 5;
		if(counter == 3)
			arr2[counter] = 7;
		if(counter == 4)
			arr2[counter] = 9;

		//If the above for loop is at greater than 3
		if(counter > 4)
		{
			for(int j = 5; j <= counter; j++)
			{
				split = 1;
				for(int a = 0; a <= counter; a++)
				{
					if(split < counter)
					{
						remaining = (counter+1) - split;
						split_res = arr2[split - 1];

						remaining_res = arr1[remaining];
						result = 2*(split_res) + remaining_res;

						//Only update "smallest_so_far" if "result" is lower
						if(result <= smallest_so_far)
							smallest_so_far = result;
					}
					//Updating "split"
					split++;
				}
			}
			//Setting the array at counter to "smallest_so_far"
			arr2[counter] = smallest_so_far;
		}
	}

}

int Towers_lg(int disks, int pegs, int arr1[], int arr2[], bool &ppart, ifstream &infile, ofstream & outfile, ofstream &fout)
{
	int even = pegs%2;
	int totres;
	int split;
   	int split_res;
   	int remaining;
 	int remaining_res;
 	int result;
 	int smallest_so_far = INT_MAX;
 	int count1 = 0;
 	int disks1 = 1;

	//Setting in reading stream cursor back to the beginning
	infile.clear();
	infile.seekg(0);

	//If the number of disks is equal to or less than the number of pegs, then calculate based on 2n-1
	if(disks < pegs)
	{
		for(int x = 0; x < disks; x++)
		{
			arr1[x] = 2*(x+1)-1;
			arr2[x] = 2*(x+1)-1;
		}
		
		cout << "The array is: ";
		outfile << "The array is: ";
		if(even == 0)
		{
			for (int g = 0; g < disks; g++)
			{
				cout << arr1[g] << " ";
				outfile << arr1[g] << " ";
				fout << arr1[g] << " ";
			}
			cout << endl;
			fout << endl;
			//Setting the writting stream cursor back to the beginning
			fout.clear();
			fout.seekp(0);
			//Making sure the reading stream is at the beginning of the file
			infile.clear();
			infile.seekg(0);
		}
		else
		{
			for (int r = 0; r < disks; r++)
			{
				cout << arr2[r] << " ";
				outfile << arr2[r] << " ";
				fout << arr2[r] << " ";
			}
			cout << endl;
			fout << endl;
			//Setting the writting stream cursor back to the beginning
			fout.clear();
			fout.seekp(0);
			//Making sure the reading stream is at the beginning of the file
			infile.clear();
			infile.seekg(0);
		}
		ppart = true;
	}
	else
	{
		while(!infile.eof())
		{
			for(int z = 0; z < disks; z++)
			{
				infile >> arr1[z];
			}
		}
		//Resetting the reading cursor back to the beginning
		infile.clear();
		infile.seekg(0);

		//Setting the first position in the next array
		arr2[0] = 1;
		
		for(int j = 0; j <= pegs; j++)
		{
			split = pegs - (pegs - 1);
			if(disks1 <= pegs)
			{
				arr2[j] = 2*(j+1)-1;
			}
			else
			{
				for(int a = 0; a <= count1; a++)
				{
					
					if(split <= pegs)
					{
						remaining = pegs - split;
						split_res = arr2[split - 1];

						remaining_res = arr1[remaining];
						result = 2*(split_res) + remaining_res;

						//Only update "smallest_so_far" if "result" is lower
						if(result <= smallest_so_far)
							smallest_so_far = result;

						//Setting the array at counter to "smallest_so_far"
						arr2[pegs] = smallest_so_far;
					}
					//Updating "split"
					split++;
				}
				//Updating "count1"
				count1++;
			}
			//Updating "disks1"
			disks1++;
		}
		
		cout << "The array is: ";
		outfile << "The array is: ";
		for (int g = 0; g < disks; g++)
		{
			cout << arr2[g] << " ";
			outfile << arr2[g] << " ";
			fout << arr2[g] << " ";
		}
		cout << endl;
		fout << endl;
		//Setting the writting stream cursor back to the beginning
		fout.clear();
		fout.seekp(0);
		//Making sure the reading stream is at the beginning of the file
		infile.clear();
		infile.seekg(0);
		
		ppart = false;
	}
	return totres = arr2[disks - 1];
}

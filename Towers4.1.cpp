//Tim Fullagar
//Towers of Hanoi
//UH REU summer 2013
//Purpose: To test that the formula provided by Paul K. Stockmeyer will give the minimum number of 
//  	   moves to solve a 4 node Towers of Hanoi puzzle with a variable number of disks. As long
//		   as the formula holds then we will start adding nodes up to 20 and see if a pattern emerges
//		   for a generalized Towers of Hanoi puzzle with a variable number of nodes above 4.

#include <iostream>
#include <cmath>
#include <fstream>
#include <climits>
using namespace std;

//Function:		 Towers_3peg
//Precondition:	 Requires "disks" and "count" to be declared and initialized and arr1[] to be declared
//Postcondition: Takes the amount of disks input by the user and calculates the minimum number of 
//				 moves using the known 2^n-1 formula for 3 pegs
//Returns:		 NONE
void Towers_3peg(int disks, int arr1[], int count, ofstream &outfile);

//Function:		 Towers_sm
//Precondition:  Requires "disks", "count", and "ppart" to be declared and initialized, "arr1[]" 
//				 and "arr2[]" to be declared and both the "fout" and "outfile" streams declared				 
//Postcondition: Splits the stack of disks at every value and tests to see which split gives the 
//				 lowest value and then places that value in an array
//Returns:		 Returns the minimum number of moves to solve the puzzle with n disks for 4
int Towers_sm(int disks, int arr1[], int arr2[], int count, bool &ppart, ofstream &fout, ofstream &outfile);

//Function:		 Towers_lg
//Precondition:  Requires "disks", "count", and "ppart" to be declared and filled, requires "arr2[]" 
//				 and "arr3[]" to be declred and recieves the infile, outfile, and fout streams
//Postcondition: The function determines if the program is on an even iteration and uses that info
//				 to determine whih array to fill. If the number of disks is less than or equal to 
//				 the number of pegs the function uses 2(n)-1 to fill both arrays, if not the function
//				 fills arr2[] with the last inforation written by the "fout" stream and uses that 
//				 array to fill arr3[], which is then written to a file for later use
//Returns:		 Returns the minimum number of moves to solve the puzzle with n disks for more than 4 pegs
int Towers_lg(int disks, int count, int arr2[], int arr3[], bool &ppart, ifstream &infile, ofstream & outfile, ofstream &fout);

int main()
{
	int count;
	bool ppart = false;
	int disks;
	int pegs;
	int orig; 
	int m;
	int n;
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
		count = 3;
		
		cout << "Please enter an integer greater than 0 for the disks you wish to use.\n";
		cin >> disks;

		cout << "Please enter an integer 3 or greater for the nuber of pegs you wish to use .\n";
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
		int arr3[disks];

		//While the input for "pegs" is not greater than 3 and is not an integer, ask the user re-enter
		//the value.
		while(pegs < 3 && m != 0)
		{
			cout << "Please enter an integer that is equal to or greater than 3.\n";
			cin >> pegs;
		}

		if(count == 3)
			Towers_3peg(disks, arr1, count, outfile);

		while(count <= pegs)
		{
			
			if(count == 4)
				orig = Towers_sm(disks, arr1, arr2, count, ppart, fout, outfile);

			else 
				orig = Towers_lg(disks, count, arr2, arr3, ppart, infile, outfile, fout);
							
			if(!ppart)
			{	
				cout << "The number of moves for " << disks << " disks and " << count << " pegs using";
				cout << " \na spliting method is approximately: " << orig << endl << endl;
				outfile << "The number of moves for " << disks << " disks and " << count << " pegs using";
				outfile << " \na spliting method is approximately: " << orig << endl << endl;
			}
			else 
			{
				cout << "The number of moves for " << disks << " disks and " << count << " pegs, in which ";
				cout << "\nthe number of disks in equal to or less than the number of pegs is: " << orig << endl;
				cout << endl;
				outfile << "The number of moves for " << disks << " disks and " << count << " pegs, in which ";
				outfile << "\nthe number of disks is less than the number of pegs is: " << orig << endl;
				outfile << endl;
			}
			count++;
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

void Towers_3peg(int disks, int arr1[], int count, ofstream &outfile)
{
	int diskssofar;
	int result;

	for(diskssofar = 1; diskssofar < count; diskssofar++)
 		arr1[diskssofar - 1] = 2*(diskssofar) - 1;

 	if(diskssofar >= count)
 	{
 		for(int h = diskssofar; h <= disks; h++)
 			arr1[h-1] = pow(2.00, diskssofar) - 1;
 	}

 	cout << "The array for 3 pegs and " << disks << " disks is: ";
	outfile << "The array for 3 pegs and " << disks << " disks is: ";
 	for (int t = 0; t < disks; t++)
 	{
		cout << arr1[t] << " ";
		outfile << arr1[t] << " ";
	}
	cout << endl;
	cout << endl;
	outfile << endl;
	outfile << endl;

}

int Towers_sm(int disks, int arr1[], int arr2[], int count, bool &ppart, ofstream &fout, ofstream &outfile)
{
	int split;
   	int split_res;
   	int remaining;
 	int remaining_res;
 	int result;
 	int diskssofar;
 	int smallest_so_far;

	for(diskssofar = 1; diskssofar < count; diskssofar++)
	{
		arr2[diskssofar - 1] = 2*(diskssofar) - 1;
		ppart = true;
	}
		
 	if(diskssofar >= count)
 	{
 		for(int a = diskssofar; a <= disks; a++)
		{
			//Resetting "smallest_so_far"
			smallest_so_far = INT_MAX;

			for(split = 1; split < diskssofar; split++)
			{
				remaining = diskssofar - split;
				split_res = arr2[split - 1];

				remaining_res = arr1[remaining - 1];
				result = 2*(split_res) + remaining_res;

				//Only update "smallest_so_far" if "result" is lower
				if(result <= smallest_so_far)
					smallest_so_far = result;
			}
			//Setting the used array to "smallest_so_far"
			arr1[a-1] = smallest_so_far;
			ppart = false;
		}
 	}

 	cout << "The array is: ";
	outfile << "The array is: ";
 	for (int g = 0; g < disks; g++)
 	{
		cout << arr2[g] << " ";
		fout << arr2[g] << " ";
		outfile << arr2[g] << " ";
	}
	cout << endl;
	outfile << endl;

	//Setting the writting stream cursor back to the beginning
	fout.clear();
	fout.seekp(0);

	return arr2[disks - 1];
}

int Towers_lg(int disks, int count, int arr2[], int arr3[], bool &ppart, ifstream &infile, ofstream & outfile, ofstream &fout)
{
	int even = count%2;
	int totres;
	int split;
   	int split_res;
   	int remaining;
 	int remaining_res;
 	int result;
 	int smallest_so_far;
 	int disks1;

	//Setting in reading stream cursor back to the beginning
	infile.clear();
	infile.seekg(0);


	for(disks1 = 1; disks1 < count; disks1++)
 	{
 		arr2[disks1 - 1] = 2*(disks1) - 1;
 		arr3[disks1 - 1] = 2*(disks1) - 1;
 	}

	//If the number of disks is equal to or less than the number of pegs, then calculate based on 2n-1
	if(disks < count)
	{
		cout << "The array is: ";
		outfile << "The array is: ";
		if(even == 0)
		{
			for (int g = 0; g < disks; g++)
			{
				cout << arr2[g] << " ";
				outfile << arr2[g] << " ";
				fout << arr2[g] << " ";
			}
			cout << endl;
			outfile << endl;
			//Setting the writting stream cursor back to the beginning
			fout.clear();
			fout.seekp(0);
			//Making sure the reading stream is at the beginning of the file
			infile.clear();
			infile.seekg(0);

			ppart = true;
			return totres = arr2[disks - 1];
		}
		else
		{
			cout << "The array is: ";
			outfile << "The array is: ";
			for (int r = 0; r < disks; r++)
			{
				cout << arr3[r] << " ";
				outfile << arr3[r] << " ";
				fout << arr3[r] << " ";
			}
			cout << endl;
			outfile << endl;

			//Setting the writting stream cursor back to the beginning
			fout.clear();
			fout.seekp(0);

			//Making sure the reading stream is at the beginning of the file
			infile.clear();
			infile.seekg(0);

			ppart = true;
			return totres = arr3[disks - 1];
		}
	}
	else
	{
		while(!infile.eof())
		{
			for(int z = 0; z < disks; z++)
			{
				infile >> arr2[z];
			}
		}
		//Resetting the reading cursor back to the beginning
		infile.clear();
		infile.seekg(0);

		//Setting the first position in the next array
		arr3[0] = 1;
		
		for(int j = 4; j <= count; j++)
		{
			//Resetting "smallest_so_far"
			smallest_so_far = INT_MAX;

			for(split = 1; split < disks1; split++)
			{
				remaining = disks1 - split;
				split_res = arr3[split - 1];

				remaining_res = arr3[remaining - 1];
				result = 2*(split_res) + remaining_res;

				//Only update "smallest_so_far" if "result" is lower
				if(result <= smallest_so_far)
					smallest_so_far = result;
			}
			//Setting the used array to "smallest_so_far"
			arr2[j - 1] = smallest_so_far;
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
		outfile << endl;

		//Setting the writting stream cursor back to the beginning
		fout.clear();
		fout.seekp(0);

		//Making sure the reading stream is at the beginning of the file
		infile.clear();
		infile.seekg(0);
		
		ppart = false;
	}
	return totres = arr3[disks - 1];
}

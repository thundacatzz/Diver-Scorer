#include <iostream>
#include <fstream>
#include <iomanip>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;
// This program was written to take properly formatted input of divers' names and judges' ratings from a dive meet, regurgitate it all in a neat, sorted format, calculate the scores
// and declare the winner.
// Written by Logan Skura 9/21/2022

// This struct carries all of the properties of the divers.
struct divers
{
	string name = "";
	double difficulty = 0;
	double ratings[9] = { 0 };
};

// These are the i/o file variables and the function prototypes within the program.
ifstream diverData;
ofstream outputFile;
void OpenInputFile();
void OpenOutputFile();
double CalculatePoints(double sum, divers diver);
void DeclareWinner(string winner, double highScore);

int main()
{
	OpenInputFile();
	OpenOutputFile();
	
	// These are some variables that come into use later on in the main function. An instance of the struct is also defined here. The first integer is also pulled from
	// the input file as it indicates the number of divers within the file.
	int numDivers = 0;
	diverData >> numDivers;
	divers diver;
	string winner = "";
	double highScore = 0;
	
	// These 3 lines do some formatting and set up the columns for the divers' data later on.
	cout.setf(ios::fixed);
	cout << "NAME" << setw(19) << "DIFFICULTY" << setw(41) << "SORTED SCORES" << setw(38) << "POINTS" << endl;
	outputFile << "NAME" << setw(19) << "DIFFICULTY" << setw(25) << "SORTED SCORES" << setw(22) << "POINTS" << endl;
	
	// This for loop iterates through according to the number of divers given by the first integer in the file.
	for (int i = 0; i < numDivers; i++)
	{
		// Here the file stream is used to assign values to the different properties of the struct.
		diverData >> diver.name >> diver.difficulty >> diver.ratings[0] >> diver.ratings[1] >> diver.ratings[2] >> diver.ratings[3] >> diver.ratings[4] >> diver.ratings[5]
			>> diver.ratings[6] >> diver.ratings[7] >> diver.ratings[8];
		
		// This function sorts the judges' ratings of the divers in ascending order.
		sort(diver.ratings, diver.ratings + 9);
		
		// These 2 lines output the name of each diver, their difficulty ratings, and does some formatting.
		cout << setprecision(1) << left << setw(8) << diver.name << '	' << diver.difficulty << '	';
		outputFile << setprecision(5) << left << setw(8) << diver.name << "		" << diver.difficulty << "		";

		// This variable is used to hold the sum of the divers' ratings in order to calculate their points total.
		double sum = 0;

		// This for loop iterates through according to the total number of judges and prints each judges' rating for a particular diver. It also sums up those ratings while ignoring
		// the highest and lowest ratings.
		for (int j = 0; j <= 8; j++)
		{
			if (j > 0 && j < 8) 
			{
				sum += diver.ratings[j];
			}
			cout << diver.ratings[j] << '	';
			outputFile << setprecision(5) << diver.ratings[j] << '	';
		}
		
		// These 2 lines use a function to print the points total of each diver.
		cout << setprecision(2) << CalculatePoints(sum, diver) << endl;
		outputFile << setprecision(5) << "	" << CalculatePoints(sum, diver) << endl;
		
		// This conditional tracks the highest point total and the name of the diver with that total in order to output the winner at the end of the program.
		if (CalculatePoints(sum, diver) > highScore)
		{
			winner = diver.name;
			highScore = CalculatePoints(sum, diver);
		}
	}
	DeclareWinner(winner, highScore);
	return 0;
}

// This function performs a simple calculation to find the points total of a diver.
double CalculatePoints(double sum, divers diver)
{
	return (sum * diver.difficulty);
}

// This function prints the winner, their score, and a nice congratulatory message.
void DeclareWinner(string winner, double highScore)
{
	cout << endl << winner << " WINS WITH A SCORE OF " << highScore << "! CONGRATULATIONS!" << endl;
	outputFile << endl << winner << " WINS WITH A SCORE OF " << highScore << "! CONGRATULATIONS!" << endl;
	return;
}


// This function opens the input file.
void OpenInputFile()
{
	diverData.open("mp7divers.txt");
	if (diverData.fail())
	{
		cout << "Failed to open input file";
		return;
	}
}

// This function opens the output file.
void OpenOutputFile()
{
	outputFile.open("MP7Output.txt");
	if (outputFile.fail())
	{
		cout << "Failed to open output file";
		return;
	}
}

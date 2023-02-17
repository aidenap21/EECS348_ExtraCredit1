#include <stdio.h>

int main() {
    char fileName[20]; // creates a character array that will store the name of the input file
	printf("Enter a file name for the input: "); // asks for the input file
	scanf("%s", fileName); // scans for the file name input from the user

	FILE* inputFile = fopen(fileName, "r"); // opens the file
	int prog[5][5], dept[5][5], output[5] = {5, 5, 5, 5, 5}; // initalizes arrays for the choices for all programmers and departments and output of placement

    if (inputFile == NULL) { // runs if the file is empty
		printf("No such file");
		return 0; // ends the program
	}

    for (int i = 0; i < 5; i++) { // for loop to add the department rankings to the array
		fscanf(inputFile, "%d %d %d %d %d ", &dept[i][0], &dept[i][1], &dept[i][2], &dept[i][3], &dept[i][4]); // adds the current line to the department array
    }

    for (int i = 0; i < 5; i++) { // for loop to add the programmer rankings to the array
		fscanf(inputFile, "%d %d %d %d %d ", &prog[i][0], &prog[i][1], &prog[i][2], &prog[i][3], &prog[i][4]); // adds the current line to the programmer array
    }

	for (int i = 0; i < 5; i++) { // for loop to increment the rows of the arrays
		for (int j = 0; j < 5; j ++) { // for loop to increment the collumns of the arrays
			dept[i][j] -= 1; // decreases each value by 1 in order to use the values as indices
			prog[i][j] -= 1; // decreases each value by 1 in order to use the values as indices
		}
	}
	
	int notFound[5] = {0, 1, 2, 3, 4}; // creates an array as a check to make sure every department has found a match
	int completed = 0; // creates a check value to break the while loop after every department has found a match
	
	while (completed == 0) { // runs until every department has found a match
		for (int i = 0; i < 5; i++) { // for loop to iterate over every department
			if (notFound[i] == 5) { // checks if the current loop's department has already been matched
				continue; // skips this loop and moves to the next
			}

			int rank = 0; // integer for the rank of programmer the department wants
			int pref = dept[rank][i]; // number of the preferred programmer for the current department

			for (int j = 0; j < 5; j++) { // loop to find the most preferred programmer that has not yet been matched
				if (pref == output[j]) { // runs if the preferred programmer has already been placed in a department
					pref = dept[++rank][i]; // sets the second choice from the current department as the new preference
					j = -1; // resets the count to check the output array fully again
				}
			}

			int conflicts[5] = {5, 5, 5, 5, 5}; // array that will store which departments also want the preferred programmer
			conflicts[i] = i; // adds the current loop's department to the array by default

			for (int j = 0; j < 5; j++) { // finds all departments that want the preferred programmer
				if (i == j) { // runs if on the current loop's department which is already in the conflicts array
					continue; // skips to the next loop
				} else if (pref == dept[0][j]) { // runs if another department also wants the preferred programmer
					conflicts[j] = j; // adds the conflicting department to the list
				}
			}

			int k; // defines k outside of the loop to use it outside of the for loop
			int matched = 0; // tracks if the programmer has been matched to a department
			for (int j = 0; j < 5; j++) { // for loop to iterate over the preferred programmer's department preferences
				for (k = -1; k < 5; ++k) { // for loop to iterate over the array that stores all the departments who want the preferred programmer
					if (prog[j][pref] == conflicts[k]) { // runs if the current rank of departments for the programmer matches a department that want the programmer
						//printf("matched prog %d to dept %d\n", pref, k); 
						output[k] = pref; // stores the programmer in the matching department
						matched = 1; // sets the matched value as 1 to break the outside loop
						notFound[k] = 5; // sets the matched department index in the notFound loop to 5 to check it off
						break; // breaks the inside loop
					}
				}
				if (matched == 1) { // runs if the programmer has already been matched to a department
					break; // breaks the outside loop
				}
			}

			for (int j = 0; j < 5; j++) { // for loop to clear out the matched department's preferences
				dept[j][k] = 5; // every rank for the matched department as 0
			}

			
		}
		completed = 1; // sets the completed check as 1 and will hold as that unless proven uncompleted
		for (int i = 0; i < 5; i++) { // iterates over the notFound list to check if every department has a match
			if (notFound[i] != 5) { // runs if the current index hasn't been replaced by 5 meaning it hasn't found a match yet
				completed = 0; // sets the completed value as 0 because it is proven uncomplete
				break; // breaks the loop
			}
		}
	}
	for (int i = 1; i < 6; i++) { // loops to print the matched output
		printf("Department #%d will get Programmer #%d\n", i, (output[i - 1] + 1)); // prints the department of the current loop with it's matching programmer
	}

}
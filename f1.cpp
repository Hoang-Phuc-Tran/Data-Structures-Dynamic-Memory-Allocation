/*
 * Project:	    Focused 1 
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		May 10, 2022
 * Description: a program that takes in information about flights and stores the destination and
				date in an array of structs to be displayed. Dynamic memory allocation is used to store
				the strings in the struct.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 6001)


#define STRING_LENGTH 30
#define ARR_MAX 10


// Prototype
int fillFlightInfo(struct FlightInfo* ptr, char destinationInfo[], char dateInfo[]);
void printFlightInfo(struct FlightInfo arr[]);



// Define a struct called FlightInfo
struct FlightInfo {
	char *destination;
	char *date;
};



int main()
{
	// Declare an array variable of struct FlightInfo of size 10
	struct FlightInfo arrFlightInfo[ARR_MAX] = { 0 };

	char strDestination[STRING_LENGTH] = { 0 };
	char strDate[STRING_LENGTH] = { 0 };
	int i = 0;
	int j = 0;
	int checkReturn = 0;

	// Declare a pointer to a struct FlightInfo 
	struct FlightInfo* ptr = NULL;

	ptr = arrFlightInfo;

	for (i = 0; i < ARR_MAX; i++)
	{
		// set 2 string that contain destination and date to empty
		memset(strDestination, '\0', sizeof(strDestination));
		memset(strDate, '\0', sizeof(strDate));

		// Get a flight destination from the user
		printf("Enter a flight destination: ");
		fgets(strDestination, sizeof(strDestination), stdin);

		// Get a flight date from the user
		printf("Enter a flight date: ");
		fgets(strDate, sizeof(strDate), stdin);

		checkReturn = fillFlightInfo(ptr, strDestination, strDate);

		// Check if malloc fails
		if (checkReturn == -1)
		{
			printf("Out of memory\n");
			return -1;
		}

		ptr++;
	}
	
	// Display all of the information contained within the array 
	printFlightInfo(arrFlightInfo);
	
	ptr = arrFlightInfo;

	// Free all memory
	for (j = 0; j < ARR_MAX; j++)
	{
		free(arrFlightInfo[j].date);
		free(arrFlightInfo[j].destination);
	}

	return 0;
}


/*
* Function: fillFlightInfo()
* Description: This function will allocate the two blocks of memory to
			   contain the destination string and date string. 
* Parameters: 3 parameters (a pointer to a struct FlightInfo - a string containing the
			  destination information - a string containing the date information).
* Returns: int: -1 if the allocation is out of memory, 0 otherwise
*/
int fillFlightInfo(struct FlightInfo* ptr, char destinationInfo[], char dateInfo[])
{
	char copyDestination[STRING_LENGTH] = { 0 };
	char copyDate[STRING_LENGTH] = { 0 };

	size_t maxLengthOfDestination = 0;
	size_t maxLengthOfDate = 0;

	strcpy(copyDestination, destinationInfo);
	strcpy(copyDate, dateInfo);

	// Get rid of newline
	copyDestination[strcspn(copyDestination, "\n")] = '\0';
	copyDate[strcspn(copyDate, "\n")] = '\0';


	// maxLengthOfDestination adds one for the null-termination
	maxLengthOfDestination = strlen(copyDestination) + 1;

	// maxLengthOfDate adds one for the null-termination
	maxLengthOfDate = strlen(copyDate) + 1;

	// Allocate a block of memory to cantain the destination string
	ptr->destination = (char*)malloc(maxLengthOfDestination * sizeof(char));
	
	// Check if the allocation fails
	if (ptr->destination == NULL)
	{
		return -1;
	}

	strcpy(ptr->destination, copyDestination);

	// Allocate a block of memory to cantain the date string
	ptr->date = (char*)malloc(maxLengthOfDate * sizeof(char));

	// Check if the allocation fails
	if (ptr->date == NULL)
	{
		return -1;
	}

	strcpy(ptr->date, copyDate);


	return 0;
}

/*
* Function: printFlightInfo()
* Description: This function will prints all of the information contained within the array
* Parameters: 1 parameter (the array of struct FlightInfo).
* Returns: void
*/
void printFlightInfo(struct FlightInfo arr[])
{
	int i = 0;

	printf("\n");

	for (i = 0; i < ARR_MAX; i++)
	{
		// Displayed destination and date information in the next 35 characters of the line (left-justified)
		printf("%-35s", arr[i].destination);
		printf("%-35s\n", arr[i].date);
	}

}
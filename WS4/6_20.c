/**
*	Description: Reads in the user's inputted amount of laps and outputs the 
*	miles
*	Author name: Danny Garcia
*	Author email: danny.garcia@sjsu.edu
*	Last modified Date: 02-27-2023
**/
#include <stdio.h>

/* Converts laps into miles */
double LapsToMiles(double userLaps){

	const int LAPS_PER_MILE = 4;
	double miles = userLaps / LAPS_PER_MILE;

	return miles;
}

int main(void) {
	/*Scan User's laps, then convert and output the laps into miles*/
	double userLaps;

	scanf("%lf", &userLaps);

	printf("%0.2lf\n", LapsToMiles(userLaps));
	return 0;
}

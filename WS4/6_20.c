#include <stdio.h>

/* Converts laps into miles */
double LapsToMiles(double userLaps){

const int LAPS_PER_MILE = 4;
double miles = userLaps / LAPS_PER_MILE;

return miles;
}

int main(void) {

   /* Type your code here. Your code must call the function.  */
double userLaps;

scanf("%lf", &userLaps);

printf("%0.2lf\n", LapsToMiles(userLaps));
   return 0;
}

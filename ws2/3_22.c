/*
	CS 149
	Danny Garcia
	3.22 zyBooks Lab
	Smallest number
*/
#include <stdio.h>

int main(void) {

	int x;
	int y;
	int z;

	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &z);

	if(x <= y){
	   if(x <= z){
	      printf("%d\n", x);}
	   else{
	      printf("%d\n", z);}}
	else if(y <= x){
	   if(y <= z){
	      printf("%d\n", y);}
	   else{
	      printf("%d\n", z);}}
   return 0;
}

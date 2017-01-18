#include <stdio.h>
#include "functions.h"

int main()
{
	int value;

	//banner
	printf("Welcome to my multi-function!\n"
		"Enjoy, but don't go too deep!\n\n");

	while(1)
	{
		//input selection
		printf("What would you like to accomplish today?\n"
			"\t1: Dice roll\n"
			"\t2: Area of Circle\n"
			"\t3: Volume of Cube\n"
			"\t5: Quit\n");
		
		value = inputfunc();
		
		if (value == 5)
		{
			printf("Have a great day!");
			break;
		}
		
		switch (value)
		{
			case 1:
				diceroll();
				break;
			case 2:
				area();
				break;
			case 3:
				volume();
				break;
			case 4:
				custom();
				break;
			default:
				printf("Invalid Input\n");
		}
		
	}
	
return 0;
}
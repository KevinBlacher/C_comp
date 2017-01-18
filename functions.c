#include "functions.h"

float inputfunc();
int save(char *result);
int diceroll();
int area();
int volume();
int custom();

float inputfunc()
{
	float result;
	char string[6];
	char *test;
	int check;
	int err;
	
	do
	{
		check = 0;
		errno = 0;
		fgets(string, 6, stdin);
		if(string[(strlen(string) - 1)] != '\n')
		{
			check = 1;
			while(getchar() != '\n');
		}
		
		result = strtof(string, &test);
		err = errno;
		if(strlen(test) > 1 || err != 0 || check == 1 || result < 1)
		{
			check = 1;
			printf("Please input a valid number!\n");
		}
	} while(check);
	return result;
}

int save(char *result)
{
	int check = 0;
	FILE *fp;

	printf("\nWould you like to save the results?\n"
		"\t1: Yes\n"
		"\t2: No\n");
	check = inputfunc();
	
	if (check == 1)
	{
		fopen_s(&fp, "save.txt", "a");
		if (fp == NULL)
		{
			printf("An error occured while trying to save!");
		}

		fprintf(fp, "%s", result);

		fclose(fp);
	}

	return 0;
}

int diceroll()
{
	int sides;
	int numdice;
	int numroll;
	int j = 0;
	char buffer[200];
	srand(time(NULL));
	
	printf("Please input the number of sides: ");
	sides = inputfunc();
	printf("Please input the number of dice: ");
	numdice = inputfunc();
	printf("Please input the number of rolls: ");
	numroll = inputfunc();
	
	printf("Your results are below...\n");

	for(int x = 1; x <= numroll; x++)
	{
		//printf("Roll %d: ", x);
		j += sprintf_s(buffer + j, 200 - j, "Roll %d: ", x);
		for(int y = 1; y <= numdice; y++)
		{
			int r = (rand() % sides) + 1;
			//printf("%d ", r);
			j += sprintf_s(buffer + j, 200 - j, "%d ", r);
		}
		//printf("\n");
		j += sprintf_s(buffer + j, 200 - j, "\n");
	}
	
	printf("%s", buffer);
	save(buffer);
	
	return 0;
}

int area()
{
	float pi = 3.14;
	float result = 0;
	float radius;
	char buffer[20];
	
	printf("Please input the radius: ");
	radius = inputfunc();
	
	result = pi * (radius * radius);
	
	printf("The area of this circle is: %.2f\n", result);
	sprintf_s(buffer, 20, "%.2f\n", result);
	save(buffer);
	
	return 0;
}

int volume()
{
	float result;
	float length;
	float width;
	float height;
	char buffer[20];
	
	printf("Please input the length: ");
	length = inputfunc();
	
	printf("Please input the width: ");
	width = inputfunc();
	
	printf("Please input the height: ");
	height = inputfunc();
	
	result = length * width * height;
	
	printf("The volume of this is: %.2f\n", result);
	sprintf_s(buffer, 20, "%.2f\n", result);
	save(buffer);
	
	return 0;
}

//Start of basic encryption program
int custom()
{
	int select;
	int j = 0;
	char phrase[32];
	char decode[62];
	char key[10];
	char result[30];
	char temp[30];
	char buffer[80];
	int x, y, z;

	printf("Welcome to the dark code.\n"
		"I will encode/decode any message you want.\n"
		"\t1: Encode\n"
		"\t2: Decode\n");
	select = inputfunc();

	//ENCODE START
	if (select == 1)
	{
		while(1)
		{
			printf("What would you like to encode? (max 30 characters)\n");
			fgets(phrase, 32, stdin);
			if (phrase[(strlen(phrase) - 1)] == '\n')
			{
				break;
			}
			else
			{
				while (getchar() != '\n');
				printf("Please input a string of 30 or less characters.\n");
			}
		}
		while(1)
		{
			printf("\nWhat key would you like to use? (exactly 8 characters)\n");
			fgets(key, 10, stdin);
			if (key[(strlen(key) - 1)] == '\n')
			{
				break;
			}
			else
			{
				while (getchar() != '\n');
				printf("Please input a string of length: 8\n");
			}
		}

		y = strlen(phrase);

		//conversion to INT and XOR, hex printed
		j += sprintf_s(buffer + j, 80 - j, "Encoded: ");
		for (x = 0; x < (y - 1); x++)
		{
			result[x] = (((int)phrase[x]) ^ ((int)key[x % 8]));
			j += sprintf_s(buffer + j, 80 - j, "%02x", result[x]);

		}
		j += sprintf_s(buffer + j, 80 - j, "\n");
		printf("%s", buffer);
		save(buffer);
	}
	//DECODE START
	else if (select == 2)
	{
		while (1)
		{
			printf("What would you like to decode? (max 60 characters)\n");
			fgets(decode, 62, stdin);
			if (decode[strlen(decode) - 1] == '\n')
			{
				break;
			}
			else
			{
				while (getchar() != '\n');
				printf("Please input a string of 60 or less characters.\n");
			}
		}
		while (1)
		{
			printf("\nWhat key was used? (exactly 8 characters)\n");
			fgets(key, 10, stdin);
			if (key[strlen(key) - 1] == '\n')
			{
				break;
			}
			else
			{
				while (getchar() != '\n');
				printf("Please input a string of length: 8\n");
			}
		}

		y = strlen(decode);
		z = 0;
		int result = 0;
		char result2[31];
		char temp[3] = { '0', '0', '\0' };
		for (x = 0; x < 30; x++)
			result2[x] = '0';
		result2[((y - 1) / 2)] = '\0';

		//splitting into hex groups
		for (x = 0; x < y; x++)
		{
			temp[x % 2] = decode[x];
			z++;
			//converting into INT and XORing
			if (z == 2)
			{
				result = strtol(temp, NULL, 16);
				result2[((x - 1) / 2)] = (char)(result ^ ((int)key[((x - 1) / 2) % 8]));
				z = 0;
			}
		}
		j += sprintf_s(buffer + j, 80 - j, "Decoded: %s\n", result2);
		printf("%s", buffer);
		save(buffer);
	}
	return 0;
}

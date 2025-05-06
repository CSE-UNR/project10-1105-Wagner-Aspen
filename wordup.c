//Aspen Wagner
//Project 10

#include <stdio.h>
#include <stdbool.h>

#define wordSize 5
#define columns 10
#define fName "mystery.txt"
#define rows 6

void getFW(int length, char wordSTR[]);
//opens, reads from, and closes file
void getNcheck(int guess, int cols, char guessList[][cols]);
//gets guess and reprompts if wrong entry style given
void decapitalize(char wordSTR[], int guess, int cols, char guessList[][cols]);
//decapitalizes guesses
void recapitalize(char wordSTR[], int guess, int cols, char guessList[][cols]);
//capitalizes correctly guessed letters
void undertext(char wordSTR[], int guess, int cols, char guessList[][cols], char underText[][cols]);
//makes the arrows under guesses
bool checkwin(char wordSTR[], int guess, int cols, char guessList[][cols]);
//checks for win by matching

int main(){
	
	int guess = 0;
	char wordSTR[columns];
	char guessList[rows][columns];
	char underText[rows][columns];
	bool win = 0;
	
	getFW(wordSize, wordSTR);
	
	do{
		getNcheck(guess, columns, guessList);
		decapitalize(wordSTR, guess, columns, guessList);
		win = checkwin(wordSTR, guess, columns, guessList);
		recapitalize(wordSTR, guess ,columns, guessList);
		undertext(wordSTR, guess, columns, guessList, underText);
		
		if(win == 0){
			for(int i = 0; i <= guess; i++){
				printf("%s\n", guessList[i]);
				printf("%s\n", underText[i]);
			}
		}
		else{
			printf("		%s\n", guessList[guess]);
			if(guess >= 1){
				printf("	You won in %d guesses!\n", guess + 1);
				printf("	       Huzzah!\n");
			}
			else{
				printf("	You won in 1 guess!\n");
				printf("	       LITTY!\n");
			}
			return 0;
		}
		guess++;
	}while(win == 0 && guess < rows);
		printf("You lost, better luck next time\n");
	
return 0;
}

void getFW(int length, char wordSTR[]){
//opens, reads from, and closes file
	FILE* Fptr;
	Fptr = fopen(fName, "r");
	
	if (Fptr == NULL){
    		printf("Failed to open file.\n");
    		return;
	}
	
	for(int i = 0; i < length; i++){
		fscanf(Fptr, "%c", &wordSTR[i]);
	}
	
	fclose(Fptr);
}

void getNcheck(int guess, int cols, char guessList[][cols]){
//gets guess and reprompts if wrong entry style given
	bool letters;
	int index = 0;
	
	if(guess < rows - 1){
		printf("GUESS %d! Enter your guess: ", guess+1);
	}
	else{
		printf("FINAL GUESS: ");
	}
	
	do{
		letters = 1;
		scanf("%s", &guessList[guess]);
		
		for(index = 0; guessList[guess][index] != '\0'; index++) {
			if ((guessList[guess][index] >= 31 && guessList[guess][index] <= 64) || (guessList[guess][index] >= 91 && guessList[guess][index] <= 96) || guessList[guess][index] >= 122){
				letters = 0;
			}
		}
		if(index != wordSize && letters == 0){
            		printf("Your guess must be 5 letters long. Your guess must contain all letters.\n");
            		printf("Please try again: ");
            	}
            	else if(index != wordSize){
            		printf("Your guess must be 5 letters long.\n");
            		printf("Please try again: ");
            	}
            	else if(letters == 0){
            		printf("Your guess must contain all letters.\n");
            		printf("Please try again: ");
            	}
      	}while(index != wordSize || letters == 0);
      	printf("================================\n");
}

void decapitalize(char wordSTR[], int guess, int cols, char guessList[][cols]){
//decapitalizes guesses
	for(int i = 0; i < wordSize; i++){
		if(guessList[guess][i] >= 65 && guessList[guess][i] <= 90){
			guessList[guess][i] = guessList[guess][i] + 32;
		}
	}
}

void undertext(char wordSTR[], int guess, int cols, char guessList[][cols], char underText[][cols]){
//makes the text under guesses
	for(int i = 0; i < wordSize; i++){
		for(int j = 0; j < wordSize; j++){
			if(guessList[guess][i] == wordSTR[j]){
				underText[guess][i] = '^';
			}
		}
			if(underText[guess][i] != '^'){
				underText[guess][i] = ' ';
			}
		}
	underText[guess][wordSize] = '\0';	
}

void recapitalize(char wordSTR[], int guess, int cols, char guessList[][cols]){
//capitalizes correctly guessed letters
	for(int i = 0; i < wordSize; i++){
		if(guessList[guess][i] == wordSTR[i]){
			guessList[guess][i] = guessList[guess][i] - 32;
		}
	}
}

bool checkwin(char wordSTR[], int guess, int cols, char guessList[][cols]){
//checks for win by matching
	bool ret = 1;
	for(int i = 0; i < wordSize; i++){
		if(guessList[guess][i] != wordSTR[i]){
			ret = 0;
		}
	}
	if(ret == 1){
		return 1;
	}
	else{
		return 0;
	}
}

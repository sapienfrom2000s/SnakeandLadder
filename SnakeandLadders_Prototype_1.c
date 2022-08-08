/*This game will contain discrete numbers from 1-100. Objective of the player is to cross number 100. On the path to 100 youx
  need to dodge snakes and take up the ladders to cross the finish line as soon as possible. Snakes are like mines placed on
  specific numbers which pushes you down to lower numbers. Similarly,ladders are also placed on specific numbers from where
  can be pulled to higher numbers. A roll of dice will decide the number of steps a player has to make. If a player reaches
  to the number where ladder is kept, he gets a bonus chance to roll again.*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MINVALSNAKE 8 //since snake pushes you down by 7
#define MAXVALSNAKE 99
#define MODFORSNAKE 92 //99-8+1; MAXVALSNAKE-MINVALSNAKE+1

#define MINVALLADDER 5 //since ladder pulls you up by 5
#define MAXVALLADDER 95
#define MODFORLADDER 91 //95-5+1

int coordinate[102]; //for leaving 0th uninitialised as starting with 1 makes code readable and 102th space for 0;
int user_position=0;
int machine_position=0;

void Initialize(void);
void Print(void);
void Place_Snakes(void);
void Place_Ladders(void);
void Turn(void);
int Roll_Dice(void);
void User_Plays(void);
void Machine_Plays(void);
void Check_ForWin(char player);
void Check_ForSnake(void);
void Check_ForLadder(void);

void Initialize(void){

	int i;
	for(i=1;i<=101;i++){

		coordinate[i] = i;
	}
	coordinate[101] = 0;
}

void Print(void){

	int i;
	for(i=1;i<=100;i++){

		printf("%02d\t",coordinate[i]);

		if(i%10 == 0){
			printf("\n");
		}
	}
	printf("-------------------------------------------------------------------------\n");
}

void Place_Snakes(void){

		int i;
		srand(time(NULL));

		for(i=1;i<=10;i++){   //placing 10 snakes

			int snake_value = (rand()%MODFORSNAKE)+MINVALSNAKE;
			coordinate[snake_value] = -7; //-7 represents the presence of snakes at those points
	}
	//Print();
}

void Place_Ladders(void){

		int i,flag = 0,ladder_value;

		srand(time(NULL)+5);  //adding alpha(5) so that seed would be different from that of Place_Snakes which will generate different 'initial' numbers

		while(flag!=10){ //generating 10 ladders

			ladder_value = (rand()%MODFORLADDER)+MINVALLADDER;

			if(coordinate[ladder_value]!=-7){

				coordinate[ladder_value] = -5; // -5 represents the placements of ladder
				flag++;
			}
		}
		//Print();
}

void Turns(){

		int choose;
		int random;
		printf("Deciding the turn by toss.Choose 1 or 0 \n");
		scanf("%d", &choose);
		while((choose!=1) || (choose!=0)){

			if((choose == 1) || (choose == 0 )) 
                                                 break;

			printf("Enter a valid input. Enter 1 or 0\n");
			scanf("%d", &choose);
		}

			random = (time(NULL)+rand())%2;

		if(random == choose){
			printf("You won the toss. You'll play first\n");
			User_Plays();
		}

		else{
			printf("Machine won the toss. It'll play first\n");
			Machine_Plays();
}
}

void User_Plays(void){

	Print();

	int anynumber;
	printf("Enter an int value to roll the dice\n");
	scanf("%d",&anynumber);

	int randnumfromdice = Roll_Dice();
	printf("Your dice rolled to the number %d\n", randnumfromdice);

	user_position += randnumfromdice;

	Check_ForWin('U');
	Check_ForSnake();
	Check_ForLadder(); //Checkforwin() in this function as if user lands on 95 he will climb to 100
	Check_ForWin('U');
	printf("User's new position is %d\n-------------------------------------------\n\n",user_position);
	Machine_Plays();
}

void Machine_Plays(void){

	//Print();

	long extrarandumness = ((Roll_Dice()+rand())%6)+1;
	int consistency = (int)extrarandumness;
	int randnumfromdice = consistency;

	printf("Machine rolled a dice of %d\n", randnumfromdice);

	machine_position += randnumfromdice;

	Check_ForWin('M');
	Check_ForSnake();
	Check_ForLadder();
	Check_ForWin('M');
	printf("Machine's new position is %d\n-----------------------------------------\n\n",machine_position);
	User_Plays();
}

int Roll_Dice(){

	long dice = (time(NULL)%6)+1;
	return (int)dice;
}

void Check_ForWin(char player){


	if(player == 'U'){

		if(user_position >= 100){

			printf("User wins the game\n");
			exit(0);
		}
	}

	if(player == 'M'){

		if(machine_position >= 100){

			printf("Machine wins the game\n");
			exit(0);
			}
		}
}

void Check_ForSnake(void){

	if(coordinate[user_position] == -7){

		printf("You have been bitten by a snake. You will go down by 7 pts\n");
		user_position -= 7;
		Check_ForLadder();  //When your depreciate you can land on a ladder.
	}

	if(coordinate[machine_position] == -7){

		printf("Machine has been bitten by a snake. It will go down by 7 pts\n");
		machine_position -= 7;
		Check_ForLadder();
	}
}

void Check_ForLadder(void){

	if(coordinate[user_position] == -5){

		printf("You have stepped into ladder. You will climb a ladder of 5 pts\n");
		user_position += 5;
		Check_ForSnake();
	}
	if(coordinate[machine_position] == -5){

		printf("Machine has stepped into a ladder. It will climb a ladder of 5 pts\n");
		machine_position += 5;
		Check_ForSnake();
	}
}


int main(){

	Initialize();
	Print();
	Place_Snakes();
	Place_Ladders();
	Turns();
}

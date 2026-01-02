#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include<ctype.h>
#include<stdio.h>

int x, y, fruitx, fruity, score;
int snaketail_x[50], snaketail_y[50], taillen;
int key;
int gameover;
char str[100];
int HighScore;

#define Height 20
#define Width 75

void setup(){
	x = Width/2;
	y = Height/2;
	gameover = 0;
	fruitx = rand() % Width;
	fruity = rand () % Height;
	while (fruitx == 0 || fruity == 0){
		fruitx = rand () % Width;
	    fruity = rand () % Height;
	}
	score = 0;
	FILE *fptr;
	fptr = fopen("HighScore.txt", "r");
	if(fptr == NULL){
		HighScore = -1;
	}
	if(fgets(str, sizeof(str), fptr)!= NULL){
		HighScore = atoi(str);
	}else{
		HighScore = 0;
	}
	fclose(fptr);
		
	
}

void display(){
	int i, j;
	system("cls");
	for(i = 0; i < Width +2; i++){
		printf("#");
	}
	printf("\n");
	for(i=0;i<Height;i++){
		for(j=0;j<=Width;j++){
			if(j == 0 || j == Width){
				printf("#");
			}else if (i == y && j == x){
				printf("0");
			}else if(fruitx == j && fruity == i){
				printf("*");
			}else{
				int prtTail = 0;
				int k;
				for(k = 0; k<taillen; k++){
					if(snaketail_x[k] == j && snaketail_y[k] == i){
						printf("o");
						prtTail = 1;
					}
				}
				if(!prtTail){
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	for(i = 0; i < Width + 2; i++){
	    printf("#");
	}
	printf("\n");
	printf("HighScore = %d\n", HighScore);
	printf("Moverment = WASD\n");
	printf("Score = %d", score);
}

void input(){
	if(kbhit()){
		switch(tolower(getch())){
			case 'w':
				if(key!= 3){
					key = 1;
				}
				break;
			case 'a':
				if(key!=4){
					key = 2;
				}
				break;
			case 's':
				if(key!= 1){
					key = 3;
				}
				break;
			case 'd':
				if(key!=2){
					key = 4;
				}
				break;
			case 'x':
				gameover = 1;
				break;
						
		}
	}
}

void logic(){
	int preX = snaketail_x[0];
	int preY = snaketail_y[0] ;
	int pre2X, pre2Y, i;
	snaketail_x[0] = x;
	snaketail_y[0] = y;
	  for(i = 1; i < taillen; i++) {
        pre2X = snaketail_x[i];
        pre2Y = snaketail_y[i];
        snaketail_x[i] = preX;
        snaketail_y[i] = preY;
        preX = pre2X;
        preY = pre2Y;
    }
    switch(key){
    	case 1:
    		y -= 1;
    		break;
    	case 2:
    		x -= 1;
    		break;
    	case 3:
    		y += 1;
    		break;
    	case 4:
    		x +=1;
    		break;
	}
	if(x == 0 || x >= Width -2 || y == 0 || y >= Height){
		gameover = 1;
	}
	for(i = 0; i < taillen; i++){
		if(snaketail_x[i] == x && snaketail_y[i] == y ){
			gameover = 1;
		}
	}
	if (x == fruitx && y == fruity){
		score += 10;
		taillen++;
		fruitx = rand () % Width;
		fruity = rand () % Height;
		while (fruitx == 0 || fruity == 0){
			fruitx = rand () % Width;
	        fruity = rand () % Height;
		}
	}
}

void check(){
	if(score > HighScore){
		FILE *fptr;
		fptr = fopen("HighScore.txt", "w");
		fprintf(fptr, "%d", score);
		fclose(fptr);
	}
}

void pause(){
	system("cls");
	printf("Score:%d\n", score);
	if(score > HighScore){
		printf("New HighScore:%d", score);
	}
	Sleep(3000);
}


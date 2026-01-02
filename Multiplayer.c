#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include<ctype.h>

int x_1, y_1, x_2, y_2, taillen_1, taillen_2;
int  score_1, score_2, fruitx, fruity;
int snaketail_X1[50], snaketail_Y1[50], snaketail_X2[50], snaketail_Y2[50];
int key_1, key_2;
int gameover_m;
int win;

#define Height 20
#define Width 75

void setup_m(){
	x_1 = Width/4;
    y_1 = Height/2; 
    x_2 = Width/1.5;
    y_2 = Height/2;
	gameover_m = 0;
	fruitx = rand() % Width;
	fruity = rand () % Height;
	while (fruitx == 0 || fruity == 0){
		fruitx = rand () % Width;
	    fruity = rand () % Height;
	}
	score_1 = 0;
	score_2 = 0;
}



void display_m(){
	int i, j;
	system("cls");
	for(i = 0; i < Width+2; i++){
		printf("#");
	}
	printf("\n");
	for(i=0;i<Height;i++){
		for(j=0;j<=Width;j++){
			if(j == 0 || j == Width){
				printf("#");
			}else if (i == y_1 && j == x_1){
				printf("0");
			}else if (i == y_2 && j == x_2 ){
				printf("O");
			}else if(fruitx == j && fruity == i){
				printf("*");
			}else{
				int prtTail_1 = 0, prtTail_2 = 0;
				int k;
				for(k = 0; k<taillen_1; k++){
					if(snaketail_X1[k] == j && snaketail_Y1[k] == i){
						printf("o");
						prtTail_1 = 1;
					}
				}
				for(k = 0; k <taillen_2; k++){
					if(snaketail_X2[k] == j && snaketail_Y2[k] == i){
						printf("l");
						prtTail_1 = 2;
					}
				}
				if(!prtTail_1 && !prtTail_2){
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	for(i = 0; i < Width+2; i++){
	    printf("#");
	}
	printf("\n");
	printf("Player 1:(WASD)\tPlayer 2:(Arrrows key)\n");
	printf("Score: %d\tScore: %d", score_1, score_2);
}

void input_m(){
	if (GetAsyncKeyState(VK_UP)){
		if(key_2!=3){
			key_2 = 1;
		}
	}
	if(GetAsyncKeyState(VK_LEFT)){
		if(key_2!=4){
			key_2 = 2;
		}
	}
	if(GetAsyncKeyState(VK_DOWN)){
		if(key_2!=1){
			key_2 = 3;
		}
	}
	if(GetAsyncKeyState(VK_RIGHT)){
		if(key_2!=2){
			key_2 = 4;
		}
	}
	if(GetAsyncKeyState('W')){
		if(key_1!=3){
			key_1 = 1;
		}
	}
	if(GetAsyncKeyState('A')){
		if(key_1!=4){
			key_1 = 2;
		}
	}
	if(GetAsyncKeyState('S')){
		if(key_1!=1){
			key_1 = 3;
		}
	}
	if(GetAsyncKeyState('D')){
		if(key_1!=2){
			key_1 = 4;
		}
	}
}

void logic_m(){
	int prex_1 = snaketail_X1[0], prex_2 = snaketail_X2[0];
	int prey_1 = snaketail_Y1[0], prey_2 = snaketail_Y2[0];
	snaketail_X1[0] = x_1;
	snaketail_Y1[0] = y_1;
	snaketail_X2[0] = x_2;
	snaketail_Y2[0] = y_2;
	int pre2x_1, pre2y_1, pre2x_2, pre2y_2, i;
	for(i = 1; i<taillen_1;i++){
		pre2x_1 = snaketail_X1[i];
		pre2y_1 = snaketail_Y1[i];
		snaketail_X1[i] = prex_1;
		snaketail_Y1[i] = prey_1;
		prey_1 = pre2y_1;
		prex_1 = pre2x_1;
	}
	for(i = 1; i<taillen_2;i++){
		pre2x_2 = snaketail_X2[i];
		pre2y_2 = snaketail_Y2[i];
		snaketail_X2[i] = prex_2;
		snaketail_Y2[i] = prey_2;
		prey_2 = pre2y_2;
		prex_2 = pre2x_2;
	}
	switch(key_1){
		case 1:
    		y_1 -= 1;
    		break;
    	case 2:
    		x_1 -= 1;
    		break;
    	case 3:
    		y_1 += 1;
    		break;
    	case 4:
    		x_1 +=1;
    		break;
	}
	switch(key_2){
		case 1:
    		y_2 -= 1;
    		break;
    	case 2:
    		x_2 -= 1;
    		break;
    	case 3:
    		y_2 += 1;
    		break;
    	case 4:
    		x_2 +=1;
    		break;
	
	}
	
	if(x_1 == 0 ||x_1 >= Width || y_1 == 0 || y_1 >= Height -2){
		win = 2;
		gameover_m = 1;
	}
	if(x_2 == 0 ||x_2 >= Width || y_2 == 0 || y_2 >= Height -2){
		win = 1;
		gameover_m = 1;
	}
	if(x_1 == x_2 && y_1 == y_2){
		gameover_m = 1;
	}
	for(i = 0; i < taillen_1; i++){
		if(snaketail_X1[i] == x_1 && snaketail_Y1[i] == y_1 ){
			gameover_m = 1;
			win = 2;
		}else if(snaketail_X1[i] == x_2 && snaketail_Y1[i] == y_2){
			gameover_m = 1;
			win = 1;
		}
	}
	
	for(i = 0; i < taillen_2; i++){
		if(snaketail_X2[i] == x_2 && snaketail_Y2[i] == y_2 ){
			gameover_m = 1;
			win = 1;
		}else if(snaketail_X2[i] == x_1 && snaketail_Y2[i] == y_1){
			gameover_m = 1;
			win = 2;
		}
	}
	if (x_1 == fruitx && y_1 == fruity){
		score_1 += 10;
		taillen_1++;
		fruitx = rand () % Width;
		fruity = rand () % Height;
		while (fruitx == 0 || fruity == 0){
			fruitx = rand () % Width;
	        fruity = rand () % Height;
		}
	}
	if (x_2 == fruitx && y_2 == fruity){
		score_2 += 10;
		taillen_2++;
		fruitx = rand () % Width;
		fruity = rand () % Height;
		while (fruitx == 0 || fruity == 0){
			fruitx = rand () % Width;
	        fruity = rand () % Height;
		}
	}
}

void check_m(){
	if(win == 1){
		printf("Player 2 collided with wall\nWinner Player 1\n");
	}else if(win == 2){
		printf("Player 1 collided with wall\nWinner Player 2\n");
	}else if(score_1 == score_2){
		printf("Draw\n");
	}else if(score_1 > score_2){
		printf("Winner Player 1\n");
	}else{
		printf("Winner Player 2\n");
	}
	Sleep(3000);
}

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include "Singleplayer.h"
#include "Multiplayer.h"
#include <time.h>

int choice;

void main_menu(int *current){
	system("cls");
	int input;
	printf("  =============\n");
	printf("  Snake game\n");
	printf("  =============\n");
	switch(*current){
		case 0:
			printf("> Single Player\n");
			printf("  Multiplayer\n");
			printf("  Quit");
			break;
		case 1:
			printf("  Single Player\n");
			printf("> Multiplayer\n");
			printf("  Quit");
			break;
		case 2:
			printf("  Single Player\n");
			printf("  Multiplayer\n");
			printf("> Quit");
			break;
	}
	input = getch();
		if (input == 224){
			input = getch();
			if(*current == 2 && input == 80){
				*current = 0;
		    }else if(*current == 0 && input == 72){
				*current = 2;
			}else if(input == 80){
				*current = *current + 1;
			}else if(input == 72){
				*current = *current - 1;
			}
		}else if(input == 13){
			choice = 1;
		}
}

int main() {
	int current = 0, count = 0;
	int match_time = 60, remain;
	while(current!= 2){
		while (!choice){
		    main_menu(&current);
	    }
		if(current == 0){
		    setup();
			while(!gameover){
			    display();
				input();
				logic();
				Sleep(33);
		    }
		    check();
		    pause();
	    }else if(current == 1){
		    setup_m();
		    time_t start = time(NULL);
		    while(!gameover_m){
			    time_t now = time(NULL);
			    remain = match_time - (now - start);
			    if(remain <= 0){
				    gameover_m = 1;
				}
			    printf("\t\t\tTime = %d\n", remain);
			    display_m();
			    input_m();
			    logic_m();
			    Sleep(100);
		    }
		    system("cls");
		    check_m();
	    }else {
		    system("exit");
        }
        system("cls");
        choice = 0;
    }
}

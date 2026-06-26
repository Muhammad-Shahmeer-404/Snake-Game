#ifndef GAME_H
#define GAME_H

void setUp(int height, int width, Window &w);
void logic(Window &w, int key);
void generateFruit(Window &w);
void collitionCheck(Window &w);
void display(Window &w);
int getPosX();
int getPosY();

extern int gameover;

#endif
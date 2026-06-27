#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cwchar>
#include "Windows.h"

wchar_t snakeSymbol  = L'█'; 
wchar_t fruitSymbol  = L'▄'; 


int gameover        = 0;
int score           = 0;
int boderPadding    = 10;
int letterPadding   = boderPadding - 2;
int obstaclePadding = boderPadding + 5;
int IncreaseFactor  = 1;

bool needsObstacle = false;

const int maxlenght      = 50;
const int maxObstacles   = 50;
int  currentLenght       = 1;
int  currentObstacle     = 0;
wchar_t ScoreString[]    = L"Score:";


typedef struct
{
    int pos_x;
    int pos_y;
}obstacle;

typedef struct 
{
    int     pos_x;
    int     pos_y;
}fruit;

typedef struct
{
    int pos_x;
    int pos_y;
}snake;


snake s[maxlenght];
fruit f;
obstacle ob[maxObstacles];

int getPosX()
{
    return s[0].pos_x;
}

int getPosY()
{
    return s[0].pos_y;
}

void generateObstacle(Window &w)
{
    if((currentObstacle < maxlenght))
    {
        srand(time(0));
        ob[currentObstacle].pos_x = rand() % (w.getHeight() - obstaclePadding);
	    ob[currentObstacle].pos_y = rand () % (w.getWidth() - obstaclePadding);
	    while (ob[currentObstacle].pos_x == 0 || ob[currentObstacle].pos_y == 0 || 
        ob[currentObstacle].pos_x == f.pos_x || ob[currentObstacle].pos_y == f.pos_y)
        {
		    ob[currentObstacle].pos_y = rand () % (w.getWidth() - obstaclePadding);
	        ob[currentObstacle].pos_x = rand () % (w.getHeight() - obstaclePadding);
        }
        currentObstacle++;
    }   
}

void generateBorder(Window &w)
{
    for(int i = 0; i < w.getWidth(); ++i)
    {
        w.setChar(0, i, snakeSymbol, 0);
    }
    for(int i = 0; i < w.getWidth(); ++i)
    {
        w.setChar(w.getHeight()-boderPadding, i, snakeSymbol, 0);
    }
    for(int i = 0; i < w.getHeight() -boderPadding; ++i)
    {
        w.setChar(i, w.getWidth() - 1, snakeSymbol , 0);
        w.setChar(i, 0, snakeSymbol, 0);   
    }
}

void generateFruit(Window &w)
{
    srand(time(0));
    f.pos_x = rand() % (w.getHeight() - boderPadding);
	f.pos_y = rand () % (w.getWidth() - boderPadding);
	while (f.pos_x == 0 || f.pos_y == 0)
    {
		f.pos_y = rand () % (w.getWidth() - boderPadding);
	    f.pos_x = rand () % (w.getHeight() - boderPadding);
    }
}


void displayScore(Window &w)
{
    for(int i = 0; i < wcslen(ScoreString); ++i)
    {
        w.setChar(w.getHeight() - letterPadding, i + 1, ScoreString[i], BLUE);   
    }
    std::string test = std::to_string(score);
    for(int i = 0; i < test.length(); ++i)
    {    
        w.setChar(w.getHeight() - letterPadding, wcslen(ScoreString) + 2 + i, test[i], BLUE);
    }
}

void increaseLenght()
{
    if(currentLenght < maxlenght && IncreaseFactor < 8)
    {
        if (score % 5 == 0 && score != 0)IncreaseFactor += 3;
        currentLenght +=IncreaseFactor;
    }
}

void setUp(int height, int width, Window &w)
{
    generateBorder(w);
    s[0].pos_x = width/2;
    s[0].pos_y = height/2;
    generateFruit(w);
    w.setChar(f.pos_x, f.pos_y, fruitSymbol, RED);
    w.setChar(s[0].pos_x, s[0].pos_y, snakeSymbol, BLUE);
    displayScore(w);
}

void collitionCheck(Window &w)
{
    for(int i = 1; i < currentLenght; ++i)
    {
        if(s[0].pos_x == s[i].pos_x && s[0].pos_y == s[i].pos_y)
        {
            gameover = 1;
            return;
        }    
    }
    if(currentObstacle > 0)
    {
        for(int i = 0; i < currentObstacle; ++i)
        {
            if(s[0].pos_x == ob[i].pos_x && s[0].pos_y == ob[i].pos_y)
            {
                gameover = 1;
                return;
            }
        }
    }
    if(s[0].pos_y == 0 ||  s[0].pos_x == 0)
    {
        gameover = 1;
        return;
    }
    else if(s[0].pos_x == w.getHeight() - boderPadding || s[0].pos_y == w.getWidth() - boderPadding)
    {
        gameover = 1;
        return;
    }
    if(f.pos_x == s[0].pos_x && f.pos_y == s[0].pos_y)
    {
        generateFruit(w);
        increaseLenght();
        score++;

        if(score % 2 == 0 && score != 0)
        {
            needsObstacle = true;
        }
    }
}

void display(Window &w)
{
    generateBorder(w);
    for(int i = 1; i < currentLenght; ++i)
    {
        w.setChar(s[i].pos_x, s[i].pos_y, snakeSymbol, 0);
    }

    while(needsObstacle)
    {
        generateObstacle(w);
        needsObstacle = false;
    }

    if(currentObstacle > 0)
    {
        for(int i = 0; i < currentObstacle; ++i)
        {
            w.setChar(ob[i].pos_x, ob[i].pos_y, snakeSymbol, MAGENTA);
        }
    }

    w.setChar(s[0].pos_x, s[0].pos_y, snakeSymbol, BLUE);
    w.setChar(f.pos_x, f.pos_y, fruitSymbol, RED);
    
    displayScore(w);
}


void logic(Window &w, int key)
{
    int keyCheck[2];
    int preX = s[0].pos_x;
	int preY = s[0].pos_y ;
	int pre2X, pre2Y;
	  for(int i = 1; i < currentLenght ; i++) {
        pre2X = s[i].pos_x;
        pre2Y = s[i].pos_y;
        s[i].pos_x = preX;
        s[i].pos_y = preY;
        preX = pre2X;
        preY = pre2Y;
    }
    switch (key)
    {
    case 119: // w
        s[0].pos_x--;
        break;
    case 115: // s
        s[0].pos_x++;
        break;
    case 100: // d
        s[0].pos_y++;
        break;
    case 97: // a
        s[0].pos_y--;
        break;
    default:
        break;
    }
    collitionCheck(w);
    display(w);
}

#include <iostream>
#include <fstream>
#include "Windows.h"

const std::string fileName = "assets/SnakeTui.txt";
wchar_t ch;

int currentFocused = 0;

std::wstring movement = L"SNAKE MOVEMENT: WASD";
std::wstring control  = L"UP/DOWN: J/K";

typedef struct
{
    std::wstring text;
    bool focused;
}Button;

Button b[2];

void setButton()
{
    b[0].text = L"* Start Game (p)\n"; b[0].focused = true;
    b[1].text = L"* Quit (q)\n";       b[1].focused = false;
}


void CreateTitle(Window &w)
{
    int col = w.getWidth()/3.5, row = w.getHeight()/3; 
    std::wifstream f (fileName.c_str());
    while(f.get(ch))
    {
        if(ch == '\n')
        {
            row++;
            col = w.getWidth()/3.5;
            if(!f.get(ch)) break;
        }
        w.setChar(row, col, ch, 0);
        col++;
    }
}

void CreateMenu(Window &w)
{
    int color;
    for(int j = 0; j < 2; ++j)
    {
        if(b[j].focused){color = CYAN;}
        else{color = 0;}

        for(int i = 0; i < b[j].text.length(); ++i)
        {
            w.setChar(w.getHeight()/1.7 + j,w.getWidth()/2.2 + i, b[j].text[i], color);
        }        
    }
    for(int i = 0; i < movement.length(); ++i)
    { 
        w.setChar(w.getHeight() - 1, w.getWidth() - movement.length() - 2 + i, movement[i], 0);
    }
    for(int i= 0; i < control.length(); ++i)
    {
        w.setChar(w.getHeight() - 1, 1 + i, control[i], 0 );
    }
}

void upDown(int key)
{
    if(key == 'k')
    {
        if(currentFocused == 1)
        {
            b[currentFocused].focused = false;
            currentFocused = 0;
            b[currentFocused].focused = true;
        }else
        {
            b[currentFocused].focused = false;
            currentFocused++;
            b[currentFocused].focused = true;
        }
    }
    if(key == 'j')
    {
        if(currentFocused == 0)
        {
            b[currentFocused].focused = false;
            currentFocused = 1;
            b[currentFocused].focused = true;
        }else
        {
            b[currentFocused].focused = false;
            currentFocused--;
            b[currentFocused].focused = true;
        }
    }
}

void PressButton(char* key)
{
    if(currentFocused == 1) *key = 'q';
    if(currentFocused == 0) *key = 'p';
}

void handleInput(char* key)
{
    if(*key == 'j' || *key == 'k')
    {
        upDown(*key);
        *key = '\0';
    }else if(*key == '\r')
    {
        PressButton(key);
    }
}

void setMainMenu(Window &w)
{
    CreateTitle(w);
    CreateMenu(w);
}
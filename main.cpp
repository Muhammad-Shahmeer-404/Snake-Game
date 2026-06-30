#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>  
#include "src/Terminal/Input.h"
#include "src/Code/Windows.h"
#include "src/Code/Game.h"
#include "src/Code/File.h"
#include "src/Code/MainMenu.h"

struct winsize w;
char c;
int key;

void mainGameLoop(Window &w);

void mainMenuLoop(Window &w)
{
    w.clear();
    setButton();
    setMainMenu(w);
    w.flush();
    c = '\0';
    while (c != 'q') 
    {
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        if (c == 'q') break;
        if(c == 'j' || c == 'k' || c == '\r')
        {
            handleInput(&c);
            w.clear();
            setMainMenu(w);
            w.flush();
        }
        if(c == 'p')
        {
            mainGameLoop(w);
        }
    }
}

void mainGameLoop(Window &w)
{
    w.clear();
    setUp(w.getWidth(), w.getHeight(), w);
    c = '\0';
    while (!gameover) 
    {
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        if (c == 'q') break;
        w.flush();
        if(c == 119 || c == 115 || c == 100 || c == 97)
        {
            key = c;
            w.clear();
            logic(w, key);
            w.flush();
        }
    }
    updateHighScore();
    if(c != 'q'){sleep(2);}
    w.clear();
    w.flush();
    mainMenuLoop(w);
}


int main()
{
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());

    std::wcout << "\x1b[?25l";

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row;
    int width  = w.ws_col;
    Window myWindow(height, width);
    enableRawMode();

    mainMenuLoop(myWindow);
    
    std::wcout << "\x1b[?25h";
    std::wcout << "\x1B[2J" << "\x1b[H";
    
    disableRawMode();

}
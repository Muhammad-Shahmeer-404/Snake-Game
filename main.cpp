#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>  
#include "src/Terminal/Input.h"
#include "src/Code/Windows.h"
#include "src/Code/Game.h"

struct winsize w;
char c;
int key;


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
    setUp(width, height, myWindow);
    c = '\0';

    while (!gameover) 
    {
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        if (c == 'q') break;
        myWindow.flush();
        if(c == 119 || c == 115 || c == 100 || c == 97)
        {
            key = c;
            myWindow.clear();
            logic(myWindow, key);
            myWindow.flush();
        }
    }
    sleep(2);
    std::wcout << "\x1b[?25h";
    std::wcout << "\x1B[2J" << "\x1b[H";
    
    disableRawMode();

}
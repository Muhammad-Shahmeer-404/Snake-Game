#include<iostream>
#include<cwchar>
#include "Windows.h"

wchar_t space = L' ';

Window::Window(int height, int width): height(height), width(width)
{
    buffer = new Cell*[height];
    for(int w = 0; w < height; w++)
    {
        buffer[w] = new Cell[width];
    }
    clear();
}


void Window::clear()
{
    for(int h = 0; h < height ;h++)
    {
        for(int w = 0; w < width; w++)
        {
            buffer[h][w].ch     = space;
            buffer[h][w].color  = 0;
        }
    }
}

void Window::flush()
{
    std::wcout << "\x1b[J";
    std::wcout << "\x1b[H";
    for(int h = 0; h < height ;h++)
    {
        for(int w = 0; w < width; w++)
        {
            std::wcout  << "\x1b[" << buffer[h][w].color << "m";
            std::wcout << buffer[h][w].ch;
        }
        if(h < height - 1)
        {
            std::wcout << '\r' <<'\n';
        }
    }
        std::wcout << "\x1b[0m";
        std::wcout.flush();
}

int Window::getHeight()
{
    return height;
}

int Window::getWidth()
{
    return width;
}

Window::~Window()
{
    for(int i = 0; i < height; i++)
    {
        delete[] buffer[i];
    }
    delete[] buffer;
}


void Window::setChar(int row, int col, wchar_t c, int color)
{
    if(col < width && row < height)
    {
        buffer[row][col].color = color;
        buffer[row][col].ch = c;
    }
}


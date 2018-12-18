/*  definations for the functions in console_position.h */
#include "console_position.h"

void gotoxy(position pos)
{
    COORD coord;
    coord.X = pos.x;
    coord.Y = pos.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}

position wherexy()
{
    position p={0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD result;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return p;
    else
    {
        result = csbi.dwCursorPosition;
        p.x = result.X;
        p.y = result.Y;
        return p;
    }
}

std::tuple <int, int> wherexy_tuple()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD result;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return std::tuple<int, int>(0, 0);
    else
    {
        result = csbi.dwCursorPosition;
        return std::tuple<int, int>(result.X, result.Y);
    }
}
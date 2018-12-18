/*  console_position.h file: used for handlin the cursor postion    */
#ifndef CONSOLE_POSITION_H
#define CONSOLE_POSITION_H

#include <windows.h>
#include <iostream>
#include <tuple>

using namespace std;

#ifndef POSITION
#define POSOTION
//  position structure
/*  REMEMBER: Console applications run in the 3rd quadrant
    of the cartesian coordinate system. The top-left is (0,0)   */
struct position
{
    int x;  //  x-axis value(left-to-right)
    int y;  //  y-axis value(top-to-bottom)
};
#endif

#ifndef GOTOXY_POS
#define GOTOXY_POS
//  gotoxy function using postion structure
void gotoxy(position pos);
#endif

#ifndef GOTOXY
#define GOTOXY
//  standard gotoxy function
void gotoxy(int x, int y);
#endif

#ifndef WHEREXY_POS
#define WHEREXY_POS
//  wherexy function using position structure
/*  wherexy function: returns the current cursor position in the console
    returns position structure    */
position wherexy();
#endif

#ifndef WHEREXY
#define WHEREXY
//  wherexy function using tuple
/*  wherexy function: returns the current cursor position in the console
    returns tupple of two values: x, y  */
std::tuple <int, int> wherexy_tuple();
#endif

#endif
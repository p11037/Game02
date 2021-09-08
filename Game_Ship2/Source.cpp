#include<stdio.h>
#include<windows.h>
#include<conio.h>
int status[5], b_x[5], b_y[5];

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y) {

    gotoxy(x, y);
    setcolor(15, 4);
    printf(" <-0-> ");

}


void erase_ship(int x, int y) {

    gotoxy(x, y);
    setcolor(15, 0);
    printf("       ");

}

void draw_bullet(int x, int y) {
    gotoxy(x, y);
    setcolor(15, 4);
    printf("*");
}

void erase_bullet(int x, int y) {
    gotoxy(x, y);
    setcolor(0, 0);
    printf(" ");
}

void shoot(int a) {
    erase_bullet(b_x[a], b_y[a]);
    if (b_y[a] > 1) 
        
        draw_bullet(b_x[a], --b_y[a]);

    else status[a] = 0;
}

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

int main() {
    setcursor(0);
    char ch = ' ';
    int x = 0, y = 20, direct = 0, L = 1, R = 2, S = 3;
    draw_ship(x, y);

    do {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a') direct = L;
            if (ch == 'd') direct = R;
            if (ch == 's') direct = S;
            if (ch == ' ') {
                 for (int i = 0; i < 5; i++) {
                     if (status[i] == 0) {
                        status[i] = 1;
                        b_x[i] = x + 3;
                        b_y[i] = y - 1;
                        break;
                      }
                }
               
            }
         fflush(stdin);
        }
 
 
        if (direct >= 1)
        {

            if (direct == L)
            {
                if (x > 0)
                {
                    erase_ship(x, y);
                    draw_ship(--x, y);

                }
               
            }
            if (direct == R)
            {
                if (x < 80)
                {
                    erase_ship(x, y);
                    draw_ship(++x, y);
                }
               
            }

       for (int i = 0; i < 5; i++) {
            if (status[i]) 
                shoot(i);
        }

        }
        Sleep(100);
    } while (ch != 'x');
    return 0;
}
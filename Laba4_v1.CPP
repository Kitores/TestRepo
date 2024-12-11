#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <bios.h>

#define LEFT 10
#define TOP 23
#define RIGHT 70
#define BOTTOM 12

struct Position {
  int x;
  int y;
};

// Чтение с клавиатуры
int getKeyboardInput() {
  if (kbhit()) {
    return getch();
  }
  return -1;
}

// Перемещение символа
void moveChar(Position *pos, int MoveX, int MoveY) {
  if ((pos->y + MoveY ) == 11){
    gotoxy(pos->x, pos->y);
    cprintf(" ");
    pos->y = 23;
  } 
  else if ((pos->y + MoveY) == 23){
    gotoxy(pos->x, pos->y);
    cprintf(" ");
    pos->y = 11;
  }

  gotoxy(pos->x, pos->y);
  cprintf(" ");
  gotoxy(pos->x + MoveX, pos->y + MoveY);
  cprintf("*");

  pos->x += MoveX;
  pos->y += MoveY;

}

// Отрисовка окна
void PrintWindow() {
  for (int x = LEFT; x < RIGHT; x++) {
    gotoxy(x, TOP);
    putch('-');
    gotoxy(x, BOTTOM - 1);
    putch('-');
  }
  for (int y = BOTTOM; y < TOP; y++) {
    gotoxy(RIGHT, y);
    putch('|');
    gotoxy(LEFT, y);
    putch('|');
  }
}


int main() {

  Position pos = {40, 16};

  clrscr();
	window(LEFT, TOP, RIGHT, BOTTOM);

  char input = ' ';
  //пока не нажат Ctrl + C
  while (input != 3) {
    PrintWindow();
    input = getKeyboardInput();
    if (input == 72)moveChar(&pos, 0, -1);        // стрелка вверх
    else if (input == 80) moveChar(&pos, 0, 1);   // стрелка вниз
  }
  return 0;
}


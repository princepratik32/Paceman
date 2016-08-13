#include "../header/gameboard.h"
#include "../header/pacman.h"
#include "../header/monster.h"
#include "../header/fruit.h"
#include "stdio.h"
#include <stdlib.h>
#include <ncurses.h>

void draw_borders(WINDOW *screen) {
  int x, y, i;

  getmaxyx(screen, y, x);

  // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+");

  // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "#");
    mvwprintw(screen, i, x - 1, "#");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "#");
    mvwprintw(screen, y - 1, i, "#");
  }
}

void gameBoardInitialize(GameBoard *a)
{
    //used to zero out a game board instance
    char wall= 0;
    char fruit1 = '-';
    char fruit2 = '&';
    char fruit3 = '*';
    char fruit4 = '$';
    char map[20][26];  //map generated by text file
    int numFruit1 = 0; //number of first fruit on level
    int numFruit2 = 0; //number of second
    int numFruit3 = 0; //number of thrid
    int numFruit4 = 0; //number of fourth
    int pacman = 0;    //number of pacman
    int monster = 0;    //number of monsters
    int pause_state = 0;
    int run_state = 1;
}

void displayBoard(GameBoard *gameboard, WINDOW *levelBuffer)
{
  int i,j;
  char character;

  for ( i = 0; i < 20; i++)
  {
      for (j = 0; j< 26; j++)
      {
          if(gameboard->map[i][j] >0 )
          {
              character = gameboard->map[i][j];
              mvwprintw(levelBuffer, i+1, j+1, "%c", character);
          }

    }
  }
}

int gameBoardLoad(GameBoard *gameboard, PacMan *pacman, Fruit fruitArr[][26], char fileName[])
{   FILE* fp = NULL;

    char fileInput;
    int i,j;


    fp = fopen(fileName, "r");
    if (!fp)
        return -1;

    for ( i = 0; i < 20; i++ )
    {
        for (j = 0; j<26; j++)
	       {
               fileInput = getc(fp);
               gameboard->map[i][j] = fileInput;
               /*
               if(fileInput=='3' || fileInput == ' ' || fileInput == 'M')
               gameboard->map[i][j] = fileInput;

               else if(fileInput == '-' || fileInput == '*' || fileInput == '&' || fileInput == '$')
               {
                   fruitArr[i][j]= fileInput;

                   gameboard->map[i][j] = fileInput;

                   if(fileInput == '-')
                   gameboard->numFruit1++;

                   else if(fileInput == '*')
                   gameboard->numFruit2++;

                   else if(fileInput == '&')
                   gameboard->numFruit3++;

                   else
                   gameboard->numFruit4++;

               }

               else if(fileInput == 'M')
               {
                   gameboard->numMonster++;
                   gameboard->map[i][j] = fileInput;
               }

               else if(fileInput == '<')
               {
                   pacman->x_start=i;
                   pacman->y_start=j;
                   gameboard->numPacman++;
                   gameboard->map[i][j] = fileInput;
               }
*/

           }
           fileInput = getc(fp);
       }
    fclose(fp);

    if (gameboard->numPacman == 1)
    return 1;
    else
    return -1;
}

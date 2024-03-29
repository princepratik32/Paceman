#include "../header/gameBoard.h"
#include <ncurses.h>


//function to draw boarder around windows
void draw_borders(WINDOW *screen) {
  int x;
  int y;
  int i;
  getmaxyx(screen, y, x);

  // 4 corners
  mvwprintw(screen, 0, 0, "X");
  mvwprintw(screen, y - 1, 0, "X");
  mvwprintw(screen, 0, x - 1, "X");
  mvwprintw(screen, y - 1, x - 1, "X");

  // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "X");
    mvwprintw(screen, i, x - 1, "X");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "X");
    mvwprintw(screen, y - 1, i, "X");
  }
}

void gameBoardInitialize(GameBoard *a)
{
    //used to zero out a game board instance
     a->numFruit1 = 0; //number of first fruit on level
     a->numFruit2 = 0; //number of second
     a->numFruit3 = 0; //number of thrid
     a->numFruit4 = 0; //number of fourth
     a->numPacman = 0;    //number of pacman
     a->numMonster = 0;    //number of monsters
     a->pause_state = 0;
     a->run_state = 1;
     a->level=1;
}


void displayLevel(GameBoard *gb, WINDOW *levelBuffer)
{
     mvwprintw(levelBuffer, 3,3, "%s", "Level:");
     mvwprintw(levelBuffer, 3,10, "%d", gb->level);
}

void displayBoard(GameBoard *gameboard, WINDOW *levelBuffer)
{
  int i,j;
  char character;

  for ( i = 0; i < 18; i++)
  {
      for (j = 0; j< 26; j++)
      {
          if(gameboard->map[i][j] > 0 )
          {
              character = gameboard->map[i][j];
              mvwprintw(levelBuffer, i+1, j+1, "%c", character);
          }
    }
  }
}

int gameBoardLoad(GameBoard *gameboard, char fileName[])
{
    FILE* fp = NULL;
    char charInput;
    char str[27];
    int i,j;
    int numRead;
    int currentPos;
    const int NUMCHAR = 100;

    fp = fopen(fileName, "r");
    if (!fp)
        return -1;

    //get wall
    fgets(str, NUMCHAR, fp);
    numRead = numBytesRead(fp);

    if(fp)
    {
        gameboard->wall = str[0];
    }

    //get fruit from second line
    fgets(str, NUMCHAR, fp);

    if(fp)
    {
        numRead = numBytesRead(fp);
        for(i = 0; i < numRead; i++)
        {
            if (str[i] > 32 && str[i] < 127 ) //32 - 127 characters only
            {
                gameboard->fruit[i] = str[i];
            }
        }
    }

    for ( i = 0; i < 18; i++ )
    {
        fgets(str, NUMCHAR, fp);
        for (j = 0; j<26; j++)
	       {
               charInput = str[j];

               if(charInput == gameboard->wall || charInput == ' ')
               gameboard->map[i][j] = charInput;

               else if(charInput == gameboard->fruit[0] ||
                   charInput == gameboard->fruit[1] ||
                   charInput == gameboard->fruit[2] ||
                   charInput == gameboard->fruit[3])
               {
                   gameboard->map[i][j] = charInput;

                   if(charInput == gameboard->fruit[0])
                   gameboard->numFruit1++;

                   else if(charInput == gameboard->fruit[1])
                   gameboard->numFruit2++;

                   else if(charInput == gameboard->fruit[2])
                   gameboard->numFruit3++;

                   else
                   gameboard->numFruit4++;
               }

               else if(charInput == 'M')
               {
                   gameboard->numMonster++;
                   gameboard->map[i][j] = charInput;
               }

               else if(charInput == '<')
               {
                   gameboard->map[i][j] = charInput;
                   gameboard->numPacman++;
               }
           }
       }
    fclose(fp);

    if (gameboard->numPacman == 1)
    return 1;
    else
    return -2;
}

int numBytesRead(FILE *ptr)
{
    static int lastPos = 0;
    int currentPos = ftell(ptr);
    int diffrence = currentPos - lastPos;
    lastPos = currentPos;

    return diffrence;
}

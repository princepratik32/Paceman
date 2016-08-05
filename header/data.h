#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef struct Direction
{
    int x;
    int y;
} Direction;

typedef struct GameBoard
{
    char wall;
    char monster;
    char fruit1, fruit2, fruit3, fruit4;
    char map[][];  //map generated by text file
    int numFruit1; //number of first fruit on level
    int numFruit2; //number of second
    int numFruit3; //number of thrid
    int numFruit4; //number of fourth
    int pacman;    //number of pacman
    int monster;    //number of monsters
    int pause_state;
    int run_state;
	int test;

} GameBoard;

#endif

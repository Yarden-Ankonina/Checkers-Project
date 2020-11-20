#pragma once
#define _CRT_SECURE_NO_WARNINGS

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*DEFINES*/
#define BOARD_SIZE 8
#define LEFT  0
#define RIGHT 1
#define TOP_DOWN 'T'
#define BOTTOM_UP 'B'
#define EMPTY_TILE ' '
#define OUT_OF_BOARD 'Z'
#define NO_WINNER 10

/*TYPEDEFS*/
typedef int MOVE;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _checkersPos
{
	char row, col;
}checkersPos;
int typedef BOOL;
#define TRUE 1
#define FALSE 0


/*LIST DATA STRUCTURE*/

//Move List data sturcture
typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell * next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell * head;
	SingleSourceMovesListCell * tail;
}SingleSourceMovesList;

//Multiply move list data structure
typedef struct _multiplySourceMovesListCell {
	SingleSourceMovesList *single_source_move_list;
	struct _multiplySourceMovesListCell * next;
}multiplySourceMovesListCell;

typedef struct _multiplySourceMovesList {
	multiplySourceMovesListCell * head;
	multiplySourceMovesListCell * tail;
}multiplySourceMovesList;

/*BINARY TREE DATA STRUCTURE*/
typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;//curr num of captures
	struct _SingleSourceMovesTreeNode *next_move[2];//available moves
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;


/*FUNCTIONS DECLARATIONS*/
//Q1
SingleSourceMovesTree * findSingleSourceMoves(Board board, checkersPos * src);
void printTree(SingleSourceMovesTree* tree);
void freeTree(SingleSourceMovesTree* tree);
SingleSourceMovesTreeNode* insertDataToTreeNode(Board board, checkersPos* pos, unsigned short captures);
SingleSourceMovesTree* makeEmptyTree(void);

//Q2
SingleSourceMovesList * findSingleSourceOptimalMove(SingleSourceMovesTree*moves_tree);
void printList(SingleSourceMovesList * list);
void freeList(SingleSourceMovesList * list);

//Q3
multiplySourceMovesList * findAllPossiblePlayerMoves(Board board, Player player);
void freeMultiList(multiplySourceMovesList * list);
void printMutliList(multiplySourceMovesList * list);

//Q4
void Turn(Board board, Player player);

//Q5
void StoreBoard(Board board, char * filename);

//Q6
void LoadBoard(char * filename, Board board);
void checkFile(void * ptr, char * filename);

//Q7
void PlayGame(Board board, Player starting_player);

//General functions
void checkAllocation(void*);
void printBoard(Board board);
int randomNum(int num);
void checkPlayGame(void);
void makeInitialGameBoard(Board board);

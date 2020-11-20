#include "check.h"

//function declararion
static void checkQ1a(Board board);
static void checkQ1a2(Board board);
static void checkQ1b(Board board);
static void checkQ1c(Board board);
static void checkQ1d(Board board);
static void checkQ1e(Board board);
static void checkQ1f(Board board);
static void checkQ1g(Board board);
static void checkQ1h(Board board);
static void checkQ1I(Board board);
static void checkQ1j(Board board);
static void checkA(Board board);
static void checkB(Board board);
static void checkC(Board board);
static void checkD(Board board);
static void checkE(Board board);
static void checkF(Board board);
static void checkG(Board board);

//function implementation
void checkQ(void)
{
	//Check Q1

	Board board;
	int num;
	printf("Please enter option number\n");

	scanf("%d", &num);

	switch (num)
	{
		//Bottom up
	case(1):
		checkQ1a(board);
		break;
	case(2):
		checkQ1b(board);
		break;
	case(3):
		checkQ1c(board);
		break;
	case(4):
		checkQ1d(board);
		break;
	case(5):
		checkQ1e(board);
		break;
	case(6):
		checkQ1f(board);
		break;
	case(7):
		checkQ1g(board);
		break;
	case(8):
		checkQ1h(board);
		break;
		//Top Down
	case(9):
		checkQ1a2(board);
		break;
	case(10):
		checkQ1I(board);
		break;
	case(11):
		checkQ1j(board);
		break;
		//Q3
	case(12):
		checkA(board);
		break;
	case(13):
		checkB(board);
		break;
	case(14):
		checkC(board);
		break;
		//Q7
	case(15):
		checkD(board);
		break;
		//Q5
	case(16):
		checkE(board);
		break;
		//general checks
	case(17):
		checkF(board);
		break;
	case(18):
		checkG(board);
		break;
	}
}

//check for starting position
static void checkQ1a(Board board)
{
	SingleSourceMovesTree * tree;

	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = board[7][2] = board[7][4] = board[7][6] = board[6][1] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][2] = board[5][4] = board[5][6] = 'B';

	checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '1';
	src->row = 'H';

	tree = findSingleSourceMoves(board, src);

	printTree(tree);

	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);
	freeList(list);

	freeTree(tree);
}

static void checkQ1a2(Board board)
{
	SingleSourceMovesTree * tree;

	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = board[7][2] = board[7][4] = board[7][6] = board[6][1] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][2] = board[5][4] = board[5][6] = 'B';

	checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '8';
	src->row = 'A';

	tree = findSingleSourceMoves(board, src);

	printTree(tree);

	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);


}

static void checkQ1b(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][4] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '1';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);

	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);

}

static void checkQ1c(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B';
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][4] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '1';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);

	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);
	freeList(list);

	freeTree(tree);
}

static void checkQ1d(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = EMPTY_TILE, board[4][1] = 'T', board[4][3] = 'T';
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][4] = board[5][6] = 'B';



	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '1';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);
	freeList(list);

	freeTree(tree);
}

static void checkQ1e(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '3';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);

}

static void checkQ1f(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE, board[4][1] = 'B';
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '3';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);

}

static void checkQ1g(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][3] = board[0][5] = board[0][7] = board[1][2] = board[1][4] = board[1][6] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE, board[4][1] = 'T', board[2][1] = 'T', board[0][1] = EMPTY_TILE, board[1][0] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '3';
	src->row = 'H';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);

}

static void checkQ1h(Board board)
{
	SingleSourceMovesTree * tree;
	board[0][3] = board[0][5] = board[0][7] = EMPTY_TILE, board[1][2] = board[1][4] = board[1][6] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'T', board[5][0] = EMPTY_TILE, board[4][1] = EMPTY_TILE, board[2][1] = EMPTY_TILE, board[0][1] = 'B', board[1][0] = EMPTY_TILE;
	board[7][2] = EMPTY_TILE, board[6][3] = 'B', board[5][4] = 'T', board[3][0] = EMPTY_TILE, board[3][2] = 'T', board[3][4] = 'T', board[3][6] = 'T';
	board[2][3] = EMPTY_TILE, board[2][5] = EMPTY_TILE, board[2][7] = EMPTY_TILE;
	board[7][4] = board[7][6] = board[6][5] = board[6][7] = board[5][6] = 'B';


	checkersPos *src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '4';
	src->row = 'G';
	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);

}

static void checkQ1I(Board board)
{
	SingleSourceMovesTree * tree;

	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[1][6] = 'B';
	board[7][0] = board[7][2] = board[7][4] = board[7][6] = board[6][1] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][2] = board[5][4] = board[5][6] = 'B';

	checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '8';
	src->row = 'A';

	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);


}

static void checkQ1j(Board board)
{
	SingleSourceMovesTree * tree;

	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[2][1] = board[2][3] = board[2][7] = 'T';
	board[1][6] = 'B', board[2][5] = EMPTY_TILE, board[3][4] = 'B', board[3][6] = 'B', board[4][7] = 'T';
	board[5][2] = 'T', board[6][5] = EMPTY_TILE, board[7][6] = EMPTY_TILE, board[6][1] = EMPTY_TILE;
	board[7][0] = board[7][2] = board[7][4] = board[6][3] = board[6][7] = board[5][0] = board[5][4] = board[5][6] = 'B';

	checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
	src->col = '8';
	src->row = 'A';

	tree = findSingleSourceMoves(board, src);

	printTree(tree);
	SingleSourceMovesList * list;
	list = findSingleSourceOptimalMove(tree);
	printList(list);

	freeTree(tree);
	freeList(list);
}

static void checkA(Board board)
{

	board[0][1] = board[0][3] = board[0][5] = board[0][7] = board[1][0] = board[1][2] = board[1][4] = board[1][6] = board[2][1] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = board[7][2] = board[7][4] = board[7][6] = board[6][1] = board[6][3] = board[6][5] = board[6][7] = board[5][0] = board[5][2] = board[5][4] = board[5][6] = 'B';

	printBoard(board);
	multiplySourceMovesList * list;
	list = findAllPossiblePlayerMoves(board, BOTTOM_UP);
	Turn(board, 'B');
	printMutliList(list);
	freeMultiList(list);
}

static void checkB(Board board)
{

	board[0][3] = board[0][5] = board[0][7] = board[1][2] = board[1][4] = board[1][6] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE, board[4][1] = 'T', board[2][1] = 'T', board[0][1] = EMPTY_TILE, board[1][0] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';

	printBoard(board);
	multiplySourceMovesList * list;
	list = findAllPossiblePlayerMoves(board, BOTTOM_UP);
	Turn(board, 'B');
	printMutliList(list);
	freeMultiList(list);

}

static void checkC(Board board)
{
	board[0][3] = board[0][5] = board[0][7] = board[1][2] = board[1][4] = board[1][6] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE, board[4][1] = 'T', board[2][1] = 'T', board[0][1] = EMPTY_TILE, board[1][0] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';

	Board newboard;

	printBoard(board);
	StoreBoard(board, "board.bin");
	LoadBoard("board.bin", newboard);
}

static void checkD(Board board)
{
	int playerNum;
	board[0][3] = board[0][5] = board[0][7] = board[1][2] = board[1][4] = board[1][6] = board[2][3] = board[2][5] = board[2][7] = 'T';
	board[7][0] = 'B', board[6][1] = 'T', board[5][2] = 'B', board[5][0] = EMPTY_TILE, board[4][1] = 'T', board[2][1] = 'T', board[0][1] = EMPTY_TILE, board[1][0] = EMPTY_TILE;
	board[7][2] = board[7][4] = board[7][6] = board[6][3] = board[6][5] = board[6][7] = board[5][4] = board[5][6] = 'B';
	playerNum = randomNum(2);
	if (playerNum == 0)
		PlayGame(board, TOP_DOWN);
	else
		PlayGame(board, BOTTOM_UP);
}

static void checkE(Board board)
{
	makeInitialGameBoard(board);
	StoreBoard(board, "checkE.bin");
	LoadBoard("checkE.bin", board);
	PlayGame(board, TOP_DOWN);

	StoreBoard(board, "checkE.bin");
	LoadBoard("checkE.bin", board);
	PlayGame(board, TOP_DOWN);
}

static void checkF(Board board)
{
	makeInitialGameBoard(board);
	board[4][3] = TOP_DOWN;
	printBoard(board);
	StoreBoard(board, "charF.bin");
	Board newBoard;
	LoadBoard("charF.bin",newBoard);
	printBoard(newBoard);
	PlayGame(newBoard, BOTTOM_UP);
	printBoard(newBoard);

}

static void checkG(Board board)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (i % 2 == 0)//if even row num
		{
			j = 1;
		}
		else //odd row num
		{
			j = 0;
		}

		for (j; j < BOARD_SIZE; j = j + 2)
		{
			board[i][j] = EMPTY_TILE;
		}
	}

	StoreBoard(board, "emptyboard.bin");
	LoadBoard("emptyboard.bin", board);
	printBoard(board);
	PlayGame(board, BOTTOM_UP);
	printBoard(board);
}


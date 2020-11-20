#include "Functions.h"

//STATIC FUNCTIONS DECLARATION
//Q1 static declaration
static BOOL isPlayerInPos(Board board, char posRow, char posCol, Player* tileID);
static void convertPositionToNum(int* row, int* col, char inputRow, char inputCol);
static SingleSourceMovesTreeNode * findSingleSourceMovesRec(SingleSourceMovesTreeNode * root, Player currPlayer, BOOL didEat);
static void copyBoard(Board toBoard, Board board);
static SingleSourceMovesTreeNode* allocateEmptyTreeNode(void);
static void movePlayerInBoard(Board board, checkersPos* pos, Player player, int move, int i);
static void advancePos(char* row, char* col, Player currPlayer, int move);
static BOOL inBoard(char posRow, char posCol);
static void eatPlayer(Board board, checkersPos* playerPos, Player currPlayer, int move);
static void printTreeRec(SingleSourceMovesTreeNode * node);
static void freeTreeRec(SingleSourceMovesTreeNode * node);
static void checkNextMoveTileWithoutPlayer(Player nextMoveTileID, Player currPlayer, SingleSourceMovesTreeNode* root, char nextMoveRow, char nextMoveCol, int direction);
static void checkNextMoveTileWithPlayer(Player nextMoveTileID, BOOL playerInDoubleNextMove, Player currPlayer, SingleSourceMovesTreeNode* root, char doubleNextMovePlayerRow, char doubleNextMovePlayerCol, int direction);

//Q2 static declaration
static void findSingleSourceOptimalMoveRec(SingleSourceMovesTreeNode * root, SingleSourceMovesList * list);
static void makeEmptyList(SingleSourceMovesList * List);
static SingleSourceMovesListCell * createNewListCell(checkersPos * pos, unsigned short captures, SingleSourceMovesListCell * next);
static int maxCapture(SingleSourceMovesTreeNode * root);
static void addToEndOFList(SingleSourceMovesListCell * cellToAdd, SingleSourceMovesList * list);
static BOOL isListEmpty(SingleSourceMovesList * list);

//Q3 static declaration
static void makeEmptyMultiList(multiplySourceMovesList * list);
static BOOL isMultiListEmpty(multiplySourceMovesList *list);
static void makeEmptyMultiList(multiplySourceMovesList * list);
static void addToEndOFMultiList(multiplySourceMovesList *list, multiplySourceMovesListCell* listToAdd);
static multiplySourceMovesListCell * createMultyListCell(SingleSourceMovesList * list, multiplySourceMovesListCell * next);
static void convertNumToPosition(int row, int col, char* rowPos, char* colPos);

//Q4 static declaration
static void getMaxCapturesInPos(SingleSourceMovesList* currList, SingleSourceMovesList** pointToBestMoveList, unsigned short* maxCapturesSoFar);
static void chooseRandomList(SingleSourceMovesList** pointToBestMoveList, SingleSourceMovesList* sameCapturesList);
static void playBestMove(Board board, SingleSourceMovesList* bestMoveList, Player currPlayer);
static int getDirection(checkersPos *currPos, checkersPos *nextPos);

//Q7  static declaration
static void printPlayerMove(Player player, SingleSourceMovesList * list);
static BOOL isGameOver(Board board);
static Player changePlayer(Player starting_player);


//FUNCTIONS IMPLEMENTATION

//Q1 - the functions return A tree of moves that the player can make
SingleSourceMovesTree* findSingleSourceMoves(Board board, checkersPos* src)
{
	SingleSourceMovesTree* tree;
	Player currPlayer; // tell player if 'T' or 'B'

	if (isPlayerInPos(board, src->row, src->col, &currPlayer))//if there is player in position 
	{
		tree = makeEmptyTree();
		tree->source = insertDataToTreeNode(board, src, 0);
		tree->source = findSingleSourceMovesRec(tree->source, currPlayer, FALSE);
	}
	else
		return NULL;

	return tree;
}

//recursive function that gets all player moves, makes them into a tree and return the tree root 
static SingleSourceMovesTreeNode* findSingleSourceMovesRec(SingleSourceMovesTreeNode* root, Player currPlayer, BOOL didEat) // didEat - checks if ate last turn
{
	Player rightnextTileID, leftnextTileID; //'B' or 'T' or ' ' or 'Z'
	BOOL playerInRightSide, playerInLeftSide; // if there is a player in pos
	char rightRow = root->pos->row, leftRow = root->pos->row;
	char rightCol = root->pos->col, leftCol = root->pos->col;

	advancePos(&rightRow, &rightCol, currPlayer, RIGHT);
	advancePos(&leftRow, &leftCol, currPlayer, LEFT);
	playerInRightSide = isPlayerInPos(root->board, rightRow, rightCol, &rightnextTileID);
	playerInLeftSide = isPlayerInPos(root->board, leftRow, leftCol, &leftnextTileID);

	//if right and left are occupied(not NULL) and are the same player - return
	if ((playerInLeftSide && playerInRightSide) && (rightnextTileID == currPlayer && leftnextTileID == currPlayer))
	{
		return root;
	}
	//if there is no player on right and left tiles 
	else if (!playerInLeftSide && !playerInRightSide)
	{
		//if already captured this turn
		if (didEat == TRUE)
		{
			return root;
		}
		else //not captured this turn
		{
			checkNextMoveTileWithoutPlayer(rightnextTileID, currPlayer, root, rightRow, rightCol, RIGHT);
			checkNextMoveTileWithoutPlayer(leftnextTileID, currPlayer, root, leftRow, leftCol, LEFT);
			return root;
		}
	}
	//if there is only one player on the right or the left side
	else if ((!playerInLeftSide && playerInRightSide) || (playerInLeftSide && !playerInRightSide))
	{
		Player tempLeft = leftnextTileID, tempRight = rightnextTileID;
		//if there is no player on the left size 
		if (!playerInLeftSide)
		{
			//already captured
			if (didEat)
			{
				root->next_move[LEFT] = NULL;
			}
			else
				checkNextMoveTileWithoutPlayer(leftnextTileID, currPlayer, root, leftRow, leftCol, LEFT);
			//move right player one more tile
			advancePos(&rightRow, &rightCol, currPlayer, RIGHT);//now right row and right col are double right row and double right col
			playerInRightSide = isPlayerInPos(root->board, rightRow, rightCol, &rightnextTileID);
			checkNextMoveTileWithPlayer(tempRight, playerInRightSide, currPlayer, root, rightRow, rightCol, RIGHT);//now right row and right col are double right row and double right col
		}
		//if there is a player on the left and not on the right side
		else
		{
			//already captured
			if (didEat)
			{
				root->next_move[RIGHT] = NULL;
			}
			//if the right player is out of board
			else
				checkNextMoveTileWithoutPlayer(rightnextTileID, currPlayer, root, rightRow, rightCol, RIGHT);
			//move left player one more tile
			advancePos(&leftRow, &leftCol, currPlayer, LEFT);//now left row and left col are double left row and double left col
			playerInLeftSide = isPlayerInPos(root->board, leftRow, leftCol, &leftnextTileID);
			checkNextMoveTileWithPlayer(tempLeft, playerInLeftSide, currPlayer, root, leftRow, leftCol, LEFT);//now left row and left col are double left row and double left col
		}
		return root;
	}
	//There are 2 players on the right and on the left side, 2 options - both are the opponent or one of them is opponent
	else
	{
		Player tempLeft = leftnextTileID, tempRight = rightnextTileID;
		//check tile behind enemy's tile
		advancePos(&rightRow, &rightCol, currPlayer, RIGHT);//now right row and right col are double right row and double right col
		advancePos(&leftRow, &leftCol, currPlayer, LEFT);//now left row and left col are double left row and double left col
		playerInLeftSide = isPlayerInPos(root->board, leftRow, leftCol, &leftnextTileID);
		playerInRightSide = isPlayerInPos(root->board, rightRow, rightCol, &rightnextTileID);
		checkNextMoveTileWithPlayer(tempRight, playerInRightSide, currPlayer, root, rightRow, rightCol, RIGHT);//now right row and right col are double right row and double right col
		checkNextMoveTileWithPlayer(tempLeft, playerInLeftSide, currPlayer, root, leftRow, leftCol, LEFT);//now left row and left col are double left row and double left col
		return root;
	}
}

//eat player changes board to 'capture' the opponent - erase the eaten player
static void eatPlayer(Board board, checkersPos* playerPos, Player currPlayer, int move)
{
	int row, col;
	convertPositionToNum(&row, &col, playerPos->row, playerPos->col);
	if (currPlayer == TOP_DOWN)
	{
		if (move == RIGHT)
		{
			(board)[row + 1][col + 1] = EMPTY_TILE;
		}
		else
		{
			(board)[row + 1][col - 1] = EMPTY_TILE;
		}
	}
	//BOTTOM_UP
	else
	{
		if (move == RIGHT)
		{
			(board)[row - 1][col + 1] = EMPTY_TILE;
		}
		else
		{
			(board)[row - 1][col - 1] = EMPTY_TILE;
		}
	}
	(board)[row][col] = EMPTY_TILE;
}

//moves the player in the board
static void movePlayerInBoard(Board board, checkersPos* pos, Player player, int move, int i)
{
	int row, col;
	convertPositionToNum(&row, &col, pos->row, pos->col);
	(board)[row][col] = EMPTY_TILE;

	if (player == TOP_DOWN)
	{
		if (move == RIGHT)
		{
			(board)[row][col] = EMPTY_TILE;
			(board)[row + i][col + i] = TOP_DOWN;
		}
		else
		{
			(board)[row][col] = EMPTY_TILE;
			(board)[row + i][col - i] = TOP_DOWN;
		}
	}
	else//BOTTOM_UP
	{
		if (move == RIGHT)
		{
			(board)[row][col] = EMPTY_TILE;
			(board)[row - i][col + i] = BOTTOM_UP;
		}
		else//LEFT
		{
			(board)[row][col] = EMPTY_TILE;
			(board)[row - i][col - i] = BOTTOM_UP;
		}
	}
}

//inserts data to tree node
SingleSourceMovesTreeNode* insertDataToTreeNode(Board board, checkersPos* pos, unsigned short captures)
{
	SingleSourceMovesTreeNode* node;

	node = allocateEmptyTreeNode();//do not need to allocate pos because pos is already allocated 
	copyBoard(node->board, board);
	node->pos = pos;
	node->total_captures_so_far = captures;
	//next left & right = null is in allocateEmptyTreeNode

	return node;
}

//the function copy the board
static void copyBoard(Board toBoard, Board board)
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			toBoard[i][j] = board[i][j];
		}
	}
}

//the functions converts to position in mat
static void convertPositionToNum(int* row, int* col, char inputRow, char inputCol)
{
	*row = (int)(inputRow - 'A');
	*col = ((int)(inputCol - '0')) - 1;
}

//make empty tree
SingleSourceMovesTree* makeEmptyTree(void)
{
	SingleSourceMovesTree* tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkAllocation(tree);
	tree->source = NULL;

	return tree;
}

//allocate empty tree node
SingleSourceMovesTreeNode * allocateEmptyTreeNode(void)
{
	SingleSourceMovesTreeNode * root;

	root = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocation(root);

	root->next_move[LEFT] = NULL;
	root->next_move[RIGHT] = NULL;
	return root;
}

//The function checks if there is a player in this position and changes tileId accordingly
static BOOL isPlayerInPos(Board board, char posRow, char posCol, Player* tileID)
{
	int row, col;
	if (inBoard(posRow, posCol))
	{
		row = (int)(posRow - 'A');
		col = ((int)(posCol - '0')) - 1;

		if ((board[row][col] == TOP_DOWN) || (board[row][col] == BOTTOM_UP))
		{
			*tileID = board[row][col];
			return (TRUE);
		}
		else
		{
			*tileID = EMPTY_TILE;
			return (FALSE);
		}
	}
	else
	{
		*tileID = OUT_OF_BOARD;
		return FALSE;
	}
}

//advances player position to next tile
static void advancePos(char* row, char* col, Player currPlayer, int move)
{
	if (move == RIGHT)
	{
		if (currPlayer == TOP_DOWN)
		{
			*col = *col + 1;
			*row = *row + 1;
		}
		else // Bottom up
		{
			*col = *col + 1;
			*row = *row - 1;
		}
	}
	else
	{
		if (currPlayer == TOP_DOWN)
		{
			*col = *col - 1;
			*row = *row + 1;
		}
		else // Bottom up
		{
			*col = *col - 1;
			*row = *row - 1;
		}
	}
	if (!inBoard(*row, *col))
	{
		*col = OUT_OF_BOARD;
		*row = OUT_OF_BOARD;
	}
}

//checks if the position is on board
static BOOL inBoard(char posRow, char posCol)
{
	if ((posRow >= 'A' && posRow <= 'H') && (posCol >= '1' && posCol <= '8'))
		return TRUE;
	else
		return FALSE;
}

static void checkNextMoveTileWithoutPlayer(Player nextMoveTileID, Player currPlayer, SingleSourceMovesTreeNode* root, char nextMoveRow, char nextMoveCol, int direction)
{
	//if next move tile is out of board 
	if (nextMoveTileID == OUT_OF_BOARD)
	{
		root->next_move[direction] = NULL;
	}
	//next move tile in board
	else
	{
		Board nextMoveBoard;
		checkersPos* nextMovePlayerPos = (checkersPos*)malloc(sizeof(checkersPos)); //check next tile
		checkAllocation(nextMovePlayerPos);
		nextMovePlayerPos->row = nextMoveRow;
		nextMovePlayerPos->col = nextMoveCol;
		copyBoard(nextMoveBoard, root->board);
		movePlayerInBoard(nextMoveBoard, root->pos, currPlayer, direction, 1);
		root->next_move[direction] = insertDataToTreeNode(nextMoveBoard, nextMovePlayerPos, root->total_captures_so_far);
	}
}

static void checkNextMoveTileWithPlayer(Player nextMoveTileID, BOOL playerInDoubleNextMove, Player currPlayer, SingleSourceMovesTreeNode* root, char doubleNextMovePlayerRow, char doubleNextMovePlayerCol, int direction)
{
	//check direction input side if - the player there is in our side, if there is a player in 2 direction move tile or if 2 direction move tile is out of board
	if (playerInDoubleNextMove || nextMoveTileID == currPlayer || !(inBoard(doubleNextMovePlayerRow, doubleNextMovePlayerCol)))
	{
		root->next_move[direction] = NULL;
	}
	//eat direction input player
	else
	{
		checkersPos* doubleNextMovePlayerPos = (checkersPos*)malloc(sizeof(checkersPos)); //check next tile
		SingleSourceMovesTreeNode* nextMoveNode;
		Board nextMoveBoard;
		checkAllocation(doubleNextMovePlayerPos);
		doubleNextMovePlayerPos->row = doubleNextMovePlayerRow;
		doubleNextMovePlayerPos->col = doubleNextMovePlayerCol;
		copyBoard(nextMoveBoard, root->board);
		movePlayerInBoard(nextMoveBoard, root->pos, currPlayer, direction, 2);//move Direction*2 after eating
		eatPlayer(nextMoveBoard, root->pos, currPlayer, direction);//eats the enemy
		nextMoveNode = insertDataToTreeNode(nextMoveBoard, doubleNextMovePlayerPos, root->total_captures_so_far + 1);
		root->next_move[direction] = findSingleSourceMovesRec(nextMoveNode, currPlayer, TRUE);
	}
}

void printTree(SingleSourceMovesTree * tree)
{
	//if not NULL
	if (tree)
	{
		if (tree->source)
		{
			printTreeRec(tree->source);
		}
	}

	else
		printf("NULL");
}

static void printTreeRec(SingleSourceMovesTreeNode *node)
{
	if (node->next_move[LEFT])
		printTreeRec(node->next_move[LEFT]);
	if (node->next_move[RIGHT])
		printTreeRec(node->next_move[RIGHT]);

	printf(" tile [%c][%c]\n\n", node->pos->row, node->pos->col);
	printBoard(node->board);
	printf("\n");

}

void freeTree(SingleSourceMovesTree * tree)
{
	if (tree->source)
	{
		freeTreeRec(tree->source);
		tree->source = NULL;
	}
	free(tree);
}

static void freeTreeRec(SingleSourceMovesTreeNode * node)
{
	if (node->next_move[LEFT])
		freeTreeRec(node->next_move[LEFT]);
	if (node->next_move[RIGHT])
		freeTreeRec(node->next_move[RIGHT]);
	free(node->pos);
	free(node);
}


//Q2 
//functions gets tree of moves and return a list with the best moves
SingleSourceMovesList * findSingleSourceOptimalMove(SingleSourceMovesTree * moves_tree)
{
	//if tree isn't NULL (root is also not NULL)
	if (moves_tree)
	{
		//if leaf can't move
		if (moves_tree->source->next_move[LEFT] || moves_tree->source->next_move[RIGHT])
		{
			SingleSourceMovesList * list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
			checkAllocation(list);
			makeEmptyList(list);
			findSingleSourceOptimalMoveRec(moves_tree->source, list);
			return list;
		}
	}
	return NULL;
}

//recursive functions checks with maxCapture which way to go to and add node to list
static void findSingleSourceOptimalMoveRec(SingleSourceMovesTreeNode * root, SingleSourceMovesList * list)
{
	checkersPos* currPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocation(currPos);
	currPos->row = root->pos->row;
	currPos->col = root->pos->col;
	//if leaf 
	if (root->next_move[LEFT] == NULL && root->next_move[RIGHT] == NULL)
	{
		addToEndOFList(createNewListCell(currPos, root->total_captures_so_far, NULL), list);
	}
	//not leaf
	else
	{
		int left = 0, right = 0;
		if (root->next_move[LEFT] != NULL)
			left = maxCapture(root->next_move[LEFT]);
		if (root->next_move[RIGHT] != NULL)
			right = maxCapture(root->next_move[RIGHT]);

		//left subtree has more captures
		if ((left > right) || (!root->next_move[RIGHT]))
		{
			addToEndOFList(createNewListCell(currPos, root->total_captures_so_far, NULL), list);
			findSingleSourceOptimalMoveRec(root->next_move[LEFT], list);
		}
		//right subtree has more captures
		else if ((right > left) || (!root->next_move[LEFT]))
		{
			addToEndOFList(createNewListCell(currPos, root->total_captures_so_far, NULL), list);
			findSingleSourceOptimalMoveRec(root->next_move[RIGHT], list);
		}
		// right and left subtree are equal choose one randomly
		else
		{
			addToEndOFList(createNewListCell(currPos, root->total_captures_so_far, NULL), list);
			findSingleSourceOptimalMoveRec(root->next_move[randomNum(2)], list);
		}
	}
}

static void makeEmptyList(SingleSourceMovesList * List)
{
	List->head = List->tail = NULL;
}

//get root and returns highest amount of captures
static int maxCapture(SingleSourceMovesTreeNode * root)
{
	//leaf
	if (!root->next_move[LEFT] && !root->next_move[RIGHT])
	{
		return root->total_captures_so_far;
	}
	else
	{
		int left = 0, right = 0;
		if (root->next_move[LEFT] != NULL)
			left = maxCapture(root->next_move[LEFT]);
		if (root->next_move[RIGHT] != NULL)
			right = maxCapture(root->next_move[RIGHT]);
		return max(left, right);
	}
}

static SingleSourceMovesListCell * createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell * next)
{
	SingleSourceMovesListCell * node = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocation(node);
	node->position = pos;//do not need to allocate pos because pos is already allocated 
	node->captures = captures;
	node->next = next;
	node->position = pos;

	return node;
}

static void addToEndOFList(SingleSourceMovesListCell * cellToAdd, SingleSourceMovesList * list)
{
	if (isListEmpty(list))
	{
		list->head = list->tail = cellToAdd;
	}
	//list isnt empty add to end of list
	else
	{
		list->tail->next = cellToAdd;
		list->tail = cellToAdd;
	}
}

static BOOL isListEmpty(SingleSourceMovesList * list)
{
	if (list->head == NULL)
		return TRUE;
	else
		return FALSE;
}

//get random number between 0 and 1 
int randomNum(int num)
{
	srand((unsigned int)time(0));
	return rand() % num;
}

void printList(SingleSourceMovesList * list)
{
	if (list != NULL)
	{
		SingleSourceMovesListCell * temp = list->head;
		printf("\n");
		while (temp != NULL)
		{
			printf(" |pos - [%c][%c],captures - %d | -> ", temp->position->row, temp->position->col, temp->captures);
			temp = temp->next;
		}
		printf("NULL\n");

	}

}

void freeList(SingleSourceMovesList * list)
{
	if (list != NULL)
	{
		SingleSourceMovesListCell * curr = list->head, *temp = list->head;
		while (curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			free(temp->position);
			free(temp);
		}
		free(list);
	}
}

//Q3 the fucntions finds all possible moves the player can make (the best from each pawn that can move) and returns it as a list
multiplySourceMovesList * findAllPossiblePlayerMoves(Board board, Player player)
{
	multiplySourceMovesList * list = (multiplySourceMovesList*)malloc(sizeof(multiplySourceMovesList));
	int i, j;
	checkAllocation(list);
	makeEmptyMultiList(list);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		//if even row num
		if (i % 2 == 0)
			j = 1;
		else //odd row num
			j = 0;

		for (j; j < BOARD_SIZE; j = j + 2)
		{
			if ((board)[i][j] == player)
			{
				multiplySourceMovesListCell* currNode;//assign variables
				SingleSourceMovesTree* currTree;
				SingleSourceMovesList* optimalMoveList;
				checkersPos* src = (checkersPos*)malloc(sizeof(checkersPos));
				checkAllocation(src);
				convertNumToPosition(i, j, &(src->row), &(src->col));
				currTree = findSingleSourceMoves(board, src); // make tree of moves
				optimalMoveList = findSingleSourceOptimalMove(currTree); //make best move list
				freeTree(currTree);
				currNode = createMultyListCell(optimalMoveList, NULL);
				if (currNode != NULL)
					addToEndOFMultiList(list, currNode);
			}
		}
	}
	return list;
}

static void makeEmptyMultiList(multiplySourceMovesList * list)
{
	list->head = list->tail = NULL;
}

static void addToEndOFMultiList(multiplySourceMovesList *list, multiplySourceMovesListCell* listToAdd)
{
	if (isMultiListEmpty(list))
	{
		list->head = list->tail = listToAdd;
	}
	//list isnt empty add to end of list
	else
	{
		list->tail->next = listToAdd;
		list->tail = listToAdd;
	}
}

static BOOL isMultiListEmpty(multiplySourceMovesList *list)
{
	if (list->head == NULL)
		return TRUE;
	else
		return FALSE;
}

static multiplySourceMovesListCell * createMultyListCell(SingleSourceMovesList * list, multiplySourceMovesListCell * next)
{
	if (list == NULL)
		return NULL;
	else
	{

		multiplySourceMovesListCell * node = (multiplySourceMovesListCell*)malloc(sizeof(multiplySourceMovesListCell));
		node->single_source_move_list = list;
		node->next = next;
		return node;
	}
}

static void convertNumToPosition(int row, int col, char* rowPos, char* colPos)
{
	*rowPos = ((char)(row + 'A'));
	*colPos = ((char)(col + '0')) + 1;
}

void freeMultiList(multiplySourceMovesList * list)
{
	multiplySourceMovesListCell * curr = list->head, *temp = list->head;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->single_source_move_list != NULL)
			freeList(temp->single_source_move_list);
		free(temp);
	}
	free(list);
}

void printMutliList(multiplySourceMovesList * list)
{
	multiplySourceMovesListCell * temp = list->head;
	printf("\n");
	while (temp != NULL)
	{
		if (temp->single_source_move_list != NULL)
		{
			printList(temp->single_source_move_list);
			printf("\n");
		}
		temp = temp->next;
	}
}

//Q4 - play the player's best turn
void Turn(Board board, Player player) //change exit
{
	multiplySourceMovesList* list;
	list = findAllPossiblePlayerMoves(board, player);
	if (list->head == NULL)
	{
		board[0][0] = NO_WINNER;
		if (player == TOP_DOWN)
			printf("No more moves to play for TOP_DOWN, TIE\n");
		else
			printf("No more moves to play for BOTTOM_UP, TIE \n");
	}
	else
	{
		multiplySourceMovesListCell* curr = list->head;
		SingleSourceMovesList* bestMoveList = list->head->single_source_move_list;
		unsigned short maxCapturesSoFar = 0;
		while (curr != NULL)
		{
			getMaxCapturesInPos(curr->single_source_move_list, &bestMoveList, &maxCapturesSoFar);
			curr = curr->next;
		}
		printPlayerMove(player, bestMoveList);
		playBestMove(board, bestMoveList, player);
	}
	freeMultiList(list);
}

static void playBestMove(Board board, SingleSourceMovesList* bestMoveList, Player currPlayer)
{
	int direction, totalCaptures = bestMoveList->tail->captures;
	SingleSourceMovesListCell* curr = bestMoveList->head;

	if (totalCaptures == 0)
	{
		direction = getDirection(curr->position, curr->next->position);
		movePlayerInBoard(board, curr->position, currPlayer, direction, 1);
	}
	else //captured enemy
	{
		while (curr->next != NULL)
		{
			direction = getDirection(curr->position, curr->next->position);
			movePlayerInBoard(board, curr->position, currPlayer, direction, 2);//move Direction*2 after eating
			eatPlayer(board, curr->position, currPlayer, direction);//eats the enemy
			curr = curr->next;
		}
	}
}

static void getMaxCapturesInPos(SingleSourceMovesList* currList, SingleSourceMovesList** pointToBestMoveList, unsigned short* maxCapturesSoFar)
{
	SingleSourceMovesListCell *maxCapturesNode = currList->tail;

	if (maxCapturesNode->captures > *maxCapturesSoFar)
	{
		*maxCapturesSoFar = maxCapturesNode->captures;
		*pointToBestMoveList = currList;
	}
	if (maxCapturesNode->captures == *maxCapturesSoFar)
	{
		chooseRandomList(pointToBestMoveList, currList);
	}
}

static int getDirection(checkersPos *currPos, checkersPos *nextPos)
{
	if (currPos->col < nextPos->col)
		return RIGHT;
	else
		return LEFT;
}

static void chooseRandomList(SingleSourceMovesList** pointToBestMoveList, SingleSourceMovesList* sameCapturesList)
{
	int num = randomNum(2);
	if (num == 0) 
		*pointToBestMoveList = sameCapturesList;
	// else point to the same node without change
}

//Q5
void StoreBoard(Board board, char * filename)
{
	unsigned short int mask, letterMsk;
	int i, j;
	FILE *fp = fopen(filename, "wb");
	checkFile(fp, filename);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		mask = 0x0000;
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 'T')
				letterMsk = 0x0001;
			else if (board[i][j] == 'B')
				letterMsk = 0x0002;
			else // empty tile - 00
				letterMsk = 0x0000;

			mask = mask << 2;
			mask = mask | letterMsk;
		}
		fwrite(&mask, sizeof(unsigned short int), 1, fp);
	}
	fclose(fp);
}

//Q6
void LoadBoard(char * filename, Board board)
{
	unsigned short int binaryRow, letterMsk, mask = 0x0000;
	int i, j;
	FILE * fp = fopen(filename, "rb"); 
	checkFile(fp, filename);
	for (i = 0; i < BOARD_SIZE; i++) 
	{
		fread(&binaryRow, sizeof(unsigned short int), 1, fp);
		letterMsk = 0xC000;
		for (j = 0; j < BOARD_SIZE; j++)
		{
			mask = binaryRow & letterMsk;
			if (mask == 0x4000) // 'T'
				board[i][j] = 'T';
			else if (mask == 0x8000) // 'B'
				board[i][j] = 'B';
			else // empty tile
				board[i][j] = EMPTY_TILE;

			binaryRow = binaryRow << 2;
		}
	}
	printf("\n");
	fclose(fp);
}

//Q7 
void PlayGame(Board board, Player starting_player)
{
	BOOL endGame = FALSE;
	printBoard(board);
	while (endGame == FALSE)
	{
		Turn(board, starting_player);
		endGame = isGameOver(board);
		starting_player = changePlayer(starting_player);
	}
}

static BOOL isGameOver(Board board)
{
	if (board[0][0] == NO_WINNER)
		return TRUE;
	else
	{
		int bottom_upCounter = 0, top_downCounter = 0;
		int i, j;
		for (i = 0; i < BOARD_SIZE; i++)
		{
			if (i % 2 == 0)//if even row num
				j = 1;
			else //odd row num
				j = 0;

			for (j; j < BOARD_SIZE; j = j + 2)
			{
				if (board[i][j] == BOTTOM_UP)
				{
					if (i == 0)
					{
						printf("THE WINNER IS BOTTOM_UP!\n");
						return TRUE;
					}
					bottom_upCounter++;
				}
				if (board[i][j] == TOP_DOWN)
				{
					if (i == 7)
					{
						printf("THE WINNER IS TOP_DOWN!\n");
						return TRUE;
					}
					top_downCounter++;
				}
			}
		}
		if (top_downCounter == 0)
		{
			printf("THE WINNER IS BOTTOM_UP!\n");
			return TRUE;
		}
		else if (bottom_upCounter == 0)
		{
			printf("THE WINNER IS TOP_DOWN!\n");
			return TRUE;
		}
		else
			return FALSE;
	}
}

static Player changePlayer(Player starting_player)
{
	if (starting_player == TOP_DOWN)
		return BOTTOM_UP;
	else
		return TOP_DOWN;
}

static void printPlayerMove(Player player, SingleSourceMovesList * list)
{
	if (player == TOP_DOWN)
		printf("player TOP_DOWN's turn\n");
	else
		printf("player BOTTOM_UP's turn\n");

	SingleSourceMovesListCell * curr = list->head;
	while (curr->next != NULL)
	{
		if (curr == list->head)
			printf("%c%c->%c%c", curr->position->row, curr->position->col, curr->next->position->row, curr->next->position->col);
		else
			printf("->%c%c", curr->next->position->row, curr->next->position->col);
		curr = curr->next;
	}
	printf("\n");

}

//general functions

void printBoard(Board board)
{
	int i, j;
	char A = 'A';
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("+ |1|2|3|4|5|6|7|8|\n");
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("+-+-+-+-+-+-+-+-+-+\n");
		printf("|%c|", A);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			printf("%c|", board[i][j]);
		}
		A++;
		printf("\n");
	}
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("\n");
}

//check memory allocation
void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "Allocation Error\n");
		exit(-1);
	}
}

void checkFile(void * ptr, char * filename)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "wasn't able to open file named %s \n", filename);
		exit(1);
	}
}

void checkPlayGame(void)
{
	int playerNum;
	Board board;
	makeInitialGameBoard(board);
	//play random player first
	playerNum = randomNum(2);
	if (playerNum == 0)
		PlayGame(board, TOP_DOWN);
	else
		PlayGame(board, BOTTOM_UP);
}

void makeInitialGameBoard(Board board)
{
	int i, j, k;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (i % 2 == 0)//if even row num
		{
			j = 1;
			k = 0;
		}
		else //odd row num
		{
			j = 0;
			k = 1;
		}

		for (j; j < BOARD_SIZE; j = j + 2)
		{
			if (i <= 2)
				board[i][j] = TOP_DOWN;
			else if (i >= 5)
				board[i][j] = BOTTOM_UP;
			else
				board[i][j] = EMPTY_TILE;
		}
		for (k; k < BOARD_SIZE; k = k + 2)
			board[i][k] = EMPTY_TILE;
	}
}
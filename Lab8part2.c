/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Muhammed Yakubu
 *
 * Date: Jan 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
void configureBoard(char board[][26], int n);
void placeTile (char board[][26], char input[]);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool availableMoves (char board[][26], int n, char colour);
bool positionInBounds(int n, int row, int col);
bool playerTurn(char board[][26], int n, char move[], char colour);
bool checkValidAndFlip(char board[][26], int row, int col, char colour, int n);
void flipInDirection(char board[][26], int row, int col, int deltaRow, int deltaCol, char colour);
void decideWinner (char board[26][26], int n);
void copyBoard (const char oldBoard[26][26], char newBoard[26][26]);
int makeMove(const char board[26][26], int n, char turn, int *row, int *col);
int moveScore(char board[][26], int row, int col, char turn, int n);
int makeSmarterMove (const char board[26][26], int n, char turn, int *row, int *col);
int smarterMoveScore ( char board[][26], int row, int col, char turn, int n);



// ========= Function implementation ==========

void initializeBoard(char board[][26], int n){
    for (int i = 0; i< 26; i++){
        for (int j = 0; j < 26 ; j++)
            board[i][j] = 'U';
    }
    board[n/2-1][n/2 - 1] = 'W';
    board[n/2][n/2] = 'W';
    board[n/2][n/2 - 1] = 'B';
    board[n/2 - 1][n/2] = 'B';
}
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    //printing the column letters
    printf("  ");
    for ( int k = 0; k < n; k++)
        printf("%c",97+k);
        
    printf("\n");
        
    for (int i = 0; i < n; i++){
        printf("%c ",97+i);//printing the column letters
        for (int j = 0; j < n; j++)
            printf("%c",board[i][j]);//printing board content
        
        printf("\n");
    }
}

void placeTile (char board[][26], char input[]){
    int row, col;
    char color;
    //converting letters input to row/column numbers
    color = input[0];
    row = input[1] - 'a';
    col = input[2] - 'a';
    board[row][col] = color;
}

void  configureBoard(char board[][26], int n){
    printf("Enter board configuration:\n");
    char input[] = "xyz", endInput[] = "!!!";
    while(strcmp(input, endInput) != 0){
        scanf("%s",input);
        placeTile (board, input);
    }
}

bool availableMoves (char board[][26], int n, char colour){
    bool legalMove;
    //looping through each board location
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            
            if (board[row][col] == 'U'){
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++){//looping through all 8 directions
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++, legalMove = false){
                        if (!(deltaCol == deltaRow && deltaCol ==0)){
                            legalMove = checkLegalInDirection( board, n, row, col, colour, deltaRow, deltaCol);
                            if (legalMove){
                                //puts("legal move available");
                                //printf("%c%c\n",row+'a',col+'a');
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool playerTurn(char board[][26], int n, char move[], char colour){
    bool valid;
    int row = move[0] - 'a';
    int col = move[1] - 'a';
    if (positionInBounds(n, row, col))
        valid = checkValidAndFlip( board, row, col, colour, n);

    if (valid)
        return true;
        else return false;
    }

bool checkValidAndFlip(char board[][26], int row, int col, char colour, int n){
    bool legalMove, wasTrue;
    if (board[row][col] == 'U'){
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
            for (int deltaCol = -1; deltaCol <= 1; deltaCol++, legalMove = false){
                if (!(deltaCol == deltaRow && deltaCol ==0)){
                    legalMove = checkLegalInDirection( board, n, row, col, colour, deltaRow, deltaCol);
                    if (legalMove){
                        flipInDirection (board, row, col, deltaRow, deltaCol, colour);
                        wasTrue = legalMove;                        
                    }
                }
            }
        }
    }
    if (wasTrue){//if any direction was legal it returns a boolean 
        wasTrue = false;
        return true;
    }
        return false;
}

void flipInDirection(char board[][26], int row, int col, int deltaRow, int deltaCol, char colour){
    if (board[row][col] == colour){//This is for the case where the location has more than one legal direction
        row +=deltaRow;
        col += deltaCol;
    }
    while(board[row][col] != colour){
        board[row][col] = colour;
        row +=deltaRow;
        col += deltaCol;
    }
}

void decideWinner (char board[26][26], int n) {
    int BCounter = 0, WCounter = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <n; j++) {
            if (board[i][j] == 'B')
                BCounter++;
            if (board[i][j] == 'W')
                WCounter++;
        }
    }
    if (WCounter > BCounter)
        puts("W player wins.");
    else if (BCounter > WCounter)
        puts("B player wins.");
    else puts("Draw!");
}

void copyBoard (const char oldBoard[26][26], char newBoard[26][26]){
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++)
            newBoard[i][j] = oldBoard[i][j];
    }
}

int moveScore(char board[][26], int row, int col, char turn, int n){
    int initialTurnCounter = 0, finalTurnCounter = 0;
    
    for (int cRow = 0; cRow < n; cRow++)//cRow is currentRow
        for (int cCol = 0; cCol < n; cCol++){
            if (board[cRow][cCol] == turn)
                initialTurnCounter++;
        }
                
    checkValidAndFlip(board, row, col, turn, n);
    
    for (int cRow = 0; cRow < n; cRow++)//cRow is currentRow
        for (int cCol = 0; cCol < n; cCol++){
            if (board[cRow][cCol] == turn)
                finalTurnCounter++;
        }
    
    return (finalTurnCounter - initialTurnCounter - 1); 
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    if (row < n && row >= 0 && col < n && col >= 0)
        return true;
    return false;  
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    row += deltaRow;
    col += deltaCol;
        if (board[row][col] == colour)
            return false;
    while (positionInBounds(n, row, col) && board[row][col] != colour && board[row][col] != 'U'){
            row += deltaRow;
            col += deltaCol;
    }

    if (board[row][col] == colour){
        return true;
    }
    else
        return false;
}

int smarterMoveScore( char board[][26], int row, int col, char turn, int n){
    int a = 1, b = 3, c = 6, oppMoves, corner;
    int noOfFlips = moveScore(board, row, col, turn, n);
    char oppColour;
    
    if ((row == col && (row == 0 || row == n - 1)) || (row == 0 && col == n - 1) || (row == n - 1 && col == 0))
        corner = 1;
    
    if (turn == 'W')
        oppColour = 'B';
        else oppColour = 'W';
    oppMoves = moveScore(board, row, col, oppColour, n);
    
    return (a*noOfFlips + b*corner + c/oppMoves);
}

		
int makeMove (const char board[26][26], int n, char turn, int *row, int *col) {	
    bool legalMove = false;	
    char boardCopy[26][26];	
    int tempScore = 0, score = 0;	
    	
    for (int cRow = 0; cRow < n; cRow++)//cRow is currentRow	
        for (int cCol = 0; cCol < n; cCol++){//cCol is curretCol	
            	
            if (board[cRow][cCol] == 'U'){	
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++)	
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++, legalMove = false){	
                        copyBoard(board, boardCopy);	
                        legalMove = checkLegalInDirection( boardCopy, n, cRow, cCol, turn, deltaRow, deltaCol);	
                        if (legalMove){//change score from a function to a part of this code	
                            tempScore = smarterMoveScore(boardCopy, cRow, cCol, turn, n);	
                            if (tempScore > score){	
                                score = tempScore;	
                                *row = cRow; *col = cCol;	
                            }	
                        }	
                    }	
            }	
        }	
    return 0;	
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    //variable declarations and initializations
    char gameBoard[26][26], move[3];
    char turn, computer;
    bool validHumanMove, gameOver, flag;
    int boardDimensions, *row, *col, compRow, compCol;
    row = &compRow; col = &compCol;
    printf("Enter the board dimension: ");
    scanf("%d",&boardDimensions);
    initializeBoard(gameBoard, boardDimensions);
    
    printf("Computer plays (B/W) : ");
    scanf(" %c", &computer);
    
    printBoard(gameBoard, boardDimensions);
    
    turn = 'B';
    //Turn-taking module
    while (availableMoves(gameBoard, boardDimensions, 'W') || availableMoves(gameBoard, boardDimensions, 'B')) {
        
        flag = true;
        if (computer == turn) {
            if (availableMoves(gameBoard, boardDimensions, turn)) {
                makeMove(gameBoard, boardDimensions, turn, row, col);
                checkValidAndFlip(gameBoard, *row, *col, turn, boardDimensions);
                printf("Computer places %c at %c%c.\n", turn, *row + 'a', *col + 'a');
            }
            else {
                flag = false;
                printf("%c player has no valid move.\n",turn);
            }
        }
        if (computer != turn) {
            if (availableMoves(gameBoard, boardDimensions, turn)) {
                printf("Enter move for colour %c (RowCol):", turn);
                scanf("%s",move);
                validHumanMove = playerTurn(gameBoard, boardDimensions, move, turn);
                
                if (!validHumanMove){
                    puts("Invalid move.");
                    printf("%c player wins.\n",computer);
                    gameOver = true;
                    break;
                }
            }
            else {
                printf("%c player has no valid move.\n",turn);
                flag = false;
            }
        }
        if (flag)
            printBoard( gameBoard, boardDimensions);
        //turn changing module
        if (turn == 'B')
            turn = 'W';
            else turn = 'B';
    }
    
    if ((!availableMoves(gameBoard, boardDimensions, 'W') && !availableMoves(gameBoard, boardDimensions, 'B')) && gameOver == false)
        decideWinner (gameBoard, boardDimensions);
    
    return 0;
}
#endif // DO NOT DELETE THIS LINE
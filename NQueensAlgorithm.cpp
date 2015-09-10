/// Algorithm to see how to place a number of queens equivalent to the dimensions of the board (eg. 8 queens for an 8x8 board)
/// without them being able to attack one another.

#include "stdafx.h"
#include <iostream>
#include <vector>

//Define the board size
#define BOARD_SIZE (8)

using namespace std;


/// Function used to display the board in its current state (1 means a queen occupies the space)
void DisplayBoard(int board[BOARD_SIZE][BOARD_SIZE])
{
	//Iterate over all rows and columns and display the current value of the square
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << board[i][j] << " ";
		}
		// Create new row
		cout << endl;
	}
	cout << endl;
}


/// Function used to check the rook style straightline moves, and the bishop style diagonal moves
bool CheckMoves(int board[BOARD_SIZE][BOARD_SIZE], int row, int column)
{
	// Check all horizontal moves to the left of the current column
	// We have not placed any queens to the right yet
	// We also have not placed any queens inthe same column
	for (int i = 0; i < column; i++)
	{
		// If square has attacking queen, return false
		if (board[row][i])
			return false;
	}

	int i,j;
	// Check the diagonal like this "\" from the current square
	for (i = row, j = column; i >= 0 && j >= 0; i--, j--)
	{
		// If square has attacking queen, return false
		if (board[i][j])
			return false;
	}

	// Check the diagonal like this "/" from the current square
	for (i = row, j = column; j >= 0 && i < BOARD_SIZE; i++, j--)
	{
		// If square has attacking queen, return false
		if (board[i][j])
			return false;
	}

	//If move is considered safe from attackers, return true
	return true;
}


/// Recursive function to try and place queens and backtrack if necessary
bool FindSolution(int board[BOARD_SIZE][BOARD_SIZE], int column)
{
	// Last queen was placed, success
	if (column >= BOARD_SIZE)
	{
		return true;
	}

	// Iterate over each row and try to place a queen in this column at that row
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		// See if it is a valid move, free of attackers
		if (CheckMoves(board, i, column))
		{
			// It is safe to move here FOR NOW
			board[i][column] = 1;

			// Recurse over this function to place the next queen
			if (FindSolution(board, column + 1))
				return true;

			//Recurse failed, backtrack and remove the queen from this square
			board[i][column] = 0;
		}
	}

	return false;
}


/// Main function to run the algorithm
int main()
{
	// Initialize empty chess board
	int board[BOARD_SIZE][BOARD_SIZE] = {};

	// Run the algorithm
	if (FindSolution(board, 0))
	{
		// Display the answer
		DisplayBoard(board);
	}
	else
		cout << "No way of placing " << BOARD_SIZE << " queens on the board." << endl;

	getchar();
    return 0;
}


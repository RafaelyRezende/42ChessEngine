
#include "../includes/board.h"
#include "../includes/interface.h"
unsigned char get_piece(t_board *board, int x, int y);

int is_valid_pawn(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	int to_piece = board -> board[to_col][to_row];

	if (from_col == to_col && to_row == from_row)
		return 0;
	else if (board->turn == WHITE)
	{
		if (to_col >= from_col)
			return (0);
		if (from_col - to_col > 2)
			return (0);
		if (to_col == from_col -1 && to_row == from_row && to_piece == EMPTY)
			return (1);
		if (from_col == 6 && to_col == from_col -2 && to_row == from_row && to_piece == EMPTY &&  board->board[from_col - 1][from_row] == EMPTY)
			return (1);
		if (to_col == from_col -1 && (to_row == from_row -1 || to_row == from_row + 1) && to_piece != EMPTY && to_piece > 5)
			return (1);
		return (0);
	}
	else
	{
		if (to_col <= from_col)
			return (0);
		if (to_col - from_col > 2)
			return (0);
		if (to_col == from_col + 1 && to_row == from_row && to_piece == EMPTY)
			return (1);
		if ( from_col == 1 && to_col == from_col + 2 && to_row == from_row && to_piece == EMPTY &&  board->board[from_col + 1][from_row] == EMPTY)
			return (1);
		if (to_col == from_col + 1 && (to_row == from_row -1 || to_row == from_row + 1) && (to_piece & WHITE) == WHITE && to_piece != EMPTY)
			return (1);
		return (0);
	}
}

int is_valid_rook(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	int row_step = 1;
	int col_step = 1;
	int to_piece = board -> board[to_col][to_row];

	if (from_col != to_col && from_row != to_row)
		return (0);
	if (to_row == from_row)
		row_step = 0;
	else if (to_row < from_row)
		row_step = -1;
	if (to_col == from_col)
		col_step = 0;
	else if (to_col < from_col)
		col_step = -1;

	int current_col = from_col + col_step;
	int current_row = from_row + row_step;

	while (current_col != to_col || current_row != to_row)
	{
		if (board -> board[current_col][current_row] != EMPTY)
			break;
		current_col += col_step;
		current_row += row_step;
	}
	if (current_col == to_col && current_row == to_row)
	{
		if ((board->turn == WHITE) && ((to_piece & BLACK) == BLACK || to_piece == EMPTY))
			return (1);
		else if(board->turn == BLACK && ((to_piece & WHITE) == WHITE || to_piece == EMPTY))
			return (1);
	}
	return (0);
}
int is_valid_knight(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	//(2, 5) to (4, 4)

	int to_piece = board -> board[to_col][to_row];
	if (to_col == from_col -2 || to_col == from_col + 2)
	{
		if (to_row == from_row -1 || to_row == from_row + 1 )
		{
			if ((board->turn == WHITE) && ((to_piece & BLACK) == BLACK || to_piece == EMPTY))
				return (1);
			else if(board->turn == BLACK && ((to_piece & WHITE) == WHITE || to_piece == EMPTY))
				return (1);
		}
	}
	if (to_col == from_col -1 || to_col == from_col + 1)
	{
		if (to_row == from_row -2 || to_row == from_row + 2 )
		{
			if ((board->turn == WHITE) && ((to_piece & BLACK) == BLACK || to_piece == EMPTY))
				return (1);
			else if(board->turn == BLACK && ((to_piece & WHITE) == WHITE || to_piece == EMPTY))
				return (1);
		}
	}
	return (0);
}

int is_valid_bishop(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	int i = 1;
	int j = 1;

	int to_piece = board -> board[to_col][to_row];
	if (to_row == from_row || to_col == from_col)
		return (0);
	if ((abs(to_col - from_col)) != abs(to_row - from_row))
		return (0);
	if (to_row < from_row)
		i = -1;
	if (to_col < from_col)
		j = -1;

	int current_col = from_col + j;
	int current_row = from_row + i;

	while (current_col != to_col && current_row != to_row)
	{
		if (board -> board[current_col][current_row] != EMPTY)
			break;
		current_col += j;
		current_row += i;
	}

	if (current_col == to_col && current_row == to_row)
	{
		if ((board->turn == WHITE) && ((to_piece & BLACK) == BLACK || to_piece == EMPTY))
			return (1);
		else if((board->turn == BLACK) && ((to_piece & WHITE) == WHITE || to_piece == EMPTY))
			return (1);
	}
	return (0);

}
//need to account for castle
int is_valid_king(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	int to_piece = board -> board[to_col][to_row];

	//see if moving 2 spaces and the direction

	if (from_row == 4 && to_row == 6 && from_col == 7 && to_col == 7)
	{
		if (board->board[7][7] == (ROOK | WHITE))
		{
			return (1);
		}
		return (0);
	}
	else if (from_row == 4 && to_row == 2 && from_col == 7 && to_col == 7)
	{
		if (board->board[7][0] == (ROOK | WHITE))
		{
				return (1);
		}
		return (0);
	}
	if (from_row == to_row && from_col == to_col)
		return (0);
	if (abs(to_col - from_col) > 1 || abs(to_row - from_row) > 1)
		return (0);
	if (board->turn == WHITE && ((to_piece & BLACK) == BLACK || to_piece == EMPTY))
		return (1);
	else if(board->turn == BLACK && ((to_piece & WHITE) == WHITE || to_piece == EMPTY))
		return (1);
	return (0);
}

int is_valid_queen(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	if (is_valid_bishop(board, from_col, from_row, to_col, to_row))
		return (1);
	else if (is_valid_rook(board, from_col, from_row, to_col, to_row))
		return (1);
	return (0);
}

int is_in_check (t_board *board)
{
	int col, row;
	if (board->turn == WHITE)
	{
		 row = board->black_king_pos[0];
		 col = board->black_king_pos[1];
	}
	else
	{
		 row = board->white_king_pos[0];
		 col = board->white_king_pos[1];
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == col && j == row)
				continue;
			if (is_valid_move(board, j, i, col, row))
			{
				fprintf(stderr, " is in check from %d, %d\n", i, j);
				if ((get_piece(board, i, j) & PAWN) == PAWN)
				{
					fprintf(stderr, "Piece is a pawn\n");
				}
				else if ((get_piece(board, i, j	) & ROOK) == ROOK)
				{
					fprintf(stderr, "Piece is a rook\n");
				}
				else if ((get_piece(board, i, j) & KNIGHT) == KNIGHT)
				{
					fprintf(stderr, "Piece is a knight\n");
				}
				else if ((get_piece(board, i, j) & BISHOP) == BISHOP)
				{
					fprintf(stderr, "Piece is a bishop\n");
				}
				else if ((get_piece(board, i, j) & QUEEN) == QUEEN)
				{
					fprintf(stderr, "Piece is a queen\n");
				}
				else if ((get_piece(board, i, j) & KING) == KING)
				{
					fprintf(stderr, "Piece is a king\n");
				}
				return (1);
			}
		}
	}
	return (0);
}

int is_valid_move(t_board *board, int from_col, int from_row, int to_col, int to_row)
{
	int piece = get_piece(board, from_row, from_col);
	if (piece == EMPTY)
		return (0);
	if ((piece & WHITE) == WHITE && board->turn == BLACK)
		return (0);
	if ((piece & BLACK) == BLACK 	&& board->turn == WHITE)
		return (0);
	// FIRST TWO BITS ARE COLORS LAST SIX ARE PIECE TYPES

	switch (piece & 0b00111111)
	{
		case PAWN:
			return is_valid_pawn(board, from_col, from_row, to_col, to_row);
			break;
		case ROOK:
			return is_valid_rook(board, from_col, from_row, to_col, to_row);
			break;
		case KNIGHT:
			return is_valid_knight(board, from_col, from_row, to_col, to_row);
			break;
		case BISHOP:
			return is_valid_bishop(board, from_col, from_row, to_col, to_row);
			break;
		case QUEEN:
			return is_valid_queen(board, from_col, from_row, to_col, to_row);
		case KING:
			return is_valid_king(board, from_col, from_row, to_col, to_row);
			break;
		default:
			return 0;
	}
	return (0);
}


#include "../../includes/interface.h"

unsigned char get_piece(t_board *board, int x, int y)
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return EMPTY;

	return board->board[y][x];
}

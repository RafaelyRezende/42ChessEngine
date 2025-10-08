/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
/* ************************************************************************** */

#include "../../includes/interface.h"

char *stringjoin(char *s1, char *s2);

int mouse_hook(int button, int x, int y, t_interface *interface)
{
	char piece;
	char move[5] = {0}; //
	char *stockmove = NULL;
	piece = get_piece(interface->board, x / 64, y / 64);
	int mouse_x = x / 64;
	int mouse_y = y / 64;

	if (mouse_x < 0 || mouse_x >= 8 || mouse_y < 0 || mouse_y >= 8)
		return (0);
	// if (button == 3)
	// {
	// 	if (interface->board->turn == WHITE)
	// 	{
	// 		interface->board->turn = BLACK;
	// 	}
	// 	else
	// 	{
	// 		interface->board->turn = WHITE;
	// 	}
	// 	interface->selected_piece[0] = -1;
	// 	interface->selected_piece[1] = -1;

	// }
	if (button == 1) // Left mouse button
	{
		if (interface->board->turn == WHITE)
		{
			if (IS_WHITE(piece))
			{
				if (interface->selected_piece[0] == mouse_x && interface->selected_piece[1] == mouse_y)
				{
					interface->selected_piece[0] = -1;
					interface->selected_piece[1] = -1;
					interface->mouse_pressed = 0;
				}
				else
				{
					interface->selected_piece[0] = mouse_x;
					interface->selected_piece[1] = mouse_y;
					interface->mouse_pressed = 1;
				}
			}
			else if (interface->selected_piece[0] != -1 && is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], mouse_y, mouse_x))
			{
				char from_piece = get_piece(interface->board, interface->selected_piece[0], interface->selected_piece[1]);
				char to_piece = get_piece(interface->board, mouse_x, mouse_y);
				interface->mouse_pressed = 0;
				interface->board->board[mouse_y][mouse_x] = from_piece;
				interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = EMPTY;

				if ((from_piece & KING) == KING)
				{
					fprintf(stderr, "Moving white king to %d, %d\n", mouse_x, mouse_y);
					interface->board->white_king_pos[0] = mouse_x;
					interface->board->white_king_pos[1] = mouse_y;
					if (interface->selected_piece[0] == 4 && mouse_x == 6 && mouse_y == 7)
					{
			
						if (interface->board->board[7][7] == (ROOK | WHITE))
						{
							interface->board->board[7][7] = EMPTY;
							interface->board->board[7][5] = (ROOK | WHITE);
						}
					}
					else if (interface->selected_piece[0] == 4 && mouse_x == 2 && mouse_y == 7)
					{
						if (interface->board->board[7][0] == (ROOK | WHITE))
						{
							interface->board->board[7][0] = EMPTY;
							interface->board->board[7][3] = (ROOK | WHITE);
						}
					}
				}
				interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
				if (is_in_check(interface->board))
				{
					interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = from_piece;
					interface->board->board[mouse_y][mouse_x] = to_piece;
					if ((from_piece & KING) == KING)
					{
						fprintf(stderr, "Moving white king to %d, %d\n", mouse_x, mouse_y);
						interface->board->white_king_pos[0] = interface->selected_piece[0];
						interface->board->white_king_pos[1] = interface->selected_piece[1];
					}
					interface->selected_piece[0] = -1;
					interface->selected_piece[1] = -1;
					interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
					fprintf(stderr, "Invalid move: King is in check.\n");
					return (0);
				}
				else
				{
					move[0] = interface->selected_piece[0] + 'a';
					move[1] = 8 - interface->selected_piece[1] + '0';
					move[2] = mouse_x + 'a';
					move[3] = 8 - mouse_y + '0';
					move[4] = '\0';
					if (interface->moves == NULL || interface->moves[0] == '\0')
						interface->moves = strdup(move);
					else {
						char *tmp = stringjoin(interface->moves, " ");
						free(interface->moves);
						interface->moves = stringjoin(tmp, move);
						free(tmp);
					}
				}
				interface->selected_piece[0] = -1;
				interface->selected_piece[1] = -1;
			}
		}
		if (interface->board->turn == BLACK)
		{
			stockmove = communicate_with_stockfish(interface->moves);
			if (stockmove)
			{
				//move piece manually on board
				fprintf(stderr, "Stockfish plays: %s\n", stockmove);
				int from_col = stockmove[0] - 'a';
				int from_row = 8 - (stockmove[1] - '0');
				int to_col = stockmove[2] - 'a';
				int to_row = 8 - (stockmove[3] - '0');
				char from_piece = get_piece(interface->board, from_col, from_row);
				interface->board->board[to_row][to_col] = from_piece;
				interface->board->board[from_row][from_col] = EMPTY;
				if (strlen(stockmove) == 5)
				{
    				char promo = stockmove[4]; //promotion checker
    				if (promo == 'q')
        				interface->board->board[to_row][to_col] = (QUEEN | BLACK);
   	 				else if (promo == 'r')
        				interface->board->board[to_row][to_col] = (ROOK | BLACK);
    				else if (promo == 'b')
        				interface->board->board[to_row][to_col] = (BISHOP | BLACK);
    				else if (promo == 'n')
        				interface->board->board[to_row][to_col] = (KNIGHT | BLACK);
				}
				if ((from_piece & KING) == KING)
				{
					if (from_col == 4 && to_col == 6 && from_row == to_row)
					{
			
						if (interface->board->board[0][7] == (ROOK | BLACK))
						{
							interface->board->board[0][7] = EMPTY;
							interface->board->board[0][5] = (ROOK | BLACK);
						}
					}
					else if (from_col == 4 && to_col == 2 && from_row == to_row)
					{
						if (interface->board->board[0][0] == (ROOK | BLACK))
						{
							interface->board->board[0][0] = EMPTY;
							interface->board->board[0][3] = (ROOK | BLACK);
						}
					}
					{

					}
					fprintf(stderr, "Moving black king to %d, %d\n", to_col, to_row);
					interface->board->black_king_pos[0] = to_col;
					interface->board->black_king_pos[1] = to_row;
				}
				interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
				if (interface->moves == NULL || interface->moves[0] == '\0')
					interface->moves = strdup(stockmove);
				else {
					char *tmp = stringjoin(interface->moves, " ");
					free(interface->moves);
					interface->moves = stringjoin(tmp, stockmove);
					free(tmp);
				}
				free(stockmove);
			}
		}
	}

	printf("Current moves: %s\n", interface->moves);
	// 	if (interface->board->turn == BLACK)pri

	// 		else if (interface->selected_piece[0] != -1 && is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], mouse_y, mouse_x))
	// 		{
	// 			char from_piece = get_piece(interface->board, interface->selected_piece[0], interface->selected_piece[1]);
	// 			char to_piece = get_piece(interface->board, mouse_x, mouse_y);
	// 			interface->mouse_pressed = 0;
	// 			interface->board->board[mouse_y][mouse_x] = from_piece;
	// 			interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = EMPTY;

	// 			if ((from_piece & KING) == KING)
	// 			{
	// 				interface->board->black_king_pos[0] = mouse_x;
	// 				interface->board->black_king_pos[1] = mouse_y;
	// 			}
	// 			interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
	// 			if (is_in_check(interface->board))
	// 			{
	// 				interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = from_piece;
	// 				interface->board->board[mouse_y][mouse_x] = to_piece;
	// 				if ((from_piece & KING) == KING)
	// 				{
	// 					fprintf(stderr, "Moving white king to %d, %d\n", mouse_x, mouse_y);
	// 					interface->board->black_king_pos[0] = interface->selected_piece[0];
	// 					interface->board->black_king_pos[1] = interface->selected_piece[1];
	// 				}
	// 				interface->selected_piece[0] = -1;
	// 				interface->selected_piece[1] = -1;
	// 				interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
	// 				fprintf(stderr, "Invalid move: King is in check.\n");
	// 				return (0);
	// 			}

	// 			interface->selected_piece[0] = -1;
	// 			interface->selected_piece[1] = -1;
	// 		}
	// 	}

	// }

	return (0);
}


void run_chess(t_board *board)
{
	t_interface interface;
	interface.moves = NULL;

	interface.board = board;
	interface.index_lookup = malloc(64 * sizeof(unsigned char));
	if (!interface.index_lookup)
	{
		fprintf(stderr, "Error allocating memory for index lookup.\n");
		exit(EXIT_FAILURE);
	}
	interface.mouse_pressed = 0;
	interface.index_lookup[PAWN] = 0;
	interface.index_lookup[ROOK] = 1;
	interface.index_lookup[KNIGHT] = 2;
	interface.index_lookup[BISHOP] = 3;
	interface.index_lookup[QUEEN] = 4;
	interface.index_lookup[KING] = 5;

	interface.selected_piece[0] = -1;
	interface.selected_piece[1] = -1;

	init_window(&interface);
	get_textures(&interface);
	mlx_hook(interface.win_ptr, DestroyNotify, (1L<<17), free_displays, &interface);
	mlx_mouse_hook(interface.win_ptr, mouse_hook, &interface);
	mlx_loop_hook(interface.mlx_ptr, interface_loop, &interface);
	mlx_loop(interface.mlx_ptr);
}





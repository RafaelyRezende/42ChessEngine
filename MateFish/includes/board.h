/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 21:46:28 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/09/20 21:51:51 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
#define BOARD_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>



# define	EMPTY	  0b00000000
# define	PAWN	  0b00000001
# define	ROOK	  0b00000010
# define	KNIGHT	0b00000100
# define	BISHOP	0b00001000
# define	QUEEN	  0b00010000
# define	KING	  0b00100000

# define RED     "\033[31m"
# define YELLOW  "\033[33m"
# define GREEN   "\033[32m"
# define CYAN    "\033[36m"
# define RST   "\033[0m"

# define	BLACK	0b01000000
# define	WHITE	0b10000000


# define WHITE_PAWN_CHAR 	"♟"
# define BLACK_PAWN_CHAR 	"♙"
# define BLACK_ROOK_CHAR 	"♖"
# define WHITE_ROOK_CHAR 	"♜"
# define BLACK_KNIGHT_CHAR 	"♘"
# define WHITE_KNIGHT_CHAR 	"♞"
# define BLACK_BISHOP_CHAR 	"♗"
# define WHITE_BISHOP_CHAR 	"♝"
# define BLACK_QUEEN_CHAR 	"♕"
# define WHITE_QUEEN_CHAR 	"♛"
# define BLACK_KING_CHAR 	"♔"
# define WHITE_KING_CHAR 	"♚"
# define WHITE_EMPTY_CHAR 	"#"
# define BLACK_EMPTY_CHAR 	"*"

# define BLACK_PIECES	(BLACK | PAWN | ROOK | KNIGHT | BISHOP | QUEEN | KING)
# define WHITE_PIECES	(WHITE | PAWN | ROOK | KNIGHT | BISHOP | QUEEN | KING)

# define IS_BLACK(piece)	((piece) & BLACK)
# define IS_WHITE(piece)	((piece) & WHITE)
//INVERTA ISSO

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define HELP_VISUAL "\nFor visual mode use: ./autoMate\n"
# define HELP_DEBUG "for debug mode use: ./autoMate --debug\n"


typedef struct
{
	int turn;
	unsigned char board[8][8];
	unsigned char white_king_pos[2]; // [col, row] position of the king
	unsigned char black_king_pos[2]; // [col, row] position of the king
}	t_board;

#endif


//function prototypes

//moves
int is_valid_move(t_board *board, int from_col, int from_row, int to_col, int to_row);
void run_chess(t_board *board);

#include "../includes/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


void initialize_board(t_board *board)
{
	board->turn = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board->board[i][j] = 0;
		}
	}

	board->turn = WHITE;

	board->board[0][0] = ROOK | BLACK;
	board->board[0][1] = KNIGHT | BLACK;
	board->board[0][2] = BISHOP | BLACK;
	board->board[0][3] = QUEEN | BLACK;
	board->board[0][4] = KING | BLACK;
	board->board[0][5] = BISHOP | BLACK;
	board->board[0][6] = KNIGHT | BLACK;
	board->board[0][7] = ROOK | BLACK;
	for (int i = 0; i < 8; i++)
		board->board[1][i] = PAWN | BLACK;

	board->board[7][0] = ROOK | WHITE;
	board->board[7][1] = KNIGHT | WHITE;
	board->board[7][2] = BISHOP | WHITE;
	board->board[7][3] = QUEEN | WHITE;
	board->board[7][4] = KING | WHITE;
	board->board[7][5] = BISHOP | WHITE;
	board->board[7][6] = KNIGHT | WHITE;
	board->board[7][7] = ROOK | WHITE;
	for (int i = 0; i < 8; i++)
		board->board[6][i] = PAWN | WHITE;
}

void print_board(const t_board *board)
{
	int column = 0;
	while (column < 8)
	{
		int row_pos = 0;
		printf("%d ", 8 - column);
		while (row_pos < 8)
		{
			 if (board->board[column][row_pos] != EMPTY)
			 {
			 	if (board->board[column][row_pos] == (PAWN | BLACK))
				{
					printf("%s", BLACK_PAWN_CHAR);
				}
				else if (board->board[column][row_pos] == (ROOK | BLACK))
				{
					printf("%s", BLACK_ROOK_CHAR);
				}
				else if (board->board[column][row_pos] == (KNIGHT | BLACK))
				{
					printf("%s", BLACK_KNIGHT_CHAR);
				}
				else if (board->board[column][row_pos] == (BISHOP | BLACK))
				{
					printf("%s", BLACK_BISHOP_CHAR);
				}
				else if (board->board[column][row_pos] == (QUEEN | BLACK))
				{
					printf("%s", BLACK_QUEEN_CHAR);
				}
				else if (board->board[column][row_pos] == (KING | BLACK))
				{
					printf("%s", BLACK_KING_CHAR);
				}
				else if (board->board[column][row_pos] == (PAWN | WHITE))
				{
					printf("%s", WHITE_PAWN_CHAR);
				}
				else if (board->board[column][row_pos] == (ROOK | WHITE))
				{
					printf("%s", WHITE_ROOK_CHAR);
				}
				else if (board->board[column][row_pos] == (KNIGHT | WHITE))
				{
					printf("%s", WHITE_KNIGHT_CHAR);
				}
				else if (board->board[column][row_pos] == (BISHOP | WHITE))
				{
					printf("%s", WHITE_BISHOP_CHAR);
				}
				else if (board->board[column][row_pos] == (QUEEN | WHITE))
				{
					printf("%s", WHITE_QUEEN_CHAR);
				}
				else if (board->board[column][row_pos] == (KING | WHITE))
				{
					printf("%s", WHITE_KING_CHAR);
				}
			 }
			else if ((column + row_pos) % 2 == 0)
			{
				printf("%s", "#");
			}
			else
			{
				printf("%s", "*");
			}
			if (row_pos < 7)
				printf(" ");

			row_pos++;
		}
		printf("\n");
		if (column == 7)
			printf("  a b c d e f g h\n");
		column++;
	}
}

int move_piece(t_board *board, char *move)
{
	if (strlen(move) != 4)
	{
		fprintf(stderr, "Invalid move format. Use 'e2e4' format.\n");
		return -1;
	}

	int start_row = move[0] - 'a';
	int start_col = 8 - (move[1] - '0');
	int end_row = move[2] - 'a';
	int end_col = 8 - (move[3] - '0');
	if (start_col < 0 || start_col > 7 || start_row < 0 || start_row > 7 ||
		end_col < 0 || end_col > 7 || end_row < 0 || end_row > 7)
	{		fprintf(stderr, "Move out of bounds.\n");
		return -1;
	}
	int piece = board->board[start_col][start_row];
	if (piece == EMPTY)
	{
		fprintf(stderr, "No piece at starting position.\n");
		return -1;
	}
	if ((piece & WHITE) && board->turn == BLACK)
	{
		fprintf(stderr, "It's not your turn.\n");
		return -1;
	}
	if ((piece & BLACK) && board->turn == WHITE)
	{
		fprintf(stderr, "It's not your turn.\n");
		return -1;
	}
	if (!is_valid_move(board, start_col, start_row, end_col, end_row))
	{
		fprintf(stderr, "Invalid move for the piece.\n");
		return -1;
	}
	board->board[end_col][end_row] = piece;
	board->board[start_col][start_row] = EMPTY;
	board->turn = (board->turn == WHITE) ? BLACK : WHITE;

	return 0;
}

char *stringjoin(char *s1, char *s2)
{
	int totallen = 0;
	if (!s1)
	{
		totallen = strlen(s2);
	}
	else
	{
		totallen = strlen(s1) + strlen(s2);
	}
	char *result = malloc(totallen + 1);
	if (!result)
		return NULL;
	if (s1)
		strcpy(result, s1);
	if (s2)
		strcpy(result + (s1 ? strlen(s1) : 0), s2);
	return result;
}
void open_stockfish()
{
	int pipe_stdin[2];
	int pipe_stdout[2];
	if (pipe(pipe_stdin) == -1 || pipe(pipe_stdout) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// Child process
		close(pipe_stdin[1]);
		close(pipe_stdout[0]);
		dup2(pipe_stdin[0], STDIN_FILENO);
		dup2(pipe_stdout[1], STDOUT_FILENO);
		execlp("./stockfish", "./stockfish", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	close(pipe_stdin[0]);
	close(pipe_stdout[1]);
}

void send_command_to_stockfish(const char *command, int write_fd)
{
	write(write_fd, command, strlen(command));
	write(write_fd, "\n", 1);
}

void handshake(int read_fd)
{
	char buffer[1024];
	read(read_fd, buffer, sizeof(buffer));
}

void close_stockfish(int read_fd, int write_fd)
{
	close(read_fd);
	close(write_fd);
}

//do the connection uci, ready, position, go, return bestmove such as e7e5
char *communicate_with_stockfish(char *moves)
{
    int pipe_stdin[2];
    int pipe_stdout[2];
    if (pipe(pipe_stdin) == -1 || pipe(pipe_stdout) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Child process
        close(pipe_stdin[1]);
        close(pipe_stdout[0]);
        dup2(pipe_stdin[0], STDIN_FILENO);
        dup2(pipe_stdout[1], STDOUT_FILENO);
        execlp("./stockfish", "./stockfish", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    close(pipe_stdin[0]);
    close(pipe_stdout[1]);

    send_command_to_stockfish("uci", pipe_stdin[1]);
    handshake(pipe_stdout[0]);
    send_command_to_stockfish("isready", pipe_stdin[1]);
    handshake(pipe_stdout[0]);
    char pos_cmd[4096];
    if (moves && strlen(moves) > 0)
        snprintf(pos_cmd, sizeof(pos_cmd), "position startpos moves %s", moves);
    else
        snprintf(pos_cmd, sizeof(pos_cmd), "position startpos");
    send_command_to_stockfish(pos_cmd, pipe_stdin[1]);
	send_command_to_stockfish(pos_cmd, pipe_stdin[1]);
    send_command_to_stockfish("go depth 1", pipe_stdin[1]);

    char line[512];
    char *move = NULL;
    FILE *fp = fdopen(pipe_stdout[0], "r");
    if (!fp) {
        perror("fdopen");
        close_stockfish(pipe_stdout[0], pipe_stdin[1]);
        return strdup("");
    }
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        if (strncmp(line, "bestmove ", 9) == 0) {
            char *bestmove = line + 9;
            char *end = strchr(bestmove, ' ');
            if (end)
                *end = '\0';
            move = strdup(bestmove);
            printf("Stockfish bestmove: %s\n", move);
            break;
        }
    }
    if (!move) {
        fprintf(stderr, "Failed to get bestmove from Stockfish.\n");
        move = strdup("");
    }
    fclose(fp);
    close(pipe_stdin[1]);
    return move;
}

//implem
int	terminal_chess(t_board *board)
{
	 print_board(board);
	 char *moves = NULL;
	 char move[6];
	 char *movestock;
	 int bytesread = 0;
	 while (1)
	 {
	 	if (board->turn == WHITE)
	 		printf("White's turn.\n");
	 	else
	 		printf("Black's turn.\n");
	 	if (board->turn == BLACK)
	 	{
	 		movestock = communicate_with_stockfish(moves);
	 		printf("Stockfish plays: %s\n\n", movestock);
	 		move_piece(board, movestock);
	 		if (moves == NULL || moves[0] == '\0')
                 moves = strdup(movestock);
             else {
                 char *tmp = stringjoin(moves, " ");
                 free(moves);
                 moves = stringjoin(tmp, movestock);
                 free(tmp);
             }
	 		free(movestock);
	 		print_board(board);
	 		continue;
	 	}
	 	else
	 	{
	 		printf("Enter your move: \n");
	 		memset(move, 0, sizeof(move));
	 		bytesread = read(0, move, 5);
	 		if (bytesread == -1)
	 		{
	 			perror("read");
	 			return (1);
	 		}
	 	}
	 	if (bytesread > 0 && move[bytesread - 1] == '\n')
	 		move[bytesread - 1] = '\0';
	 	else
	 		move[bytesread] = '\0';
	 	printf("You entered: %s\n\n", move);
	 	move_piece(board, move);
	 	if (moves == NULL || moves[0] == '\0')
             moves = strdup(move);
         else {
             char *tmp = stringjoin(moves, " ");
             free(moves);
             moves = stringjoin(tmp, move);
             free(tmp);
         }
	 	print_board(board);
	  }
}

//ents this on the actual game to play as black*/
int	main(int ac, char **av)
{
	t_board board;
	initialize_board(&board);
	if (ac == 2 && !strcmp(av[1], "--debug"))
		terminal_chess(&board);
	else if (ac == 2 && !strcmp(av[1], "--help"))
			printf("%s%s%s%s", RED, HELP_VISUAL, HELP_DEBUG, RST);
	else if (ac == 1)
		run_chess(&board);
	else
		printf("%sError!%s\n", RED, RST);
	return (0);
}

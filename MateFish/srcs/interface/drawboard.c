#include "../../includes/interface.h"

void drawboard(t_interface *interface, t_board *board)
{
	int x = 0;
	int y = 0;
	int color;

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			if ((x + y) % 2 == 0)
				color = 0xeeeed2;
			else
				color = 0x769656;
			drawrect(&interface->image, (t_point){x * 64, y * 64}, (t_point){64, 64}, color);
			unsigned char piece = board->board[y][x];
			if (piece != EMPTY)
			{
				t_image *texture;
				if (IS_WHITE(piece))
					texture = &interface->white_pieces[interface->index_lookup[piece & 0b00111111]];
				else
					texture = &interface->black_pieces[interface->index_lookup[piece & 0b00111111]];
				if (x == interface->selected_piece[0] && y == interface->selected_piece[1])
				{
					continue;
				}
				else
					drawtexture(interface, (t_point){(x * 64) + 5, (y * 64) + 5}, texture, 1.25);
			}
		}
	}
	int mouse_x = interface->mouse_x / 64;
	int mouse_y = interface->mouse_y / 64;
	char piece = get_piece(interface->board, mouse_x, mouse_y);
	if (interface->board->turn == WHITE)
	{
		if (interface->selected_piece[0] == -1)
		{
			if (IS_WHITE(piece))
			{
				drawborder(&interface->image, (t_point){mouse_x * 64, mouse_y * 64}, (t_point){64, 64}, 0x00FF00);
			}
		}
		else
		{
			drawborder(&interface->image, (t_point){interface->selected_piece[0] * 64, interface->selected_piece[1] * 64}, (t_point){64, 64}, 0x0000FF);
			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					if (is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], y, x))
					{
						drawborder(&interface->image, (t_point){x * 64, y * 64}, (t_point){64, 64}, 0xFF0000);
					}
				}
			}
		}
	}
	else
	{
		if (interface->selected_piece[0] == -1)
		{
			if (IS_BLACK(piece))
			{
				drawborder(&interface->image, (t_point){mouse_x * 64, mouse_y * 64}, (t_point){64, 64}, 0x0000ff);
			}
		}
		else
		{
			drawborder(&interface->image, (t_point){interface->selected_piece[0] * 64, interface->selected_piece[1] * 64}, (t_point){64, 64}, 0x0000FF);
			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					if (is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], y, x))
					{

						drawborder(&interface->image, (t_point){x * 64, y * 64}, (t_point){64, 64}, 0xFF0000);
					}
				}
			}
		}

	}
	if (interface->selected_piece[0] != -1 )
	{
		int mouse_x;
		int mouse_y;

		get_mouse_pos(interface, &mouse_x, &mouse_y);
		piece = get_piece(interface->board, interface->selected_piece[0], interface->selected_piece[1]);
		t_image *texture;
		if (IS_WHITE(piece))
			texture = &interface->white_pieces[interface->index_lookup[piece & 0b00111111]];
		else
			texture = &interface->black_pieces[interface->index_lookup[piece & 0b00111111]];

		drawtexture(interface, (t_point){(mouse_x  - 32 - 5), (mouse_y  - 32) - 5}, texture, 1.4);
	}
}

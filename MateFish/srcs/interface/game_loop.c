/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/08 18:42:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/interface.h"

void	drawtext(t_interface *interface)
{
	mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 10, 0xFFFFFF, "Turn: ");
	if (interface->board->turn == WHITE)
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 30, 0xFFFFFF, "White");
	else
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 30, 0xFFFFFF, "Black");

	if (interface->selected_piece[0] != -1)
	{
		char text[50];
		sprintf(text, "Selected Piece: %c, %d", interface->selected_piece[0] + 'a', 8 - interface->selected_piece[1]);
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 50, 0xFFFFFF, text);
	}
	else
	{
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 50, 0xFFFFFF, "No Piece Selected");
	}
}

int	update(t_interface *interface)
{
	calculate_Delta(interface);
	mlx_mouse_get_pos(interface->mlx_ptr, interface->win_ptr, &interface->mouse_x, &interface->mouse_y);




	return (1);
}

int	renderer(t_interface *interface)
{
	memset(interface->image.addr, 0, SCREEN_SIZE_X * SCREEN_SIZE_Y * (interface->image.bits_per_pixel / 8));
	drawtext(interface);
	drawboard(interface, interface->board);


	mlx_put_image_to_window(interface->mlx_ptr, interface->win_ptr, interface->image.img, 0, 0);
	drawtext(interface);
	return (1);
}

int	interface_loop(t_interface *interface)
{
	update(interface);
	renderer(interface);
	return (1);
}

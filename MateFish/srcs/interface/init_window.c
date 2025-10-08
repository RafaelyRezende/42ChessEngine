/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:26:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:08:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/interface.h"

void	init_window(t_interface *interface)
{
	interface->mlx_ptr = mlx_init();
	if (!interface->mlx_ptr)
	{
		fprintf(stderr, "Error initializing MLX.\n");
		exit(EXIT_FAILURE);
	}

	interface->win_ptr = mlx_new_window(interface->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y, "Chess Game");
	if (!interface->win_ptr)
	{
		fprintf(stderr, "Error creating window.\n");
		exit(EXIT_FAILURE);
	}

	interface->last_frame_time = get_time();
	interface->started = 0;
}

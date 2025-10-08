/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_displays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:41:42 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:08:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/interface.h"



int	free_displays(t_interface *interface)
{
	mlx_loop_end((*interface).mlx_ptr);
	mlx_destroy_window((*interface).mlx_ptr, (*interface).win_ptr);
	free((*interface).mlx_ptr);
	printf("Closing Application!");
	exit(1);
	return (0);
}

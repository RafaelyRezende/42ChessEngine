/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/07/06 22:51:17 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/interface.h"

int	ft_load_images(t_interface *interface, t_image *image, char *name);

void get_textures(t_interface *interface)
{
	interface->image.img = mlx_new_image(interface->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	if (!interface->image.img)
	{
		fprintf(stderr, "Error creating image.\n");
		exit(EXIT_FAILURE);
	}
	interface->image.addr = mlx_get_data_addr(interface->image.img, &interface->image.bits_per_pixel,
			&interface->image.line_length, &interface->image.endian);


	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[PAWN]], "./assets/white_pawn.xpm");
	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[ROOK]], "./assets/white_rook.xpm");
	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[KNIGHT]], "./assets/white_knight.xpm");
	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[BISHOP]], "./assets/white_bishop.xpm");
	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[QUEEN]], "./assets/white_queen.xpm");
	ft_load_images(interface, &interface->white_pieces[interface->index_lookup[KING]], "./assets/white_king.xpm"	);

	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[PAWN]], "./assets/black_pawn.xpm");
	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[ROOK]], "./assets/black_rook.xpm");
	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[KNIGHT]], "./assets/black_knight.xpm");
	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[BISHOP]], "./assets/black_bishop.xpm");
	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[QUEEN]], "./assets/black_queen.xpm");
	ft_load_images(interface, &interface->black_pieces[interface->index_lookup[KING]], "./assets/black_king.xpm");


}
int	ft_load_images(t_interface *interface, t_image *image, char *name)
{
	image->img = mlx_xpm_file_to_image(interface->mlx_ptr, name, &image->x, &image->y);
	if (!image->img)
	{
		fprintf(stderr, "Error loading image: %s\n", name);
		exit(EXIT_FAILURE);
	}
	image->addr = mlx_get_data_addr(image->img, \
			&image->bits_per_pixel, &image->line_length, &image->endian);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:35:18 by ssian             #+#    #+#             */
/*   Updated: 2024/11/06 21:35:21 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/*calculate the actual pixel location and color it*/
void	my_mlx_pixel_put(t_image *t_img, int x, int y, int color)
{
	char	*pixel;

	pixel = t_img->addr + ((y * t_img->line_len) + (x * (t_img->bpp / 8)));
	*(unsigned int *)pixel = color;
}

/* load wall texture from file */
t_texture load_texture(void *mlx, char *file_path) 
{
    t_texture texture;

    ft_bzero(&texture, sizeof(t_texture));
    texture.img = mlx_xpm_file_to_image(mlx, (char *)file_path, &texture.width, &texture.height);
    if (!texture.img) 
	{
        printf("Failed to load texture: %s\n", file_path);
        //exit(1);
		//texture = NULL;
    }

    // Get the image data address
    texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_length, &texture.endian);
    return texture;
}
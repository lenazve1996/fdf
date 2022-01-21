/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_creation_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:56:11 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/21 13:00:44 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_fill_window(char **map, t_data *data)
{
	char	symb;

	data->tmp_str = 0;
	while (map[data->tmp_str] != NULL)
	{
		data->tmp_c = 0;
		while (map[data->tmp_str][data->tmp_c] != '\0')
		{
			symb = map[data->tmp_str][data->tmp_c];
			if (ft_put_image(symb, data) == 1)
				return (1);
			data->tmp_c++;
		}
		data->tmp_str++;
	}
	return (0);
}

static int	ft_imgs_creation(t_data *data, int *h, int *w)
{
	data->wall = mlx_xpm_file_to_image(data->ml, "./xpm/tree.xpm", h, w);
	data->fond = mlx_xpm_file_to_image(data->ml, "./xpm/paper.xpm", h, w);
	data->harry = mlx_xpm_file_to_image(data->ml, "./xpm/harry.xpm", h, w);
	data->ex = mlx_xpm_file_to_image(data->ml, "./xpm/exit.xpm", h, w);
	data->plr = mlx_xpm_file_to_image(data->ml, "./xpm/dem2.xpm", h, w);
	data->enemy = mlx_xpm_file_to_image(data->ml, "./xpm/phoenix.xpm", h, w);
	data->enemy2 = mlx_xpm_file_to_image(data->ml, "./xpm/phoenix2.xpm", h, w);
	data->enemy3 = mlx_xpm_file_to_image(data->ml, "./xpm/phoenix3.xpm", h, w);
	if (data->wall == NULL || data->fond == NULL || data->harry == NULL || \
	data->ex == NULL || data->plr == NULL || data->enemy == NULL)
		return (ft_putstr_fd_ret("Error\nmlx_xpm_file_to_image failed\n", 2));
	return (0);
}

int	ft_win_and_img_creation(t_data *data)
{
	int	*h;
	int	*w;

	h = &data->im_hei;
	w = &data->im_wid;
	data->ml = mlx_init();
	if (!data->ml)
		return (ft_putstr_fd_ret("Error\nFailed to set up the connection", 2));
	if (ft_imgs_creation(data, h, w) == 1)
		return (1);
	data->wn = mlx_new_window(data->ml, data->map_width * data->im_wid, \
	data->map_height * data->im_hei, "so_long");
	if (!data->wn)
	{
		perror("Failed to open a new window");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:58:53 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/20 12:22:11 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_img_to_fond(t_data *data, void *character, int x, int y)
{
	mlx_put_image_to_window(data->ml, data->wn, data->fond, x, y);
	mlx_put_image_to_window(data->ml, data->wn, character, x, y);
}

static int	ft_put_images_to_background(t_data *data, char symbol)
{
	t_img	*new_elem;
	char	*character;
	int		x;
	int		y;

	x = data->tmp_c * data->im_wid;
	y = data->tmp_str * data->im_hei;
	mlx_put_image_to_window(data->ml, data->wn, data->fond, x, y);
	if (symbol == 'P')
		character = data->plr;
	else if (symbol == 'E')
		character = data->ex;
	else if (symbol == 'C')
		character = data->harry;
	else
		character = data->enemy;
	mlx_put_image_to_window(data->ml, data->wn, character, x, y);
	new_elem = ft_lstnew(character, x, y);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(&data->images, new_elem);
	return (0);
}

static int	ft_put_background(t_data *data)
{
	t_img	*new_elem;

	mlx_put_image_to_window(data->ml, data->wn, data->fond, \
	data->tmp_c * data->im_wid, data->tmp_str * data->im_hei);
	new_elem = ft_lstnew(data->fond, data->tmp_c * data->im_wid, \
	data->tmp_str * data->im_hei);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(&data->images, new_elem);
	return (0);
}

static int	ft_put_walls(int s, int c, t_data *data)
{
	t_img	*new_elem;
	int		x;
	int		y;

	x = c * data->im_wid;
	y = s * data->im_hei;
	ft_put_img_to_fond(data, data->wall, x, y);
	if (s == 0 && c == 0)
	{
		data->images = ft_lstnew(data->wall, x, y);
		if (data->images == NULL)
			return (1);
		ft_put_img_to_fond(data, data->wall, 0, 0);
		mlx_string_put(data->ml, data->wn, 44, 24, 0x00000000, "0");
	}
	else
	{
		new_elem = ft_lstnew(data->wall, x, y);
		if (new_elem == NULL)
			return (1);
		ft_lstadd_back(&data->images, new_elem);
	}
	return (0);
}

int	ft_put_image(char symb, t_data *data)
{
	if (symb == '1')
	{
		if (ft_put_walls(data->tmp_str, data->tmp_c, data) == 1)
			return (1);
	}
	else if (symb == '0')
	{
		if (ft_put_background(data) == 1)
			return (1);
	}
	else if (symb == 'P' || symb == 'E' || symb == 'C' || symb == 'N')
	{
		if (ft_put_images_to_background(data, symb) == 1)
			return (1);
	}
	return (0);
}

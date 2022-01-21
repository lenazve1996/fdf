/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:17:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/21 13:00:34 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_error_processing(char *str)
{
	perror(str);
	return (1);
}

t_img	*ft_locate_new_pos(t_data *data, int keycode, t_img *old_p)
{
	t_img	*new_p;
	int		i;

	i = 0;
	new_p = old_p;
	if (keycode == 0)
		new_p = old_p->prev;
	else if (keycode == 1 || keycode == 13)
	{
		while (i < (data->map_width))
		{
			if (keycode == 1)
				new_p = new_p->next;
			else if (keycode == 13)
				new_p = new_p->prev;
			i++;
		}
	}
	else if (keycode == 2)
		new_p = old_p->next;
	return (new_p);
}

int	ft_key(int keycode, t_data *data)
{
	t_img	*new_p;
	t_img	*old_p;
	int		i;

	i = 0;
	if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
	{
		old_p = data->images;
		while (old_p->img != data->plr)
			old_p = old_p->next;
		new_p = ft_locate_new_pos(data, keycode, old_p);
		ft_move_processing(old_p, new_p, data);
	}
	else if (keycode == 53)
	{
		ft_cleaning(data);
		ft_destroy_imgs(data);
		mlx_destroy_window(data->ml, data->wn);
		exit(0);
	}
	return (0);
}

void	ft_animation(t_data *data, int c)
{
	int			i;
	t_img		*old_p;

	i = 0;
	old_p = data->images;
	while (i < data->enemy_numb)
	{
		while (old_p->img != data->enemy)
			old_p = old_p->next;
		if (c % 12000 == 6000)
			ft_put_img_to_fond(data, data->enemy2, old_p->x, old_p->y);
		else if (c % 12000 == 8000)
			ft_put_img_to_fond(data, data->enemy3, old_p->x, old_p->y);
		else if (c % 12000 == 10000)
			ft_put_img_to_fond(data, data->enemy2, old_p->x, old_p->y);
		else if (c % 12000 == 0)
			ft_put_img_to_fond(data, data->enemy, old_p->x, old_p->y);
		old_p = old_p->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		parser_result;

	if (argc != 2)
	{
		return (ft_putstr_fd_ret("The number of arguments should be 1: file \
		with a map with the .ber extension\n", 2));
	}
	data.loop_count = 0;
	parser_result = ft_parser(argv, &data);
	if (parser_result == 1)
	{
		if (data.ml != NULL)
		{
			ft_destroy_imgs(&data);
			mlx_destroy_window(data.ml, data.wn);
		}
		if (data.map != NULL)
			ft_cleaning(&data);
		return (1);
	}
	data.images->return_exit = 0;
	printf("Moves -> %d\n", data.movements);
	mlx_loop_hook(data.ml, ft_patrols, &data);
	mlx_key_hook(data.wn, ft_key, &data);
	mlx_hook(data.wn, 17, (1L << 17), ft_destroy, &data);
	mlx_loop(data.ml);
}

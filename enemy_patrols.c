/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_patrols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:39:51 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/20 12:22:19 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_enemy_direction(t_img *new_p, t_data *data)
{
	if (new_p->img == data->wall || new_p->img == data->harry || \
	new_p->img == data->ex || new_p->img == data->enemy)
		return (1);
	else if (new_p->img == data->plr)
		ft_player_lose(new_p, data);
	return (0);
}

static t_img	*ft_set_enemy_direction(t_data *data, t_img *old_p, int *array)
{
	int		check;
	t_img	*new_p;
	int		i;
	int		n;
	int		direction;

	i = 0;
	n = 0;
	check = 1;
	while (check != 0 && n != 4)
	{
		if (i == 0)
			direction = old_p->direction;
		else
			direction = array[n++];
		new_p = ft_locate_new_pos(data, direction, old_p);
		check = ft_check_enemy_direction(new_p, data);
		i++;
	}
	if (n == 4)
		new_p = old_p;
	else
		new_p->direction = direction;
	return (new_p);
}

static void	ft_move_enemy(t_data *data, t_img *old_p)
{
	t_img	*new;
	int		array_direct[4];

	array_direct[0] = 1;
	array_direct[1] = 13;
	array_direct[2] = 0;
	array_direct[3] = 2;
	new = ft_set_enemy_direction(data, old_p, &array_direct[0]);
	mlx_put_image_to_window(data->ml, data->wn, data->fond, old_p->x, old_p->y);
	old_p->img = data->fond;
	mlx_put_image_to_window(data->ml, data->wn, data->enemy, new->x, new->y);
	new->img = data->enemy;
}

static t_img	*ft_find_enemy(t_data *data, int n)
{
	t_img	*old_p;

	old_p = data->images;
	while (old_p->img != data->enemy)
		old_p = old_p->next;
	while (n != 0)
	{
		old_p = old_p->next;
		while (old_p->img != data->enemy)
			old_p = old_p->next;
		n--;
	}
	return (old_p);
}

int	ft_patrols(t_data *data)
{
	int			n;
	t_img		*old_p;

	n = 0;
	ft_animation(data, data->loop_count);
	while (n < data->enemy_numb)
	{
		old_p = ft_find_enemy(data, n);
		if (data->loop_count % 12000 == n * 300)
			ft_move_enemy(data, old_p);
		n++;
	}
	data->loop_count++;
	return (0);
}

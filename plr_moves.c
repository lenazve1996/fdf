/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:19:17 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/20 12:22:07 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_return_exit(t_img *old_p, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->ex, old_p->x, old_p->y);
	old_p->img = data->ex;
	data->images->return_exit = 0;
}

static void	ft_move_player(t_img *old, t_img *new, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->fond, old->x, old->y);
	old->img = data->fond;
	if (data->images->return_exit == 1)
		ft_return_exit(old, data);
	if (new->img == data->harry)
		mlx_put_image_to_window(data->ml, data->wn, data->fond, new->x, new->y);
	mlx_put_image_to_window(data->ml, data->wn, data->plr, new->x, new->y);
	new->img = data->plr;
	++data->movements;
}

static void	ft_player_move_to_exit(t_img *old_p, t_img *new_p, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->fond, old_p->x, old_p->y);
	old_p->img = data->fond;
	mlx_put_image_to_window(data->ml, data->wn, data->plr, new_p->x, new_p->y);
	new_p->img = data->plr;
	data->images->return_exit = 1;
	new_p = data->images;
	while (new_p->next != NULL && new_p->img != data->harry)
	{
		if (new_p->img != data->harry)
			new_p = new_p->next;
	}
	if (new_p->next == NULL)
	{
		++data->movements;
		printf("Moves -> %d\n", data->movements);
		ft_destroy_imgs(data);
		mlx_destroy_window(data->ml, data->wn);
		ft_cleaning(data);
		exit(0);
	}
	++data->movements;
}

void	ft_move_processing(t_img *old_p, t_img *new_p, t_data *data)
{
	char	*moves;

	if (new_p->img != data->wall && new_p->img != data->ex \
	&& new_p->img != data->enemy)
		ft_move_player(old_p, new_p, data);
	if (new_p->img == data->enemy)
	{
		++data->movements;
		ft_player_lose(new_p, data);
	}
	else if (new_p->img == data->ex)
		ft_player_move_to_exit(old_p, new_p, data);
	printf("Moves -> %d\n", data->movements);
	mlx_put_image_to_window(data->ml, data->wn, data->wall, 0, 0);
	moves = ft_itoa(data->movements);
	ft_put_img_to_fond(data, data->wall, 0, 0);
	ft_put_img_to_fond(data, data->wall, 64, 0);
	mlx_string_put(data->ml, data->wn, 44, 24, 0x00000000, moves);
	free(moves);
}

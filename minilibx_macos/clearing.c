/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:02:48 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/19 17:04:02 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_lstclear_list(t_img *lst)
{
	t_img	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = tmp->next;
		free(tmp);
	}
}

void	ft_cleaning(t_data *data)
{
	int	s;

	s = 0;
	while (s <= data->map_height)
	{
		free(data->map[s]);
		s++;
	}
	free(data->map);
	ft_lstclear_list(data->images);
}

void	ft_destroy_imgs(t_data *data)
{
	mlx_destroy_image(data->ml, data->fond);
	mlx_destroy_image(data->ml, data->wall);
	mlx_destroy_image(data->ml, data->plr);
	mlx_destroy_image(data->ml, data->harry);
	mlx_destroy_image(data->ml, data->ex);
}
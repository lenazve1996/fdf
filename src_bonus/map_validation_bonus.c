/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:50:59 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/21 13:00:24 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_count_enemies(t_data *data, char *str)
{
	while (*str)
	{
		if (*str == 'N')
			data->enemy_numb++;
		str++;
	}
}

static int	ft_check_extra_characters(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->map_height)
	{
		if (i >= 1 && (int)ft_strlen(data->map[i]) != data->map_width)
			return (ft_putstr_fd_ret("Error\nDifferent str sizes in map\n", 2));
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] != '1' && data->map[i][j] != 'N' && \
			data->map[i][j] != 'P' && data->map[i][j] != '0' && \
			data->map[i][j] != 'C' && data->map[i][j] != 'E')
			{
				return (ft_putstr_fd_ret("Error\
				There are some extra characters in the map\n", 2));
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_check_characters(char **map, t_data *data)
{
	int	i;
	int	collectible;
	int	player;
	int	ex;

	i = 0;
	collectible = 0;
	player = 0;
	ex = 0;
	data->enemy_numb = 0;
	while (i < data->map_height)
	{
		if (ft_strchr(map[i], 'C') != NULL)
			collectible++;
		if (ft_strchr(map[i], 'P') != NULL)
			player++;
		if (ft_strchr(map[i], 'E') != NULL)
			ex++;
		ft_count_enemies(data, map[i]);
		i++;
	}
	if ((collectible == 0) || (player != 1) || (ex == 0))
		return (ft_putstr_fd_ret("Error\nThe map is not valid\n", 2));
	return (0);
}

static int	ft_check_walls(char **map, t_data *data)
{
	int	str;
	int	c;

	c = 0;
	str = 0;
	while (map[0][c] != '\0' && map[data->map_height - 1][c] != '\0')
	{
		if (map[0][c] == '1' && map[data->map_height - 1][c] == '1')
			c++;
		else
		{
			return (ft_putstr_fd_ret("Error\nThe map is not valid: \
			the map must be closed/surrounded by walls\n", 2));
		}
	}
	while (str < data->map_height)
	{
		if (map[str][0] == '1' && map[str][data->map_width - 1] == '1')
			str++;
		else
		{
			return (ft_putstr_fd_ret("Error\nThe map is not valid: \
			the map must be closed/surrounded by walls\n", 2));
		}
	}
	return (0);
}

int	ft_map_validation(char **map, t_data *data)
{
	data->map_height = 0;
	while (map[data->map_height] != NULL)
		data->map_height++;
	data->map_width = ft_strlen(map[0]);
	if (ft_check_characters(map, data) == 1 || \
	ft_check_extra_characters(data) == 1 || ft_check_walls(map, data) == 1)
		return (1);
	return (0);
}

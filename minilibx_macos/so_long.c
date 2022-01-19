/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:17:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/19 17:15:27 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_img_to_fond(t_data *data, void *character, int x, int y)
{
	mlx_put_image_to_window(data->ml, data->wn, data->fond, x, y);
	mlx_put_image_to_window(data->ml, data->wn, character, x, y);
}

void	ft_error_inmap_read(char *line, char *tmp, char *str)
{
	free(line);
	if (tmp != NULL)
		free(tmp);
	perror(str);
}

int	ft_putstr_fd_ret(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int	ft_imgs_creation(t_data *data, int *h, int *w)
{
	data->wall = mlx_xpm_file_to_image(data->ml, "tree.xpm", h, w);
	data->fond = mlx_xpm_file_to_image(data->ml, "paper.xpm", h, w);
	data->harry = mlx_xpm_file_to_image(data->ml, "harry.xpm", h, w);
	data->ex = mlx_xpm_file_to_image(data->ml, "exit.xpm", h, w);
	data->plr = mlx_xpm_file_to_image(data->ml, "dem2.xpm", h, w);
	data->enemy = mlx_xpm_file_to_image(data->ml, "phoenix.xpm", h, w);
	data->enemy2 = mlx_xpm_file_to_image(data->ml, "phoenix2.xpm", h, w);
	data->enemy3 = mlx_xpm_file_to_image(data->ml, "phoenix3.xpm", h, w);
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

int	ft_put_images_to_background(t_data *data, char symbol)
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

int	ft_put_walls(int s, int c, t_data *data)
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

int	ft_put_background(t_data *data)
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

char	*ft_reading(char *line, char *tmp, int fd)
{
	int	n;

	n = 1;
	while (n != 0)
	{
		n = read(fd, tmp, 1);
		if (n == -1)
		{
			ft_error_inmap_read(line, tmp, "Error\nRead failed");
			return (NULL);
		}
		tmp[1] = '\0';
		if (n != 0)
			line = ft_strjoin_free(line, tmp);
	}
	return (line);
}

char	*ft_map_read(int fd)
{
	char	*line;
	char	*tmp;
	int		n;

	n = 1;
	line = malloc(2 * sizeof(char));
	if (line == NULL)
	{
		perror("Error\nMalloc failed");
		return (NULL);
	}
	line[0] = '\0';
	tmp = (char *)malloc(2 * sizeof(char));
	if (tmp == NULL)
	{
		ft_error_inmap_read(line, NULL, "Error\nMalloc failed");
		return (NULL);
	}
	line = ft_reading(line, tmp, fd);
	free(tmp);
	return (line);
}

void	ft_player_lose(t_img *new_p, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->plr, new_p->x, new_p->y);
	new_p->img = data->plr;
	ft_destroy_imgs(data);
	mlx_destroy_window(data->ml, data->wn);
	printf("Moves -> %d\n", data->movements);
	ft_cleaning(data);
	exit(0);
}

void	ft_return_exit(t_img *old_p, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->ex, old_p->x, old_p->y);
	old_p->img = data->ex;
	data->images->return_exit = 0;
}

void	ft_move_player(t_img *old, t_img *new, t_data *data)
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

void	ft_player_move_to_exit(t_img *old_p, t_img *new_p, t_data *data)
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

void	ft_count_enemies(t_data *data, char *str)
{
	while (*str)
	{
		if (*str == 'N')
			data->enemy_numb++;
		str++;
	}
}

int	ft_check_characters(char **map, t_data *data)
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

int	ft_check_walls(char **map, t_data *data)
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

int	ft_check_extra_characters(t_data *data)
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

int	ft_map_validation(char **map, t_data *data)
{
	data->ml = NULL;
	data->map_height = 0;
	while (map[data->map_height] != NULL)
		data->map_height++;
	data->map_width = ft_strlen(map[0]);
	if (ft_check_characters(map, data) == 1 || \
	ft_check_extra_characters(data) == 1 || ft_check_walls(map, data) == 1)
		return (1);
	return (0);
}

int	ft_destroy(t_data *data)
{
	ft_destroy_imgs(data);
	mlx_destroy_window(data->ml, data->wn);
	ft_cleaning(data);
	exit(0);
}

int	ft_parser(char	**argv, t_data *data)
{
	int		fd;
	char	*line;

	data->movements = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open map");
		return (1);
	}
	line = ft_map_read(fd);
	if (line == NULL)
		return (1);
	close(fd);
	data->map = ft_split(line, '\n');
	if (data->map == NULL)
	{
		free(line);
		return (1);
	}
	free(line);
	if (ft_map_validation(data->map, data) == 1 || \
	ft_win_and_img_creation(data) == 1 || ft_fill_window(data->map, data) == 1)
		return (1);
	return (0);
}

int	ft_check_enemy_direction(t_img *new_p, t_data *data)
{
	if (new_p->img == data->wall || new_p->img == data->harry || \
	new_p->img == data->ex || new_p->img == data->enemy)
		return (1);
	else if (new_p->img == data->plr)
		ft_player_lose(new_p, data);
	return (0);
}

t_img	*ft_set_enemy_direction(t_data *data, t_img *old_p, int *array_direct)
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
			direction = array_direct[n++];
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

void	ft_move_enemy(t_data *data, t_img *old_p)
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

t_img	*ft_find_enemy(t_data *data, int n)
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
		ft_cleaning(&data);
		return (1);
	}
	data.images->return_exit = 0;
	mlx_loop_hook(data.ml, ft_patrols, &data);
	mlx_key_hook(data.wn, ft_key, &data);
	mlx_hook(data.wn, 17, (1L << 17), ft_destroy, &data);
	mlx_loop(data.ml);
}

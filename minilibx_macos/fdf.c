/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:17:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2021/12/28 20:17:19 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_img
{
	void	*img;
	int		return_exit;
	int		x;
	int		y;
	void	*next;
	void	*prev;
}				t_img;

typedef struct s_data{
	void	*wn;
	void	*ml;
	void	*fond;
	void	*wall;
	void	*harry;
	void	*ex;
	void	*plr;
	void	*enemy;
	int		tmp_str;
	int		tmp_c;
	int		movements;
	int		im_hei;
	int		im_wid;
	int		map_width;
	int		map_wid_pix;
	int		map_height;
	int		map_hei_pix;
	t_img	*images;
}				t_data;

void	ft_error_inmap_read(char *line, char *tmp, char *str)
{
	free(line);
	if (tmp != NULL)
		free(tmp);
	perror(str);
}

void	ft_lstadd_front(t_img **lst, t_img *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_putstr_fd_ret(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

t_img	*ft_lstlast(t_img *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_img	*ft_lstnew(void	*img, int n, int j)
{
	t_img	*new_element;

	new_element = (t_img *)malloc(sizeof(t_img));
	if (!new_element)
		return (NULL);
	new_element->img = img;
	new_element->x = n;
	new_element->y = j;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lstadd_back(t_img **lst, t_img *new)
{
	t_img	*last_elem;

	if (new != NULL && lst != NULL && *lst != NULL)
	{
		last_elem = ft_lstlast(*lst);
		last_elem->next = new;
		new->prev = last_elem;
	}
	else if (*lst == NULL)
	{
		ft_lstadd_front(lst, new);
	}
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

int	ft_win_and_images_creation(t_data *data)
{
	int	*h;
	int	*w;

	h = &data->im_hei;
	w = &data->im_wid;
	data->map_wid_pix = data->map_width * data->im_wid;
	data->map_hei_pix = data->map_height * data->im_hei;
	data->wn = mlx_new_window(data->ml, data->map_wid_pix, \
	data->map_hei_pix, "so_long");
	if (!data->wn)
	{
		perror("Failed to open a new window");
		return (1);
	}
	data->wall = mlx_xpm_file_to_image(data->ml, "fence.xpm", h, w);
	data->fond = mlx_xpm_file_to_image(data->ml, "back.xpm", h, w);
	data->harry = mlx_xpm_file_to_image(data->ml, "harry.xpm", h, w);
	data->ex = mlx_xpm_file_to_image(data->ml, "exit.xpm", h, w);
	data->plr = mlx_xpm_file_to_image(data->ml, "dementor.xpm", h, w);
	data->enemy = mlx_xpm_file_to_image(data->ml, "phoenix.xpm", h, w);
	if (data->wall == NULL || data->fond == NULL || data->harry == NULL || \
	data->ex == NULL || data->plr == NULL || data->enemy == NULL)
		return (ft_putstr_fd_ret("Error\nmlx_xpm_file_to_image failed\n", 2));
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
	char	*moves;
	int		x;
	int		y;

	x = c * data->im_wid;
	y = s * data->im_hei;
	mlx_put_image_to_window(data->ml, data->wn, data->wall, x, y);
	if (s == 0 && c == 0)
	{
		data->images = ft_lstnew(data->wall, x, y);
		if (data->images == NULL)
			return (1);
		moves = ft_itoa(data->movements);
		mlx_string_put(data->ml, data->wn, 24, 24, 0x00FF0000, moves);
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
			line = ft_strjoin(line, tmp);
	}
	return (line);
}

char	*ft_map_read(int fd)
{
	char	*line;
	char	*tmp;
	int		n;

	n = 1;
	line = (char *)malloc(2 * sizeof(char));
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
	return (line);
}

int	ft_player_lose(t_img *new_p, t_data *data)
{
	mlx_put_image_to_window(data->ml, data->wn, data->plr, new_p->x, new_p->y);
	new_p->img = data->plr;
	mlx_destroy_window(data->ml, data->wn);
	++data->movements;
	printf("%d\n", data->movements);
	exit (0);
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
		printf("%d\n", data->movements);
		mlx_destroy_window(data->ml, data->wn);
		exit(0);
	}
	++data->movements;
}

int	ft_move_processing(t_img *old_p, t_img *new_p, t_data *data)
{
	char	*moves;

	if (new_p->img != data->wall && new_p->img != data->ex \
	&& new_p->img != data->enemy)
		ft_move_player(old_p, new_p, data);
	if (new_p->img == data->enemy)
		return (ft_player_lose(new_p, data));
	else if (new_p->img == data->ex)
		ft_player_move_to_exit(old_p, new_p, data);
	printf("%d\n", data->movements);
	mlx_put_image_to_window(data->ml, data->wn, data->wall, 0, 0);
	moves = ft_itoa(data->movements);
	mlx_string_put(data->ml, data->wn, 24, 24, 0x00FF0000, moves);
	return (0);
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
	printf("%d\n", keycode);
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
		//mlx_destroy_image(data->ml, data->fond);
		//mlx_destroy_image(data->ml, data->wall);
		//mlx_destroy_image(data->ml, data->player);
		//mlx_destroy_image(data->ml, data->harry);
		//mlx_destroy_image(data->ml, data->ex);
		mlx_destroy_window(data->ml, data->wn);
		exit(0);
	}
	return (0);
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
	while (i < data->map_height)
	{
		if (ft_strchr(map[i], 'C') != NULL)
			collectible++;
		if (ft_strchr(map[i], 'P') != NULL)
			player++;
		if (ft_strchr(map[i], 'E') != NULL)
			ex++;
		if (i >= 1 && (int)ft_strlen(map[i]) != data->map_width)
			return (ft_putstr_fd_ret("Error\nDifferent line sizes in map\n", 2));
		i++;
	}
	if ((collectible == 0) || (player == 0) || (ex == 0))
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

int	ft_map_validation(char **map, t_data *data)
{
	data->map_height = 0;
	while (map[data->map_height] != NULL)
		data->map_height++;
	data->map_width = ft_strlen(map[0]);
	if (ft_check_characters(map, data) == 1 || ft_check_walls(map, data) == 1)
		return (1);
	return (0);
}

int	ft_destroy(t_data *data)
{
	mlx_destroy_window(data->ml, data->wn);
	exit(0);
}

int	ft_parser(char	**argv, t_data *data)
{
	int		fd;
	char	**map;
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
	map = ft_split(line, '\n');
	if (map == NULL)
	{
		free(line);
		return (1);
	}
	free(line);
	if (ft_map_validation(map, data) == 1 || \
	ft_win_and_images_creation(data) == 1 || ft_fill_window(map, data) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		parser_result;

	if (argc != 2)
	{
		return (ft_putstr_fd_ret("The number of arguments should be 1: file with a map\
		with the .ber extension\n", 2));
	}
	data.ml = mlx_init();
	data.im_wid = 64;
	data.im_hei = 64;
	if (!data.ml)
		return (ft_putstr_fd_ret("Error\nFailed to set up the connection", 2));
	parser_result = ft_parser(argv, &data);
	if (parser_result == 1)
		return (1);
	data.images->return_exit = 0;
	mlx_key_hook(data.wn, ft_key, &data);
	mlx_hook(data.wn, 17, (1L << 17), ft_destroy, &data);
	mlx_loop(data.ml);
	return (0);
}

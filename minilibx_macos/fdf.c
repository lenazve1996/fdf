#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_img
{
	void	*mlx_img;
	int		return_exit;
	int		x;
	int		y;
	void	*next;
	void	*prev;
}				t_img;

typedef struct s_data{
	void	*win;
	void	*mlx;
	void	*background;
	void	*fence;
	void	*harry;
	void	*ex;
	void	*dementor;
	void	*enemy;
	int		tmp_str;
	int		tmp_c;
	int		movements;
	int		img_height;
	int		img_width;
	int		map_width;
	int		map_width_pix;
	int		map_height;
	int		map_height_pix;
	t_img	*images;
}				t_data;

//int	ft_error_processing(char *str)
//{
//	perror(str);
//	return(1);
//}

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

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

t_img	*ft_lstlast(t_img *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_img	*ft_lstnew(void	*mlx_img, int n, int j)
{
	t_img	*new_element;

	new_element = (t_img *)malloc(sizeof(t_img));
	if (!new_element)
		return (NULL);
	new_element->mlx_img = mlx_img;
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
	data->map_width_pix = data->map_width * data->img_width;
	data->map_height_pix = data->map_height * data->img_height;
	data->win = mlx_new_window(data->mlx, data->map_width_pix, data->map_height_pix, "so_long");
	if (!data->win)
	{
		perror("Failed to open a new window");
		return (1);
	}
	data->fence = mlx_xpm_file_to_image(data->mlx, "fence.xpm", &data->img_height, &data->img_width);
	data->background = mlx_xpm_file_to_image(data->mlx, "back.xpm", &data->img_height, &data->img_width);
	data->harry = mlx_xpm_file_to_image(data->mlx, "harry.xpm", &data->img_height, &data->img_width);
	data->ex = mlx_xpm_file_to_image(data->mlx, "exit.xpm", &data->img_height, &data->img_width);
	data->dementor = mlx_xpm_file_to_image(data->mlx, "dementor.xpm", &data->img_height, &data->img_width);
	data->enemy = mlx_xpm_file_to_image(data->mlx, "phoenix.xpm", &data->img_height, &data->img_width);
	if (data->fence == NULL || data->background == NULL || data->harry == NULL || data->ex == NULL || data->dementor == NULL || data->enemy == NULL)
	{
		ft_putstr_fd("Error\nmlx_xpm_file_to_image failed\n", 2);
		return (1);
	}
	return (0);
}

int	ft_put_images_to_background(t_data *data, char symbol)
{
	t_img	*new_elem;
	char	*character;

	mlx_put_image_to_window(data->mlx, data->win, data->background, data->tmp_c * data->img_width, data->tmp_str * data->img_height);
	if (symbol == 'P')
		character = data->dementor;
	else if (symbol == 'E')
		character = data->ex;
	else if (symbol == 'C')
		character = data->harry;
	else if (symbol == 'N')
		character = data->enemy;
	mlx_put_image_to_window(data->mlx, data->win, character, data->tmp_c * data->img_width, data->tmp_str * data->img_height);
	new_elem = ft_lstnew(character, data->tmp_c * data->img_width, data->tmp_str * data->img_height);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(&data->images, new_elem);
	//printf("created %p\n", new_elem);
	//printf("previous %p\n", new_elem->prev);
	//printf("next %p\n", new_elem->next);
	return (0);
}

int	ft_put_walls(int str, int c, t_data *data)
{
	t_img	*new_elem;

	mlx_put_image_to_window(data->mlx, data->win, data->fence, c * data->img_width, str * data->img_height);
	if (str == 0 && c == 0)
	{
		data->images = ft_lstnew(data->fence, c * data->img_width, str * data->img_height);
		if (data->images == NULL)
			return (1);
		mlx_string_put(data->mlx, data->win, 24, 24, 0x00FF0000, ft_itoa(data->movements));
	}
	else
	{
		new_elem = ft_lstnew(data->fence, c * data->img_width, str * data->img_height);
		if (new_elem == NULL)
			return (1);
		ft_lstadd_back(&data->images, new_elem);
	}
	//printf("created %p\n", new_elem);
	//printf("previous %p\n", new_elem->prev);
	//printf("next %p\n", new_elem->next);
	return (0);
}

int	ft_put_background(t_data *data)
{
	t_img	*new_elem;

	mlx_put_image_to_window(data->mlx, data->win, data->background, data->tmp_c * data->img_width, data->tmp_str * data->img_height);
	new_elem = ft_lstnew(data->background, data->tmp_c * data->img_width, data->tmp_str * data->img_height);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(&data->images, new_elem);
	//printf("created %p\n", new_elem);
	//printf("previous %p\n", new_elem->prev);
	//printf("next %p\n", new_elem->next);
	return(0);
}

int	ft_fill_window(char **map, t_data *data)
{
	int		str;
	char	symbol;
	int		c;
	t_img	*tmp;

	data->tmp_str = 0;
	while (map[data->tmp_str] != NULL)
	{
		data->tmp_c = 0;
		while (map[data->tmp_str][data->tmp_c] != '\0')
		{
			symbol = map[data->tmp_str][data->tmp_c];
			if (map[data->tmp_str][data->tmp_c] == '1')
			{
				if (ft_put_walls(data->tmp_str, data->tmp_c, data) == 1)
					return (1);
				printf("here walls %d %d \n", data->tmp_str, data->tmp_c);
			}
			else if (map[data->tmp_str][data->tmp_c] == '0')
			{
				if (ft_put_background(data) == 1)
					return (1);
				printf("here back %d %d \n", data->tmp_str, data->tmp_c);
			}
			else if (map[data->tmp_str][data->tmp_c] == 'P' || map[data->tmp_str][data->tmp_c] == 'E' || map[data->tmp_str][data->tmp_c] == 'C' || map[data->tmp_str][data->tmp_c] == 'N')
			{
				if (ft_put_images_to_background(data, symbol) == 1)
					return (1);
				printf("here characters %d %d \n", data->tmp_str, data->tmp_c);
			}
			data->tmp_c++;
		}
		data->tmp_str++;
	}
	tmp = data->images;
	//while (tmp != NULL)
	//{
	//	printf("%p\n", data->images);
	//	printf("%p\n", data->images->prev);
	//	printf("%p\n", data->images->next);
	//	printf("%p\n\n", data->images->mlx_img);
	//	tmp = tmp->next;
	//}
	//printf("");
	printf("here\n");
	return (0);
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
	free(tmp);
	return (line);
}

void	ft_return_exit()
{
	
}


int	ft_key(int keycode, t_data *data)
{
	t_img	*tmp;
	t_img	*old_pos;
	int		i;

	i = 0;
	printf("%d\n", keycode);
	old_pos = data->images;
	if (keycode == 0)
	{
		while (old_pos->mlx_img != data->dementor)
			old_pos = old_pos->next;
		tmp = old_pos->prev;
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex && tmp->mlx_img != data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (data->images->return_exit == 1)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->ex, old_pos->x, old_pos->y);
				old_pos->mlx_img = data->ex;
				data->images->return_exit = 0;
			}
			if (tmp->mlx_img == data->harry)
				mlx_put_image_to_window(data->mlx, data->win, data->background, tmp->x, tmp->y);
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			++data->movements;
		}
		else if (tmp->mlx_img == data->ex || tmp->mlx_img == data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (tmp->mlx_img == data->enemy)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
				tmp->mlx_img = data->dementor;
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			data->images->return_exit = 1;
			tmp = data->images;
			while (tmp->next != NULL && tmp->mlx_img != data->harry)
			{
				if (tmp->mlx_img != data->harry)
					tmp = tmp->next;
			}
			if (tmp->next == NULL)
			{
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			++data->movements;
		}
		printf("%d\n", data->movements);
		mlx_put_image_to_window(data->mlx, data->win, data->fence, 0, 0);
		mlx_string_put(data->mlx, data->win, 24, 24, 0x00FF0000, ft_itoa(data->movements));
	}
	else if (keycode == 1)
	{
		while (old_pos->mlx_img != data->dementor)
			old_pos = old_pos->next;
		tmp = old_pos;
		while (i < (data->map_width))
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex && tmp->mlx_img != data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (data->images->return_exit == 1)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->ex, old_pos->x, old_pos->y);
				old_pos->mlx_img = data->ex;
				data->images->return_exit = 0;
			}
			if (tmp->mlx_img == data->harry)
				mlx_put_image_to_window(data->mlx, data->win, data->background, tmp->x, tmp->y);
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			++data->movements;
		}
		else if (tmp->mlx_img == data->ex || tmp->mlx_img == data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (tmp->mlx_img == data->enemy)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
				tmp->mlx_img = data->dementor;
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			data->images->return_exit = 1;
			tmp = data->images;
			while (tmp->next != NULL && tmp->mlx_img != data->harry)
			{
				if (tmp->mlx_img != data->harry)
					tmp = tmp->next;
			}
			if (tmp->next == NULL)
			{
				mlx_destroy_window(data->mlx, data->win);
				exit(0);
			}
			++data->movements;
		}
		printf("%d\n", data->movements);
		mlx_put_image_to_window(data->mlx, data->win, data->fence, 0, 0);
		mlx_string_put(data->mlx, data->win, 24, 24, 0x00FF0000, ft_itoa(data->movements));
	}
	else if (keycode == 2)
	{
		while (old_pos->mlx_img != data->dementor)
		{
			old_pos = old_pos->next;
		}
		tmp = old_pos->next;
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex && tmp->mlx_img != data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (data->images->return_exit == 1)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->ex, old_pos->x, old_pos->y);
				old_pos->mlx_img = data->ex;
				data->images->return_exit = 0;
			}
			if (tmp->mlx_img == data->harry)
				mlx_put_image_to_window(data->mlx, data->win, data->background, tmp->x, tmp->y);
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			++data->movements;
		}
		else if (tmp->mlx_img == data->ex || tmp->mlx_img == data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (tmp->mlx_img == data->enemy)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
				tmp->mlx_img = data->dementor;
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			data->images->return_exit = 1;
			tmp = data->images;
			while (tmp->next != NULL && tmp->mlx_img != data->harry)
			{
				if (tmp->mlx_img != data->harry)
					tmp = tmp->next;
			}
			if (tmp->next == NULL)
			{
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			++data->movements;
		}
		printf("%d\n", data->movements);
		mlx_put_image_to_window(data->mlx, data->win, data->fence, 0, 0);
		mlx_string_put(data->mlx, data->win, 24, 24, 0x00FF0000, ft_itoa(data->movements));
	}
	else if (keycode == 13)
	{
		while (old_pos->mlx_img != data->dementor)
			old_pos = old_pos->next;
		tmp = old_pos;
		while (i < data->map_width)
		{
			tmp = tmp->prev;
			i++;
		}
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex && tmp->mlx_img != data->enemy)
		{
			i = i - data->map_width;
			while (i > 0)
			{
				tmp = tmp->next;
				i--;
			}
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (data->images->return_exit == 1)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->ex, old_pos->x, old_pos->y);
				old_pos->mlx_img = data->ex;
				data->images->return_exit = 0;
			}
			if (tmp->mlx_img == data->harry)
				mlx_put_image_to_window(data->mlx, data->win, data->background, tmp->x, tmp->y);
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			++data->movements;
		}
		else if (tmp->mlx_img == data->ex || tmp->mlx_img == data->enemy)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			if (tmp->mlx_img == data->enemy)
			{
				mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
				tmp->mlx_img = data->dementor;
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			data->images->return_exit = 1;
			tmp = data->images;
			while (tmp->next != NULL && tmp->mlx_img != data->harry)
			{
				if (tmp->mlx_img != data->harry)
					tmp = tmp->next;
			}
			if (tmp->next == NULL)
			{
				mlx_destroy_window(data->mlx, data->win);
				exit(1);
			}
			++data->movements;
		}
		printf("%d\n", data->movements);
		mlx_put_image_to_window(data->mlx, data->win, data->fence, 0, 0);
		mlx_string_put(data->mlx, data->win, 24, 24, 0x00FF0000, ft_itoa(data->movements));
	}
	else if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->background);
		mlx_destroy_image(data->mlx, data->fence);
		mlx_destroy_image(data->mlx, data->dementor);
		mlx_destroy_image(data->mlx, data->harry);
		mlx_destroy_image(data->mlx, data->ex);
		mlx_destroy_window(data->mlx, data->win);
		exit(1);
	}
	return (0);
}

int	ft_check_characters(char **map, t_data *data)
{
	int	i;
	int	collectible;
	int	dementor;
	int	ex;

	i = 0;
	collectible = 0;
	dementor = 0;
	ex = 0;
	while (i < data->map_height)
	{
		if (ft_strchr(map[i], 'C') != NULL)
			collectible++;
		if (ft_strchr(map[i], 'P') != NULL)
			dementor++;
		if (ft_strchr(map[i], 'E') != NULL)
			ex++;
		if (i >= 1 && (int)ft_strlen(map[i]) != data->map_width)
		{
			ft_putstr_fd("Error\nThe map is not valid: different line sizes\n", 2);
			return (1);
		}
		i++;
	}
	if ((collectible == 0) || (dementor == 0) || (ex == 0))
	{
		ft_putstr_fd("Error\nThe map is not valid: map must have at least one exit, one collectible, and one starting position\n", 2);
		return (1);
	}
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
			ft_putstr_fd("Error\nThe map is not valid: the map must be closed/surrounded by walls\n", 2);
			return (1);
		}
	}
	while (str < data->map_height)
	{
		if (map[str][0] == '1' && map[str][data->map_width - 1] == '1')
			str++;
		else
		{
			ft_putstr_fd("Error\nThe map is not valid: the map must be closed/surrounded by walls\n", 2);
			return (1);
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
	mlx_destroy_window(data->mlx, data->win);
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
		return (1);
	free(line);
	if (ft_map_validation(map, data) == 1)
		return (1);
	if (ft_win_and_images_creation(data) == 1)
		return (1);
	if (ft_fill_window(map, data) == 1)
		return (1);
	data->images->return_exit = 0;
	mlx_key_hook(data->win, ft_key, data);
	mlx_hook(data->win, 17, (1L <<17), ft_destroy, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		parser_result;

	if (argc != 2)
	{
		ft_putstr_fd("The number of arguments should be 1: file with a map with the .ber extension\n", 2);
		return (1);
	}
	data.mlx = mlx_init();
	data.img_width = 64;
	data.img_height = 64;
	if (!data.mlx)
	{
		ft_putstr_fd("Error\nFailed to set up the connection to the graphical system", 2);
		return (1);
	}
	parser_result = ft_parser(argv, &data);
	if (parser_result == 1)
		return (1);
	mlx_loop(data.mlx);
	return (0);
}

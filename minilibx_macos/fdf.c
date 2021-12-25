#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct	s_img
{
	void	*mlx_img;
	int		x;
	int		y;
	void	*next;
}				t_img;


typedef struct	s_data{
	void	*win;
	void	*mlx;
	void	*background;
	void	*fence;
	void	*harry;
	void	*ex;
	void	*dementor;
	char	*filename;
	char	*filename2;
	char	*filename3;
	char	*filename4;
	char	*filename5;
	int		movements;
	int		img_height;
	int		img_height2;
	int		img_height3;
	int		img_height4;
	int		img_height5;
	int		img_width;
	int		img_width2;
	int		img_width3;
	int		img_width4;
	int		img_width5;
	int		map_width;
	int		map_height;
	t_img	*images;
}				t_data;

void	ft_lstadd_front(t_img  **lst, t_img  *new)
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
	return (new_element);
}

void	ft_lstadd_back(t_img **lst, t_img *new)
{
	t_img	*last_elem;

	if (new != NULL && lst != NULL && *lst != NULL)
	{
		last_elem = ft_lstlast(*lst);
		last_elem->next = new;
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

t_img	*ft_fill_window(char **map, t_data *data)
{
	t_img	*head;
	t_img	*new_elem;
	int		height;
	int		width;
	int		img_height;
	int		img_height2;
	int		img_width;
	int		img_width2;
	int		x;
	int		y;
	int		str;
	int		c;
	int		flag;

	str = 0;
	c = 0;
	height = data->map_height * 64;
	width = data->map_width * 64;
	data->win = mlx_new_window(data->mlx, width, height, "fdf");
	if (!data->win)
	{
		perror("Failed to open a new window");
		exit(1);
	}
	data->background = mlx_xpm_file_to_image(data->mlx, data->filename2, &data->img_height, &data->img_width);
	data->fence = mlx_xpm_file_to_image(data->mlx, data->filename, &data->img_height2, &data->img_width2);
	data->harry = mlx_xpm_file_to_image(data->mlx, data->filename3, &data->img_height3, &data->img_width3);
	data->ex = mlx_xpm_file_to_image(data->mlx, data->filename4, &data->img_height4, &data->img_width4);
	data->dementor = mlx_xpm_file_to_image(data->mlx, data->filename5, &data->img_height5, &data->img_width5);
	flag = -1;
	while (map[str] != NULL)
	{
		c = 0;
		while (map[str][c] != '\0')
		{
			if (map[str][c] == '1')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->fence, c * 64, str * 64);
				if(flag == -1)
				{
					head = ft_lstnew(data->fence, c * 64, str * 64);
					flag = 0;
				}
				else
				{
					new_elem = ft_lstnew(data->fence, c * 64, str * 64);
					ft_lstadd_back(&head, new_elem);
				}
			}
			else if (map[str][c] == '0')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, c * 64, str * 64);
				new_elem = ft_lstnew(data->background, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			else if (map[str][c] == 'P')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, c * 64, str * 64);
				mlx_put_image_to_window(data->mlx, data->win, data->dementor, c * 64, str * 64);
				new_elem = ft_lstnew(data->dementor, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			else if (map[str][c] == 'E')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, c * 64, str * 64);
				mlx_put_image_to_window(data->mlx, data->win, data->ex, c * 64, str * 64);
				new_elem = ft_lstnew(data->ex, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			else if (map[str][c] == 'C')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, c * 64, str * 64);
				mlx_put_image_to_window(data->mlx, data->win, data->harry, c * 64, str * 64);
				new_elem = ft_lstnew(data->harry, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			c++;
		}
		str++;
	}
	//new_elem = head;
	//i = 0;
	//while(new_elem != NULL)
	//{
	//	printf("--->%d<---\n", i);
	//	printf("%p\n", new_elem);
	//	printf("%p\n", new_elem->mlx_img);
	//	printf("%d\n", new_elem->x);
	//	printf("%d\n", new_elem->y);
	//	printf("%p\n\n", new_elem->next);
	//	new_elem = new_elem->next;
	//	i++;
	//}
	return (head);
}

char	*ft_map_read(int fd)
{
	char	*line;
	char	*tmp;
	int		n;

	n = 1;
	line = (char *)malloc(2 * sizeof(char));
	tmp = (char *)malloc(2 * sizeof(char));
	read(fd, line, 1);
	line[1] = '\0';

	while (n != 0)
	{
		n = read(fd, tmp, 1);
		tmp[1] = '\0';
		if (n != 0)
			line = ft_strjoin(line, tmp);
	}
	free(tmp);
	tmp = NULL;
	return (line);
}

int	ft_key(int keycode, t_data *data)
{
	t_img	*tmp;
	t_img	*old_pos;
	int		i;
	int 	movements;

	i = 0;
	movements = 0;
	printf("%d\n", keycode);
	tmp = data->images;
	if (keycode == 0)
	{
		while(tmp->mlx_img != data->dementor)
		{
			tmp = tmp->next;
			i++;
		}
		old_pos = tmp;
		tmp = data->images;
		while(i > 1)
		{
			tmp = tmp->next;
			i--;
		}
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			movements++;
		}
		else if (tmp->mlx_img == data->ex)
		{
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
		}
		printf("%d\n", ++data->movements);
	}
	else if (keycode == 1)
	{
		while(tmp->mlx_img != data->dementor)
		{
			tmp = tmp->next;
		}
		old_pos = tmp;
		while (i < (data->map_width))
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
		}
		else if (tmp->mlx_img == data->ex)
		{
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
		}
		printf("%d\n", ++data->movements);
	}
	else if (keycode == 2)
	{
		while(tmp->mlx_img != data->dementor)
		{
			tmp = tmp->next;
		}
		old_pos = tmp;
		tmp = tmp->next;
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			movements++;
		}
		else if (tmp->mlx_img == data->ex)
		{
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
		}
		printf("%d\n", ++data->movements);
	}
	else if (keycode == 13)
	{
		while(tmp->mlx_img != data->dementor)
		{
			tmp = tmp->next;
			i++;
		}
		old_pos = tmp;
		i = i - data->map_width;
		tmp = data->images;
		while (i > 0)
		{
			tmp = tmp->next;
			i--;
		}
		if (tmp->mlx_img != data->fence && tmp->mlx_img != data->ex)
		{
			i = i - data->map_width;
			while (i > 0)
			{
				tmp = tmp->next;
				i--;
			}
			mlx_put_image_to_window(data->mlx, data->win, data->background, old_pos->x, old_pos->y);
			old_pos->mlx_img = data->background;
			mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
			tmp->mlx_img = data->dementor;
			movements++;
			write(1, &movements, 1);
		}
		else if (tmp->mlx_img == data->ex)
		{
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
		}
		printf("%d\n", ++data->movements);
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

void	ft_map_validation(char	**map, t_data *data)
{
	int	i;
	int	j;
	int	collectible;
	int	dementor;
	int	ex;

	i = 0;
	j = 0;
	collectible = 0;
	dementor = 0;
	ex = 0;
	while (map[i] != NULL)
		i++;
	data->map_height = i;
	data->map_width = ft_strlen(map[0]);
	while (map[0][j] != '\0' && map[data->map_height - 1][j] != '\0')
	{
		if (map[0][j] == '1' && map[data->map_height - 1][j] == '1')
			j++;
		else
		{
			ft_putstr_fd("1Error\nThe map is not valid: the map must be closed/surrounded by walls", 2);
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < data->map_height)
	{
		if (map[i][0] == '1' && map[i][data->map_width - 1] == '1')
			i++;
		else
		{
			ft_putstr_fd("2Error\nThe map is not valid: the map must be closed/surrounded by walls", 2);
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < data->map_height)
	{
		if (ft_strchr(map[i], 'C') != NULL)
			collectible++;
		if (ft_strchr(map[i], 'P') != NULL)
			dementor++;
		if (ft_strchr(map[i], 'E') != NULL)
			ex++;
		i++;
	}
	if ((collectible == 0) || (dementor == 0) || (ex == 0))
	{
		ft_putstr_fd("Error\nThe map is not valid: map must have at least one exit, one collectible, and one starting position", 2);
		exit(EXIT_FAILURE);
	}
}


void	ft_parser(char	**argv, t_data *data)
{
	int		fd;
	int		i;
	int		n;
	char	**map;
	char	*line;

	i = 0;
	data->movements = 0;
	map = (char **)malloc(10 * sizeof(char *));
	if (!map)
	{
		perror("Malloc failed");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
			perror("Failed to open map");
	line = ft_map_read(fd);
	map = ft_split(line, '\n');
	free(line);
	line = NULL;
	ft_map_validation(map, data);
	data->images = ft_fill_window(map, data);
	n = mlx_key_hook(data->win, ft_key, data);
	return;
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("The number of arguments should be 1: file with a map with the .ber extension\n", 2);
		return (1);
	}
	data.filename = "fence.xpm";
	data.filename2 = "back.xpm";
	data.filename3 = "harry.xpm";
	data.filename4 = "exit.xpm";
	data.filename5 = "dementor.xpm";
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
		return (1);
	}
	ft_parser(argv, &data);
	mlx_loop(data.mlx);
	return (0);
}
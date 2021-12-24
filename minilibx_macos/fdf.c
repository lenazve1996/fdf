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
	void	*exit;
	void	*dementor;
	char	*filename;
	char	*filename2;
	char	*filename3;
	char	*filename4;
	char	*filename5;
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
	t_img	*images;
}				t_data;

//int ft_key(int keycode, t_data *data)
//{
//	int	i;
//	int	y;

//	printf("Hello!\n");
//	printf("%d\n", keycode);
//	if (keycode == 0)
//	{
//		i = 0;
//		while (i < 20)
//		{
//			y = 40;
//			while (y < 60)
//				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
//			i++;
//		}
//	}
//	else if (keycode == 1)
//	{
//		i = 40;
//		while (i < 60)
//		{
//			y = 40;
//			while (y < 60)
//				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
//			i++;
//		}
//	}
//	else if (keycode == 2)
//	{
//		i = 80;
//		while (i < 100)
//		{
//			y = 40;
//			while (y < 60)
//				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
//			i++;
//		}
//	}
//	else if (keycode == 13)
//	{
//		i = 40;
//		while (i < 60)
//		{
//			y = 0;
//			while (y < 20)
//				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
//			i++;
//		}
//	}
//}

void	ft_lstadd_front(t_img  **lst, t_img  *new)
{
	new->next = *lst;
	*lst = new;
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

t_img	*ft_fill_window(char **map, t_data *data)
{
	t_img	*head;
	t_img	*new_elem;
	int 	width;
	int 	height;
	int		img_height;
	int		img_height2;
	int		img_width;
	int		img_width2;
	int		x;
	int		y;
	int		str;
	int		c;
	int		i;
	int		flag;

	str = 0;
	c = 0;
	i = 0;
	while (map[i] != NULL)
		i++;
	height = i * 64;
	width = ft_strlen(map[0]) * 64;
	data->win = mlx_new_window(data->mlx, width, height, "fdf");
	if (!data->win)
	{
		perror("Failed to open a new window");
		exit(1);
	}
	data->background = mlx_xpm_file_to_image(data->mlx, data->filename2, &data->img_height, &data->img_width);
	data->fence = mlx_xpm_file_to_image(data->mlx, data->filename, &data->img_height2, &data->img_width2);
	data->harry = mlx_xpm_file_to_image(data->mlx, data->filename3, &data->img_height3, &data->img_width3);
	data->exit = mlx_xpm_file_to_image(data->mlx, data->filename4, &data->img_height4, &data->img_width4);
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
				mlx_put_image_to_window(data->mlx, data->win, data->exit, c * 64, str * 64);
				new_elem = ft_lstnew(data->exit, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			else if (map[str][c] == 'C')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, c * 64, str * 64);
				mlx_put_image_to_window(data->mlx, data->win, data->harry, c * 64, str * 64);
				new_elem = ft_lstnew(data->harry, c * 64, str * 64);
				ft_lstadd_back(&head, new_elem);
			}
			printf("%c\n", map[str][c]);
			printf("%d\n", str * 64);
			printf("%d\n", c * 64);
			c++;
		}
		str++;
	}
	new_elem = head;
	i = 0;
	while(new_elem != NULL)
	{
		printf("--->%d<---\n", i);
		printf("%p\n", new_elem);
		printf("%p\n", new_elem->mlx_img);
		printf("%d\n", new_elem->x);
		printf("%d\n", new_elem->y);
		printf("%p\n\n", new_elem->next);
		new_elem = new_elem->next;
		i++;
	}
	return (head);
	//mlx_put_image_to_window(data->mlx, data->win, data->background, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->fence, 64, 0);
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
	printf("%s\n", line);
	return (line);
}

int	ft_key(int keycode, t_data *data)
{
	t_img	*tmp;
	int		i;

	i = 0;
	printf("Hello!\n");
	printf("%d\n", keycode);
	printf("%p\n", data->images);
	tmp = data->images;
	while(tmp != NULL)
	{
		printf("--->%d<---\n", i);
		printf("%p\n", tmp);
		printf("%p\n", tmp->mlx_img);
		printf("%d\n", tmp->x);
		printf("%d\n", tmp->y);
		printf("%p\n\n", tmp->next);
		tmp = tmp->next;
		i++;
		//printf("%p\n", tmp->next);
	}
	if (keycode == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 60, 200);
	}
	else if (keycode == 1)
	{
		while(tmp->mlx_img != data->dementor)
		{
			printf("%p\n", tmp->mlx_img);
			printf("%p\n", data->dementor);
			printf("%p\n", tmp->next);
			tmp = tmp->next;
			printf("%p\n", tmp->mlx_img);
			//printf("%p\n", tmp->next);
			i++;
		}
		mlx_put_image_to_window(data->mlx, data->win, data->background, tmp->x, tmp->y);
		tmp->mlx_img = data->background;
		tmp = data->images;
		tmp = tmp + i - 1;
		mlx_put_image_to_window(data->mlx, data->win, data->dementor, tmp->x, tmp->y);
		tmp->mlx_img = data->dementor;
	}
	else if (keycode == 2)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 340, 200);
	}
	else if (keycode == 13)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 200, 60);
	}
	//else if (keycode == 53)
	//{

	//}
	return(0);
}

void	ft_parser(char	**argv, t_data *data)
{
	int		fd;
	int		i;
	char	**map;
	char	*line;

	i = 0;
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
	data->images = ft_fill_window(map, data);
	printf("%p\n", data->images);
	mlx_key_hook(data->win, ft_key, data);

}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
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
	//data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	//while (i < 100)
	//{
	//	y = 0;
	//	while (y < 100)
	//	{
	//		my_mlx_pixel_put(&img, i, y, 0x00FF0000);
	//		y++;
	//	}
	//	i++;
	//}
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	ft_parser(argv, &data);
	mlx_loop(data.mlx);
}


//int main()
//{
//	t_param	data;
//	void	*img;
//	char	*addr;
//	int		n;
//	int		img_width;
//	int		img_height;
//	int		bits_per_pixel;
//	int		line_length;
//	int		endian;

//	//t_data	img;
//	int		i;
//	int		y;
//	//char	*relative_path = "/Users/ayajirob/Downloads/abstract-clouds.xpm";

//	i = 0;
//	y = 0;
//	data.mlx = mlx_init();
//	if (!data.mlx)
//	{
//		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
//		return(1);
//	}
//	data.win = mlx_new_window(data.mlx, 1920, 1080, "fdf");
//	if (!data.win)
//	{
//		ft_putstr_fd("Failed to open a new window", 1);
//		return(1);
//	}
//	img = mlx_new_image(data.mlx, 1280, 720);
//	if (!img)
//	{
//		ft_putstr_fd("Failed to make an image", 1);
//		return(1);
//	}
//	//addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
//	while (i < 100 && y < 100)
//	{
//		mlx_pixel_put(data.mlx, data.win, i, y, 0x00FF0000);
//		i++;
//		y++;
//	}
//	mlx_key_hook(data.win, ft_key, &data);
//	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//	//n = mlx_put_image_to_window(mlx, win_ptr, img, 1, 1);
//	//img_ptr = mlx_xpm_file_to_image(ptr_to_connection, relative_path, &img_width, &img_height);
//	//printf("%p\n", img_ptr);
//	mlx_loop(data.mlx);
//}

//int	main(void)
//{
//	void	*mlx;
//	void	*win;
//	void	*img;
//	void	*n_img;
//	char	*filename = "dobby.xpm";
//	char	*filename2 = "abstract-clouds.xpm";
//	int		img_width;
//	int		img_height;

//	img_height = 0;
//	img_width = 0;
//	mlx = mlx_init();
//	win = mlx_new_window(mlx, 1920, 1080, "fdf");
//	//img = mlx_new_image(mlx, 1280, 720);
//	n_img = mlx_xpm_file_to_image(mlx, filename, &img_height, &img_width);
//	mlx_put_image_to_window(mlx, win, n_img, 0, 0);
//	//img = mlx_png_file_to_image(mlx, filename, img_width, img_height);
//	mlx_loop(mlx);
//}
#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;


typedef struct	s_data{
	void	*win;
	void	*mlx;
	void	*background;
	void	*fence;
	void	*harry;
	void	*exit;
	char	*filename;
	char	*filename2;
	char	*filename3;
	char	*filename4;
	int		img_height;
	int		img_height2;
	int		img_height3;
	int		img_height4;
	int		img_width;
	int		img_width2;
	int		img_width3;
	int		img_width4;
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

void 	ft_fill_window(char **map, int i, t_data *data)
{
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

	str = 0;
	c = 0;
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
	while (map[str] != NULL)
	{
		c = 0;
		while(map[str][c] != '\n')
		{
			if (map[str][c] == '1')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->fence, str * 64, c * 64);
			}
			else if (map[str][c] == '0')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, str * 64, c * 64);
			}
			else if (map[str][c] == 'P')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->background, str * 64, c * 64);
				mlx_put_image_to_window(data->mlx, data->win, data->harry, str * 64, c * 64);
			}
			else if (map[str][c] == 'E')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->exit, str * 64, c * 64);
			}
			c++;
		}
		str++;
	}
	//mlx_put_image_to_window(data->mlx, data->win, data->background, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->fence, 64, 0);
}

void	ft_parser(char	**argv, t_data *data)
{
	int	fd;
	int	i;
	char **map;

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
	*map = get_next_line(fd);
	printf("%s", *map);
	while(i < 5)
	{
		i++;
		map++;
		*map = get_next_line(fd);
		printf("%s", *map);
		//printf("%s\n", get_next_line(fd));
		//printf("%s\n", get_next_line(fd));
	}
	map = map - i;
	ft_fill_window(map, i, data);
}

void	ft_key(int keycode, t_data *data)
{
	printf("Hello!\n");
	printf("%d\n", keycode);
	if (keycode == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 60, 200);
	}
	else if (keycode == 1)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 200, 200);
	}
	else if (keycode == 2)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 340, 200);
	}
	else if (keycode == 13)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->harry, 200, 60);
	}
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
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
		return (1);
	}
	//data.win = mlx_new_window(data.mlx, 1280, 720, "fdf");
	//if (!data.win)
	//{
	//	ft_putstr_fd("Failed to open a new window", 1);
	//	return (1);
	//}
	//data.img.mlx_img = mlx_new_image(data.mlx, 1280, 720);
	//if (!data.img.mlx_img)
	//{
	//	ft_putstr_fd("Failed to make an image", 1);
	//	return(1);
	//}
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
	//data.background = mlx_xpm_file_to_image(data.mlx, data.filename2, &img_height, &img_width);
	//data.dobby = mlx_xpm_file_to_image(data.mlx, data.filename, &img_height, &img_width);
	//img_ptr = mlx_xpm_file_to_image(ptr_to_connection, relative_path, &img_width, &img_height);
	//printf("%p\n", img_ptr);
	mlx_key_hook(data.win, ft_key, &data);
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
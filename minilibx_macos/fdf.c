#include <mlx.h>
#include <unistd.h>

typedef struct	s_param {
	void	*win;
	void	*mlx;
}				t_param;


size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (*s++ != '\0')
		length++;
	return (length);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

//int main()
//{
//	void    *mlx;
//	void    *win_ptr;
//	int		n;
//	int		img_width;
//	int		img_height;
//	t_data	img;
//	int		i;
//	int		y;
//	//char	*relative_path = "/Users/ayajirob/Downloads/abstract-clouds.xpm";

//	i = 0;
//	y = 0;
//	mlx = mlx_init();
//	if (!mlx)
//	{
//		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
//		return(1);
//	}
//	win_ptr = mlx_new_window(mlx, 1920, 1080, "fdf");
//	if (!win_ptr)
//	{
//		ft_putstr_fd("Failed to open a new window", 1);
//		return(1);
//	}
//	img.img = mlx_new_image(mlx, 1280, 720);
//	if (!img.img)
//	{
//		ft_putstr_fd("Failed to make an image", 1);
//		return(1);
//	}
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	while (i < 100)
//	{
//		y = 0;
//		while (y < 100)
//		{
//			my_mlx_pixel_put(&img, i, y, 0x00FF0000);
//			y++;
//		}
//		i++;
//	}
//	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//	n = mlx_put_image_to_window(mlx, win_ptr, img.img, 0, 0);
//	//img_ptr = mlx_xpm_file_to_image(ptr_to_connection, relative_path, &img_width, &img_height);
//	//printf("%p\n", img_ptr);
//	mlx_loop(mlx);a
//}

int ft_key(int keycode, t_param *data)
{
	int	i;
	int	y;

	printf("Hello!\n");
	printf("%d\n", keycode);
	if (keycode == 0)
	{
		i = 0;
		while (i < 20)
		{
			y = 40;
			while (y < 60)
				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
			i++;
		}
	}
	else if (keycode == 1)
	{
		i = 40;
		while (i < 60)
		{
			y = 40;
			while (y < 60)
				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
			i++;
		}
	}
	else if (keycode == 2)
	{
		i = 80;
		while (i < 100)
		{
			y = 40;
			while (y < 60)
				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
			i++;
		}
	}
	else if (keycode == 13)
	{
		i = 40;
		while (i < 60)
		{
			y = 0;
			while (y < 20)
				mlx_pixel_put(data->mlx, data->win, i, y++, 0x00FF0000);
			i++;
		}
	}
}

int main()
{
	t_param	data;
	void	*img;
	char	*addr;
	int		n;
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	//t_data	img;
	int		i;
	int		y;
	//char	*relative_path = "/Users/ayajirob/Downloads/abstract-clouds.xpm";

	i = 0;
	y = 0;
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
		return(1);
	}
	data.win = mlx_new_window(data.mlx, 1920, 1080, "fdf");
	if (!data.win)
	{
		ft_putstr_fd("Failed to open a new window", 1);
		return(1);
	}
	img = mlx_new_image(data.mlx, 1280, 720);
	if (!img)
	{
		ft_putstr_fd("Failed to make an image", 1);
		return(1);
	}
	//addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	while (i < 100 && y < 100)
	{
		mlx_pixel_put(data.mlx, data.win, i, y, 0x00FF0000);
		i++;
		y++;
	}
	mlx_key_hook(data.win, ft_key, &data);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//n = mlx_put_image_to_window(mlx, win_ptr, img, 1, 1);
	//img_ptr = mlx_xpm_file_to_image(ptr_to_connection, relative_path, &img_width, &img_height);
	//printf("%p\n", img_ptr);
	mlx_loop(data.mlx);
}
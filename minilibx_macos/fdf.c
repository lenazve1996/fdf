#include <mlx.h>
#include <unistd.h>

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
	void	*dobby;
	char	*filename;
	char	*filename2;
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

void ft_key(int keycode, t_data *data)
{
	int		img_height;
	int		img_height2;
	int		img_width;
	int		img_width2;

	printf("Hello!\n");
	printf("%d\n", keycode);
	if (keycode == 0)
	{
		mlx_destroy_image(data->mlx, data->dobby);
		data->dobby = mlx_xpm_file_to_image(data->mlx, data->filename, &img_height, &img_width);
		mlx_put_image_to_window(data->mlx, data->win, data->dobby, 60, 200);
	}
	else if (keycode == 1)
	{
		mlx_destroy_image(data->mlx, data->dobby);
		data->dobby = mlx_xpm_file_to_image(data->mlx, data->filename, &img_height, &img_width);
		mlx_put_image_to_window(data->mlx, data->win, data->dobby, 200, 200);
	}
	else if (keycode == 2)
	{
		mlx_destroy_image(data->mlx, data->dobby);
		data->dobby = mlx_xpm_file_to_image(data->mlx, data->filename, &img_height, &img_width);
		mlx_put_image_to_window(data->mlx, data->win, data->dobby, 340, 200);
	}
	else if (keycode == 13)
	{
		mlx_destroy_image(data->mlx, data->dobby);
		data->dobby = mlx_xpm_file_to_image(data->mlx, data->filename, &img_height, &img_width);
		mlx_put_image_to_window(data->mlx, data->win, data->dobby, 200, 60);
	}
}

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

int main()
{
	t_data	data;
	void	*background;
	void	*dobby;
	int		img_height;
	int		img_height2;
	int		img_width;
	int		img_width2;

	data.filename = "dobby.xpm";
	data.filename2 = "abstract-clouds.xpm";
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
		return(1);
	}
	data.win = mlx_new_window(data.mlx, 1280, 720, "fdf");
	if (!data.win)
	{
		ft_putstr_fd("Failed to open a new window", 1);
		return(1);
	}
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
	data.background = mlx_xpm_file_to_image(data.mlx, data.filename2, &img_height, &img_width);
	data.dobby = mlx_xpm_file_to_image(data.mlx, data.filename, &img_height, &img_width);
	//img_ptr = mlx_xpm_file_to_image(ptr_to_connection, relative_path, &img_width, &img_height);
	//printf("%p\n", img_ptr);
	mlx_put_image_to_window(data.mlx, data.win, data.background, 0, 0);
	mlx_put_image_to_window(data.mlx, data.win, data.dobby, 200, 200);
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
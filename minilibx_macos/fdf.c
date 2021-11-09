#include <mlx.h>
#include <unistd.h>

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
	void    *ptr_to_connection;
	void    *ptr_to_window;
	
	ptr_to_connection = mlx_init();
	if (!ptr_to_connection)
	{
		ft_putstr_fd("Failed to set up the connection to the graphical system", 1);
		return(1);
	}
	ptr_to_window = mlx_new_window(ptr_to_connection, 1920, 1080,"fdf");
	if (!ptr_to_window)
	{
		ft_putstr_fd("Failed to open a new window", 1);
		return(1);		
	}
	mlx_loop(ptr_to_connection);
}
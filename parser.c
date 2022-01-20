/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:45:38 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/20 12:49:11 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_reading(char *line, char *tmp, int fd)
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

static char	*ft_map_read(int fd)
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

int	ft_parser(char	**argv, t_data *data)
{
	int		fd;
	char	*line;

	data->map = NULL;
	data->ex = NULL;
	data->movements = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_processing("Failed to open map");
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

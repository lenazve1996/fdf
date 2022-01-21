/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:09:36 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/21 13:00:41 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_putstr_fd_ret(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

void	ft_error_inmap_read(char *line, char *tmp, char *str)
{
	free(line);
	if (tmp != NULL)
		free(tmp);
	perror(str);
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

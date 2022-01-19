/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:43:22 by ayajirob          #+#    #+#             */
/*   Updated: 2022/01/19 16:44:08 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	int	ft_count_char_number(int n)
{
	int	counter;

	counter = 0;
	if (n == 0 || n < 0)
		counter++;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static	char	*ft_fill_str(char	*str, int n)
{
	int	sign_flag;

	sign_flag = 0;
	if (n < 0)
		sign_flag = 1;
	else
		n = 0 - n;
	*str = '\0';
	if (n == 0)
		*--str = '0';
	else
	{
		while (n != 0)
		{
			str--;
			*str = (0 - (n % 10)) + '0';
			n = (n - (n % 10)) / 10;
		}
	}
	if (sign_flag == 1)
		*--str = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		number_of_char;
	char	*str;

	number_of_char = ft_count_char_number(n);
	str = (char *)malloc((number_of_char + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	str = str + number_of_char;
	str = ft_fill_str(str, n);
	return (str);
}

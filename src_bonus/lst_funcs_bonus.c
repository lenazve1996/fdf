/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:01:35 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/19 17:33:02 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_lstadd_front(t_img **lst, t_img *new)
{
	new->next = *lst;
	*lst = new;
}

static t_img	*ft_lstlast(t_img *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_img	*ft_lstnew(void	*img, int n, int j)
{
	t_img	*new_element;

	new_element = (t_img *)malloc(sizeof(t_img));
	if (!new_element)
		return (NULL);
	new_element->img = img;
	new_element->x = n;
	new_element->y = j;
	new_element->next = NULL;
	new_element->prev = NULL;
	new_element->direction = 2;
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

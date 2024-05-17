/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:25:17 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/13 16:11:58 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_malloc	*ft_lstlast(t_malloc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_malloc	*ft_lstnew(void *content)
{
	t_malloc	*node;

	node = malloc(sizeof(t_malloc));
	if (node == NULL)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_malloc **lst, t_malloc *new)
{
	t_malloc	*ptr;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}

void	ft_lstclear(t_malloc **lst)
{
	t_malloc	*head;
	t_malloc	*copy;

	if (lst && *lst)
	{
		head = *lst;
		while (head != NULL)
		{
			copy = head;
			free(head->data);
			head = head->next;
			free(copy);
		}
		*lst = NULL;
	}
}

void	*ft_malloc(t_malloc **str, int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_lstclear(str);
		exit(1);
	}
	ft_lstadd_back(str, ft_lstnew(ptr));
	return (ptr);
}

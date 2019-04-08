/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:30:10 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:30:51 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_sort_by_names(DIR *dir, int r)
{
	struct dirent	*inf;
	t_list			*cur;
	t_list			*head;
	int				len;

	inf = readdir(dir);
	cur = ft_lstnew(NULL, 0);
	head = cur;
	len = 1;
	while (inf)
	{
		len++;
		cur->content = ft_strdup(inf->d_name);
		if ((inf = readdir(dir)))
		{
			cur->next = ft_lstnew(NULL, 0);
			cur = cur->next;
		}
	}
	ft_sort_tlist(&head, len);
	return (head);
}

void	ft_sort_by_time(t_f **list)
{
	t_f	*cur;
	t_f	*a;
	t_f	*head;

	cur = *list;
	head = cur;
	while (cur->next)
	{
		cur->next->prev = cur;
		if (cur->next->time > cur->time)
		{
			a = cur->next;
			a->prev = cur->prev;
			(a->prev) ? (a->prev->next = a) : 0;
			(cur->next->next) ? (cur->next->next->prev = cur) : 0;
			cur->next = a->next;
			a->next = cur;
			cur->prev = a;
			head = (cur == head) ? a : head;
			cur = head;
		}
		else
			cur = cur->next;
	}
	*list = head;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:15:49 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 11:46:02 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ft_sort_struct(t_list **lst, t_opt *o)
{
	t_list	*head;
	t_list	*a;

	head = *lst;
	while ((*lst)->next)
	{
		if (o->r && ft_strcmp((*lst)->content, (*lst)->next->content) < 0)
		{
			a = (*lst)->content;
			(*lst)->content = (*lst)->next->content;
			(*lst)->next->content = a;
			*lst = head;
		}
		else if (!(o->r) &&
				ft_strcmp((*lst)->content, (*lst)->next->content) > 0)
		{
			a = (*lst)->content;
			(*lst)->content = (*lst)->next->content;
			(*lst)->next->content = a;
			*lst = head;
		}
		else
			*lst = (*lst)->next;
	}
	*lst = head;
}

t_list			*ft_save_sorted_names(int ac, char **av, t_opt *opt, int i)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_lstnew(NULL, 0);
	head = lst;
	while (++i < ac)
	{
		lst->content = ft_strdup(av[i]);
		(i < ac - 1) ? (lst->next = ft_lstnew(NULL, 0)) : 0;
		lst = lst->next;
	}
	if (!head->content)
		head->content = ft_strdup(".");
	ft_sort_struct(&head, opt);
	return (head);
}

void			ft_save_sorted_files(t_list *names, t_list **lst)
{
	t_list		*head;
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	*lst = ft_lstnew(NULL, 0);
	head = *lst;
	while (names)
	{
		if (lstat(names->content, buf) == 0 &&
				!(S_ISDIR(buf->st_mode & S_IFMT)))
		{
			(*lst)->content = ft_strdup(names->content);
			if (names->next && lstat(names->next->content, buf) == 0 &&
					!(S_ISDIR(buf->st_mode & S_IFMT)))
			{
				(*lst)->next = malloc(sizeof(t_list));
				*lst = (*lst)->next;
			}
		}
		names = names->next;
	}
	*lst = (!(head->content)) ? NULL : head;
	(!(head->content)) ? free(head) : 0;
	free(buf);
}

void			ft_save_sorted_directories(t_list *names, t_list **lst)
{
	t_list		*head;
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	*lst = ft_lstnew(NULL, 0);
	head = *lst;
	while (names)
	{
		if (lstat(names->content, buf) == 0 && (S_ISDIR(buf->st_mode & S_IFMT)))
		{
			(*lst)->content = ft_strdup(names->content);
			if (names->next && lstat(names->next->content, buf) == 0 &&
					(S_ISDIR(buf->st_mode & S_IFMT)))
			{
				(*lst)->next = malloc(sizeof(t_list));
				*lst = (*lst)->next;
			}
		}
		names = names->next;
	}
	*lst = (!(head->content)) ? NULL : head;
	(!(head->content)) ? free(head) : 0;
	free(buf);
}

void			ft_sort_by_time(t_f **list)
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

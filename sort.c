/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:15:49 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:53:11 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_rev(t_list **lst, int r)
{
	t_list	*head;
	t_list	*a;

	while ((*lst)->next)
	{
		if (ft_strcmp((*lst)->content, (*lst)->next->content) < 0)
		{
			a = (*lst)->content;
			(*lst)->content = (*lst)->next->content;
			(*lst)->next->content = a;
			*lst = head;
		}
		else
			*lst = (*lst)->next;
	}
}

void		ft_sort_struct(t_list **lst, int r)
{
	t_list	*head;
	t_list	*a;

	head = *lst;
	if (r)
		ft_rev(lst, r);
	else
	{
		while ((*lst)->next)
		{
			if (ft_strcmp((*lst)->content, (*lst)->next->content) > 0)
			{
				a = (*lst)->content;
				(*lst)->content = (*lst)->next->content;
				(*lst)->next->content = a;
				*lst = head;
			}
			else
				*lst = (*lst)->next;
		}
	}
	*lst = head;
}

t_list		*ft_save_sorted_names(int ac, char **av, t_opt *opt, int i)
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
	ft_sort_struct(&head, opt->r);
	return (head);
}

void		ft_save_sorted_files(t_list *names, t_list **lst)
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
			(*lst)->next = NULL;
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

void		ft_save_sorted_directories(t_list *names, t_list **lst)
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
			(*lst)->next = NULL;
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

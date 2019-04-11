/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:15:49 by astanton          #+#    #+#             */
/*   Updated: 2019/04/10 02:44:41 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	(!(opt->f)) ? ft_sort_tlist(&head) : 0;
	return (head);
}

static void	ft_check_link(char *name, t_list **lst, t_opt *opt)
{
	struct stat	bufer;

	if (opt->one && ((stat(name, &bufer) == 0 &&
		!(S_ISDIR((bufer).st_mode))) || (stat(name, &bufer) == -1)))
	{
		(*lst)->content = ft_strdup(name);
		(*lst)->next = NULL;
	}
	else if (!opt->one)
	{
		(*lst)->content = ft_strdup(name);
		(*lst)->next = NULL;
	}
}

void		ft_save_sorted_files(t_list *names, t_list **lst, t_opt *opt)
{
	t_list		*head;
	struct stat	buf;

	*lst = ft_lstnew(NULL, 0);
	head = *lst;
	while (names)
	{
		if (lstat(names->content, &buf) == 0 && !(S_ISDIR(buf.st_mode)))
			ft_check_link(names->content, lst, opt);
		if (names->next && stat(names->next->content, &buf) == 0 &&
				(*lst)->content && !(S_ISDIR(buf.st_mode)))
		{
			(*lst)->next = malloc(sizeof(t_list));
			*lst = (*lst)->next;
		}
		names = names->next;
	}
	*lst = (!(head->content)) ? NULL : head;
	(!(head->content)) ? free(head) : 0;
}

void		ft_save_sorted_directories(t_list *names, t_list **lst, int o)
{
	t_list		*head;
	struct stat	buf;

	*lst = ft_lstnew(NULL, 0);
	head = *lst;
	while (names)
	{
		if ((o && (stat(names->content, &buf) == 0 && (S_ISDIR(buf.st_mode))))
			|| (lstat(names->content, &buf) == 0 && (S_ISDIR(buf.st_mode))))
		{
			(*lst)->content = ft_strdup(names->content);
			(*lst)->next = NULL;
		}
		if (names->next && stat(names->next->content, &buf) == 0 &&
				(*lst)->content && (S_ISDIR(buf.st_mode)))
		{
			(*lst)->next = malloc(sizeof(t_list));
			*lst = (*lst)->next;
		}
		names = names->next;
	}
	*lst = (!(head->content)) ? NULL : head;
	(!(head->content)) ? free(head) : 0;
}

void		ft_print_error_names(char *str)
{
	ft_putstr_fd("ft_ls: ", 2);
	if (str && str[0] == '\0')
		perror("fts_open");
	else
		perror(str);
}

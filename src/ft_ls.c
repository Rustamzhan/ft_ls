/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:28:47 by astanton          #+#    #+#             */
/*   Updated: 2019/04/09 11:13:57 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_empty_task(t_list **name)
{
	t_list	*cur;

	ft_sort_tlist(name);
	cur = *name;
	while (cur)
	{
		ft_putstr(cur->content);
		ft_putstr("\n");
		cur = cur->next;
	}
	free_names(name, NULL, NULL);
}

static void		ft_save_and_print_empty_task(char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*name;
	t_list			*head;

	dir = opendir(dirname);
	entry = readdir(dir);
	name = NULL;
	while (entry)
	{
		if (!name)
		{
			name = ft_lstnew(NULL, 0);
			head = name;
		}
		if ((entry->d_name)[0] != '.')
			name->content = ft_strdup(entry->d_name);
		if ((entry = readdir(dir)) && name->content)
		{
			name->next = ft_lstnew(NULL, 0);
			name = name->next;
		}
	}
	closedir(dir);
	ft_print_empty_task(&head);
}

static void		ft_error_use(t_list **names, t_list **head, t_list **prev)
{
	free((*names)->content);
	(*names)->content = NULL;
	if (*names == *head)
		*head = (*names)->next;
	else
		(*prev)->next = (*names)->next;
	(*head == (*names)->next) ? (*prev = *head) : 0;
	free(*names);
	*names = NULL;
	*names = (*prev == *head) ? *prev : (*prev)->next;
}

static int		ft_check_for_errors_and_delete_badnames(t_list **names)
{
	t_list		*cur;
	t_list		*prev;
	struct stat	*buf;
	int			i;

	i = 0;
	prev = *names;
	cur = *names;
	buf = (struct stat *)malloc(sizeof(struct stat));
	while (cur)
	{
		if (lstat(cur->content, buf) == -1)
		{
			i = 1;
			ft_print_error_names(cur->content);
			ft_error_use(&cur, names, &prev);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	free(buf);
	return (i);
}

int				main(int ac, char **av)
{
	t_list	*names;
	t_list	*files;
	t_list	*directories;
	t_opt	*option;
	int		i;

	if (ac == 1)
		ft_save_and_print_empty_task(".");
	else
	{
		i = 0;
		i = ft_check_and_save_opt(ac, av, &option, i);
		names = ft_save_sorted_names(ac, av, option, i);
		i = ft_check_for_errors_and_delete_badnames(&names);
		ft_save_sorted_files(names, &files, option);
		ft_save_sorted_directories(names, &directories, option->one);
		if (option->d)
			ft_save_file_attr(names, &option);
		else
			ft_save_files_and_dirs(files, directories, &option, i);
		free(option);
		free_names(&names, &files, &directories);
	}
	return (0);
}

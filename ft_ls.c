/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:28:47 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:23:28 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_empty_task(t_list **name)
{
	t_list	*cur;

	cur = *name;
	ft_sort_struct(name, 0);
	while (cur)
	{
		ft_putstr(cur->content);
		ft_putstr("\n");
		cur = cur->next;
	}
	free_names(name, NULL, NULL);
}

static void		ft_save_empty_task(char *dirname)
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
			name->next = ft_lstnew(NULL, 0);
		name = name->next;
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

static t_list	*ft_check_for_errors_and_delete_badnames(t_list *names)
{
	t_list		*head;
	t_list		*prev;
	struct stat	*buf;

	prev = names;
	head = names;
	buf = (struct stat *)malloc(sizeof(struct stat));
	while (names)
	{
		if (lstat(names->content, buf) == -1)
		{
			ft_print_error(names->content);
			ft_error_use(&names, &head, &prev);
		}
		else
		{
			prev = names;
			names = names->next;
		}
	}
	free(buf);
	return (head);
}

int				main(int ac, char **av)
{
	t_list	*names;
	t_list	*files;
	t_list	*directories;
	t_opt	*option;
	int		i;

	if (ac == 1)
		ft_save_empty_task(".");
	else
	{
		i = 0;
		i = ft_check_and_save_opt(ac, av, &option, i);
		names = ft_save_sorted_names(ac, av, option, i);
		names = ft_check_for_errors_and_delete_badnames(names);
		ft_save_sorted_files(names, &files);
		ft_save_sorted_directories(names, &directories);
		if (files)
			ft_save_file_attr(files, &option);
		if (directories)
			ft_save_dir_inf(files, directories, &option);
		free(option);
		free_names(&names, &files, &directories);
	}
	return (0);
}

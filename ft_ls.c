/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:28:47 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 11:56:05 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_empty_task(char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	dir = opendir(dirname);
	while ((entry = readdir(dir)))
	{
		i = -1;
		if ((entry->d_name)[0] != '.')
		{
			ft_putstr(entry->d_name);
			write(1, "\n", 1);
		}
	}
	closedir(dir);
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
		ft_print_empty_task(".");
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

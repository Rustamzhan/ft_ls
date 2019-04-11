/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:28:20 by astanton          #+#    #+#             */
/*   Updated: 2019/04/09 11:14:18 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_error(char *str)
{
	int	i;

	ft_putstr_fd("ft_ls: ", 2);
	i = 0;
	if (str[0] == '\0')
		perror("fts_open");
	else
	{
		while (str[i] != '\0')
			i++;
		while (i > 0 && str[i] != '/')
			i--;
		if (str[i] == '/')
			i++;
		perror(&(str[i]));
	}
}

struct dirent	*ft_read_after_error(DIR *dir, char *path_name,
		struct dirent *inf, t_opt **option)
{
	if (A || (!A && *(inf->d_name) != '.') || (*option)->f)
		ft_print_error(path_name);
	return (readdir(dir));
}

void			ft_rev_sort(t_f **list)
{
	t_f *cur;

	cur = *list;
	while (cur && cur->next)
	{
		cur->next->prev = cur;
		cur = cur->next;
	}
	*list = cur;
	while (cur && cur->prev)
	{
		cur->next = cur->prev;
		cur = cur->next;
	}
	(cur) ? (cur->next = NULL) : 0;
}

void			ft_save_files_and_dirs(t_list *files,
		t_list *directories, t_opt **option, int i)
{
	if (files)
		ft_save_file_attr(files, option);
	if (directories)
		ft_save_dir(files, directories, option, i);
}

struct dirent	*ft_save_inf(DIR **dir, t_f **list)
{
	struct dirent *inf;

	inf = readdir(*dir);
	(*list)->check = 1;
	(*list)->next = (inf) ? malloc(sizeof(t_f)) : NULL;
	return (inf);
}

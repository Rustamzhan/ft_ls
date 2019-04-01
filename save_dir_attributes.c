/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_dir_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:52:03 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 12:22:17 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_attr(t_f **list, t_opt **option)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	lstat((*list)->path_name, buf);
	(*list)->type = ft_get_type(buf->st_mode);
	(*list)->prev = NULL;
	(*list)->time = buf->st_mtime;
	((*option)->u) ? ((*list)->time = buf->st_atime) : 0;
	((*option)->c) ? ((*list)->time = buf->st_ctime) : 0;
	if ((*option)->l)
	{
		(*list)->time_str = ft_get_time((*list)->time);
		ft_get_owner_and_group_name(buf->st_uid, buf->st_gid, list);
		(*list)->links_number = ft_itoa(buf->st_nlink);
		CUR1 = ft_strlen((*list)->links_number);
		MAX1 = (MAX1 < CUR1) ? CUR1 : MAX1;
		(*list)->size_of_file = ft_itoa(buf->st_size);
		CUR4 = ft_strlen((*list)->size_of_file);
		MAX4 = (MAX4 < CUR4) ? CUR4 : MAX4;
		(*list)->acces = ft_get_acces(buf->st_mode);
		CUR2 = ft_strlen((*list)->owner_name);
		MAX2 = (MAX2 < CUR2) ? CUR2 : MAX2;
		CUR3 = ft_strlen((*list)->group_name);
		MAX3 = (MAX3 < CUR3) ? CUR3 : MAX3;
	}
	free(buf);
}

static void	ft_save_dir_attr(char *name, t_f **list, t_opt **option, DIR *dir)
{
	struct dirent	*inf;
	t_f				*cur;

	inf = readdir(dir);
	cur = *list;
	while (inf)
	{
		cur->dir_name = ft_strdup(name);
		cur->file_name = ft_strdup(inf->d_name);
		cur->path_name = ft_get_path(cur->file_name, name);
		cur->recursive = NULL;
		cur->next_dir = NULL;
		cur->next = NULL;
		save_attr(&cur, option);
		if ((inf = readdir(dir)))
		{
			cur->next = malloc(sizeof(t_f));
			cur = cur->next;
		}
	}
}

static void	ft_recursive_save(t_f **list, t_opt **option)
{
	t_f	*cur;

	cur = *list;
	while (cur)
	{
		if (cur->type == 'd' && ft_strcmp(cur->file_name, ".") &&
				ft_strcmp(cur->file_name, "..") && ((!A && *(cur->file_name) != '.') || A))
		{
			cur->recursive = malloc(sizeof(t_f));
			ft_putstr("\n");
			ft_putstr(cur->path_name);
			ft_putstr(":\n");
			ft_create_and_print_at(cur->path_name, option, &cur->recursive);
			ft_free_dir_list(&cur->recursive, *option);
		}
		else
			cur->recursive = NULL;
		cur = cur->next;
	}
}

static void	ft_create_and_print_at(char *name, t_opt **option, t_f **list)
{
	DIR	*dir;
	t_f	*cur;

	(*option)->max_link_len = 0;
	(*option)->max_user_len = 0;
	(*option)->max_group_len = 0;
	(*option)->max_size_len = 0;
	if ((dir = opendir(name)))
	{
		ft_save_dir_attr(name, list, option, dir);
		closedir(dir);
		print_list(*list, *option);
	}
	else
	{
		free(*list);
		*list = NULL;
		ft_print_error(name);
	}
	((*option)->rec) ? ft_recursive_save(list, option) : 0;
}

void		ft_save_dir_inf(t_list *file, t_list *name, t_opt **option)
{
	t_f	*list;
	t_f	*head;
	int	count;

	count = 0;
	list = malloc(sizeof(t_f));
	head = list;
	while (name)
	{
		if (file || name->next || count)
		{
			ft_putstr("\n");
			ft_putstr(name->content);
			ft_putstr(":\n");
		}
		ft_create_and_print_at(name->content, option, &list);
		if (name->next)
		{
			list->next_dir = malloc(sizeof(t_f));
			list = list->next_dir;
		}
		count = 1;
		name = name->next;
	}
	ft_free_dir_list(&head, *option);
}

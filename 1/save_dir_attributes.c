/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_dir_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:52:03 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:39:46 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_attr(t_f **list, t_opt **option)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (lstat((*list)->path_name, buf) == -1)
	{
		(*list)->error = 1;
		ft_print_error((*list)->path_name);
		free((*list)->path_name);
		free((*list)->file_name);
		free(buf);
		return ;
	}
	else
		(*list)->error = 0;	
	(*list)->type = ft_get_type(buf->st_mode);
	(*list)->time = buf->st_mtime;
	((*option)->u) ? ((*list)->time = buf->st_atime) : 0;
	((*option)->c) ? ((*list)->time = buf->st_ctime) : 0;
	if ((*option)->l)
	{
		(*list)->blocks = buf->st_blocks;
		(*list)->time_str = ft_get_time((*list)->time);
		ft_get_owner_and_group_name(buf->st_uid, buf->st_gid, list);
		(*list)->links_number = ft_itoa(buf->st_nlink);
		(*list)->size_of_file = ft_itoa(buf->st_size);
		if ((*list)->type == 'b' || (*list)->type == 'c')
		{
			(*list)->upper_num = ft_itoa(major(buf->st_rdev));
			(*list)->lower_num = ft_itoa(minor(buf->st_rdev));
		}
		(*list)->acces = ft_get_acces(buf->st_mode);
		ft_check_for_max(list, option);
	}
	free(buf);
}

static void	ft_save_dir_a(char *dir, t_list **name, t_f **list, t_opt **option)
{
	struct dirent	*inf;
	t_f				*cur;

	cur = *list;
	cur->prev = NULL;
	while (*name)
	{
		cur->file_name= ft_strdup((*name)->content);
		cur->path_name = ft_get_path(cur->file_name, dir);
		cur->recursive = NULL;
		cur->next = NULL;
		save_attr(&cur, option);
		(!cur->error && (A || (!A && (*(cur->file_name) != '.')))) ?
			(*option)->all_bl += cur->blocks : 0;
		if ((*name = (*name)->next) && !cur->error)
		{
			cur->next = malloc(sizeof(t_f));
			cur->next->prev = cur;
			cur = cur->next;
		}
	}
	free_names(name, NULL, NULL);
}

static void	ft_recursive_save(t_f **list, t_opt **option)
{
	t_f	*cur;

	cur = *list;
	while (cur)
	{
		if (cur->type == 'd' && !(*list)->error && ft_strcmp(cur->file_name, ".") &&
				ft_strcmp(cur->file_name, "..") &&
				((!A && *(cur->file_name) != '.') || A))
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
		cur = ((*option)->r) ? cur->prev : cur->next;
	}
}

static void	ft_create_and_print_at(char *name, t_opt **option, t_f **list)
{
	DIR		*dir;
	t_f		*cur;
	t_list	*names;

	ft_null_max(option);
	if ((dir = opendir(name)))
	{
		names = ft_sort_by_names(dir, 0);
		closedir(dir);
		ft_save_dir_a(name, &names, list, option);
		((*option)->t) ? ft_sort_by_time(list) : 0;
		((*option)->r) ? ft_rev_sort(list) : 0;
		print_list(*list, *option);
	}
	else
	{
		cur->error = 1;
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
		ft_free_dir_list(&head, *option);
		if (name->next)
			list = malloc(sizeof(t_f));
		count = 1;
		name = name->next;
	}
}

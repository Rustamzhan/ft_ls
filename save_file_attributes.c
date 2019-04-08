/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file_attributes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:08:47 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 11:14:33 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_attr(char *name, t_opt **option, struct stat *buf, t_f **list)
{
	(*list)->file_name = ft_strdup(name);
	(*list)->path_name = NULL;
	(*list)->type = ft_get_type(buf->st_mode);
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
}

static void	ft_free_files_list(t_f **head, t_opt *o)
{
	t_f	*f;

	f = *head;
	while (f)
	{
		free(f->file_name);
		if (o->l)
		{
			free(f->time_str);
			free(f->links_number);
			free(f->size_of_file);
			free(f->acces);
			free(f->owner_name);
			free(f->group_name);
		}
		f = f->next;
		free(*head);
		*head = f;
	}
}

void		ft_save_file_attr(t_list *names, t_opt **option)
{
	t_f			*list;
	t_f			*head;
	struct stat	*buf;

	list = malloc(sizeof(t_f));
	head = list;
	buf = malloc(sizeof(struct stat));
	while (names)
	{
		lstat(names->content, buf);
		ft_attr(names->content, option, buf, &list);
		list->prev = NULL;
		list->next = NULL;
		if (names->next)
		{
			list->next = malloc(sizeof(t_f));
			list = list->next;
		}
		names = names->next;
	}
	free(buf);
	((*option)->t && !((*option)->f)) ? ft_sort_by_time(&list) : 0;
	((*option)->r && !((*option)->f)) ? ft_rev_sort(&list) : 0;
	print_list(head, *option);
	ft_free_files_list(&head, *option);
}

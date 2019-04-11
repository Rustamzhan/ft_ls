/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file_attributes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:08:47 by astanton          #+#    #+#             */
/*   Updated: 2019/04/10 02:25:00 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_attr(char *name, t_opt **option, struct stat *buf, t_f **list)
{
	lstat(name, buf);
	(*list)->file_name = ft_strdup(name);
	(*list)->check = 0;
	(*list)->type = ft_get_type(buf->st_mode);
	(*list)->size = buf->st_size;
	(*list)->time = buf->st_mtime;
	((*option)->burn) ? ((*list)->time = buf->st_birthtime) : 0;
	((*option)->u) ? ((*list)->time = buf->st_atime) : 0;
	((*option)->c) ? ((*list)->time = buf->st_ctime) : 0;
	if ((*option)->l || (*option)->g)
	{
		ft_get_time((*list)->time, &((*list)->time_str));
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

void		ft_get_file_inf(t_f **list, t_opt **option, struct stat *buf)
{
	char	linkbuf[1025];
	int		len;

	len = readlink((*list)->file_name, linkbuf, 1025);
	linkbuf[len] = '\0';
	if (lstat(linkbuf, buf) && !(S_ISDIR(buf->st_mode & S_IFMT)))
	{
		(*list)->next = malloc(sizeof(t_f));
		*list = (*list)->next;
		ft_attr(linkbuf, option, buf, list);
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

static void	ft_sorting(t_f **head, t_opt **option)
{
	(!(*option)->f) ? ft_sort_tf(head) : 0;
	(((*option)->t) && !(*option)->sort && !((*option)->f)) ?
		ft_sort_by_time(head) : 0;
	((*option)->sort && !(*option)->f) ? ft_sort_by_size(head) : 0;
	((*option)->r && !((*option)->f)) ? ft_rev_sort(head) : 0;
}

void		ft_save_file_attr(t_list *names, t_opt **option)
{
	t_f			*list;
	t_f			*head;
	struct stat	buf;

	list = malloc(sizeof(t_f));
	head = list;
	while (names)
	{
		ft_attr(names->content, option, &buf, &list);
		list->path_name = list->file_name;
		list->prev = NULL;
		list->next = NULL;
		if (names->next)
		{
			list->next = malloc(sizeof(t_f));
			list = list->next;
		}
		names = names->next;
	}
	ft_sorting(&head, option);
	print_list(head, *option);
	ft_free_files_list(&head, *option);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:17:48 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 19:54:50 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_names(t_list **lst, t_list **f, t_list **d)
{
	t_list *cur;

	while (*lst)
	{
		free((*lst)->content);
		cur = (*lst)->next;
		free(*lst);
		*lst = NULL;
		*lst = cur;
	}
	while (f && *f)
	{
		free((*f)->content);
		cur = (*f)->next;
		free(*f);
		*f = NULL;
		*f = cur;
	}
	while (d && *d)
	{
		free((*d)->content);
		cur = (*d)->next;
		free(*d);
		*d = cur;
	}
}

void	ft_free_dir_list(t_f **list, t_opt *o)
{
	t_f	*f;

	f = *list;
	while (f)
	{
		free(f->path_name);
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
		free(*list);
		*list = NULL;
		*list = f;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:43:02 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 12:10:18 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_spaces(int max, int cur)
{
	int	i;
	int	j;

	i = -1;
	j = max - cur;
	while (++i <= j)
		write(1, " ", 1);
}

void		ft_print_error(char *str)
{
	ft_putstr("ft_ls: ");
	perror(str);
}

static void	ft_rev_sort(t_f **list)
{
	t_f *cur;

	cur = *list;
	while (cur->next)
	{
		cur->next->prev = cur;
		cur = cur->next;
	}
	*list = cur;
}

static void	ft_print_l(t_f *list, t_opt *opt)
{
	ft_putchar(list->type);
	ft_putstr(list->acces);
	ft_print_spaces(opt->max_link_len, list->link_len);
	ft_putstr(list->links_number);
	ft_print_spaces(opt->max_user_len, list->user_len);
	ft_putstr(list->owner_name);
	ft_print_spaces(opt->max_group_len, list->group_len - 1);
	ft_putstr(list->group_name);
	ft_print_spaces(opt->max_size_len, list->size_len - 1);
	ft_putstr(list->size_of_file);
	write(1, " ", 1);
	ft_putstr(list->time_str);
	write(1, " ", 1);
}

void		print_list(t_f *list, t_opt *opt)
{
	(opt->t) ? ft_sort_by_time(&list) : 0;
	(opt->r) ? ft_rev_sort(&list) : 0;
	while (list)
	{
		if (opt->a || (list->file_name)[0] != '.')
		{
			if (opt->l == 1)
				ft_print_l(list, opt);
			ft_putstr(list->file_name);
			write(1, "\n", 1);
		}
		list = (opt->r) ? list->prev : list->next;
	}
}

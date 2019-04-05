/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:43:02 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:27:59 by astanton         ###   ########.fr       */
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

static void	ft_print_dev(t_f *list, t_opt *opt)
{
	ft_print_spaces(opt->max_upper_num, list->upper_len - 1);
	ft_putstr(list->upper_num);
	write(1, ",", 1);
	ft_print_spaces(opt->max_lower_num, list->lower_len);
	ft_putstr(list->lower_num);
}

static void	ft_print_link(char *path)
{
	char	linkbuf[1025];
	int		len;

	len = readlink(path, linkbuf, 1025);
	linkbuf[len] = '\0';
	write(1, " -> ", 4);
	ft_putstr(linkbuf);
}

static void	ft_print_l(t_f *list, t_opt *opt)
{
	ft_putchar(list->type);
	ft_putstr(list->acces);
	ft_print_spaces(opt->max_link_len, list->link_len);
	ft_putstr(list->links_number);
	write(1, " ", 1);
	ft_putstr(list->owner_name);
	ft_print_spaces(opt->max_user_len, list->user_len - 1);
	ft_putstr(list->group_name);
	ft_print_spaces(opt->max_group_len, list->group_len);
	if (list->type == 'b' || list->type == 'c')
		ft_print_dev(list, opt);
	else
	{
		(opt->max_upper_num) ?
			ft_print_spaces(opt->max_upper_num + opt->max_lower_num + 1, 0) : 0;
		ft_print_spaces(opt->max_size_len, list->size_len);
		ft_putstr(list->size_of_file);
	}
	write(1, " ", 1);
	ft_putstr(list->time_str);
	write(1, " ", 1);
}

void		print_list(t_f *list, t_opt *opt)
{
	(opt->l && list->path_name) ? ft_putstr("total ") : 0;
	(opt->l && list->path_name) ? ft_putnbr(opt->all_bl) : 0;
	(opt->l && list->path_name) ? ft_putstr("\n") : 0;
	while (list)
	{
		if ((opt->a || *(list->file_name) != '.') && !list->error)
		{
			if (opt->l == 1)
				ft_print_l(list, opt);
			ft_putstr(list->file_name);
			if (list->type == 'l')
				ft_print_link(list->path_name);
			write(1, "\n", 1);
		}
		list = (opt->r) ? list->prev : list->next;
	}
}

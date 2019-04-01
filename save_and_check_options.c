/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_and_check_options.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:46:08 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 11:40:55 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_usage_error(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-Raclrtu] [file ...]\n");
	exit(2);
}

static void	ft_save_option(char c, t_opt **opt)
{
	(*opt)->rec = (c == 'R') ? 1 : (*opt)->rec;
	(*opt)->a = (c == 'a') ? 1 : (*opt)->a;
	(*opt)->c = (c == 'c') ? 1 : (*opt)->c;
	(*opt)->r = (c == 'r') ? 1 : (*opt)->r;
	(*opt)->t = (c == 't') ? 1 : (*opt)->t;
	(*opt)->l = (c == 'l') ? 1 : (*opt)->l;
	(*opt)->u = (c == 'u') ? 1 : (*opt)->u;
}

static void	ft_zero_option(t_opt **o)
{
	t_opt	*a;

	a = *o;
	a->rec = 0;
	a->a = 0;
	a->l = 0;
	a->r = 0;
	a->t = 0;
	a->u = 0;
	a->c = 0;
	a->max_link_len = 0;
	a->max_user_len = 0;
	a->max_group_len = 0;
	a->max_size_len = 0;
}

int			ft_check_and_save_opt(int ac, char **av, t_opt **opt, int i)
{
	int	j;

	if (!(*opt = (t_opt *)malloc(sizeof(t_opt))))
		exit(1);
	ft_zero_option(opt);
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j] != '\0')
			{
				if (!ft_strchr("Raclrtu", av[i][j]))
				{
					free(*opt);
					ft_print_usage_error(av[i][j]);
				}
				ft_save_option(av[i][j], opt);
			}
		}
		else
			return (i - 1);
	}
	return (i);
}

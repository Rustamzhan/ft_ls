/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_and_check_options.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:46:08 by astanton          #+#    #+#             */
/*   Updated: 2019/04/10 02:19:57 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_usage_error(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ft_ls [-1RSUacdgflprtu] [file ...]\n", 2);
	exit(1);
}

static void	ft_save_option(char c, t_opt **opt)
{
	(*opt)->l = (c == '1') ? 0 : (*opt)->l;
	(*opt)->g = (c == '1') ? 0 : (*opt)->g;
	(*opt)->c = (c == 'u' || c == 'U') ? 0 : (*opt)->c;
	(*opt)->u = (c == 'c' || c == 'U') ? 0 : (*opt)->u;
	(*opt)->burn = (c == 'c' || c == 'u') ? 0 : (*opt)->burn;
	(*opt)->one = (c == '1') ? 1 : (*opt)->one;
	(*opt)->rec = (c == 'R') ? 1 : (*opt)->rec;
	(*opt)->a = (c == 'a') ? 1 : (*opt)->a;
	(*opt)->d = (c == 'd') ? 1 : (*opt)->d;
	(*opt)->g = (c == 'g') ? 1 : (*opt)->g;
	(*opt)->f = (c == 'f') ? 1 : (*opt)->f;
	(*opt)->c = (c == 'c') ? 1 : (*opt)->c;
	(*opt)->p = (c == 'p') ? 1 : (*opt)->p;
	(*opt)->r = (c == 'r') ? 1 : (*opt)->r;
	(*opt)->sort = (c == 'S') ? 1 : (*opt)->sort;
	(*opt)->t = (c == 't') ? 1 : (*opt)->t;
	(*opt)->l = (c == 'l') ? 1 : (*opt)->l;
	(*opt)->u = (c == 'u') ? 1 : (*opt)->u;
	(*opt)->burn = (c == 'U') ? 1 : (*opt)->burn;
}

static void	ft_zero_option(t_opt **o)
{
	t_opt	*a;

	a = *o;
	a->rec = 0;
	a->one = 0;
	a->a = 0;
	a->d = 0;
	a->g = 0;
	a->f = 0;
	a->l = 0;
	a->p = 0;
	a->r = 0;
	a->sort = 0;
	a->t = 0;
	a->u = 0;
	a->burn = 0;
	a->c = 0;
	a->all_bl = 0;
	a->max_link_len = 0;
	a->max_user_len = 0;
	a->max_group_len = 0;
	a->max_size_len = 0;
	a->max_upper_num = 0;
	a->max_lower_num = 0;
}

int			ft_check_and_save_opt(int ac, char **av, t_opt **opt, int i)
{
	int	j;

	*opt = (t_opt *)malloc(sizeof(t_opt));
	ft_zero_option(opt);
	while (++i < ac)
	{
		if (av[i][0] == '-' && av[i][1] != '\0')
		{
			if (av[i][1] == '-' && av[i][2] == '\0')
				return (i);
			j = 0;
			while (av[i][++j] != '\0')
			{
				if (!ft_strchr("1RSUacdgflprtu", av[i][j]))
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

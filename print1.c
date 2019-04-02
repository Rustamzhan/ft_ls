/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:28:20 by astanton          #+#    #+#             */
/*   Updated: 2019/04/02 20:53:40 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error(char *str)
{
	ft_putstr("ft_ls: ");
	perror(str);
}

void	ft_rev_sort(t_f **list)
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

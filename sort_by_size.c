/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:25:12 by astanton          #+#    #+#             */
/*   Updated: 2019/04/10 02:25:27 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_sort_massive(t_f **stack, int i, int len)
{
	int	count;
	t_f	*temp;

	count = 0;
	while (--i > 0)
	{
		if (stack[i]->size > stack[i - 1]->size)
		{
			temp = stack[i];
			stack[i] = stack[i - 1];
			stack[i - 1] = temp;
			count = 1;
		}
		if (i == 1 && count)
		{
			count = 0;
			i = len - 1;
		}
	}
}

void		ft_sort_by_size(t_f **list)
{
	t_f	**stack;
	t_f	*cur;
	int	i;
	int	len;

	len = ft_list_len(*list);
	stack = malloc(sizeof(t_list *) * len);
	cur = *list;
	i = -1;
	while (cur)
	{
		stack[++i] = cur;
		cur = cur->next;
	}
	stack[++i] = NULL;
	ft_sort_massive(&stack[0], i, len);
	i = -1;
	while (++i < len - 1)
		stack[i]->next = stack[i + 1];
	*list = stack[0];
	free(stack);
}

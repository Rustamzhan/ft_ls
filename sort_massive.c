/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_massive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:55:50 by astanton          #+#    #+#             */
/*   Updated: 2019/04/09 10:56:45 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_listlen(t_list *list)
{
	int len;

	len = 1;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

static void	ft_sort_massive_tlist(t_list **stack, int i, int len)
{
	int		count;
	t_list	*temp;

	count = 0;
	while (--i > 0)
	{
		if (ft_strcmp(stack[i]->content, stack[i - 1]->content) < 0)
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

void		ft_sort_tlist(t_list **list)
{
	t_list	**stack;
	t_list	*cur;
	int		i;
	int		len;

	len = ft_listlen(*list);
	stack = malloc(sizeof(t_list *) * len);
	cur = *list;
	i = -1;
	while (cur)
	{
		stack[++i] = cur;
		cur = cur->next;
	}
	stack[++i] = NULL;
	ft_sort_massive_tlist(&stack[0], i, len);
	i = -1;
	while (++i < len - 1)
		stack[i]->next = stack[i + 1];
	*list = stack[0];
	free(stack);
}

static void	ft_sort_massive_tf(t_f **stack, int i, int len)
{
	int	count;
	t_f	*temp;

	count = 0;
	while (--i > 0)
	{
		if (ft_strcmp(stack[i]->file_name, stack[i - 1]->file_name) < 0)
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

void		ft_sort_tf(t_f **list)
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
	ft_sort_massive_tf(&stack[0], i, len);
	i = -1;
	while (++i < len - 1)
		stack[i]->next = stack[i + 1];
	*list = stack[0];
	free(stack);
}

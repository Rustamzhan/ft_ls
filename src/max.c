/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:40:06 by astanton          #+#    #+#             */
/*   Updated: 2019/04/09 10:52:21 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_check_for_max(t_f **list, t_opt **option)
{
	if (A || *(*list)->file_name != '.' || (*option)->f)
	{
		CUR1 = ft_strlen((*list)->links_number);
		MAX1 = (MAX1 < CUR1) ? CUR1 : MAX1;
		CUR2 = ft_strlen((*list)->owner_name);
		MAX2 = (MAX2 < CUR2) ? CUR2 : MAX2;
		CUR3 = ft_strlen((*list)->group_name);
		MAX3 = (MAX3 < CUR3) ? CUR3 : MAX3;
		CUR4 = ft_strlen((*list)->size_of_file);
		MAX4 = (MAX4 < CUR4) ? CUR4 : MAX4;
		if ((*list)->type == 'b' || (*list)->type == 'c')
		{
			CUR5 = ft_strlen((*list)->upper_num);
			MAX5 = (MAX5 < CUR5) ? CUR5 : MAX5;
			CUR6 = ft_strlen((*list)->lower_num);
			MAX6 = (MAX6 < CUR6) ? CUR6 : MAX6;
		}
	}
}

void	ft_null_max(t_opt **option)
{
	(*option)->max_link_len = 0;
	(*option)->max_user_len = 0;
	(*option)->max_group_len = 0;
	(*option)->max_size_len = 0;
	(*option)->max_upper_num = 0;
	(*option)->max_lower_num = 0;
	(*option)->all_bl = 0;
}

int		ft_len_of_struct(t_f *head)
{
	int	len;

	len = 1;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

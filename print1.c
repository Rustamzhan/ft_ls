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
	int	i;

	ft_putstr("ft_ls: ");
	i = 0;
	while (str[i] != '\0')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	if (str[i] == '/')
		i++;
	perror(&(str[i]));
}

struct dirent	*ft_read_after_error(DIR *dir, char *path_name, struct dirent *inf, t_opt **option)
{
	if (A || (!A && *(inf->d_name) != '.') || (*option)->f)
        ft_print_error(path_name);
    return (readdir(dir));
}

void	ft_rev_sort(t_f **list)
{
	t_f *cur;

	cur = *list;
	while (cur && cur->next)
	{
		cur->next->prev = cur;
		cur = cur->next;
	}
	*list = cur;
	while (cur && cur->prev)
	{
		cur->next = cur->prev;
		cur = cur->next;
	}
	(cur) ? (cur->next = NULL) : 0;
}

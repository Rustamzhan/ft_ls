/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:37:32 by astanton          #+#    #+#             */
/*   Updated: 2019/04/10 02:38:09 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_get_path(char *name, char *path)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(path) + 2));
	i = -1;
	j = -1;
	while (path[++i] != '\0')
		str[++j] = path[i];
	(str[j] == '/') ? 0 : (str[++j] = '/');
	i = -1;
	while (name[++i] != '\0')
		str[++j] = name[i];
	str[++j] = '\0';
	return (str);
}

void	ft_get_time(time_t date, char **t)
{
	char	*str;
	int		i;
	int		j;

	i = 3;
	j = -1;
	str = ctime(&date);
	*t = malloc(sizeof(char) * 13);
	while (++i < 11)
		(*t)[++j] = str[i];
	if (time(NULL) - date > 15811200 || (date - time(NULL) > 0))
	{
		i = 18;
		while (++i < 24)
			(*t)[++j] = str[i];
		((*t)[j] == ' ') ? (j -= 4) : 0;
		if ((*t)[j] == ' ')
			while (i < 29)
				(*t)[++j] = str[i++];
	}
	else
		while (i < 16)
			(*t)[++j] = str[i++];
	(*t)[++j] = '\0';
}

char	ft_get_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISLNK(mode))
		return ('l');
	else
		return ('-');
}

char	*ft_get_acces(mode_t mode)
{
	char	*str;

	str = malloc(sizeof(char) * 10);
	str[9] = '\0';
	str[0] = (S_IRUSR & mode) ? 'r' : '-';
	str[1] = (S_IWUSR & mode) ? 'w' : '-';
	str[2] = (S_IXUSR & mode) ? 'x' : '-';
	str[3] = (mode & S_IRGRP) ? 'r' : '-';
	str[4] = (mode & S_IWGRP) ? 'w' : '-';
	str[5] = (mode & S_IXGRP) ? 'x' : '-';
	str[6] = (mode & S_IROTH) ? 'r' : '-';
	str[7] = (mode & S_IWOTH) ? 'w' : '-';
	str[8] = (mode & S_IXOTH) ? 'x' : '-';
	return (str);
}

void	ft_get_owner_and_group_name(uid_t uid, gid_t gid, t_f **list)
{
	struct passwd	*p;
	struct group	*g;

	p = getpwuid(uid);
	(*list)->owner_name = ft_strdup(p->pw_name);
	g = getgrgid(gid);
	(*list)->group_name = ft_strdup(g->gr_name);
}

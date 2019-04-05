/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:24:03 by astanton          #+#    #+#             */
/*   Updated: 2019/04/01 11:40:00 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# define MAX1 ((*option)->max_link_len)
# define MAX2 ((*option)->max_user_len)
# define MAX3 ((*option)->max_group_len)
# define MAX4 ((*option)->max_size_len)
# define MAX5 ((*option)->max_upper_num)
# define MAX6 ((*option)->max_lower_num)
# define CUR1 ((*list)->link_len)
# define CUR2 ((*list)->user_len)
# define CUR3 ((*list)->group_len)
# define CUR4 ((*list)->size_len)
# define CUR5 ((*list)->upper_len)
# define CUR6 ((*list)->lower_len)
# define A ((*option)->a)

typedef struct	s_file_attr
{
	char				*upper_num;
	char				*lower_num;
	char				*path_name;
	char				*dir_name;
	char				type;
	char				*acces;
	char				*links_number;
	char				*owner_name;
	char				*group_name;
	char				*size_of_file;
	time_t				time;
	char				*time_str;
	char				*file_name;
	struct s_file_attr	*next;
	struct s_file_attr	*prev;
	struct s_file_attr	*recursive;
	int					blocks;
	int					link_len;
	int					user_len;
	int					group_len;
	int					size_len;
	int					upper_len;
	int					lower_len;
	int					error;
}				t_f;

typedef struct	s_options
{
	int	all_bl;
	int	max_link_len;
	int	max_user_len;
	int	max_group_len;
	int	max_size_len;
	int	max_upper_num;
	int max_lower_num;
	int	rec;
	int	a;
	int	r;
	int	t;
	int	l;
	int	u;
	int	c;
}				t_opt;

static void		ft_create_and_print_at(char *name, t_opt **option, t_f **list);
void			ft_save_sorted_directories(t_list *names, t_list **lst);
void			ft_save_sorted_files(t_list *names, t_list **lst);
t_list			*ft_save_sorted_names(int ac, char **av, t_opt *opt, int i);
void			free_names(t_list **lst, t_list **f, t_list **d);
void			ft_print_error(char *str);
void			print_list(t_f *list, t_opt *opt);
int				ft_check_and_save_opt(int ac, char **av, t_opt **opt, int i);
void			ft_get_owner_and_group_name(uid_t uid, gid_t gid, t_f **list);
char			*ft_get_acces(mode_t mode);
char			ft_get_type(mode_t mode);
char			*ft_get_time(time_t date);
char			*ft_get_path(char *name, char *path);
void			ft_save_dir_inf(t_list *file, t_list *name, t_opt **option);
void			ft_save_file_attr(t_list *names, t_opt **option);
void			ft_sort_by_time(t_f **list);
void			ft_free_dir_list(t_f **list, t_opt *o);
void			ft_rev_sort(t_f **list);
void			ft_sort_struct(t_list **lst, int r);
t_list			*ft_sort_by_names(DIR *dir, int r);
void			ft_check_for_max(t_f **list, t_opt **option);
void			ft_null_max(t_opt **option);

#endif

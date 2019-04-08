#include "ft_ls.h"

static void	save_attr(t_f **list, t_opt **option, struct stat *buf, struct dirent *inf)
{
    (*list)->prev = NULL;
    (*list)->file_name = ft_strdup(inf->d_name);
	(*list)->type = ft_get_type(buf->st_mode);
	(*list)->time = buf->st_mtime;
	((*option)->u) ? ((*list)->time = buf->st_atime) : 0;
	((*option)->c) ? ((*list)->time = buf->st_ctime) : 0;
	if ((*option)->l)
	{
		(*list)->blocks = buf->st_blocks;
        (*option)->all_bl += (A || (!A && (*((*list)->file_name) != '.'))) ?
	        (*list)->blocks : 0;
		(*list)->time_str = ft_get_time((*list)->time);
		ft_get_owner_and_group_name(buf->st_uid, buf->st_gid, list);
		(*list)->links_number = ft_itoa(buf->st_nlink);
		(*list)->size_of_file = ft_itoa(buf->st_size);
		if ((*list)->type == 'b' || (*list)->type == 'c')
		{
			(*list)->upper_num = ft_itoa(major(buf->st_rdev));
			(*list)->lower_num = ft_itoa(minor(buf->st_rdev));
		}
		(*list)->acces = ft_get_acces(buf->st_mode);
		ft_check_for_max(list, option);
	}
}

static void	ft_recursive_save(t_f **list, t_opt **option)
{
	t_f	*cur;

	cur = *list;
	while (cur)
	{
		if (cur->type == 'd' && ft_strcmp(cur->file_name, ".") &&
				ft_strcmp(cur->file_name, "..") &&
				((!A && *(cur->file_name) != '.') || A || (*option)->f))
		{
			ft_putstr("\n");
			ft_putstr(cur->path_name);
			ft_putstr(":\n");
			ft_save_and_print(cur->path_name, option);
		}
		cur = cur->next;
	}
}

static void ft_save_attr(DIR *dir, char *name, t_opt **option, t_f **head)
{
    char    *path_name;
    struct stat *buf;
    struct dirent *inf;
    t_f *list;

    buf = malloc(sizeof(struct stat));
    inf = readdir(dir);
    while (inf)
    {
        path_name = ft_get_path(inf->d_name, name);
        if (lstat(path_name, buf) == -1)
            inf = ft_read_after_error(dir, path_name, inf, option);
        else if (A || (!A && *(inf->d_name) != '.') || (*option)->f)
        {
            list = (list) ? list->next : malloc(sizeof(t_f));
            *head = (*head) ? *head : list;
            list->path_name = ft_strdup(path_name);
            save_attr(&list, option, buf, inf);
            list->next = ((inf = readdir(dir))) ? malloc(sizeof(t_f)) : NULL;
        }
        else
            inf = readdir(dir);
        free(path_name);
    }
    free(buf);
}

void    ft_save_and_print(char *name, t_opt **option)
{
    DIR *dir;
    t_f *head;
    int len;

    head = NULL;
    ft_null_max(option);
    if (!(dir = opendir(name)))
        ft_print_error(name);
    else
    {
        ft_save_attr(dir, name, option, &head);
        (!(*option)->f) ? len = ft_len_of_struct(head) : 0;
        (!(*option)->f) ? ft_sort_tf(&head, len) : 0; 
        ((*option)->t && !(*option)->f) ? ft_sort_by_time(&head) : 0;
		((*option)->r && !(*option)->f) ? ft_rev_sort(&head) : 0;
        print_list(head, *option);
        ((*option)->rec) ? ft_recursive_save(&head, option) : 0;
        ft_free_dir_list(&head, *option);
        closedir(dir);
    }
}

void    ft_save_dir(t_list  *file, t_list   *dir, t_opt **options)
{
    int count;

    count = 0;
    while (dir)
    {
        if (file || dir->next || count)
    	{
	        (count || file) ? ft_putstr("\n") : 0;
	    	ft_putstr(dir->content);
	    	ft_putstr(":\n");
	    }
        ft_save_and_print(dir->content, options);
        dir = dir->next;
        count = 1;
    }
}
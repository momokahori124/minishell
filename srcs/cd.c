/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/24 02:47:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// t_my_env	*my_env_lstlast(t_my_env *lst)
// {
// 	while (lst->next)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

t_my_env	*make_my_env(char *env_name, char *env_value, t_minishell_info *info)
{
	t_my_env	*new;

	if (!(new = malloc(sizeof(t_my_env))))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	if (!(new->value = ft_strjoin(env_name, env_value)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	new->next = NULL;
	return (new);
}


bool	update_standard_env(char *env_name, char *env_value)
{
	extern char	**environ;
	size_t		i;
	int			j;
	int			k;

	i = 0;
	while (environ[i])
	{

		// if (ft_strcmp("PWD", environ[i]) == 0)
		if (env_name[0] == environ[i][0] &&
			ft_strncmp(env_name, environ[i], ft_strlen(env_name)) == 0)
		{
			puts("IN");
			j = 0;
			printf("before env : %s\n", environ[i]);
			while (environ[i][j++] != '=')
				;
			k = -1;
			printf("after env : %s\n", environ[i] + j);
			printf("env_value : %s\n", env_value);
			while (env_value[++k])
				environ[i][j + k] = env_value[k];
			environ[i][j + k] = '\0';
			printf("after env : %s\n", environ[i]);
			printf("=%s\n", env_value);
			printf("=%s\n", search_env("PWD", 3, NULL));
			// exit(0);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	update_my_env(t_my_env **my_env, char *env_name, char *env_value,
				t_minishell_info *info)
{
	t_my_env	*begin;

	begin = *my_env;
	while (*my_env)
	{
		if ((*my_env)->value[0] == env_name[0] &&
			!ft_strcmp(env_name, (*my_env)->value))
		{
			if (!((*my_env)->value =
					  re_strjoin(&((*my_env)->value), env_name, env_value)))
				all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
			*my_env = begin;
			return (true);
		}
		*my_env = (*my_env)->next;
	}
	if (begin == NULL)
		*my_env = make_my_env(env_name, env_value, info);
	else
	{
		*my_env = make_my_env(env_name, env_value, info);
		*my_env = begin;
	}
	return (true);
}

bool	is_in_env_and_update_if_any(t_my_env **my_env, char *env_name,
			char *env_value, t_minishell_info *info)
{
	extern char	**environ;

	if (update_standard_env(env_name, env_value) == true)
		return (true);
	if (update_my_env(my_env, env_name, env_value, info) == true)
		return (true);
	return (true);
}

void	update_env_value(t_my_env **my_env, char *env_name, char *env_value,
							t_minishell_info *info)
{
	extern char	**environ;

	if (update_standard_env(env_name, env_value) == true)
		return ;
	if (update_my_env(my_env, env_name, env_value, info) == true)
		return ;
	return ;
}

static void	go_to_home(t_minishell_info *info)
{
	char		*cwd;
	char		*home_path;

	cwd = getcwd(NULL, 0);
	update_env_value(&(info->my_env), "OLDPWD=", cwd, info);
	home_path = search_env("HOME", 4, NULL);
	if (chdir(home_path) == -1)
		all_free_perror_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	ptr_free((void **)&cwd);
}

char	*change_to_symbolic_source(char *dir_name, t_minishell_info *info)
{
	char		*res;
	int			i;
	int			j;

	i = 0;
	while (info->current_dir_path[i])
		i++;
	j = 0;
	while (dir_name[j])
		j++;
	if (!(res = malloc(i + j + 2)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (info->current_dir_path[++i])
		res[i] = info->current_dir_path[i];
	res[i++] = '/';
	j = 0;
	while (dir_name[j])
	{
		res[i + j] = dir_name[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

bool	is_symbolic_dir(t_minishell_info *info, char *dir_name)
{
	char	*symbo_src;
	t_stat	stat_buf;

	if (lstat(dir_name, &stat_buf) == -1)
	{
		if (errno == EFAULT || errno == ELOOP || errno == ENOMEM)
			all_free_perror_exit(info, ERR_LSTAT, __LINE__, __FILE__);
		return (false);
	}
	if (S_ISLNK(stat_buf.st_mode) == 0 || S_ISDIR(stat_buf.st_mode))
		return (false);
	symbo_src = change_to_symbolic_source(dir_name, info);
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = symbo_src;
	if (chdir(symbo_src) == -1)
	{
		if (errno == EFAULT || errno == EIO || errno == ENOMEM)
			all_free_perror_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	}
	return (true);
}

void	set_tenten(t_minishell_info *info, char *dir_name)
{
	char	*path;
	char	*cwd;
	int		i;

	i = -1;
	while (info->current_dir_path[++i])
		if (info->current_dir_path[i] == '/')
			path = info->current_dir_path + i;
	if (!(cwd = malloc(i + ft_strlen(dir_name) + 1)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (&info->current_dir_path[++i] != path)
		cwd[i] = info->current_dir_path[i];
	cwd[i] = '\0';
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = cwd;
}

void	set_next_cwd(t_minishell_info *info, char *dir_name)
{
	char	*cwd;
	int		i;
	int		j;

	i = -1;
	while (info->current_dir_path[++i])
		;
	if (!(cwd = malloc(i + ft_strlen(dir_name) + 2)))
		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = -1;
	while (info->current_dir_path[++i])
		cwd[i] = info->current_dir_path[i];
	cwd[i++] = '/';
	j = -1;
	while (dir_name[++j])
		cwd[i + j] = dir_name[j];
	cwd[i + j] = '\0';
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = cwd;
}

// void	set_current_dir(t_minishell_info *info, char *dir_name,
// 			char **ptr)
// {
// 	char	*cwd;
// 	int		i;
// 	int		j;

// 	ptr_free((void **)&(info->current_dir_path));
// 	if (ptr != NULL)
// 		ptr_free((void **)ptr);
// 	i = -1;
// 	while (info->current_dir_path[++i])
// 		;
// 	if (!(cwd = malloc(i + ft_strlen(dir_name) + 2)))
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	i = -1;
// 	while (info->current_dir_path[++i])
// 		cwd[i] = info->current_dir_path[i];
// 	cwd[i++] = '/';
// 	j = -1;
// 	while (dir_name[++j])
// 		cwd[i + j] = dir_name[j];
// 	cwd[i + j] = '\0';
// 	info->current_dir_path = cwd;
// }

static void	go_to_path(t_minishell_info *info, char *dir,
			bool option_p_flag)
{
	// char		*cwd;
	char		*dir_name;

	if (dir == NULL)
		return (go_to_home(info));
	if (dir[0] == '.' && dir[1] == '\0')
		return ;
	// cwd = getcwd(NULL, 0);
	update_env_value(&(info->my_env), "OLDPWD=", info->current_dir_path, info);
	dir_name = dir;
	if (dir[0] == '$' && dir[1] != '\0')
		dir_name = search_env(dir + 1, ft_strlen(dir + 1), info->my_env);
	if (option_p_flag == false)
		if (is_symbolic_dir(info, dir_name) == true)
			return ;
	if (chdir(dir_name) == -1)
	{
		if (errno == EFAULT || errno == EIO || errno == ENOMEM)
			all_free_perror_exit(info, ERR_CHDIR, __LINE__, __FILE__);
		if (write(STDERR_FILENO, "minishell: ", 12) < 0)
			all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		perror(dir_name);
	}
	if (dir_name[0] == '.' && dir_name[1] == '.' && dir_name[2] == '\0')
		return (set_tenten(info, ""));
	else if (dir_name[0] != '.')
		return (set_next_cwd(info, dir));
}

// static void	go_to_normal_dir(t_cmdlst *cmd)
// {
// 	char		*cwd;
// 	char		*path;

// 	if (dir == NULL)
// 		return (go_to_home(info));
// 	cwd = getcwd(NULL, 0);
// 	update_env_value(&(info->my_env), "OLDPWD=", cwd, info);
// 	if (dir[0] == '$' && dir[1] != '\0')
// 		path = search_env(dir + 1, ft_strlen(dir + 1), info->my_env);
// 	else
// 		path = dir;
// 	if (chdir(path) == -1)
// 		all_free_perror_exit(info, ERR_CHDIR, __LINE__, __FILE__);
// 	ptr_free((void **)&cwd);
// }

static void	go_to_oldpwd(t_minishell_info *info)
{
	char		*oldpwd_path;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	oldpwd_path = search_env("OLDPWD", 6, info->my_env);
	if (oldpwd_path == NULL)
	{
		if (write(STDERR_FILENO, NO_OLDPWD, 29) < 0)
			all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
		return ;
	}
	if (chdir(oldpwd_path) == -1)
		all_free_perror_exit(info, ERR_CHDIR, __LINE__, __FILE__);
	if (ft_putendl_fd(oldpwd_path, 1) == false)
	{
		ptr_free((void **)&cwd);
		all_free_perror_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
	update_env_value(&(info->my_env), "OLDPWD=", cwd, info);
	ptr_free((void **)&cwd);
}

void	exec_cd(t_minishell_info *info, t_cmdlst *cmd)
{
	char	**arg;

	arg = cmd->arg;
	if (arg[1] == NULL ||
		(arg[1] != NULL && arg[1][0] == '~' && arg[1][1] == '\0'))
		go_to_home(info);
	else if (arg[1][0] == '-' && arg[1][1] == '\0')
		go_to_oldpwd(info);
	else if (arg[1][0] == '-' && arg[1][1] == 'P' && arg[1][2] == '\0')
		go_to_path(info, arg[2], true);
	else if (arg[1][0] == '-' && arg[1][1] == 'L' && arg[1][2] == '\0')
		go_to_path(info, arg[2], false);
	else
		go_to_path(info, arg[1], false);
}

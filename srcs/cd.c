/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 01:13:20 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/24 17:18:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

static void	go_to_home(t_minishell_info *info)
{
	char		*cwd;
	char		*home_path;

	cwd = getcwd(NULL, 0);
	update_env_value(&(info->env), "OLDPWD=", cwd, info);
	home_path = search_env("HOME", 4, info->env);
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
	update_env_value(&(info->env), "PWD=", info->current_dir_path, info);
	return (true);
}

// void	set_tenten(t_minishell_info *info, char *dir_name)
// {
// 	char	*path;
// 	char	*cwd;
// 	int		i;

// 	i = -1;
// 	while (info->current_dir_path[++i])
// 		if (info->current_dir_path[i] == '/')
// 			path = info->current_dir_path + i;
// 	if (!(cwd = malloc(i + ft_strlen(dir_name) + 1)))
// 		all_free_perror_exit(info, ERR_MALLOC, __LINE__, __FILE__);
// 	i = -1;
// 	while (&info->current_dir_path[++i] != path)
// 		cwd[i] = info->current_dir_path[i];
// 	cwd[i] = '\0';
// 	ptr_free((void **)&(info->current_dir_path));
// 	info->current_dir_path = cwd;
// }

// void	set_next_cwd(t_minishell_info *info, char *dir_name)
// {
// 	char	*cwd;
// 	int		i;
// 	int		j;

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
// 	ptr_free((void **)&(info->current_dir_path));
// 	info->current_dir_path = cwd;
// }

static void	go_to_path(t_minishell_info *info, char *dir,
			bool option_p_flag)
{
	char		*dir_name;

	if (dir == NULL)
		return (go_to_home(info));
	if (dir[0] == '.' && dir[1] == '\0')
		return ;
	update_env_value(&(info->env), "OLDPWD=", info->current_dir_path, info);
	dir_name = dir;
	if (dir[0] == '$' && dir[1] != '\0')
		dir_name = search_env(dir + 1, ft_strlen(dir + 1), info->env);
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
	ptr_free((void **)&(info->current_dir_path));
	info->current_dir_path = getcwd(NULL, 0);
	update_env_value(&(info->env), "PWD=", info->current_dir_path, info);
}

static void	go_to_oldpwd(t_minishell_info *info)
{
	char		*oldpwd_path;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	oldpwd_path = search_env("OLDPWD", 6, info->env);
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
	update_env_value(&(info->env), "OLDPWD=", cwd, info);
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

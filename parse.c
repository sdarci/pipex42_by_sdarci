/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:05:32 by sdarci            #+#    #+#             */
/*   Updated: 2022/02/16 22:42:51 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	parse_files(t_params *arg, const char *f1, const char *f2)
{
	int	i;

	i = 0;
	while (f1[i])
		i++;
	arg->filename1 = malloc(sizeof(char) * (i + 1));
	if (!(arg->filename1))
		return (0);
	(arg->filename1)[i] = 0;
	while (--i >= 0)
		(arg->filename1)[i] = f1[i];
	i = 0;
	while (f2[i])
		i++;
	arg->filename2 = malloc(sizeof(char) * (i + 1));
	if (!(arg->filename2))
		return (0);
	(arg->filename2)[i] = 0;
	while (--i >= 0)
		(arg->filename2)[i] = f2[i];
	return (1);
}

static char	*check_cmd(const char *cmd, size_t s_cmd, char *path, size_t s_path)
{
	char	*new;
	size_t	i;
	int		flg;

	flg = s_path != 0;
	i = -1;
	new = malloc(sizeof(char) * (s_cmd + s_path + 1 + flg));
	if (!new)
		return (NULL);
	while (++i < s_path)
		new[i] = path[i];
	if (flg)
		new[s_path] = '/';
	i = -1;
	while (++i < s_cmd)
		new[i + s_path + flg] = cmd[i];
	new[i + s_path + flg] = 0;
	if (!access(new, X_OK))
		return (new);
	free(new);
	return (NULL);
}

static char	parse_cmd(char **dst, const char *cmd, char *path)
{
	size_t	size_cmd;
	size_t	size_path;

	size_cmd = 0;
	while (cmd[size_cmd])
		size_cmd++;
	*dst = check_cmd(cmd, size_cmd, path, 0);
	if (*dst)
		return (0);
	while (*path)
	{
		size_path = 0;
		while (path[size_path] && path[size_path] != ':')
			size_path++;
		*dst = check_cmd(cmd, size_cmd, path, size_path);
		if (*dst)
			return (0);
		path += size_path + 1;
	}
	return (1);
}

ssize_t	parsa(t_params *arg, char **argv, char *path)
{
	arg->filename1 = NULL;
	arg->filename2 = NULL;
	arg->cmd1 = NULL;
	arg->cmd2 = NULL;
	arg->exist = 0;
	if (!parse_files(arg, argv[0], argv[3]))
		ft_exit(arg, 1);
	if (access(arg->filename1, R_OK) == -1)
		return (write_error(strerror(errno), arg->filename1));
	if (!access(arg->filename2, F_OK) && access(arg->filename2, W_OK) == -1)
		return (write_error(strerror(errno), arg->filename2));
	if (access(arg->filename2, F_OK) == 0)
		arg->exist = 1;
	arg->cmd1 = ft_split(argv[1], ' ');
	arg->cmd2 = ft_split(argv[2], ' ');
	if (!arg->cmd1 || !arg->cmd2)
		ft_exit(arg, 1);
	if (parse_cmd(&((arg->cmd1)[0]), (arg->cmd1)[0], path))
		return (write_error("Command doesn't exist", argv[1]));
	if (parse_cmd(&((arg->cmd2[0])), (arg->cmd2)[0], path))
		return (write_error("Command doesn't exist", argv[2]));
	return (0);
}

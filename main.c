/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:05:32 by sdarci            #+#    #+#             */
/*   Updated: 2022/02/16 22:42:51 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_child(t_params *arg, int fds[2])
{
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	arg->fd = open(arg->filename1, O_RDONLY);
	if (arg->fd < 0)
		ft_exit(arg, 2);
	dup2(arg->fd, 0);
	close(arg->fd);
	execve(arg->cmd1[0], arg->cmd1, arg->pathh);
	ft_exit(arg, 6);
}

static void	do_parent(t_params *arg, int fds[2])
{
	int	status;

	wait(&status);
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	if (arg->exist)
		arg->fd2 = open(arg->filename2, O_WRONLY | O_TRUNC);
	else
		arg->fd2 = open(arg->filename2, O_WRONLY | O_CREAT, S_IRUSR | \
		S_IWUSR | S_IRGRP | S_IROTH);
	if (arg->fd2 < 0)
		ft_exit(arg, 3);
	dup2(arg->fd2, 1);
	close(arg->fd2);
	execve(arg->cmd2[0], arg->cmd2, arg->pathh);
	ft_exit(arg, 6);
}

void	family(t_params *params, int *fdp, pid_t p)
{
	p = fork();
	if (p < 0)
		ft_exit(params, 4);
	else if (p == 0)
		do_child(params, fdp);
	else
		do_parent(params, fdp);
}

int	main(int argc, char **argv, char **env)
{
	t_params	*params;
	pid_t		p_id;
	int			fdpipe[2];

	p_id = 0;
	if (argc - 1 > 4)
		return (write(2, "ERROR: too many arguments\n", 26));
	if (argc - 1 < 4)
		return (write(2, "ERROR: not enough arguments\n", 28));
	params = malloc(sizeof(t_params));
	if (!params)
		ft_exit(params, 1);
	params->pathh = env;
	while (ft_strncmp("PATH=", *env, 5) != 0 && *env)
		env++;
	if ((parsa(params, ++argv, (*env) + 5)))
		ft_exit(params, 0);
	if (pipe(fdpipe) == -1)
		ft_exit(params, 5);
	family(params, fdpipe, p_id);
	ft_exit(params, 0);
}

void	ft_exit(t_params *par, int flg)
{
	if (flg == 1)
		write_error("Not enough memory", "malloc");
	else if (flg == 2)
		write_error(strerror(errno), par->filename1);
	else if (flg == 3)
		write_error(strerror(errno), par->filename2);
	else if (flg == 4)
		write_error(strerror(errno), "fork");
	else if (flg == 5)
		write_error(strerror(errno), "pipe");
	else if (flg == 6)
		write_error(strerror(errno), "execve");
	if (par)
	{
		free(par->filename1);
		free(par->filename2);
		free_split(par->cmd1);
		free_split(par->cmd2);
	}
	free(par);
	exit(flg);
}

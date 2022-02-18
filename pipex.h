/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:05:32 by sdarci            #+#    #+#             */
/*   Updated: 2022/02/16 22:42:51 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct params
{
	char	*filename1;
	char	*filename2;
	int		fd;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	char	**pathh;
	int		exist;
}	t_params;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(t_params *par, int flg);
ssize_t	write_error(char *s_err, char *file);
char	**ft_split(char const *s, char c);
ssize_t	parsa(t_params *arg, char **argv, char *path);
void	free_split(char **spl);
size_t	ft_strlen(const char *s);

#endif

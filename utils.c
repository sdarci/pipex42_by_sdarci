/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:05:32 by sdarci            #+#    #+#             */
/*   Updated: 2022/02/16 22:42:51 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{		
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

ssize_t	write_error(char *s_err, char *filename)
{
	write(2, "ERROR: ", 7);
	write(2, s_err, ft_strlen(s_err));
	write(2, "(", 1);
	write(2, filename, ft_strlen(filename));
	write(2, ").\n", 3);
	return (1);
}

void	free_split(char **spl)
{
	size_t	i;

	i = 0;
	if (spl)
	{
		while (spl[i])
		{
			free(spl[i]);
			i++;
		}
	}
	free(spl);
}

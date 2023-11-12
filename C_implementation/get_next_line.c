/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:51:17 by sstanfel          #+#    #+#             */
/*   Updated: 2023/05/28 18:32:14 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*buff_in_pot(char *pot, int fd)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	i = 1;
	while (!ft_strchr(pot, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(pot);
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		pot = ft_strjoin(pot, str);
	}
	free(str);
	return (pot);
}

char	*complete_line(char *pot)
{
	char	*final_line;
	int		count;

	count = 0;
	if (!pot[count])
		return (NULL);
	final_line = malloc(sizeof(char) * (ft_strlen(pot) + 2));
	if (!final_line)
		return (NULL);
	while (pot[count] && pot[count] != '\n')
	{
		final_line[count] = pot[count];
		count++;
	}
	if (pot[count] == '\n')
	{
		final_line[count] = '\n';
		count++;
	}
	final_line[count] = '\0';
	return (final_line);
}

char	*new_pod(char *old_pot)
{
	char	*new_pot;
	int		count;
	int		i;

	i = 0;
	while (old_pot[i] && old_pot[i] != '\n')
		i++;
	if (old_pot[i] == '\n')
		i++;
	if (!old_pot[i])
	{
		free(old_pot);
		return (0);
	}
	new_pot = (char *)malloc(sizeof(char) * (ft_strlen(old_pot) - i + 1));
	if (!new_pot)
		return (NULL);
	count = 0;
	while (old_pot[i])
		new_pot[count++] = old_pot[i++];
	new_pot[count] = '\0';
	free(old_pot);
	return (new_pot);
}

char	*get_next_line(int fd)
{
	static char	*pot;
	char		*print;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pot = buff_in_pot(pot, fd);
	if (!pot)
		return (NULL);
	print = complete_line(pot);
	pot = new_pod(pot);
	return (print);
}

/*
int	main(void)
{
	int		fd;
	int		i;
	char	*s;

	i = 1;
	fd = open("hello.txt", O_RDONLY);
	while (i < 17)
	{
		s = NULL;
		s = get_next_line(fd);
		printf("%i: %s", i++, s);
		free(s);
	}
	return (0);
}*/

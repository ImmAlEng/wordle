/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:47:27 by iengels           #+#    #+#             */
/*   Updated: 2023/11/11 03:04:50 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_putstr_fd(char *s, int fd)
{
    if (!s)
       { return;}
	write(fd, s, ft_strlen(s));
}

static int	ft_index(const char *str, const char *set)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	while (str[a])
	{
		b = 0;
		while (str[a] != set[b])
		{
			if (str[a] != set[b] && set[b] == '\0')
				return (a);
			b++;
		}
		a++;
	}
	return (a);
}

static int	ft_revindex(const char *str, const char *set)
{
	unsigned int	a;
	unsigned int	b;

	a = ft_strlen((char*)str);
	while (a > 0)
	{
		b = 0;
		while (str[a] != set[b])
		{
			if (str[a] != set[b] && set[b] == '\0')
				return (a);
			b++;
		}
		a--;
	}
	return (a);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen((char*)s) < start)
		len = 0;
	else if (len > ft_strlen((char*)s + start))
		len = ft_strlen((char*)s + start);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	if (len != 0)
	{
		while (s[start] != '\0' && i < len)
		{
			sub[i] = s[start + i];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*str;

	start = ft_index(s1, set);
	end = ft_revindex(s1, set);
	end = end + 1 - start;
	str = ft_substr(s1, start, end);
	return (str);
}


int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i == n)
		return (0);
	return (0);
}

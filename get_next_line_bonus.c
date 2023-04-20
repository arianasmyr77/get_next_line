/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforouz <arforouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:27:00 by arforouz          #+#    #+#             */
/*   Updated: 2023/01/24 14:47:34 by arforouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_words(char *stash, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(stash, str);
	free(stash);
	return (tmp);
}

static char	*read_file(int fd, char *stash)
{
	int		len;
	char	*str;

	if (!stash)
		stash = ft_calloc(1, 1);
	str = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!str)
		return (NULL);
	len = 5;
	while (!ft_strchr(stash, '\n') && len != 0)
	{
		len = read(fd, str, BUFFER_SIZE);
		str[len] = '\0';
		stash = join_words(stash, str);
	}
	free (str);
	return (stash);
}

static char	*static_to_str(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i])
	{
		i++;
	}
	str = ft_calloc(i + 2, sizeof(char));
	while (i >= 0)
	{
		str[i] = stash[i];
		i--;
	}
	return (str);
}

static char	*static_control(char *stash)
{
	char	*temp;
	char	*str;
	int		i;

	temp = ft_strchr(stash, '\n');
	if (!temp)
	{
		free(stash);
		return (NULL);
	}
	temp++;
	str = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	i = 0;
	while (i <= (int) ft_strlen(str))
	{
		str[i] = temp[i];
		i++;
	}
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash[1028];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	stash[fd] = read_file(fd, stash[fd]);
	line = static_to_str(stash[fd]);
	stash[fd] = static_control(stash[fd]);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int		fd, fd1;

	fd = open("fd", O_RDONLY);
	fd1 = open("fd1", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	//system ("./a.out");
	fd = close(fd);
}*/
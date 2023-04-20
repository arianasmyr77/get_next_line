/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arforouz <arforouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:22:26 by arforouz          #+#    #+#             */
/*   Updated: 2023/01/23 14:05:17 by arforouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_words(char *stash, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(stash, str);
	free(stash);
	return (tmp);
}

char	*read_file(int fd, char *stash)
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

char	*static_to_str(char *stash)
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

char	*static_control(char *stash)
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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	stash = read_file(fd, stash);
	line = static_to_str(stash);
	stash = static_control(stash);
	return (line);
}
/*
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	// test reading a file
	fd = open("file", O_RDONLY);
	// test STDIN 
	//fd = 0;
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	return (0);
}
*/
/*
int main(void)
{
	int		fd;
	char	*line;
	fd = open("file", O_RDONLY);
	while (line != NULL)
	{
		get_next_line(fd);
		printf("%s", line);
	}
	close(fd);
	return (0);
}*/
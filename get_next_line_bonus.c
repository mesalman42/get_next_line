/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:58:17 by mesalman          #+#    #+#             */
/*   Updated: 2025/08/02 11:59:46 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *stash)
{
	int		len;
	char	*line;
	char	*pos;

	if (!stash)
		return (NULL);
	pos = ft_strchr(stash, '\n');
	if (pos)
		len = pos - stash + 1;
	else
		len = ft_strlen(stash);
	line = ft_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*get_stash(char *stash, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != c)
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	line = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free(stash);
	if (!line || line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

static char	*read_file(int fd, char *stash)
{
	int		byte_count;
	char	*buff;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	byte_count = 1;
	while (byte_count > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		byte_count = read(fd, buff, BUFFER_SIZE);
		if (byte_count == 0)
			break ;
		else if (byte_count < 0)
			return (free(buff), free(stash), NULL);
		buff[byte_count] = '\0';
		temp = ft_strjoin(stash, buff);
		if (!temp)
			return (free(buff), free(stash), NULL);
		free(stash);
		stash = temp;
	}
	free (buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = get_stash(stash[fd], '\n');
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:52:33 by mesalman          #+#    #+#             */
/*   Updated: 2025/08/01 17:49:07 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *stash)
{
	int	len;
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
		return(NULL);
	return (line);
}

static  char	*get_stash(char *stash, char c)
{
	int i;
    char    *line;

    i = 0;
    while(stash[i] && stash[i] != c)
        i++;

    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }

    line = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
    free(stash);
     if (!line)
        return (NULL);
    if (line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    return (line);
}

static char *read_file(int fd, char *stash)
{
    char    *buff;
    char    *temp;
    int byte_count;


    buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buff)
        return (NULL);
    byte_count = 1;
    while(byte_count > 0 && (!stash || !ft_strchr(stash, '\n')))
    {
        byte_count = read(fd, buff, BUFFER_SIZE);
        if (byte_count == 0)
            break ;
        else if (byte_count < 0)
            return(free(buff), free(stash), NULL);
        buff[byte_count] = '\0';
        temp = ft_strjoin(stash, buff);
        if (!temp)
            return(free(buff), free(stash), NULL);
        free(stash);
        stash = temp; 
    }
    free(buff);
    return (stash);
}

char *get_next_line(int fd)
{
    char  *line;
    static char *stash;
 
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_file(fd, stash);
    if (!stash)
        return (NULL);
    line = get_line(stash);
    stash = get_stash(stash, '\n');
    return (line);
}

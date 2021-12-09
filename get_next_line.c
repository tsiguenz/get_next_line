/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/09 15:25:33 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_new_stat(char *stat)
{
	char	*new_stat;
	int		i;

	i = 0;
	if (!stat)
		return (0);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (!stat[i])
		new_stat = ft_strdup("");
	else
		new_stat = ft_strdup(stat + i + 1);
	free(stat);
	stat = 0;
	return (new_stat);
}

int	ft_len_next_line(char *stat, int read_val)
{
	int	i;

	i = 0;
	if (!stat || read_val == -1)
		return (0);
	while (stat[i])
	{
		if (stat[i] == '\n')
			return (++i);
		i++;
	}
	if (read_val == 0)
		return (-1);
	return (0);
}

char	*ft_get_line(char *stat, int read_val)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_len_next_line(stat, read_val);
	if (!stat || !len || (!*stat && !read_val))
		return (0);
	if (len == -1)
		len = ft_strlen(stat);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (0);
	while (stat[i])
	{
		if (stat[i] == '\n' && len != -1)
			break ;
		res[i] = stat[i];
		i++;
	}
	res[i] = stat[i];
	return (res);
}

char	*ft_fill_stat(char *stat, int fd, int *read_val)
{
	char	*tmp;
	char	*new_stat;

	new_stat = 0;
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (0);
	*read_val = read(fd, tmp, BUFFER_SIZE);
	if (!stat)
		new_stat = ft_strdup(tmp);
	else
		new_stat = ft_strjoin(stat, tmp);
	free(tmp);
//	if (!stat)
		free(stat);
	return (new_stat);
}

char	*get_next_line(int fd)
{
	static char	*stat[FOPEN_MAX];
	char		*next_line;
	int			read_val;

	read_val = 1;
	if ((fd < 0 || fd > FOPEN_MAX) || (!read_val && !stat[fd]))
		return (0);
	while (ft_len_next_line(stat[fd], read_val) == 0 && read_val != 0)
		stat[fd] = ft_fill_stat(stat[fd], fd, &read_val);
	next_line = ft_get_line(stat[fd], read_val);
	stat[fd] = ft_new_stat(stat[fd]);
	if (!next_line && stat[fd])
		free(stat[fd]);
	return (next_line);
}
/*
int	main(void)
{
	int		fd;
	char	*str;
	
	fd = open("text2.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);

	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	printf("%s", str);
	free(str);

	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/07 23:43:43 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_cut_before_cr(char *stat)
{
	char	*new_stat;
	int		i;

	i = 0;
	new_stat = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (!stat[i])
		new_stat = ft_strdup(stat + i);
	else
		new_stat = ft_strdup(stat + i + 1);
	free(stat);
	return (new_stat);
}

int	ft_pos_cr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-2);
}

char	*ft_return_next_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc((ft_pos_cr(str) + 2), sizeof(char));
	if (!res)
		return (0);
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\n';
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
	if (*read_val > 0)
	{
		if (!stat)
			new_stat = ft_strdup(tmp);
		else
			new_stat = ft_strjoin(stat, tmp);
	}
	free(tmp);
	free(stat);
	return (new_stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*next_line;
	int			read_val;

	read_val = 1;
	while (ft_pos_cr(stat) < 0 && read_val != 0)
	{
		stat = ft_fill_stat(stat, fd, &read_val);
		if (!stat)
			return (0);
	}
	next_line = ft_return_next_line(stat);
	stat = ft_cut_before_cr(stat);
	if (read_val == 0)
		free(stat);
	return (next_line);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	printf("%s", str);
	free(str);
	return (0);
}


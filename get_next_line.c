/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/05 23:45:52 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_cut_after_cr(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (str[i] && str[i] != '\n')
		i++;
	res = malloc(i + 1 * sizeof(char));
	if (!res)
		return (0);
	res[i + 1] = 0;
	while (i >= 0)
	{
		res[i] = str[i];
		i--;
	}
	return (res);
}

char	*ft_cut_before_cr(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (str + (i + 1));
}

char	*get_next_line(int fd)
{
	int			i;
	char		*tmp;
	static char	*res;

	i = 0;
	tmp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!tmp)
		return (0);
	if (res)
		res = ft_cut_before_cr(res);
	while (read(fd, tmp, BUFFER_SIZE) != 0)
	{
		if (!res)
			res = ft_strdup(tmp);
		else
			res = ft_strjoin(res, tmp);
		while (tmp[i])
		{
			if (tmp[i] == '\n')
				return (ft_cut_after_cr(res));
			i++;
		}
		i = 0;
	}
	return (0);
}

int	main(void)
{
	int		fd;
	char	*str = 0;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	free(str);
	return (0);
}

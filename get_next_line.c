/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/06 17:34:19 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	return (-1);
}

char	*ft_return_next_line(char **str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc((ft_pos_cr(*str) + 2), sizeof(char));
	if (!res)
		return (0);
	while (**str && **str != '\n')
	{
		res[i] = **str;
		i++;
		(*str)++;
	}
	res[i] = '\n';
	res[i + 1] = 0;
	(*str)++;
	return (res);
}

char	*ft_fill_res(char *res, int fd)
{
	char	*tmp;

	if (ft_pos_cr(res) != -1)
		return (res);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (0);
	if (read(fd, tmp, BUFFER_SIZE) > 0)
	{
		if (!res)
			res = ft_strdup(tmp);
		else
			res = ft_strjoin(res, tmp);
	}
	else
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res;

	if (!res)
		res = ft_fill_res(res, fd);
	while (ft_pos_cr(res) == -1)
	{
		res = ft_fill_res(res, fd);
		if (!res)
			return (0);
	}
	return (ft_return_next_line(&res));
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	return (0);
}
*/

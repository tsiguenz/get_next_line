/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/07 18:15:51 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_cut_before_cr(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] && str[i] != '\n')
		i++;
	res = ft_calloc((ft_strlen(str) - (i)) + 1, sizeof(char));
	if (!res)
		return (0);
	res = ft_strdup(&str[i + 1]);
	free(str);
	return (res);
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
	return (-1);
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
	static char	*str;
	char		*next_line;

	while (ft_pos_cr(str) == -1)
	{
		str = ft_fill_res(str, fd);
		if (!str)
			return (0);
		if (!*str)
		{
			free(str);
			return (0);
		}
	}
	next_line = ft_return_next_line(str);
	str = ft_cut_before_cr(str);
	return (next_line);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
/*	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	str = get_next_line(fd);
	printf("%s", str);
*/
	free(str);
	return (0);
}


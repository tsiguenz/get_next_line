/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:10:35 by tsiguenz          #+#    #+#             */
/*   Updated: 2021/12/02 17:51:00 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	int			i;
	static char	*str;

	i = 0;
	str = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!str)
		return (0);
	while (read(fd, str, BUFFER_SIZE) != -1)
	{
		while (str[i])
		{
			if (str[i] == '\n')
			{	
				str[i + 1] = 0;
				return (str);
			}
			i++;
		}
	}
	return (0);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("../text.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	free(str);
	return (0);
}

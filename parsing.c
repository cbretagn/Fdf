/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 20:10:51 by cbretagn          #+#    #+#             */
/*   Updated: 2019/04/24 11:49:49 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "./libft/libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int			nb_points(char	*str)
{
	int		ret;

	ret = 0;
	while (*str && *str != '\n')
	{
		while (*str == ' ')
			str++;
		if (*str >= '0' && *str <= '9')
			ret++;
		while (*str >= '0' && *str <= '9')
			str++;
		if (*str && *str != ' ' && *str != '\n')
			return (-1);
	}
	return (ret);
}

int			nb_lines(char *file)
{
	int		fd;
	int		i;
	int		lines;
	char	buffer[4097];

	i = 0;
	lines = 0;
	buffer[4096] = '\0';
	fd = open(file, O_RDONLY);
	while (read(fd, buffer, 4096) > 0)
	{
		while (buffer[i] == '\n')
			i++;
		while (buffer[++i])
		{
			if (buffer[i] == '\n')
			{
				if (buffer[i - 1] == '\n')
				{
					close(fd);
					return (lines);
				}
				lines++;
			}
		}
	}
	close(fd);
	return (lines);
}

char			*next_nbr(char *str, float *current)
{
	int		nb;

	nb = 0;
	while (*str && *str == ' ')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str + '0';
		str++;
	}
	current[2] = nb;
	while (*str && *str == ' ')
		str++;
	return (str);
}

float			**generate_array_points(int x, int y)
{
	float		**ret;
	int			size;
	int			i;

	i = -1;
	size = x * y;
	if (!(ret = (float **)malloc(sizeof(float *) * size)))
		return (NULL);
	while (++i < size)
	{
		if (!(ret[i] = (float *)malloc(sizeof(float) * 3)))
			return (NULL);
		ret[i][0] = BASE;
		ret[i][1] = BASE;
		ret[i][2] = 0.0;
	}
	return (ret);
}

//TODO remove

#include <stdio.h>

void			print_point(float *point, int i, int x)
{
	if (i % x == 0)
		printf("\n");
	printf("%.0f, %.0f, %.0f; ", point[0], point[1], point[2]);
}

void			print_array_points(float **array, int x, int y)
{
	int		i;
	int		size;

	size = x * y;
	i = -1;
	while (++i < size)
		print_point(array[i], i, x);
}
//TODO STOP

float			**parser_fdf(int fd, int x, int y)
{
	int			current_x;
	int			current_y;
	float		**ret;
	char		*line;

	//if ((y = nb_lines(file) < 1))
	//	return (NULL); //set error pour savoir quel message d'erreur afficher
	current_x = -1;
	current_y = -1;
	ret = generate_array_points(x, y);
	while (++current_y < y)
	{
		get_next_line(fd, &line);
		while (++current_x < x)
			line = next_nbr(line, ret[current_y * x + current_x - 1]);
		free(line);
	}
	//gestion des erreurs
	return (ret);
}

#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	(void)argc;

	int 	y;
	int 	x;
	char	*line;
	int		fd;
	float	**array;

	y = nb_lines(argv[1]);
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	x = nb_points(line);
	free(line);
	array = parser_fdf(fd, x, y);
	print_array_points(array, x, y);
	return (0);
}
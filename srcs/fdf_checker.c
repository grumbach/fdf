/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 10:52:13 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/18 11:10:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		count_numbers(char *line, int x)
{
	while (*line)
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (*line && *line == '-')
			line++;
		if (*line)
		{
			if (ft_isdigit(*line))
				x++;
			else
				return (-1);
		}
		while (*line && ft_isdigit(*line))
			line++;
		if (*line == ',')
		{
			line++;
			while (*line && (ft_isdigit(*line) || ft_strchr("xABCDEF", *line)))
				line++;
		}
	}
	return (x);
}

static char		*joiner(char *read, char *line)
{
	char		*tmp_read;
	char		*tmp_line;
	char		*new;

	tmp_read = read;
	tmp_line = line;
	new = ft_strnjoin(3, (read ? read : ""), line, "\n");
	if (tmp_read)
		free(tmp_read);
	free(tmp_line);
	return (new);
}

char			*fdf_reader_checker(const char *file, int *y, int *x)
{
	char 	*line;
	char	*read;
	int		fd;
	int		status;
	int		countx;

	read = NULL;
	status = 1;
	if (((fd = open(file, O_RDONLY)) || 1) && fd == -1)
		errors(0, 0);
	line = NULL;
	while ((status = ft_get_next_line(fd, &line)) && status == 1)
	{
		countx = count_numbers(line , 0);
		if (!*y)
			*x = countx;
		else if (*x != countx || countx == -1)
			return (NULL);
		read = joiner(read, line);
		(*y)++;
	}
	if (status == -1)
		errors(0, 0);
	close(fd);
	return (read);
}

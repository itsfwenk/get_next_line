/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:22 by fli               #+#    #+#             */
/*   Updated: 2024/06/06 17:12:39 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*gnl;
	static t_list	*init[1024] = {0};
	t_list			*new;

	if (fd >= 1024)
		return (NULL);
	new = NULL;
	while (end_line(&init[fd]) != -1)
	{
		new = ft_lstnew(fd, &init[fd]);
		if (new == NULL)
		{
			ft_lstclear(&init[fd]);
			return (NULL);
		}
		ft_lstadd_back(&init[fd], new);
	}
	gnl = ft_strdup(&init[fd], &gnl);
	if (gnl == NULL)
		return (NULL);
	return (gnl);
}

int	end_line(t_list **current)
{
	int		i;
	t_list	*pos;

	if (!*current)
		return (0);
	if (((*current)->s)[(*current)->min] == '\0')
		ft_lstdelone(current);
	pos = *current;
	while (pos != NULL)
	{
		i = pos->min;
		while ((pos->s)[i] != '\0')
		{
			if ((pos->s)[i] == '\n' || pos->max != BUFFER_SIZE
				|| (pos->next && ((pos->next)->s)[0] == '\0'))
				return (-1);
			i++;
		}
		pos = pos->next;
	}
	return (1);
}

int	count_char(t_list **lst)
{
	int		i;
	int		count;
	t_list	*pos;

	pos = *lst;
	i = pos->min;
	count = 0;
	while (pos)
	{
		while ((pos->s)[i] != '\0')
		{
			if ((pos->s)[i] == '\n')
				return (count + 1);
			count++;
			i++;
		}
		i = 0;
		pos = pos->next;
	}
	return (count);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main()
{

	int fd = open("te.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	int	fd;
	char *gnl;

	printf("BUFFER SIZE = %d\n", BUFFER_SIZE);
	fd = open("text.txt", O_RDONLY);

	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
}*/

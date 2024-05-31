/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:22 by fli               #+#    #+#             */
/*   Updated: 2024/05/30 18:37:50 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*gnl;
	static t_list	*init;
	t_list			*new;

	init = NULL;
	new = NULL;
	while (end_line(new) != -1)
	{
		new = ft_lstnew(fd);
		if (new == NULL)
		{
			ft_lstclear(&init);
			return (NULL);
		}
		ft_lstadd_back(&init, new);
	}
	gnl = ft_strdup(&init, &gnl);
	if (gnl == NULL)
		return (NULL);
	return (gnl);
}

int	end_line(t_list *current)
{
	int	i;

	i = 0;

	while ((current->s)[i] != '\0')
	{
		if ((current->s)[i] == '\n' || current->max != BUFFER_SIZE)
			return (i);
		i++;
	}
	return (-1);
}

int	count_char(t_list **lst)
{
	int		i;
	int		count;
	t_list	*pos;

	i = 0;
	count = 0;
	pos = *lst;
	while (pos)
	{
		while ((pos->s)[i] != '\0')
		{
			 count++;
			 i++;
		}
		i = 0;
		pos = pos->next;
	}
	return (count + 1);
}
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int	fd;

	fd = open("testfile", O_RDONLY);
	if (fd == -1)
			printf("Cannot read file.\n");
	printf("%s\n", get_next_line(fd));
}

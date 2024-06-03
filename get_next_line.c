/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:22 by fli               #+#    #+#             */
/*   Updated: 2024/06/03 16:54:48 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*gnl;
	static t_list	*init = NULL;
	t_list			*new;

	new = NULL;
	while (end_line(&init) != -1)
	{
		new = ft_lstnew(fd);
		if ((new == NULL)
			|| (init && (init->s)[init->min] == '\0'))
		{
			ft_lstclear(&init);
			return ("\0");
		}
		ft_lstadd_back(&init, new);
	}
	gnl = ft_strdup(&init, &gnl);
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
	if(((*current)->s)[(*current)->min] == '\0')
		ft_lstdelone(current);
	pos = *current;
	while (pos != NULL)
	{
		i = pos->min;
		while ((pos->s)[i] != '\0')
		{
			if ((pos->s)[i] == '\n' || pos->max != BUFFER_SIZE)
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
			 	return (count);
			 count++;
			 i++;
		}
		i = 0;
		pos = pos->next;
	}
	return (count);
}
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int	nb_l;
	int	fd;

	fd = open("testfile", O_RDONLY);
	if (fd == -1)
			printf("Cannot read file.\n");
	nb_l = 0;
	while (nb_l < 5)
	{
		printf("%s\n", get_next_line(fd));
		//get_next_line(fd);
		nb_l++;
	}
}

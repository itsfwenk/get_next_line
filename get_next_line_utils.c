/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:56:56 by fli               #+#    #+#             */
/*   Updated: 2024/05/30 18:37:27 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

t_list	*ft_lstnew(int fd)
{
	int		read_return;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	read_return = read(fd, new->s, BUFFER_SIZE);
	if (read_return <= 0)
		return (NULL);
	(new->s)[ft_strlen(new->s)] = '\0';
	new->min = 0;
	new->max = ft_strlen(new->s);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last != NULL)
	{
		if ((last->next) == NULL)
			last->next = new;
		last = last->next;
	}
}

char	*ft_strdup(t_list **init, char **gnl)
{
	int		j;
	t_list	*pos;
	t_list	*temp;

	*gnl = malloc(count_char(init) * sizeof(char));
	if (*gnl == NULL)
		return (NULL);
	j = 0;
	pos = *init;
	while ((pos->s)[pos->min] != '\n'
		|| (pos->min == pos->max && pos->max != BUFFER_SIZE))
	{
		if ((pos->s)[pos->min] == '\0' && pos->next)
		{
			temp = pos;
			pos = pos->next;
			free(temp);
		}
		*gnl[j++] = (pos->s)[pos->min];
		pos->min = (pos->min) + 1;
	}
	return (*gnl);
}
void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

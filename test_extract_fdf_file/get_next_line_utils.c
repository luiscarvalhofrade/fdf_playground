/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:54:05 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/11 15:54:06 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found_new_line(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next_node;
	}
	return (0);
}

int	ft_len_of_new_line(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next_node;
	}
	return (len);
}

void	ft_copy_string(t_list *list, char *str)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content[i++];
		}
		list = list->next_node;
	}
	str[k] = '\0';
}

t_list	*ft_find_last_node(t_list *list)
{
	if (!list)
		return (0);
	while (list->next_node)
		list = list->next_node;
	return (list);
}

void	ft_free(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next_node;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node && clean_node->content[0] != '\0')
		*list = clean_node;
	else
	{
		free(buf);
		if (clean_node)
			free(clean_node);
	}
}

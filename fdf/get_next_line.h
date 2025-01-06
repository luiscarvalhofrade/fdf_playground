/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:53:47 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/11 15:53:49 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next_node;
}					t_list;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);

int		ft_found_new_line(t_list *list);
int		ft_len_of_new_line(t_list *list);

void	ft_copy_string(t_list *list, char *str);
void	ft_free(t_list **list, t_list *clean_node, char *buffer);

t_list	*ft_find_last_node(t_list *list);

#endif

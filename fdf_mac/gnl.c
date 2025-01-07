#include "fdf.h"

void	ft_reorg_lst(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	clean_node = (t_list *)malloc(sizeof(t_list));
	if (!buffer || !clean_node)
		return ;
	last_node = ft_find_last_node(*lst);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[i++])
		buffer[k++] = last_node->content[i];
	buffer[k] = '\0';
	clean_node->content = buffer;
	clean_node->next_node = NULL;
	ft_free(lst, clean_node, buffer);
}

char	*ft_get_line(t_list *lst)
{
	int		new_line_len;
	char	*new_line;

	if (!lst)
		return (0);
	new_line_len = ft_len_of_new_line(lst);
	new_line = (char *)malloc((new_line_len + 1) * sizeof(char));
	if (!new_line)
		return (0);
	ft_copy_string(lst, new_line);
	return (new_line);
}

void	ft_append_buffer(t_list **lst, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_last_node(*lst);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*lst = new_node;
	else
		last_node->next_node = new_node;
	new_node->content = buffer;
	new_node->next_node = NULL;
}

void	ft_create_lst(t_list **lst, int fd)
{
	char	*buffer;
	int		char_read;

	while (!ft_found_new_line(*lst))
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buffer);
			ft_free(lst, NULL, NULL);
			return ;
		}
		if (char_read == 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_append_buffer(lst, buffer);
	}
}

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*lst = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ft_create_lst(&lst, fd);
	next_line = ft_get_line(lst);
	if (!next_line)
	{
		ft_free(&lst, NULL, NULL);
		return (0);
	}
	ft_reorg_lst(&lst);
	if (*next_line == '\0')
		return (free(next_line), NULL);
	return (next_line);
}
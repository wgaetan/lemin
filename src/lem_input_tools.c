/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_input_tools.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 14:40:12 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_input_buffer		*new_buffer_line(char *str)
{
	t_input_buffer	*new_line;

	new_line = gc_alloc((sizeof(t_input_buffer)), 0);
	new_line->line = ft_strdup(str);
	new_line->pos = 0;
	new_line->line_type = 0;
	new_line->prev = NULL;
	new_line->next = NULL;
	return (new_line);
}

void				add_buffer_line(t_input_buffer **head, t_input_buffer *line)
{
	t_input_buffer	*tmp;
	int				pos;

	tmp = *head;
	pos = 1;
	if (tmp)
	{
		while (tmp->next)
		{
			tmp = tmp->next;
			pos++;
		}
		line->pos = pos;
		tmp->next = line;
		line->prev = tmp;
	}
	else
		*head = line;
}

void				fill_input_buffer(void)
{
	t_stock			*stock;
	char			*line;

	stock = get_stock();
	while (get_next_line(0, &line) > 0)
	{
		add_buffer_line(&stock->parse_data.input_buffer, new_buffer_line(line));
		stock->parse_data.line_number++;
		gc_free(line, 0);
	}
}

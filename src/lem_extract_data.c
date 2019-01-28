/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_extract_data.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 16:45:20 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			alloc_tables(int count)
{
	t_stock			*stock;
	int				i;
	int				a;

	stock = get_stock();
	i = 0;
	stock->tables.x_coor = gc_alloc((sizeof(int) * count), 0);
	stock->tables.y_coor = gc_alloc((sizeof(int) * count), 0);
	stock->tables.names = gc_alloc((sizeof(char *) * (count + 1)), 0);
	stock->tables.tunnels = gc_alloc((sizeof(short *) * count), 0);
	while (i < count)
	{
		a = 0;
		stock->tables.names[i] = NULL;
		stock->tables.tunnels[i] = gc_alloc((sizeof(short) * count), 0);
		while (a < count)
			stock->tables.tunnels[i][a++] = 0;
		i++;
	}
	stock->tables.names[count] = NULL;
	stock->rooms_number = count;
}

static int			init_tables(t_input_buffer *buff)
{
	t_stock			*stock;
	t_input_buffer	*tmp;
	int				count;
	int				end;

	stock = get_stock();
	tmp = buff;
	end = 0;
	count = 0;
	while (tmp && end == 0 && stock->parse_data.line_error == -1)
	{
		tmp->line_type = get_line_type(tmp->line);
		if (tmp->line_type == 2)
			count++;
		else if (tmp->line_type == 3)
			end = 1;
		else if (tmp->line_type != 1)
			stock->parse_data.line_error = tmp->pos;
		tmp = tmp->next;
	}
	if (stock->parse_data.line_error == -1)
		alloc_tables(count);
	return (buff->pos);
}

static void			handle_line(t_input_buffer *buff, char *cmd)
{
	t_stock			*stock;

	stock = get_stock();
	if (stock->parse_data.first_room_line == -1)
		stock->parse_data.first_room_line = init_tables(buff);
	if (buff->line_type == 2 && stock->parse_data.first_tunnel_line == -1 &&
			stock->parse_data.line_error == -1)
		add_room(buff, cmd);
	else if (buff->line_type == 3)
		add_tunnel(buff);
	else if (stock->parse_data.line_error == -1)
		stock->parse_data.line_error = buff->pos;
	cmd[0] = 'a';
}

static void			handle_command(t_input_buffer *buff, char *cmd)
{
	t_stock			*stock;

	stock = get_stock();
	if (ft_strcmp(buff->line, "##start") == 0)
	{
		if (cmd[0] == 's' || cmd[0] == 'e')
			stock->parse_data.line_error = buff->pos;
		cmd[0] = 's';
	}
	else if (ft_strcmp(buff->line, "##end") == 0)
	{
		if (cmd[0] == 's' || cmd[0] == 'e')
			stock->parse_data.line_error = buff->pos;
		cmd[0] = 'e';
	}
}

void				extract_data(void)
{
	t_stock			*stock;
	t_input_buffer	*tmp;
	char			cmd;

	stock = get_stock();
	tmp = stock->parse_data.input_buffer;
	cmd = 'a';
	while (tmp && stock->parse_data.line_error == -1)
	{
		tmp->line_type = get_line_type(tmp->line);
		if (tmp->line_type == 4)
		{
			if ((stock->ants_number = ft_atoi(tmp->line)) <= 0)
				stock->parse_data.line_error = tmp->pos;
			cmd = 'a';
		}
		else if (tmp->line_type == 1)
			handle_command(tmp, &cmd);
		else if (tmp->line_type == 2 || tmp->line_type == 3)
			handle_line(tmp, &cmd);
		else
			stock->parse_data.line_error = tmp->pos;
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_rooms.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/08 15:07:28 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

short			get_room_id_by_name(char *name)
{
	t_stock		*stock;
	short		id;
	short		i;

	id = -1;
	i = 0;
	stock = get_stock();
	while (stock->tables.names[i] != NULL && id == -1)
	{
		if (ft_strcmp(name, stock->tables.names[i]) == 0)
			id = i;
		i++;
	}
	return (id);
}

static void		assign_room(t_stock *stock, char **split, char *cmd)
{
	int			i;

	i = 1;
	if (cmd[0] == 's' || cmd[0] == 'e')
	{
		i = (cmd[0] == 's') ? 0 : (stock->rooms_number - 1);
		stock->tables.x_coor[i] = ft_atoi(split[1]);
		stock->tables.y_coor[i] = ft_atoi(split[2]);
		stock->tables.names[i] = ft_strdup(split[0]);
	}
	else
	{
		while (i < stock->rooms_number - 1)
		{
			if (stock->tables.names[i] == NULL)
			{
				stock->tables.x_coor[i] = ft_atoi(split[1]);
				stock->tables.y_coor[i] = ft_atoi(split[2]);
				stock->tables.names[i] = ft_strdup(split[0]);
				break ;
			}
			i++;
		}
	}
}

void			add_room(t_input_buffer *buff, char *cmd)
{
	t_stock		*stock;
	char		**split;

	stock = get_stock();
	split = ft_strsplit(buff->line, ' ');
	if (stock->parse_data.first_tunnel_line != -1)
		stock->parse_data.line_error = buff->pos;
	assign_room(stock, split, cmd);
	ft_strsplit_free(split);
	cmd[0] = 'a';
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_tunnels.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/08 16:10:45 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	add_tunnel(t_input_buffer *buff)
{
	t_stock *stock;
	char	**split;
	int		a;
	int		b;

	stock = get_stock();
	split = ft_strsplit(buff->line, '-');
	if (stock->parse_data.first_tunnel_line == -1)
		stock->parse_data.first_tunnel_line = buff->pos;
	if ((a = get_room_id_by_name(split[0])) == -1 ||
			(b = get_room_id_by_name(split[1])) == -1)
	{
		stock->parse_data.line_error = buff->pos;
	}
	else
	{
		stock->tables.tunnels[a][b] = 1;
		stock->tables.tunnels[b][a] = 1;
	}
	ft_strsplit_free(split);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_write_ants.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/22 15:39:11 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 10:38:30 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			write_ant(int id, char *room)
{
	ft_putchar('L');
	ft_putnbr(id + 1);
	ft_putchar('-');
	ft_putstr(room);
	ft_putchar(' ');
}

void				write_data(void)
{
	t_stock			*stock;
	t_input_buffer	*tmp;
	int				i;

	stock = get_stock();
	tmp = stock->parse_data.input_buffer;
	i = 0;
	if (stock->parse_data.line_error == -1)
		stock->parse_data.line_error = stock->parse_data.line_number;
	while (i < stock->parse_data.line_error && tmp)
	{
		ft_putstr(tmp->line);
		ft_putchar('\n');
		tmp = tmp->next;
		i++;
	}
	ft_putchar('\n');
}

void				start_end_direct(void)
{
	t_stock			*stock;
	int				i;

	stock = get_stock();
	i = 0;
	write_data();
	while (i < stock->ants_number)
	{
		write_ant(i, stock->tables.names[stock->rooms_number - 1]);
		i++;
	}
	ft_putchar('\n');
}

static void			orientate_ant(t_stock *stock, t_ant *tmp, int *sent)
{
	t_paths			*path;

	if (tmp->turn >= 0)
	{
		path = get_path_by_id(stock->bit_fields.id[
				stock->solving_set.paths_id[tmp->path]]);
		if (tmp->turn < path->len)
		{
			write_ant(tmp->id, stock->tables.names[path->path[tmp->turn + 1]]);
			sent[0] = 1;
		}
	}
}

void				write_ants(void)
{
	t_stock			*stock;
	t_ant			*tmp;
	int				sent;

	stock = get_stock();
	sent = 1;
	write_data();
	while (sent == 1)
	{
		tmp = stock->ant;
		sent = 0;
		while (tmp)
		{
			orientate_ant(stock, tmp, &sent);
			tmp->turn++;
			tmp = tmp->next;
		}
		write(1, "\n", 1);
	}
}

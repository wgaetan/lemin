/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_stock.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 22:18:38 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:48:05 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			set_bit_fields_to_null(t_stock *stock)
{
	stock->bit_fields.paths = NULL;
	stock->bit_fields.len = NULL;
	stock->bit_fields.id = NULL;
}

static void			set_paths_set_to_null(t_stock *stock)
{
	stock->solving_set.paths_id = NULL;
	stock->solving_set.paths_len = NULL;
	stock->solving_set.to_avoid = NULL;
	stock->tmp_set.paths_id = NULL;
	stock->tmp_set.paths_len = NULL;
	stock->tmp_set.to_avoid = NULL;
}

t_stock				*get_stock(void)
{
	static t_stock	*stock;

	if (!stock)
	{
		stock = gc_alloc((sizeof(t_stock)), 0);
		init_parse_data(&stock->parse_data);
		stock->ant = NULL;
		stock->send_tab = NULL;
		stock->tables.tunnels = NULL;
		stock->tables.names = NULL;
		stock->tables.x_coor = NULL;
		stock->tables.y_coor = NULL;
		stock->paths = NULL;
		stock->passed = NULL;
		set_paths_set_to_null(stock);
		set_bit_fields_to_null(stock);
		stock->mode = 0;
		stock->limit_step = -1;
		stock->rooms_number = 0;
		stock->ants_number = 0;
		stock->paths_number = 0;
	}
	return (stock);
}

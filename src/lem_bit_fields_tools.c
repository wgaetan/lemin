/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_bit_fields_tools.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 15:30:35 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	swap_bit_fields(t_stock *stock, int id1, int id2)
{
	unsigned int	tmp;
	int				i;

	i = 0;
	while (i < stock->bit_fields.size)
	{
		tmp = stock->bit_fields.paths[id1][i];
		stock->bit_fields.paths[id1][i] = stock->bit_fields.paths[id2][i];
		stock->bit_fields.paths[id2][i] = tmp;
		i++;
	}
	tmp = stock->bit_fields.len[id1];
	stock->bit_fields.len[id1] = stock->bit_fields.len[id2];
	stock->bit_fields.len[id2] = tmp;
	tmp = stock->bit_fields.id[id1];
	stock->bit_fields.id[id1] = stock->bit_fields.id[id2];
	stock->bit_fields.id[id2] = tmp;
}

void	sort_bit_fields(void)
{
	t_stock *stock;
	int		i;

	stock = get_stock();
	i = 0;
	while (i < stock->paths_number - 1)
	{
		if (stock->bit_fields.len[i] > stock->bit_fields.len[i + 1])
		{
			swap_bit_fields(stock, i, i + 1);
			i = i - 1;
		}
		else
			i++;
		if (i < 0)
			i = 0;
	}
}

void	init_bit_fields(void)
{
	t_stock	*stock;
	t_paths *tmp;
	int		i;

	stock = get_stock();
	tmp = stock->paths;
	stock->bit_fields.paths = gc_alloc((sizeof(unsigned int *) *
				stock->paths_number), 0);
	stock->bit_fields.len = gc_alloc((sizeof(short) *
				stock->paths_number), 0);
	stock->bit_fields.id = gc_alloc((sizeof(int) *
				stock->paths_number), 0);
	i = 0;
	while (i < stock->paths_number && tmp)
	{
		stock->bit_fields.paths[i] = path_to_bit_field(tmp);
		stock->bit_fields.len[i] = (short)tmp->len;
		stock->bit_fields.id[i] = i;
		tmp = tmp->next;
		i++;
	}
	stock->bit_fields.size = ((stock->rooms_number >> 5) + ((stock->rooms_number
					& 0x1F) != 0 ? 1 : 0));
	sort_bit_fields();
}

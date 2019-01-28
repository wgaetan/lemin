/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_path_set_tools.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 17:52:55 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			copy_set(t_path_set *dest, t_path_set *src)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	while (i < dest->size)
	{
		dest->paths_id[i] = src->paths_id[i];
		dest->paths_len[i] = src->paths_len[i];
		i++;
	}
	i = 0;
	while (i < stock->bit_fields.size)
	{
		dest->to_avoid[i] = src->to_avoid[i];
		i++;
	}
	dest->solving_turns = src->solving_turns;
	dest->size = src->size;
	dest->count = src->count;
}

void			remove_last_from_path_set(t_path_set *set)
{
	t_stock		*stock;
	int			i;

	if (set->count > 0)
	{
		stock = get_stock();
		i = 0;
		while (i < stock->bit_fields.size)
		{
			set->to_avoid[i] ^=
				stock->bit_fields.paths[set->paths_id[set->count - 1]][i];
			i++;
		}
		set->paths_id[set->count - 1] = -1;
		set->paths_len[set->count - 1] = -1;
		set->count--;
	}
}

void			add_to_path_set(t_path_set *set, int id)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	if (id < stock->paths_number)
	{
		if (set->count < set->size)
		{
			set->paths_id[set->count] = id;
			set->paths_len[set->count] = stock->bit_fields.len[id];
		}
		while (i < stock->bit_fields.size)
		{
			set->to_avoid[i] |= stock->bit_fields.paths[id][i];
			i++;
		}
		set->count++;
	}
}

void			init_path_set(t_path_set *set, int size)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	set->paths_id = gc_alloc((sizeof(int) * size), 0);
	set->paths_len = gc_alloc((sizeof(short) * size), 0);
	set->to_avoid = create_bit_field(stock->rooms_number);
	while (i < size)
	{
		set->paths_id[i] = -1;
		set->paths_len[i] = -1;
		i++;
	}
	set->size = size;
	set->count = 0;
	set->solving_turns = stock->ants_number + stock->rooms_number + 1;
}

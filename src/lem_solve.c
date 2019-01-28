/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_solve.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/30 13:23:07 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			simulate_solve(int ants, t_path_set *set)
{
	int			passed;
	int			turn;
	int			i;

	passed = 0;
	turn = 0;
	while (ants > 0)
	{
		i = 0;
		while (i < set->count && ants > 0)
		{
			if (set->paths_len[i] <= turn)
			{
				passed |= (1 << i);
				ants--;
			}
			i++;
		}
		turn++;
	}
	if (passed != ((1 << set->count) - 1))
		turn = -1;
	set->solving_turns = turn;
}

int				available_path(t_stock *stock, t_path_set *set, int *d)
{
	int			i;
	int			j;
	int			error;

	i = 0;
	i = d[0];
	while (i < stock->paths_number)
	{
		error = 0;
		j = 0;
		while (j < stock->bit_fields.size && error == 0)
		{
			if ((stock->bit_fields.paths[i][j] & set->to_avoid[j]) != 0)
				error = 1;
			j++;
		}
		if (error == 0)
			break ;
		i++;
	}
	if (i == stock->paths_number)
		i = -1;
	d[0] = i;
	return (i);
}

void			best_path_loop(t_stock *stock, t_path_set *set, int milestone)
{
	int			i;
	int			new_path;

	i = milestone;
	if (set->count >= set->size)
		return ;
	while (i < stock->paths_number)
	{
		new_path = available_path(stock, set, &i);
		if (new_path < 0)
			return ;
		add_to_path_set(set, new_path);
		simulate_solve(stock->ants_number, set);
		if (set->solving_turns != -1 && set->solving_turns <
				stock->solving_set.solving_turns)
			copy_set(&stock->solving_set, set);
		best_path_loop(stock, set, i);
		remove_last_from_path_set(set);
		i++;
	}
}

void			solve(void)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	stock->path = gc_alloc((sizeof(short) * stock->rooms_number), 0);
	stock->passed = gc_alloc((sizeof(short) * stock->rooms_number), 0);
	while (i < stock->rooms_number)
		stock->passed[i++] = 0;
	if (stock->limit_step == -1 || stock->limit_step > stock->rooms_number)
		stock->limit_step = stock->rooms_number;
	if (stock->mode == 0)
		explore_all(0, 0, stock);
	else if (stock->mode == 1)
		explore_reduced(0, 0, stock);
	else if (stock->mode == 2)
		explore_unique(0, 0, stock);
	init_bit_fields();
	init_path_set(&stock->solving_set, maximum_path_number());
	init_path_set(&stock->tmp_set, stock->solving_set.size);
	best_path_loop(stock, &stock->tmp_set, 0);
	(stock->solving_set.count > 0) ? send_ants() : invalid_parsing();
}

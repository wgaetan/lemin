/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_send_ants.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/20 20:10:22 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			distrib_ants(int ants, t_path_set set, int **tab)
{
	int				turn;
	int				i;

	turn = 0;
	while (ants > 0)
	{
		i = 0;
		while (i < set.count && ants > 0)
		{
			if (set.paths_len[i] <= turn)
			{
				tab[0][i]++;
				ants--;
			}
			i++;
		}
		turn++;
	}
}

static t_ant		*new_ant(int path, int turn, int id)
{
	t_ant			*new_ant;

	new_ant = gc_alloc((sizeof(t_ant)), 0);
	new_ant->next = NULL;
	new_ant->path = path;
	new_ant->turn = 0 - turn;
	new_ant->id = id;
	return (new_ant);
}

static void			add_ant(int path, int turn)
{
	t_stock			*stock;
	t_ant			*tmp;
	int				i;

	stock = get_stock();
	tmp = stock->ant;
	if (tmp == NULL)
		stock->ant = new_ant(path, turn, 0);
	else
	{
		i = 1;
		while (tmp->next)
		{
			i++;
			tmp = tmp->next;
		}
		tmp->next = new_ant(path, turn, i);
	}
}

void				send_ants(void)
{
	t_stock			*stock;
	int				i;
	int				j;
	int				turn;

	stock = get_stock();
	stock->send_tab = gc_alloc((sizeof(int) * stock->solving_set.count), 0);
	distrib_ants(stock->ants_number, stock->solving_set, &stock->send_tab);
	i = 0;
	j = 0;
	turn = 0;
	while (i < stock->ants_number)
	{
		if (j >= stock->solving_set.count)
		{
			j = 0;
			turn++;
		}
		add_ant(j++, turn);
		i++;
	}
	write_ants();
}

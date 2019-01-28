/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_path_finder.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/30 18:15:44 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			explore_unique(short room, short step, t_stock *stock)
{
	int			i;

	i = 0;
	stock->path[step] = room;
	stock->passed[room] = 1;
	if (room == (stock->rooms_number - 1) && stock->paths == NULL)
	{
		add_path(&stock->paths, new_path(stock->path, step));
		stock->paths_number++;
	}
	else if (step < stock->limit_step && stock->paths == NULL)
	{
		while (i < stock->rooms_number)
		{
			if (stock->tables.tunnels[room][i] == 1 && stock->passed[i] == 0)
				explore_unique(i, step + 1, stock);
			i++;
		}
	}
	stock->passed[room] = 0;
}

void			explore_reduced(short room, short step, t_stock *stock)
{
	int			i;

	i = 0;
	stock->path[step] = room;
	stock->passed[room] = 1;
	if (room == (stock->rooms_number - 1))
	{
		add_path(&stock->paths, new_path(stock->path, step));
		stock->limit_step = step;
		stock->paths_number++;
	}
	else if (step < stock->limit_step)
	{
		while (i < stock->rooms_number)
		{
			if (stock->tables.tunnels[room][i] == 1 && stock->passed[i] == 0)
				explore_reduced(i, step + 1, stock);
			i++;
		}
	}
	stock->passed[room] = 0;
}

void			explore_all(short room, short step, t_stock *stock)
{
	int			i;

	i = 0;
	stock->path[step] = room;
	stock->passed[room] = 1;
	if (room == (stock->rooms_number - 1))
	{
		add_path(&stock->paths, new_path(stock->path, step));
		stock->paths_number++;
	}
	else if (step < stock->limit_step)
	{
		while (i < stock->rooms_number)
		{
			if (stock->tables.tunnels[room][i] == 1 && stock->passed[i] == 0)
				explore_all(i, step + 1, stock);
			i++;
		}
	}
	stock->passed[room] = 0;
}

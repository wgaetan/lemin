/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_path_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 17:32:40 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_paths		*get_path_by_id(int id)
{
	t_stock *stock;
	t_paths	*tmp;
	int		i;

	stock = get_stock();
	tmp = stock->paths;
	i = 0;
	while (tmp)
	{
		if (i == id)
			break ;
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

int			maximum_path_number(void)
{
	t_stock	*stock;
	int		a;
	int		b;
	int		i;

	stock = get_stock();
	i = 0;
	a = 0;
	b = 0;
	while (i < stock->rooms_number)
	{
		if (stock->tables.tunnels[0][i] == 1)
			a++;
		if (stock->tables.tunnels[stock->rooms_number - 1][i] == 1)
			b++;
		i++;
	}
	return (a < b ? a : b);
}

t_paths		*new_path(short *tab, short len)
{
	t_paths	*new_path;
	int		i;

	i = 0;
	new_path = gc_alloc((sizeof(t_paths)), 0);
	new_path->path = gc_alloc((sizeof(short) * (len + 1)), 0);
	new_path->len = len;
	while (i <= len)
	{
		new_path->path[i] = tab[i];
		i++;
	}
	new_path->next = NULL;
	return (new_path);
}

void		add_path(t_paths **head, t_paths *new_path)
{
	t_paths	*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_path;
	}
	else
		*head = new_path;
}

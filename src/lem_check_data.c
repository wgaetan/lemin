/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_check_data.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/12 17:21:16 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		check_null_name(void)
{
	t_stock		*stock;
	int			ret;
	int			i;

	stock = get_stock();
	ret = 0;
	i = 0;
	while (i < stock->rooms_number && ret == 0)
		if (stock->tables.names[i++] == NULL)
			ret = 1;
	return (ret);
}

static int		check_same_coor_or_name(void)
{
	t_stock		*stock;
	int			ret;
	int			i;
	int			j;

	stock = get_stock();
	ret = 0;
	i = 0;
	while (i < stock->rooms_number && ret == 0)
	{
		j = i + 1;
		while (j < stock->rooms_number && ret == 0)
		{
			if ((stock->tables.x_coor[i] == stock->tables.x_coor[j] &&
					stock->tables.y_coor[i] == stock->tables.y_coor[j])
					|| ft_strcmp(stock->tables.names[i],
						stock->tables.names[j]) == 0)
				ret = 1;
			j++;
		}
		i++;
	}
	return (ret);
}

static int		check_error_line(void)
{
	t_stock		*stock;
	int			ret;

	stock = get_stock();
	ret = 0;
	if (stock->parse_data.line_error != -1)
		if (stock->parse_data.line_error <= stock->parse_data.first_tunnel_line)
			ret = 1;
	return (ret);
}

static int		have_path(short id)
{
	t_stock		*stock;
	int			ret;
	short		i;

	stock = get_stock();
	i = 0;
	ret = 0;
	if (stock->tables.tunnels)
	{
		while (stock->tables.tunnels[id] && i < stock->rooms_number && ret == 0)
		{
			if (stock->tables.tunnels[id][i] == 1)
				ret = 1;
			i++;
		}
	}
	return (ret);
}

void			check_data(void)
{
	t_stock		*stock;
	int			error;

	stock = get_stock();
	error = 0;
	if (check_null_name() == 1)
		error = 1;
	else if (check_same_coor_or_name() == 1)
		error = 1;
	else if (check_error_line() == 1)
		error = 1;
	else if (have_path(0) == 0 || have_path(stock->rooms_number - 1) == 0)
		error = 1;
	if (error == 1)
		invalid_parsing();
}

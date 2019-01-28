/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_detect_line_type.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/07 16:57:22 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		findchar(char c, char *str, int n)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	if (str)
		while (str[i] && i < n)
			count += (str[i++] == c ? 1 : 0);
	return (count);
}

static int		is_cmd(char *str)
{
	int			type;

	type = 1;
	if (findchar('#', str, 2) != 2 && findchar('#', str, 2) != 1)
		type = 0;
	return (type);
}

static int		is_room(char *str)
{
	char		**split;
	int			type;

	type = 1;
	split = ft_strsplit(str, ' ');
	if (ft_split_elem_count(split) != 3)
		type = 0;
	else if (str[0] == 'L' || str[0] == ' ')
		type = 0;
	else if (findchar('-', split[0], ft_strlen(split[0])) > 0)
		type = 0;
	else if (!(ft_isalldigit(split[1]) && ft_isalldigit(split[2])))
		type = 0;
	ft_strsplit_free(split);
	return (type);
}

static int		is_tunnel(char *str)
{
	char		**split;
	int			type;

	type = 1;
	split = ft_strsplit(str, '-');
	if (ft_split_elem_count(split) != 2)
		type = 0;
	else if (str[0] == 'L')
		type = 0;
	else if (findchar(' ', split[0], ft_strlen(split[0])) > 0)
		type = 0;
	ft_strsplit_free(split);
	return (type);
}

int				get_line_type(char *str)
{
	t_stock		*stock;
	int			type;

	stock = get_stock();
	type = 0;
	if (is_cmd(str))
		type = 1;
	else if (stock->ants_number > 0)
	{
		if (is_room(str))
			type = 2;
		else if (is_tunnel(str))
			type = 3;
	}
	else if (ft_isalldigit(str))
		type = 4;
	return (type);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_get_param.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 08:29:19 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			get_params(int argc, char **argv)
{
	t_stock		*stock;
	char		**split;
	int			i;

	i = 0;
	stock = get_stock();
	while (++i < argc)
	{
		split = ft_strsplit(argv[i], '=');
		if (ft_split_elem_count(split) == 2)
		{
			if (ft_strcmp(split[0], "mode") == 0)
			{
				if (ft_strcmp(split[1], "reduced") == 0)
					stock->mode = 1;
				else if (ft_strcmp(split[1], "unique") == 0)
					stock->mode = 2;
			}
			if (ft_strcmp(split[0], "limit_steps") == 0)
				if ((stock->limit_step = ft_atoi(split[1])) <= 0)
					stock->limit_step = -1;
		}
		ft_strsplit_free(split);
	}
}

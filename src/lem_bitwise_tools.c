/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_bitwise_tools.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/20 10:28:33 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

unsigned int		*path_to_bit_field(t_paths *path)
{
	t_stock			*stock;
	unsigned int	*new;
	int				i;

	stock = get_stock();
	new = create_bit_field(stock->rooms_number);
	i = 1;
	while (i < path->len)
		set_bit(path->path[i++], &new);
	return (new);
}

unsigned int		*create_bit_field(int size)
{
	unsigned int	*new;
	int				i;

	i = (size >> 5) + ((size & 0x1F) != 0 ? 1 : 0);
	new = gc_alloc((sizeof(unsigned int) * i), 0);
	while (--i >= 0)
		new[i] &= 0;
	return (new);
}

void				set_bit(int i, unsigned int **tab)
{
	int				rank;

	rank = i >> 5;
	tab[0][rank] |= (1 << (i - (rank << 5)));
}

void				unset_bit(int i, unsigned int **tab)
{
	int				rank;

	rank = i >> 5;
	tab[0][rank] &= ~(1 << (i - (rank << 5)));
}

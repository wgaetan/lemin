/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 14:19:28 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:36:07 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		invalid_parsing(void)
{
	ft_putstr("ERROR");
	ft_putchar('\n');
	gc_exit(-1);
}

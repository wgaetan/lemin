/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_parse.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 17:26:07 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:21:01 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdio.h>

void		parse(void)
{
	fill_input_buffer();
	extract_data();
	check_data();
}

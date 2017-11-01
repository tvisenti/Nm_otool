/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 09:49:48 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/01 10:03:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			set_architecture(unsigned int magic_number)
{
	g_big_endian = 0;
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM
		|| magic_number == FAT_CIGAM)
		g_big_endian = 1;
}

t_symtab		init_symtab(void)
{
	t_symtab	symt;

	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.ns = 1;
	return (symt);
}

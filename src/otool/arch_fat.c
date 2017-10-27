/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:07:11 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/27 13:37:32 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint32_t		swap_uint32(uint32_t val, unsigned int magic_number)
{
	if (magic_number == FAT_MAGIC)
		return (val);
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

void			handle_fat(char *ptr, unsigned int magic_number, char *file)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	uint32_t			offset;

	fat = (void*)ptr;
	i = fat->nfat_arch;
	i = swap_uint32(i, magic_number);
	arch = (void*)ptr + sizeof(fat);
	ft_printf("%s:\n", file);
	while (i)
	{
		if (swap_uint32(arch->cputype, magic_number) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		i--;
	}
	ft_otool(ptr + swap_uint32(offset, magic_number), NULL, 0);
}

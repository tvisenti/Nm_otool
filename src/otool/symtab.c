/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 10:05:05 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/06 17:57:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		symtab_building_bis(struct segment_command *seg,
	struct section *sect, struct mach_header *header)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
	{
		if (g_bonus_otool == 0)
		{
			if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sect->segname, SEG_TEXT) == 0)
			{
				print_section(sect->addr, sect->size,
					(char *)header + sect->offset,
					"Contents of (__TEXT,__text) section");
			}
		}
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
		{
			print_section(sect->addr, sect->size,
				(char *)header + sect->offset,
				"Contents of (__DATA,__data) section");
		}
		sect = (void *)sect + sizeof(*sect);
		i++;
	}
}

void			symtab_building(struct mach_header *header,
	struct load_command *lc)
{
	uint32_t				i;
	struct segment_command	*seg;
	struct section			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(seg, sect, header);
		}
		if (check_range_addr(lc))
			return (print_error("file", "truncated or malformed object"));
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void		symtab_building_bis_64(struct segment_command_64
	*seg, struct section_64 *sect, struct mach_header_64 *header)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
	{
		if (g_bonus_otool == 0)
		{
			if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sect->segname, SEG_TEXT) == 0)
			{
				print_section_64(sect->addr, sect->size,
					(char *)header + sect->offset,
					"Contents of (__TEXT,__text) section");
			}
		}
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
		{
			print_section_64(sect->addr, sect->size,
				(char *)header + sect->offset,
				"Contents of (__DATA,__data) section");
		}
		sect = (void *)sect + sizeof(*sect);
		i++;
	}
}

void			symtab_building_64(struct mach_header_64 *header,
	struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((void *)seg + sizeof(*seg));
			symtab_building_bis_64(seg, sect, header);
		}
		if (check_range_addr(lc))
			return (print_error("file", "truncated or malformed object"));
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

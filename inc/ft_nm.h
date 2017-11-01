/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:55 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/01 10:02:58 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

int						g_bonus_nm;
int						g_big_endian;
uint32_t				g_buff_size;
void					*g_buff_addr;

typedef struct			s_symtab
{
	unsigned int		data;
	unsigned int		bss;
	unsigned int		text;
	int					ns;
}						t_symtab;

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
}						t_offlist;

/*
** FT_NM
*/

int						check_range_addr(void *ptr);
void					ft_nm(void *ptr, char *file);
void					loop_arg(char *av);

/*
** DISPLAY
*/

void					display_output(struct nlist elem, char *str,
	t_symtab *symt);
void					display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt);
void					display_loop_64(struct nlist_64 *array,
	char *stringtable, t_symtab symt, struct symtab_command *sym);
void					display_loop(struct nlist *array, char *stringtable,
	t_symtab symt, struct symtab_command *sym);
void					print_error(char *file, char *str);

/*
** SORT
*/

t_offlist				*order_off(t_offlist *lst);
struct nlist			*fill_array(struct nlist *tab, uint32_t nsyms);
struct nlist			*bubble_sort(char *stringtable, struct nlist *tab,
	uint32_t nsyms);
struct nlist_64			*fill_array_64(struct nlist_64 *tab, uint32_t nsyms);
struct nlist_64			*bubble_sort_64(char *stringtable, struct nlist_64 *tab,
	uint32_t nsyms);

/*
** ARCH_64
*/

void					print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr);
void					handle_64(char *ptr);

/*
** ARCH_32
*/

void					print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr);
void					handle_32(char *ptr);

/*
** ARCH_LIB
*/

int						get_size(char *name);
char					*get_name(char *name);
t_offlist				*add_off(t_offlist *lst, uint32_t off, uint32_t strx);
void					print_ar(t_offlist *lst, char *ptr, char *file);
void					handle_lib(char *ptr, char *name);

/*
** ARCH_FAT
*/

uint32_t				swap_uint32(uint32_t val);
void					handle_fat(char *ptr, char *file);

/*
** UTILS
*/

char					type_n_sect(unsigned int n_sect, t_symtab *symt);
char					get_type(uint32_t type, uint32_t n_sect, int value,
	t_symtab *symt);
int						search_lst(t_offlist *lst, uint32_t off);
void					check_bonus(char *bonus);

/*
** SYMTAB
*/

void					symtab_building_64(t_symtab *symt,
	struct mach_header_64 *header, struct load_command *lc);

void					symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc);

/*
** SET_ENV
*/

void					set_architecture(unsigned int magic_number);
t_symtab				init_symtab(void);

#endif

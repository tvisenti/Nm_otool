/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:55 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 14:25:56 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

int					ft_printf(const char *str, ...);

/*
** NM
*/

void				handle_64(char *ptr);
void				nm(char *ptr);
int					loop_arg(char *av);

/*
** DISPLAY
*/

int					print_error(char *file, char *str);
char				type_n_sect(unsigned int n_sect);
char				get_type(uint32_t type, uint32_t n_sect, int addr);
void				display_output(unsigned int value, char *str, unsigned int type, uint32_t n_sect);
void				print_output(int nsyms, int symoff, int stroff, char *ptr);

/*
** SORT
*/

struct nlist_64		*fill_array(struct nlist_64 *tab, int taille, char *stringtable);
struct nlist_64		*tri_bulle(char *stringtable, struct nlist_64 *tab, int taille);

#endif

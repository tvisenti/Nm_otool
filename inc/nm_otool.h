/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:55 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 13:07:57 by tvisenti         ###   ########.fr       */
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

int				ft_printf(const char *str, ...);

/*
** NM
*/

void			display_output(unsigned int value, char *str);
void			print_output(int nsyms, int symoff, int stroff, char *ptr);
void			handle_64(char *ptr);
void			nm(char *ptr);
int				print_error(char *file, char *str);
int				loop_arg(char *av);

/*
** SORT
*/
struct nlist_64     *fill_array(struct nlist_64 *tab, int taille, char *stringtable);
struct nlist_64		*tri_bulle(char *stringtable, struct nlist_64 *tab, int taille);

#endif

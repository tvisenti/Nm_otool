/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:22:52 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/06 18:01:29 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				get_size(char *name)
{
	int		i;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	i = ft_atoi(word);
	return (i);
}

char			*get_name(char *name)
{
	char	*str;
	int		length;

	length = ft_strlen(ARFMAG);
	str = ft_strstr(name, ARFMAG) + length;
	return (str);
}

t_offlist		*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	if (search_lst(lst, off))
		return (lst);
	tmp2->next = tmp;
	return (lst);
}

void			print_ar(t_offlist *lst, char *ptr, char *file)
{
	t_offlist		*tmp;
	int				size_name;
	struct ar_hdr	*arch;
	char			*name;

	tmp = lst;
	ft_printf("Archive : %s\n", file);
	while (tmp)
	{
		arch = (void*)ptr + tmp->off;
		name = get_name(arch->ar_name);
		size_name = get_size(arch->ar_name);
		ft_printf("%s(%s):\n", file, name);
		ft_otool((void*)arch + sizeof(*arch) + size_name, file, 0);
		tmp = tmp->next;
	}
}

void			handle_lib(char *ptr, char *name)
{
	struct ranlib	*ran;
	t_offlist		*lst;
	int				i;
	int				size;
	char			*offset_struct;

	lst = NULL;
	i = get_size((void*)ptr + SARMAG);
	offset_struct = (void*)ptr + sizeof(struct ar_hdr) + SARMAG + i;
	ran = (void*)ptr + sizeof(struct ar_hdr) + SARMAG + i + sizeof(uint32_t);
	size = (*((int *)offset_struct)) / sizeof(struct ranlib);
	if (check_range_addr(ran) || check_range_addr(offset_struct))
		return (print_error("file", "truncated or malformed object"));
	i = -1;
	while (++i < size)
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
	print_ar(order_off(lst), ptr, name);
}

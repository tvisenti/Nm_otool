/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:22:52 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/24 18:52:44 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

int			catch_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

char		*catch_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
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
	tmp2->next = tmp;
	return (lst);
}

void			print_ar(uint32_t off, char *ptr, char *file)
{
	int				size_name;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size_name = catch_size(arch->ar_name);
	ft_printf("\n%s(%s):\n", file, name);
	nm((void*)arch + sizeof(*arch) + size_name, file);
}

void			browse_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}

void	handle_lib(char *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size_name;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_name = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_name;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_name + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_ar(lst, ptr, name);
}

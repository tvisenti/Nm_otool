/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 13:06:57 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

struct nlist_64     *fill_array(struct nlist_64 *tab, int taille, char *stringtable)
{
    struct nlist_64 *tab2;
    int             i;

    tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * taille);
    i = -1;
    while (++i < taille)
        tab2[i] = tab[i];
    return (tab2);
}

struct nlist_64		*tri_bulle(char *stringtable, struct nlist_64 *tab, int taille)
{
    struct nlist_64	*tab2;
    struct nlist_64	temp;
    int				i;
    int				j;

    i = 0;
    tab2 = fill_array(tab, taille, stringtable);
    while (i < taille)
    {
        j = 0;
        while(j < taille)
        {
            if (ft_strcmp(stringtable + tab2[i].n_un.n_strx,
                stringtable + tab2[j].n_un.n_strx) < 0)
            {
                temp = tab2[i];
                tab2[i] = (struct nlist_64)tab2[j];
                tab2[j] = temp;
            }
            j++;
        }
        i++;
    }
    return (tab2);
}

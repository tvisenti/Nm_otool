/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 10:19:40 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 13:48:03 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

struct nlist_64     *fill_array(struct nlist_64 *tab, int taille, char *stringtable)
{
    int             i;
    struct nlist_64 *tab2;

    tab2 = (struct nlist_64*)malloc(sizeof(struct nlist_64) * taille);
    i = -1;
    while (++i < taille)
        tab2[i] = tab[i];
    return (tab2);
}

struct nlist_64     *tri_bulle(char *stringtable, struct nlist_64 *tab, int taille)
{
    int             i;
    int             j;
    struct nlist_64 *new_tab;
    struct nlist_64 temp;

    i = 0;
    new_tab = fill_array(tab, taille, stringtable);
    while (i < taille)
    {
        j = 0;
        while (j < taille)
        {
            if (ft_strcmp(stringtable + new_tab[i].n_un.n_strx,
                stringtable + new_tab[j].n_un.n_strx) < 0)
            {
                temp = new_tab[i];
                new_tab[i] = new_tab[j];
                new_tab[j] = temp;
            }
            j++;
        }
        i++;
    }
    return (new_tab);
}

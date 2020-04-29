/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 14:36:41 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:48:02 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!(lst))
		return ;
	if (lst)
		del(lst->content);
	free(lst);
	lst = NULL;
}

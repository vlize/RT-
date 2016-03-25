/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 15:36:28 by vlize             #+#    #+#             */
/*   Updated: 2014/11/26 16:15:21 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = ft_lstnew(lst->content, lst->content_size);
	if (!tmp)
		return (NULL);
	tmp = f(tmp);
	tmp->next = ft_lstmap(lst->next, f);
	return (tmp);
}

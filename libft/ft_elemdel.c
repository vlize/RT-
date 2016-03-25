/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elemdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 13:23:11 by vlize             #+#    #+#             */
/*   Updated: 2014/11/26 13:29:16 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_elemdel(void *content, size_t content_size)
{
	if (content)
		free(content);
	content = NULL;
	content_size = content_size * 0;
}

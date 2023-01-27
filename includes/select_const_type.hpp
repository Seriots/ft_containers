/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_const_type.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:00:04 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/27 13:00:17 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

    template <bool IsConst, typename NonConst, typename Const>
    struct select_const_type {};

    template <typename NonConst, typename Const>
    struct select_const_type<false, NonConst, Const>
    {
        typedef NonConst type;
    };

    template <typename NonConst, typename Const>
    struct select_const_type<true, NonConst, Const>
    {
        typedef Const type;
    };

}


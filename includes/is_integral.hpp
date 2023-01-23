/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:27:25 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/19 14:42:58 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<typename _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp				value = __v;

		typedef _Tp							value_type;
		typedef integral_constant<_Tp, __v>	type;

		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;
	
	template <class T> struct is_integral : ft::false_type { };

	template <> struct is_integral<bool> : ft::true_type { };
	template <> struct is_integral<char> : ft::true_type { };
	template <> struct is_integral<signed char> : ft::true_type { };
	template <> struct is_integral<unsigned char> : ft::true_type { };
	template <> struct is_integral<wchar_t> : ft::true_type { };
	template <> struct is_integral<short> : ft::true_type { };
	template <> struct is_integral<unsigned short> : ft::true_type { };
	template <> struct is_integral<int> : ft::true_type { };
	template <> struct is_integral<unsigned int> : ft::true_type { };
	template <> struct is_integral<long> : ft::true_type { };
	template <> struct is_integral<unsigned long> : ft::true_type { };
	template <> struct is_integral<long long> : ft::true_type { };
	template <> struct is_integral<unsigned long long> : ft::true_type { };
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_integral.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:58 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/18 12:51:07 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

extern std::string name;

#include "is_integral.hpp"

void	test_is_integral(void)
{
	std::cout << name << "is_integral_test" << std::endl;

	std::cout << "<Need to be True>" << std::endl;
	std::cout << "bool -> "<< std::boolalpha << ft::is_integral<bool>::value << std::endl;
	std::cout << "char -> "<< std::boolalpha << ft::is_integral<char>::value << std::endl;
	std::cout << "signed char -> "<< std::boolalpha << ft::is_integral<signed char>::value << std::endl;
	std::cout << "unsigned char -> "<< std::boolalpha << ft::is_integral<unsigned char>::value << std::endl;
	std::cout << "wchar_t -> "<< std::boolalpha << ft::is_integral<wchar_t>::value << std::endl;
	std::cout << "short -> "<< std::boolalpha << ft::is_integral<short>::value << std::endl;
	std::cout << "unsigned short -> "<< std::boolalpha << ft::is_integral<unsigned short>::value << std::endl;
	std::cout << "int -> "<< std::boolalpha << ft::is_integral<int>::value << std::endl;
	std::cout << "long int -> "<< std::boolalpha << ft::is_integral<long int>::value << std::endl;
	std::cout << "long long int -> "<< std::boolalpha << ft::is_integral<long long int>::value << std::endl;
	std::cout << "unsigned int -> "<< std::boolalpha << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "unsigned char -> "<< std::boolalpha << ft::is_integral<unsigned char>::value << std::endl;
	std::cout << "unsigned short int -> "<< std::boolalpha << ft::is_integral<unsigned short int>::value << std::endl;
	std::cout << "long -> "<< std::boolalpha << ft::is_integral<long>::value << std::endl;
	std::cout << "unsigned long -> "<< std::boolalpha << ft::is_integral<unsigned long>::value << std::endl;
	std::cout << "unsigned long int -> "<< std::boolalpha << ft::is_integral<unsigned long int>::value << std::endl;
	std::cout << "long long -> "<< std::boolalpha << ft::is_integral<long long>::value << std::endl;
	std::cout << "unsigned long long -> "<< std::boolalpha << ft::is_integral<unsigned long long>::value << std::endl;
	std::cout << "unsigned long long int -> "<< std::boolalpha << ft::is_integral<unsigned long long int>::value << std::endl;
	
	std::cout << "<Need to be False>" << std::endl;
	std::cout << "float -> "<< std::boolalpha << ft::is_integral<float>::value << std::endl;
	std::cout << "double -> "<< std::boolalpha << ft::is_integral<double>::value << std::endl;
	std::cout << "long double -> "<< std::boolalpha << ft::is_integral<long double>::value << std::endl;
	std::cout << "std::string -> "<< std::boolalpha << ft::is_integral<std::string>::value << std::endl;
	std::cout << "std::vector<int> -> "<< std::boolalpha << ft::is_integral<std::vector<int> >::value << std::endl;
	std::cout << "std::vector<std::string> -> "<< std::boolalpha << ft::is_integral<std::vector<std::string> >::value << std::endl;
	std::cout << "std::vector<std::vector<int> > -> "<< std::boolalpha << ft::is_integral<std::vector<std::vector<int> > >::value << std::endl;
}

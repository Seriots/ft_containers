/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:18:05 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/16 16:59:57 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <ctime>

#if NAMESPACE == 0
	#include <stack>
	namespace ft = std;
	std::string	name = "std_";
#else
	#include "stack.hpp"
	std::string	name = "ft_";
#endif

#include "utils.hpp"

int	stacked()
{
	ft::stack<int>	stack;

	std::cout << name << "stack_test" << std::endl; 
	stack.push(84512);
	stack.push(63695);
	std::cout << stack.size() << std::endl;
	std::cout << stack.top() << std::endl;
	std::cout << stack.empty() << std::endl;
	std::cout << stack.size() << std::endl;
	return (0);
}

void	time_test(void f())
{
	clock_t start = clock();
	f();
	clock_t end = clock();
	std::cout << std::fixed << "Time: " << (end - start) / (double)CLOCKS_PER_SEC << std::endl;
}

int	main(void)
{
	time_test(&stack_test_with_vector);
	time_test(&stack_test_with_deque);
}
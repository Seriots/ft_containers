/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:23:31 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/16 16:50:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>

#include <map>
#include <stack>
#include <vector>

#include "utils.hpp"
#include "stack.hpp"

extern std::string name;

void	stack_test_with_vector(void)
{
	std::cout << name << "stack_vector\n";
	ft::stack<int> ft_stack;

	std::cout << "Stack empty: " << ft_stack.empty() << std::endl;

	std::cout << "\n<Set Stack>" << std::endl;
	
	ft_stack.push(1);
	ft_stack.push(2);
	ft_stack.push(3);
	ft_stack.push(4);

	std::cout << "Stack no-empty: " << ft_stack.empty() << std::endl;
	std::cout << "Stack top: " << ft_stack.top() << std::endl;
	std::cout << "Stack size: " << ft_stack.size() << std::endl;
	
	std::cout << "\n<Pop one element>" << std::endl;
	ft_stack.pop();

	std::cout << "Stack top: " << ft_stack.top() << std::endl;
	std::cout << "Stack size: " << ft_stack.size() << std::endl;

	std::cout << "\n<Operator Test>" << std::endl;
	
	ft::stack<int> ft_stack2 = ft_stack;
	std::cout << "Operator =: " << ft_stack2.top() << " " << ft_stack2.size() << std::endl;
	std::cout << "Operator ==: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator !=: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator >: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator =>: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <=: " << (ft_stack == ft_stack2) << std::endl;

	std::cout << "\n<Add one elem>" << std::endl;
	ft_stack2.push(5);

	std::cout << "Operator =: " << ft_stack2.top() << " " << ft_stack2.size() << std::endl;
	std::cout << "Operator ==: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator !=: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator >: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator =>: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <=: " << (ft_stack == ft_stack2) << std::endl;
}

void	stack_test_with_deque(void)
{
	std::cout << name << "stack_deque\n";
	ft::stack<int, std::deque<int> > ft_stack;

	std::cout << "Stack empty: " << ft_stack.empty() << std::endl;

	std::cout << "\n<Set Stack>" << std::endl;
	
	ft_stack.push(1);
	ft_stack.push(2);
	ft_stack.push(3);
	ft_stack.push(4);

	std::cout << "Stack no-empty: " << ft_stack.empty() << std::endl;
	std::cout << "Stack top: " << ft_stack.top() << std::endl;
	std::cout << "Stack size: " << ft_stack.size() << std::endl;
	
	std::cout << "\n<Pop one element>" << std::endl;
	ft_stack.pop();

	std::cout << "Stack top: " << ft_stack.top() << std::endl;
	std::cout << "Stack size: " << ft_stack.size() << std::endl;

	std::cout << "\n<Operator Test>" << std::endl;
	
	ft::stack<int, std::deque<int> > ft_stack2 = ft_stack;
	std::cout << "Operator =: " << ft_stack2.top() << " " << ft_stack2.size() << std::endl;
	std::cout << "Operator ==: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator !=: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator >: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator =>: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <=: " << (ft_stack == ft_stack2) << std::endl;

	std::cout << "\n<Add one elem>" << std::endl;
	ft_stack2.push(5);

	std::cout << "Operator =: " << ft_stack2.top() << " " << ft_stack2.size() << std::endl;
	std::cout << "Operator ==: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator !=: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator >: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator =>: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <: " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "Operator <=: " << (ft_stack == ft_stack2) << std::endl;
}

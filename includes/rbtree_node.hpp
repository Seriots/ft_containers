/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:11:56 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/26 12:47:45 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream>

#ifndef color_black
 #define color_black false
 #define color_red true
#endif

namespace ft
{
	template <class V>
	class node
	{
		public:
			typedef V			value_type;
		
		private:
			value_type			value;
			node<value_type>	*parent;
			node<value_type>	*left;
			node<value_type>	*right;
			bool				color;
			bool				is_delete;
			
		public:
			node() : value(), parent(NULL), left(NULL), right(NULL), color(color_black), is_delete(0) {};
			node(const value_type& val) : value(val),  parent(NULL), left(NULL), right(NULL), color(color_black), is_delete(0) {};
			~node() {};
			
			void	setParent(node *p) { parent = p; };
			void	setLeft(node *l) { left = l; };
			void	setRight(node *r) { right = r; };
			void	setColor(bool c) { color = c; };
			void	setDelete(bool d) { is_delete = d; };

			value_type	&getValue() { return value; };
			node	*getParent() const { return parent; };
			node	*getLeft() const { return left; };
			node	*getRight() const { return right; };
			bool	getColor() const { return color; };
			bool	getDelete() const { return is_delete; };

			void	display()
			{
				std::cout << this->getValue().first << "-";
				if (this->getColor() == color_red)
					std::cout << "red ::: ";
				else
					std::cout << "black ::: ";
				if (this->getParent()->getParent() != NULL && this->getParent())
				{
					if (this->getParent()->getLeft() == this)
						std::cout << "left (from " << this->getParent()->getValue().first << ")" << std::endl;
					else
						std::cout << "right(from " << this->getParent()->getValue().first << ")" << std::endl;
				}
				else
					std::cout << "root" << std::endl;
				if (this->getLeft() != NULL)
					this->getLeft()->display();
				if (this->getRight() != NULL)
					this->getRight()->display();
			};
	};
}
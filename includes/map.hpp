/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:34 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/28 15:47:23 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree.hpp"
#include "lexicographical_compare.hpp"


namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key				 														key_type;
			typedef T																		mapped_type;
			typedef ft::pair<const key_type, mapped_type>									value_type;
			typedef Compare																	key_compare;
			typedef Allocator																allocator_type;
			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef ft::rbTreeIterator<value_type>											iterator;
			typedef ft::rbTreeIterator<value_type, true>									const_iterator;	
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef typename allocator_type::difference_type								difference_type;
			typedef typename allocator_type::size_type										size_type;
			typedef typename ft::rbTree<key_type, mapped_type, key_compare, std::allocator<ft::node<value_type> > > rbTree;

			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			

		private:
			allocator_type		_allocator;
			key_compare			_comp;
			rbTree				_tree;
					

		public:
			/*************************Contructor*******************************/
			map() : _allocator(Allocator()), _comp(Compare()), _tree(rbTree()) {};

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _allocator(alloc), _comp(comp), _tree(rbTree()) {};

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ): _allocator(alloc), _comp(comp), _tree(rbTree())
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
			};

	 		map( const map& other ) : _allocator(other._allocator), _comp(other._comp), _tree(other._tree) {};	
			
			map	&operator=( const map& other )
			{
				if (*this == other)
					return (*this);
				_allocator = other._allocator;
				_comp = other._comp;
				_tree = other._tree;
				return (*this);
			};

			~map() { clear(); };
			
			/*************************Iterators********************************/
			iterator				begin() { return (_tree.begin()); };
			const_iterator			begin() const { return (_tree.begin()); };
			iterator				end() { return (_tree.end()); };
			const_iterator			end() const { return (_tree.end()); };
			reverse_iterator		rbegin() { return (_tree.rbegin()); };
			const_reverse_iterator	rbegin() const { return (_tree.rbegin()); };
			reverse_iterator		rend() { return (_tree.rend()); };
			const_reverse_iterator	rend() const { return (_tree.rend()); };
			
			/*************************Capacity*********************************/
			bool		empty() const { return (_tree.empty()); };
			size_type	size() const { return (_tree.size()); };
			size_type	max_size() const { return (_tree.max_size()); };
			
			/*************************Element Access***************************/
			mapped_type&		at( const key_type& key ) { return (_tree.at(key)); }
			const mapped_type&	at( const key_type& key ) const { return (_tree.at(key)); }
			mapped_type&		operator[]( const key_type& key ) { return (_tree[key]); }

			/*************************Modifiers********************************/
			void						clear() { _tree.clear(); };
			ft::pair<iterator, bool>	insert( const value_type& value ) { return (_tree.insert(value)); };	
			iterator 					insert( iterator pos, const value_type& value ) { return (_tree.insert(pos, value)); }
			
			template< class InputIt >
			void 						insert( InputIt first, InputIt last ) { while (first != last) { _tree.insert(*first); first++; } }
			size_type					erase( const key_type& key ) { return (_tree.remove(key)); };
			void						erase( iterator pos ) { _tree.remove(pos); };
			void						erase( iterator first, iterator last ) { while (first != last) { _tree.remove(first); first++; } };
			void						swap( map& other ) { _tree.swap(other._tree); _allocator = other.get_allocator(); _comp = other._comp; };
			
			/**************************Lookup**********************************/
			size_type		count( const key_type& key ) const {return (_tree.count(key));};
			iterator		find( const key_type& key ) {if (_tree.find(key) == NULL) return (end()); return (iterator(_tree.find(key)));};
			const_iterator	find( const key_type& key ) const { if (_tree.find(key) == NULL) return (end()); return (const_iterator(_tree.find(key)));};

			ft::pair<iterator,iterator>				equal_range( const key_type& key ) {return (_tree.equal_range(key));};
			ft::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const {return (_tree.equal_range(key));}
			iterator								lower_bound( const key_type& key ) {return (_tree.lower_bound(key));};
			const_iterator							lower_bound( const key_type& key ) const {return (_tree.lower_bound(key));};
			iterator								upper_bound( const key_type& key ) {return (_tree.upper_bound(key));};
			const_iterator							upper_bound( const key_type& key ) const {return (_tree.upper_bound(key));};
			
			/*************************Observers********************************/			
			value_compare	value_comp() const {return value_compare(_comp);};
			key_compare		key_comp() const {return (_comp);};

			/*************************Allocator********************************/
			allocator_type	get_allocator() const {return (_allocator);};
	};
	
	/*************************Non-member function overloads********************/
	template< class Key, class T, class Compare, class Allocator >
	bool	operator==( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		typename ft::map<Key,T,Compare,Allocator>::const_iterator it1 = lhs.begin();
		typename ft::map<Key,T,Compare,Allocator>::const_iterator it2 = rhs.begin();
		typename ft::map<Key,T,Compare,Allocator>::const_iterator e_it1 = lhs.end();
		typename ft::map<Key,T,Compare,Allocator>::const_iterator e_it2 = rhs.end();

		if (lhs.size() != rhs.size())
			return (false);
		while ((it1 != e_it1) && (it2 != e_it2))
		{
			if (!(*it1 == *it2))
				return (false);
			++it1;
			++it2;
		}
		return (true);
	};

	template< class Key, class T, class Compare, class Allocator >
	bool	operator!=( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(lhs == rhs));
	};

	template< class Key, class T, class Compare, class Allocator >
	bool	operator<(const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	
	};
	
	template< class Key, class T, class Compare, class Allocator >
	bool	operator<=( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(rhs < lhs));
	};

	template< class Key, class T, class Compare, class Allocator >
	bool	operator>( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		return (rhs < lhs);
	};

	template< class Key, class T, class Compare, class Allocator >
	bool	operator>=( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(lhs < rhs));
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs);};
}

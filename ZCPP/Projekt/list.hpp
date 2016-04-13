/**
 * 
 */

#ifndef UJ_LIST_HPP
#define UJ_LIST_HPP

#include<memory>
#include<iterator>
#include<stdexcept>

namespace uj
{
	class list;
	class citer;
	class iter;
	
	class lnode
	{
		lnode() = default;
		lnode next* = nullptr;

		void null() noexcept
		{
			this->next=null;
		}
		
		friend class list;
		friend class citer;
		friend class iter;
	};
	
	template<typename T>
	class typenode: public lnode
	{
		friend class list;
		friend class citer;
		friend class iter;
		T value;

		template<typename... Args>
		typenode(Args&&... args): value(std::forward<Args>(args)..)
		{}
	};
	
	template<typename T>
	class citer
	{
	public:
		using value_type = T;
		using pointer = const value_type*;
		using reference = const value_type&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;
		
	protected:
		lnode* pnode = nullptr;
		
	public:
		citer() = default;
		~citer() = default;
		citer(lnode* p): pnode(p){}
		citer(const citer&) = default;
		citer(citer&&) = default;
		citer& operator=(const citer&) = default;
		citer& operator=(citer&&) = default;
		
		reference operator*() const noexcept
		{
			return reinterpret_cast<typenode<T>*>(this->pnode)->value;
		}
		
		pointer operator->() const noexcept
		{
			return &reinterpret_cast<typenode<T>*>(this->pnode)->value;
		}
		
		citer& operator++() noexcept
		{
			this->pnode=this->pnode->next;
			return *this;
		}
		
		citer operator++(int) noexcept
		{
			citer tmp(*this);
			this->pnode=this->pnode->next;
			return tmp;
		}
		
		lnode* node() const noexcept
		{
			return this->pnode;
		}

		bool operator==(const citer& x) const noexcept
		{
			return this->pnode == x.pnode;
		}
		
		bool operator!=(const citer& x) const noexcept
		{
			return this->pnode != x.pnode;
		}
		
		citer next() const noexcept
		{
			if(this->pnode->next)
				return citer(this->pnode->next->next);
			else
				return citer(this->pnode->next);
		}


	};
	
	template<typename T>
	class iter : public citer<T>
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;

	public:
		iter() = default;
		~iter() = default;
		iter(lnode* p) : pnode(p) {}
		iter(const iter&) = default;
		iter(iter&&) = default;
		iter& operator=(const iter&) = default;
		iter& operator=(iter&&) = default;

		reference operator*() const noexcept
		{
			return reinterpret_cast<typenode<T>*>(this->pnode)->value;
		}

		pointer operator->() const noexcept
		{
			return &reinterpret_cast<typenode<T>*>(this->pnode)->value;
		}

		iter& operator++() noexcept
		{
			this->pnode = this->pnode->next;
			return *this;
		}

		iter operator++(int) noexcept
		{
			iter tmp(*this);
			this->pnode = this->pnode->next;
			return tmp;
		}
	};

	template<typename T>
	inline bool operator==(const citer<T>& a, const citer<T>& b) noexcept
	{
		return a.pnode==b.pnode;
	}
	
	template<typename T>
	inline bool operator!=(const citer<T>& a, const citer<T>& b) noexcept
	{
		return a.pnode!=b.pnode;
	}

	template<typename T, typename Allocator = std::allocator<T>>
	class list
	{
	private:
		using Alloc = std::allocator_traits<Allocator>;
		using node_allocator_type = typename Alloc::rebind_alloc<typenode<T>>;
		using NodeAlloc = typename Alloc::rebind_traits<node_allocator_type>;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = Alloc::pointer;
		using const_pointer = Alloc::const_pointer;
		using iterator = iter<T>;
		using const_iterator = citer<T>;

	private:
		lnode head;
		size_t lSize = 0;
		node_allocator_type alloc;

	public:
		list() : list(Allocator());
		explicit list(const Allocator& alloc);
		list(size_type count, const T& value, const Allocator& alloc = Allocator);
		list(size_type count, const Allocator& alloc = Allocator());
		template<typename InIterator>
		list(InIterator first, InIterator last, const Allocator& alloc);
		list(const list& other);
		list(const list& other, const Allocator& other);
		list(list&& other);
		list(list&& other, const Allocator& other);
		list(std::initializer_list<T> init, const Allocator& alloc = Allocator());
		~list();

		list& operator=(const list& other);
		list& operator=(list&& other);
		list& operator=(std::initializer_list<T> ilist);

		void assing(size_type count, const T& value);
		template<typename InIterator>
		void assing(InIterator first, InIterator last);
		void assing(std::initializer_list<T> ilist);

		allocator_type get_allocator() const
		{
			return Allocator();
		}

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		//Err? What? How to do that?
		//reverse_iterator rbegin() noexcept;
		//const_reverse_iterator rbegin() const noexcept;
		//const_reverse_iterator crbegin() const noexcept;

		//reverse_iterator rend() noexcept;
		//const_reverse_iterator rend() const noexcept;
		//const_reverse_iterator crend() const noexcept;

		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type size() const noexcept;

		void clear() noexcept;

		iterator insert(const_iterator pos, const T& value);
		iterator insert(const_iterator pos, T&& value);
		iterator insert(const_iterator pos, size_type count, const T& value);
		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);

		template< class... Args >
		iterator emplace(const_iterator pos, Args&&... args);

		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);

		void push_back(const T& value);
		void push_back(T&& value);

		template< class... Args >
		void emplace_back(Args&&... args);

		void pop_back();

		void push_front(const T& value);
		void push_front(T&& value);

		template< class... Args >
		void emplace_front(Args&&... args);

		void pop_front();

		void resize(size_type count);
		void resize(size_type count, const value_type& value);

		void swap(list& other);

		void merge(list& other);
		void merge(list&& other);
		template <class Compare>
		void merge(list& other, Compare comp);
		template <class Compare>
		void merge(list&& other, Compare comp);

		void splice(const_iterator pos, list& other);
		void splice(const_iterator pos, list&& other);
		void splice(const_iterator pos, list& other, const_iterator it);
		void splice(const_iterator pos, list&& other, const_iterator it);
		void splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
		void splice(const_iterator pos, list&& other, const_iterator first, const_iterator last);

		void remove(const T& value);
		template< class UnaryPredicate >
		void remove_if(UnaryPredicate p);

		void reverse();

		void unique();
		template< class BinaryPredicate >
		void unique(BinaryPredicate p);

		void sort();
		template< class Compare >
		void sort(Compare comp);
	};

	template< class T, class Alloc >
	bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	template< class T, class Alloc >
	bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	template< class T, class Alloc >
	bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	template< class T, class Alloc >
	bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	template< class T, class Alloc >
	bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	template< class T, class Alloc >
	bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);

	template< class T, class Alloc >
	void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs);

}

#endif // !UJ_LIST_HPP

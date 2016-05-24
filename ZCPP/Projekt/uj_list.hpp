/**
 * uj::list by Piotr Grudzien
 * @file uj_list.hpp
 * @author Piotr Grudzien
 */


#ifndef UJ_LIST_HPP
#define UJ_LIST_HPP

#include<memory>
#include<iterator>
#include<stdexcept>
#include<limits>

/** UJ namespace for assignment */
namespace uj
{
	/**
	 * \brief Forward List providing C++98 std::list interface.
	 * 
	 * Does not support reverse iterators.
	 */
	template<typename T, typename Allocator = std::allocator<T>>
	class list
	{
	private:
		/**
		 * \brief Private nested class of uj::list.
		 * 
		 * Basic node for use as a sentinel.
		 */
		struct lnode
		{
			lnode* next = nullptr; /**< Pointer to node containing next element in list. */
		};

		/**
		 * \brief Private nested class of uj::list.
		 *
		 * Node containing actual element of list.
		 */
		struct typenode : lnode
		{
			T value; /**< value of element contained in list. */

			/**
			 * \brief Typenode constructor.
			 * 
			 * Constructs typenode passing parameters to constructed object.
			 * \param[in] args Arguments passed to constructed object.
			 */
			template<typename... Args>
			typenode(Args&&... args): value(std::forward<Args>(args)...)
			{}
		};
	
//	public:
		/**
		 * \brief Const interator class.
		 * 
		 * const Forward Iterator used by uj::list
		 */
		class citer
		{
			friend class list;
		public:
			using value_type = T;
			using pointer = const value_type*;
			using reference = const value_type&;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;
			
		protected:
			lnode* pnode = nullptr;/**< Pointer to node before the element pointed to by iterator */
		
		public:
			/** Default constructor */
			citer() = default;
			/** Default destructor */
			~citer() = default;
			/** Constructs iterator pointing to element in p->next node
			 * \param[in] Pointer to node
			 */
			citer(lnode* p): pnode(p){}
			/** Default copu constructor */
			citer(const citer&) = default;
			/** Default copy assignment operator */
			citer& operator=(const citer&) = default;
			
			/**
			 * Dereference operator
			 * \return reference to const object pointed to by iterator.
			 */
			reference operator*() const noexcept
			{
				return reinterpret_cast<typenode*>(this->pnode->next)->value;
			}
			
			/**
			* Class member operator
			* \return pointer to const object pointed to by iterator.
			*/
			pointer operator->() const noexcept
			{
				return &reinterpret_cast<typenode*>(this->pnode->next)->value;
			}
			
			/**
			 * Pre-increment operator
			 * \return reference to *this
			 */
			citer& operator++() noexcept
			{
				
				this->pnode=this->pnode->next;
				return *this;
			}
			
			/**
			* Post-increment operator
			* \return Copy of *this before incrementation
			*/
			citer operator++(int) noexcept
			{
				citer tmp(*this);
				this->pnode=this->pnode->next;
				return tmp;
			}
			
			/**
			* Returns pointer held by iterator
			* \return held pointer
			*/
			lnode* node() const noexcept
			{
				return this->pnode;
			}

			/**
			* Equality operator
			* \return true if iterators point to the same element, otherwise false.
			*/
			friend bool operator==(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode == rhs.pnode;
			}
			
			/**
			* Unequality operator
			* \return false if iterator point to different elements, otherwise true.
			*/
			friend bool operator!=(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode != rhs.pnode;
			}
			
			/**
			* Returns iterator to next element in list without incrementing *this
			* \return Iterator to next element in sequence
			*/
			citer next() const noexcept
			{
				return citer(this->pnode->next);
			}
		};
		
		/**
		* \brief Iterator class.
		*
		* Forward Iterator used by uj::list.
		*/
		class iter : public citer
		{
			friend class list;
		public:
			using value_type = T;
			using pointer = value_type*;
			using reference = value_type&;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

		public:
			/** Default constructor */
			iter() = default;
			/** Default destructor */
			~iter() = default;
			/** Constructs iterator pointing to element in node p->next 
			 * \param[in] p Pointer to node
			 */
			iter(lnode* p) : citer(p) {}
			/** Default copy constructor */
			iter(const iter&) = default;
			/** Default copy assignment */
			iter& operator=(const iter&) = default;
			
			/**
			 * Dereference operator
			 * \return Reference to object pointed to by iterator
			 */
			reference operator*() const noexcept
			{
				return reinterpret_cast<typenode*>(this->pnode->next)->value;
			}

			/**
			* Class member operator
			* \return Pointer to object pointed to by iterator
			*/
			pointer operator->() const noexcept
			{
				return &reinterpret_cast<typenode*>(this->pnode->next)->value;
			}

			/**
			* Pre-increment operator
			* \return Reference to *this
			*/
			iter& operator++() noexcept
			{
				this->pnode = this->pnode->next;
				return *this;
			}

			/**
			* Post-increment operator
			* \return Copy of *this before incrementation
			*/
			iter operator++(int) noexcept
			{
				iter tmp(*this);
				this->pnode = this->pnode->next;
				return tmp;
			}
		};

	private:
		using Alloc = std::allocator_traits<Allocator>;
		using node_allocator_type = typename Alloc::template rebind_alloc<typenode>;
		using NodeAlloc = typename Alloc::template rebind_traits<typenode>;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = typename Alloc::pointer;
		using const_pointer = typename Alloc::const_pointer;
		using iterator = iter;
		using const_iterator = citer;

	private:
		lnode head; /**< Sentinel node */
		lnode* tail = &this->head; /** Pointer to last node in sequence. Can point to head when list is empty */
		size_type lSize = 0; /** Number of elements contained in the list */
		node_allocator_type alloc; /** Allocator used by the list */

		/**
		 * \brief Allocates and constructs typenode and element
		 * 
		 * \param[in] Parameters passed to constructed object
		 * \return Pointer to constructed node, nullptr if object constructor throws
		 */
		template<typename... Args>
		typenode* getNode(Args&&... args)
		{
			typenode* node = nullptr;
			try
			{
				node = NodeAlloc::allocate(this->alloc,1);
				NodeAlloc::construct(this->alloc,node,std::forward<Args>(args)...);
			}
			catch(...)
			{
				if(node)
				{
					NodeAlloc::deallocate(this->alloc,node,1);
				}
				throw;
			}
			return node;
		}
		
		/**
		 * \brief Destroys and deallocate given node
		 *
		 * \param[in] Pointer to node to be freed
		 */
		void freeNode(typenode* node) noexcept
		{
			NodeAlloc::destroy(this->alloc,node);
			NodeAlloc::deallocate(this->alloc,node,1);
		}
		
		void updateTail(lnode* tmp)
		{
			while(tmp->next)
			{
				tmp=tmp->next;
			}
			this->tail = tmp;
		}
		
	public:
		explicit list(const Allocator& alloc = Allocator()):
			alloc(alloc)
		{}
		
		explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator()):
			alloc(alloc)
		{
			this->insert(this->begin(),count,value);
		}

		list(const list& other) :
			alloc(NodeAlloc::select_on_container_copy_construction(other.alloc))
		{
			this->insert(this->begin(), other.begin(), other.end());
		}
		
		template<typename InIterator>
		list(InIterator first, InIterator last, const Allocator& alloc = Allocator()):
			alloc(alloc)
		{
			this->insert(this->begin(),first,last);
		}

		~list()
		{
			this->clear();
		}
		
		list& operator=(const list& other)
		{
			if(this!=std::addressof(other))
			{
				if(NodeAlloc::propagate_on_container_copy_assignment::value)
				{
					this->alloc = other.alloc;
				}
				this->assign(other.begin(),other.end());
			}
			return *this;
		}

		void assign(size_type count, const T& value)
		{
			this->clear();
			this->insert(this->begin(),count,value);
		}
		
		template<typename InIterator>
		void assign(InIterator first, InIterator last)
		{
			this->clear();
			this->insert(this->begin(),first,last);
		}

		allocator_type get_allocator() const
		{
			return Allocator();
		}

		reference front()
		{
			return reinterpret_cast<typenode*>(this->head.next)->value;
		}

		const_reference front() const
		{
			return reinterpret_cast<typenode*>(this->head.next)->value;
		}

		reference back()
		{
			return reinterpret_cast<typenode*>(this->tail)->value;
		}
		
		const_reference back() const
		{
			return reinterpret_cast<typenode*>(this->tail)->value;
		}

		iterator begin() noexcept
		{
			return iterator(&this->head);
		}
		
		const_iterator begin() const noexcept
		{
			return const_iterator(const_cast<lnode*>(&this->head));
		}
		
		const_iterator cbegin() const noexcept
		{
			return this->begin();
		}
		
		iterator end() noexcept
		{
			return iterator(this->tail);
		}
		
		const_iterator end() const noexcept
		{
			return const_iterator(this->tail);
		}
		
		const_iterator cend() const noexcept
		{
			return this->end();
		}

		bool empty() const noexcept
		{
			return this->lSize==0;
		}
		
		size_type size() const noexcept
		{
			return this->lSize;
		}
		
		size_type max_size() const noexcept
		{
			return std::numeric_limits<size_type>::max();
		}

		void clear() noexcept
		{
			while(this->head.next!=nullptr)
			{
				auto node = reinterpret_cast<typenode*>(this->head.next);
				this->head.next=node->next;
				freeNode(node);
			}
			this->tail = &this->head;
			this->lSize=0;
		}

		iterator insert(iterator pos, const T& value)
		{
			auto node = getNode(value);
			node->next = pos.pnode->next;
			pos.pnode->next = node;
			++this->lSize;
			if(this->tail==pos.pnode)
			{
				this->tail=node;
			}
			return pos;
		}
		
		void insert(iterator pos, size_type count, const T& value)
		{
			while(count--)
			{
				insert(pos,value);
			}
		}
		
		template< class InputIt >
		void insert(iterator pos, InputIt first, InputIt last)
		{
			while(first!=last)
			{
				insert(pos,*(first++));
				++pos;
			}
		}

		iterator erase(iterator pos)
		{
			auto node = pos.pnode->next;
			pos.pnode->next=node->next;
			if(node==this->tail)
			{
				this->tail=pos.pnode;
			}
			--this->lSize;
			freeNode(reinterpret_cast<typenode*>(node));
			return pos;
		}
		
		iterator erase(iterator first, iterator last)
		{
			auto end = last.pnode->next;
			while(first.pnode->next!=end)
			{
				first=this->erase(first);
			}
			return first;
		}

		void push_back(const T& value)
		{
			this->insert(this->end(),value);
		}

		void pop_back()
		{
			if(this->lSize==0) return;
			auto it = this->begin();
			while(it.pnode->next!=this->tail) ++it;
			this->erase(it);
		}

		void push_front(const T& value)
		{
			this->insert(this->begin(),value);
		}

		void pop_front()
		{
			this->erase(this->begin());
		}

		void resize(size_type count, value_type value = T() )
		{
			if(count < this->lSize)
			{
				auto it = this->begin();
				while(count--) ++it;
				this->erase(it,this->end());
			}
			else
			{
				count-=this->lSize;
				this->insert(this->end(),count,value);
			}
		}

		void swap(list& other)
		{
			using std::swap;
			if(NodeAlloc::propagate_on_container_swap::value)
			{
				swap(this->alloc,other.alloc);
			}
			swap(this->lSize,other.lSize);
			swap(this->tail,other.tail);
			swap(this->head,other.head);
		}

		void merge(list& other)
		{
			this->merge(other,[](const T& lhs,const T& rhs)->bool{return lhs<rhs;});
		}
		
		
		template <class Compare>
		void merge(list& other, Compare comp)
		{
			auto a = &this->head;
			auto b = &other.head;
			lnode* tmp = nullptr;
			while(a->next && b->next)
			{
				if(comp(reinterpret_cast<typenode*>(b->next)->value,reinterpret_cast<typenode*>(a->next)->value))
				{
					tmp = b->next;
					b->next=tmp->next;
					tmp->next = a->next;
					a->next=tmp;
					a=tmp;
				}
				else
				{
					a=a->next;
				}
			}
			if(b->next)
			{
				a->next=b->next;
				b->next=nullptr;
				while(a->next!=nullptr)
				{
					a = a->next;
				}
				this->tail = a;
			}
			
			this->lSize+=other.lSize;
			other.lSize=0;
			other.tail = &other.head;
		}

		void splice(const_iterator pos, list& other)
		{
			if(this==&other) return;
			other.tail->next=pos.pnode->next;
			pos.pnode->next=other.head.next;
			this->lSize+=other.lSize;
			other.lSize=0;
			if(pos.pnode==this->tail) this->tail=other.tail;
			other.tail = &other.head;
			other.head.next = nullptr;
		}
		
		void splice(const_iterator pos, list& other, const_iterator it)
		{
			if(it.pnode->next == nullptr) return;
			auto tmp = it.pnode->next;
			it.pnode->next = it.pnode->next->next;
			if(it.pnode->next==other.tail) other.tail = it.pnode;
			++this->lSize;
			tmp->next=pos.pnode->next;
			pos.pnode->next = tmp;
			if(pos.pnode==this->tail) this->tail = tmp;
			--other.lSize;
		}
		
		void splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
		{
			auto tmp = last.pnode->next;
			if(this==&other)
			{
				if(last.pnode==this->tail) this->tail=first.pnode;
				if(pos.pnode==this->tail) this->tail=last.pnode;
				last.pnode->next = pos.pnode->next;
				pos.pnode->next = first.pnode->next;
				first.pnode->next = tmp;
			}
			else
			{
				{
					size_type count = 0;
					auto tmp = first;
					while((tmp++)!=last) ++count;
					this->lSize+=count;
					other.lSize-=count;
				}
				last.pnode->next = pos.pnode->next;
				pos.pnode->next = first.pnode->next;
				first.pnode->next = tmp;
				if(last.pnode == other.tail) other.tail = first.pnode;
				if(pos.pnode == this->tail) this->tail = last.pnode;
			}
		}

		void remove(const T& value)
		{
			this->remove_if([&value](const T& e)->bool{return e==value;});
		}
		
		template< class UnaryPredicate >
		void remove_if(UnaryPredicate p)
		{
			auto it = this->begin();
			while(it!=this->end())
			{
				if(p(*it)) it=this->erase(it);
				else ++it;
			}
		}

		void reverse()
		{
			auto pnode = this->head.next;
			auto tmp = pnode;
			while(pnode->next)
			{
				tmp = pnode->next;
				pnode->next = pnode->next->next;
				tmp->next = this->head.next;
				this->head.next = tmp;
			}
			this->tail = pnode;
		}

		void unique()
		{
			this->unique([](const T& lhs, const T& rhs)->bool {return lhs==rhs;});
		}
		
		template< class BinaryPredicate >
		void unique(BinaryPredicate p)
		{
			auto second = this->begin();
			auto first = second++; 
			while(second!=this->end())
			{
				if(p(*first,*second)) second=this->erase(second);
				else
				{
					++first;
					++second;
				}
			}
		}

		void sort()
		{
			this->sort([](const T& lhs, const T& rhs)->bool {return lhs<rhs;});
		}
		
		template< class Compare >
		void sort(Compare comp)
		{
			bool swapped = true;
			lnode* a = nullptr, *b = nullptr, *tmp = nullptr;
			while(swapped)
			{
				a = &this->head;
				b = this->head.next;
				swapped = false;
				while(b->next)
				{
					if(comp(reinterpret_cast<typenode*>(b->next)->value,reinterpret_cast<typenode*>(a->next)->value))
					{
						tmp = b->next;
						b->next = tmp->next;
						tmp->next = b;
						a->next = tmp;
						a=tmp;
						swapped=true;
					}
					else
					{
						a=b;
						b=b->next;
					}
				}
			}
		}
	};

	template< class T, class Alloc >
	bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if(lhs.size()!=rhs.size()) return false;
		for(auto a = lhs.begin(), b = rhs.begin(), end = lhs.end(); a!=end; ++a,++b)
		{
			if(*a!=*b) return false;
		}
		return true;
	}
	
	template< class T, class Alloc >
	bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if(lhs.size()!=rhs.size()) return true;
		for(auto a = lhs.begin(), b = rhs.begin(), end = lhs.end(); a!=end; ++a,++b)
		{
			if(*a!=*b) return true;
		}
		return false;
	}

	/*
{
    for ( ; (first1 != last1) && (first2 != last2); first1++, (void) first2++ ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}*/

	template< class T, class Alloc >
	bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		auto a = lhs.begin(), b = rhs.begin(), aend = lhs.end(), bend = rhs.end();
		for(;(a!=aend) && (b != bend); ++a, ++b)
		{
			if(*a < *b) return true;
			if(*b < *a) return false;
		}
		return (a==aend) && (b!=bend);
	}
	
	template< class T, class Alloc >
	bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs>rhs);
	}
	
	template< class T, class Alloc >
	bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		auto a = lhs.begin(), b = rhs.begin(), aend = lhs.end(), bend = rhs.end();
		for(;(a!=aend) && (b != bend); ++a, ++b)
		{
			if(*a > *b) return true;
			if(*b > *a) return false;
		}
		return (a!=aend) && (b==bend);
	}
	
	template< class T, class Alloc >
	bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs<rhs);
	}

	template< class T, class Alloc >
	void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}

#endif // !UJ_LIST_HPP

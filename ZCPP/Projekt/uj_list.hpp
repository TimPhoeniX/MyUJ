/**
 * uj::list by Piotr Grudzien
 * \file uj_list.hpp
 * \author Piotr Grudzien
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
			typenode(Args&&... args) : value(std::forward<Args>(args)...)
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
			/**
			 * \brief Constructs iterator pointing to element in p->next node
			 *
			 * \param[in] Pointer to node
			 */
			citer(lnode* p) : pnode(p) {}
			/** Default copu constructor */
			citer(const citer&) = default;
			/** Default copy assignment operator */
			citer& operator=(const citer&) = default;

			/**
			 * \brief Dereference operator
			 *
			 * \return reference to const object pointed to by iterator.
			 */
			reference operator*() const noexcept
			{
				return reinterpret_cast<typenode*>(this->pnode->next)->value;
			}

			/**
			 * \brief Class member operator
			 *
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

				this->pnode = this->pnode->next;
				return *this;
			}

			/**
			 * \brief Post-increment operator
			 *
			 * \return Copy of *this before incrementation
			 */
			citer operator++(int) noexcept
			{
				citer tmp(*this);
				this->pnode = this->pnode->next;
				return tmp;
			}

			/**
			 * \brief Returns pointer held by iterator
			 *
			 * \return held pointer
			 */
			lnode* node() const noexcept
			{
				return this->pnode;
			}

			/**
			 * \brief Equality operator
			 *
			 * \return true if iterators point to the same element, otherwise false.
			 */
			friend bool operator==(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode == rhs.pnode;
			}

			/**
			 * \brief Unequality operator
			 *
			 * \return false if iterator point to different elements, otherwise true.
			 */
			friend bool operator!=(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode != rhs.pnode;
			}

			/**
			 * \brief Returns iterator to next element in list without incrementing *this
			 * 
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
		 * \param[in] args Parameters passed to constructed object
		 * \return Pointer to constructed node, nullptr if object constructor throws
		 */
		template<typename... Args>
		typenode* getNode(Args&&... args)
		{
			typenode* node = nullptr;
			try
			{
				node = NodeAlloc::allocate(this->alloc, 1);
				NodeAlloc::construct(this->alloc, node, std::forward<Args>(args)...);
			}
			catch(...)
			{
				if(node)
				{
					NodeAlloc::deallocate(this->alloc, node, 1);
				}
				throw;
			}
			return node;
		}

		/**
		 * \brief Destroys and deallocate given node
		 *
		 * \param[in] node Pointer to node to be freed
		 * \remarks Complexity Constant
		 */
		void freeNode(typenode* node) noexcept
		{
			NodeAlloc::destroy(this->alloc, node);
			NodeAlloc::deallocate(this->alloc, node, 1);
		}

		void updateTail(lnode* tmp)
		{
			while(tmp->next)
			{
				tmp = tmp->next;
			}
			this->tail = tmp;
		}

	public:
		/**
		 * \brief Constructs an empty list with given allocator
		 *
		 * \param[in] alloc Allocator to be used by the list
		 * \remarks Complexity constant
		 */
		explicit list(const Allocator& alloc = Allocator()) :
			alloc(alloc)
		{}

		/**
		 * \brief Constructs a list with count copies of value and given allocator
		 *
		 * \param[in] count Number of new elements
		 * \param[in] value Value of new elements
		 * \param[in] alloc Allocator to be used by the list
		 * \remarks Complexity linear in count
		 */
		explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
			alloc(alloc)
		{
			this->insert(this->begin(), count, value);
		}

		/**
		 * \brief Constructs a list that is copy of other
		 *
		 * \param[in] other List to be copied
		 * \remarks Complexity linear in other.size()
		 */
		list(const list& other) :
			alloc(NodeAlloc::select_on_container_copy_construction(other.alloc))
		{
			this->insert(this->begin(), other.begin(), other.end());
		}

		/**
		 * \brief Constructs list of elements from range [first,last)
		 *
		 * \param[in] first Iterator to the first element in range
		 * \param[in] last Iterator beyond the last element in range
		 * \param[in] alloc Allocator to be used by the list
		 * \remarks Complexity linear in std::distance(first,last)
		 */
		template<typename InIterator>
		list(InIterator first, InIterator last, const Allocator& alloc = Allocator()) :
			alloc(alloc)
		{
			this->insert(this->begin(), first, last);
		}

		/**
		 * \brief Destroys a list
		 *
		 * \remarks Complexity linear in this->size()
		 */
		~list()
		{
			this->clear();
		}

		/**
		 * \brief Replaces contents of *this with contents of other
		 *
		 * \param[in] other List to be copied
		 * \remarks Complexity linear in this->size()+other.size()
		 * All references and iterators (except begin()) are invalidated
		 */
		list& operator=(const list& other)
		{
			if(this != std::addressof(other))
			{
				if(NodeAlloc::propagate_on_container_copy_assignment::value)
				{
					this->alloc = other.alloc;
				}
				this->assign(other.begin(), other.end());
			}
			return *this;
		}

		/**
		 * \brief Replaces contents with count copies of value
		 *
		 * \param[in] count Number of new elements
		 * \param[in] value Value of new elements
		 * \remarks Complexity linear in this->size()+count
		 * All references and iterators (except begin()) are invalidated
		 */
		void assign(size_type count, const T& value)
		{
			this->clear();
			this->insert(this->begin(), count, value);
		}

		/**
		 * \brief Replaces contents with elements from range [first,last)
		 *
		 * \param[in] first Iterator to the first element in range
		 * \param[in] last Iterator beyond the last element in range
		 * \remarks Complexity linear in this->size()+std::distance(first,last)
		 * All references and iterators (except begin()) are invalidated
		 */
		template<typename InIterator>
		void assign(InIterator first, InIterator last)
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}

		/**
		 * \brief Returns an instance of Allocator
		 *
		 * \return instance of Allocator
		 */
		allocator_type get_allocator() const
		{
			return Allocator();
		}

		/**
		 * \brief Returns reference to the first element in list
		 *
		 * \return Reference to the first element in list
		 * \remarks Complexity constant
		 */
		reference front()
		{
			return reinterpret_cast<typenode*>(this->head.next)->value;
		}

		/**
		 * \brief Returns const_reference to the first element in list
		 *
		 * \return Const Reference to the first element in list
		 * \remarks Complexity constant
		 */
		const_reference front() const
		{
			return reinterpret_cast<typenode*>(this->head.next)->value;
		}

		/**
		 * \brief Returns reference to the last element in list
		 *
		 * \return Reference to the last element in list
		 * \remarks Complexity constant
		 */
		reference back()
		{
			return reinterpret_cast<typenode*>(this->tail)->value;
		}

		/**
		 * \brief Returns const_reference to the last element in list
		 *
		 * \return Const Reference to the last element in list
		 * \remarks Complexity constant
		 */
		const_reference back() const
		{
			return reinterpret_cast<typenode*>(this->tail)->value;
		}

		/**
		 * \brief Returns iterator to the first element
		 *
		 * \return Iterator to the first elements
		 * \remarks Complexity constant
		 */
		iterator begin() noexcept
		{
			return iterator(&this->head);
		}

		/**
		 * \brief Returns const iterator to the first element
		 *
		 * \return Const Iterator to the first elements
		 * \remarks Complexity constant
		 */
		const_iterator begin() const noexcept
		{
			return const_iterator(const_cast<lnode*>(&this->head));
		}

		/**
		 * \brief Returns const iterator to the first element
		 *
		 * \return Const iterator to the first elements
		 * \remarks Complexity constant
		 */
		const_iterator cbegin() const noexcept
		{
			return this->begin();
		}

		/**
		 * \brief Returns iterator beyond the last element
		 *
		 * \return Iterator to the first elements
		 * \remarks Complexity constant
		 */
		iterator end() noexcept
		{
			return iterator(this->tail);
		}

		/**
		 * \brief Returns const iterator beyond the last element
		 *
		 * \return Const iterator to the first elements
		 * \remarks Complexity constant
		 */
		const_iterator end() const noexcept
		{
			return const_iterator(this->tail);
		}

		/**
		 * \brief Returns const iterator beyond the last element
		 *
		 * \return Const iterator to the first elements
		 * \remarks Complexity constant
		*/
		const_iterator cend() const noexcept
		{
			return this->end();
		}

		/**
		 * \brief Checks if the list has no elements
		 *
		 * \return true if the list is empty, otherwise false
		 * \remarks Complexity constant
		 */
		bool empty() const noexcept
		{
			return this->lSize == 0;
		}

		/**
		 * \brief Returns the number of elements in list
		 *
		 * \return Number of elements in list
		 * \remarks Complexity constant
		 */
		size_type size() const noexcept
		{
			return this->lSize;
		}

		/**
		 * \brief Returns the maximum number of elements the list can contain
		 *
		 * \return Maximum number of elements
		 * \remarks Complexity constant. 
		 * Typically returns a theoretical number of elements, actual number may be different.
		 */
		size_type max_size() const noexcept
		{
			return std::numeric_limits<size_type>::max();
		}

		/**
		 * \brief Empties the list
		 *
		 * \remarks Complexity linear in this->size()
		 * All references and iterators (except begin()) are invalidated
		 */
		void clear() noexcept
		{
			while(this->head.next != nullptr)
			{
				auto node = reinterpret_cast<typenode*>(this->head.next);
				this->head.next = node->next;
				freeNode(node);
			}
			this->tail = &this->head;
			this->lSize = 0;
		}

		/**
		 * \brief Inserts new element into the list.
		 *
		 * New element is inserted before the element pointed to by the pos
		 * \param[in] pos iterator to element before which new element will be inserted. May be end()
		 * \param[in] value Value of element to be inserted
		 * \return Iterator to inserted element
		 * \remarks Complexity constant.
		 * No references are invalidated.
		 * Iterators equal to pos now point to the inserted element
		 */
		iterator insert(iterator pos, const T& value)
		{
			auto node = getNode(value);
			node->next = pos.pnode->next;
			pos.pnode->next = node;
			++this->lSize;
			if(this->tail == pos.pnode)
			{
				this->tail = node;
			}
			return pos;
		}

		/**
		 * \brief Inserts count new elements into the list.
		 *
		 * New element is inserted before the element pointed to by the pos
		 * \param[in] pos Iterator to element before which new element will be inserted. May be end()
		 * \param[in] value Value of elements to be inserted
		 * \return Iterator to inserted element
		 * \remarks Complexity linear in count
		 * No references are invalidated.
		 * Iterators equal to pos now point to the first inserted element
		 */
		void insert(iterator pos, size_type count, const T& value)
		{
			while(count--)
			{
				insert(pos, value);
				++pos;
			}
		}

		/**
		 * \brief Inserts elements from range [first,last) into the list.
		 *
		 * New elements is inserted before the element pointed to by the pos
		 * \param[in] pos iterator to element before which new elements will be inserted. May be end()
		 * \param[in] first Iterator to the first element in range
		 * \param[in] last Iterator beyond the last element in range
		 * \remarks Complexity linear in std::distance(first,last)
		 * No references are invalidated.
		 * Iterators equal to pos now point to the first element inserted
		 */
		template< class InputIt >
		void insert(iterator pos, InputIt first, InputIt last)
		{
			while(first != last)
			{
				insert(pos, *(first++));
				++pos;
			}
		}

		/**
		 * \brief Removes element pointed to by pos
		 *
		 * \param[in] pos Iterator to element to be removed
		 * \return Iterator to the next element in the list
		 * \remarks Complexity constant
		 * Iterators equal to pos now point to the next element in the list
		 * Iterators equal to std::next(pos) are invalidated
		 * References to removed element are invalidated
		 * Behavior is only defined if pos is not end()
		 */
		iterator erase(iterator pos)
		{
			auto node = pos.pnode->next;
			pos.pnode->next = node->next;
			if(node == this->tail)
			{
				this->tail = pos.pnode;
			}
			--this->lSize;
			freeNode(reinterpret_cast<typenode*>(node));
			return pos;
		}

		/**
		 * \brief Removes elements in range [first,last)
		 *
		 * \param[in] first Iterator to the first element to be removed
		 * \param[in] last Iterator beyond the last element to be removed
		 * \return Iterator to the next element in the list
		 * \remarks Complexity linear in std::distance(first,last)
		 * Iterators equal to first now point to the next element in the list
		 * last is invalidated
		 * All references and iterators (except first) to removed elements are invalidated
		 */
		iterator erase(iterator first, iterator last)
		{
			auto end = last.pnode->next;
			while(first.pnode->next != end)
			{
				this->erase(first);
			}
			return first;
		}

		/**
		 * \brief Inserts new element at the end of the list
		 *
		 * \param[in] value of element to be inserted
		 * \remarks Complexity constant
		 */
		void push_back(const T& value)
		{
			this->insert(this->end(), value);
		}

		/**
		 * \brief Removes the last element from the list
		 *
		 * \remarks Complexity constant.
		 * Is a No-op if the list is empty
		 * References and iterators to removed element are invalidated
		 * end() iterators are invalidated
		 */
		void pop_back()
		{
			if(this->lSize == 0) return;
			auto it = this->begin();
			while(it.pnode->next != this->tail) ++it;
			this->erase(it);
		}

		/**
		 * \brief Inserts new element at the beginning of the list
		 *
		 * \param[in] value of element to be inserted
		 * \remarks Complexity constant
		*/
		void push_front(const T& value)
		{
			this->insert(this->begin(), value);
		}

		/**
		 * \brief Removes the last element from the list
		 *
		 * \remarks Complexity constant.
		 * Is a No-op if the list is empty
		 * References to removed elements are invalidated.
		 * Iterators to removed element and begin() now point to next element in the list
		 */
		void pop_front()
		{
			this->erase(this->begin());
		}

		/**
		 * \brief Changes size of the list to count
		 *
		 * Removes elements exceeding count or adds new elements equal to value if count > this->size()
		 * \param[in] count New size of the container
		 * \param[in] value Value of new elements that may be inserted
		 * \remarks Complexity linear in this->size() if count < this->size, otherwise linear in count-this->size()
		 * If any element is removed all references and iterators to it are invalidated, except iterator to first element removed, which now is end()
		 */
		void resize(size_type count, value_type value = T())
		{
			if(count < this->lSize)
			{
				auto it = this->begin();
				while(count--) ++it;
				this->erase(it, this->end());
			}
			else
			{
				count -= this->lSize;
				this->insert(this->end(), count, value);
			}
		}

		/**
		 * \brief Swaps the contents of *this and other
		 *
		 * \param[in] other List to be swapped with
		 * \remarks Complexity consant
		 * No references are invalidated
		 * begin() iterators remain valid, but after the swap they point to the first element in their respective container
		 */
		void swap(list& other)
		{
			using std::swap;
			if(NodeAlloc::propagate_on_container_swap::value)
			{
				swap(this->alloc, other.alloc);
			}
			swap(this->lSize, other.lSize);
			swap(this->tail, other.tail);
			swap(this->head, other.head);
		}

		/**
		 * \brief Merges sorted elements of two lists
		 *
		 * Elements are compared using operator<
		 * other becomes empty after this operation, no elements are copied
		 * \param[in] other List to be merged with
		 * \remarks Complexity linear in this->size()+other.size()
		 * No references are invalidated
		 * begin() iterators remain valid, but after the merge they point to the first element in *this, or end() in other
		 */
		void merge(list& other)
		{
			this->merge(other, [](const T& lhs, const T& rhs)->bool {return lhs < rhs; });
		}

		/**
		 * \brief Merges sorted elements of two lists
		 *
		 * Elements are compared using given comparator comp
		 * comp should have following signature bool(const T&,const T&), const is not required, but comp must not modify compared elements
		 * other becomes empty after this operation, no elements are copied
		 * \param[in] other List to be merged with
		 * \param[in] comp Comparator used to compare elements
		 * \remarks Complexity linear in this->size()+other.size()
		 * No references are invalidated
		 * begin() iterators remain valid, but after the merge they point to the first element in *this, or end() in other
		 */
		template <class Compare>
		void merge(list& other, Compare comp)
		{
			auto a = &this->head;
			auto b = &other.head;
			lnode* tmp = nullptr;
			while(a->next && b->next)
			{
				if(comp(reinterpret_cast<typenode*>(b->next)->value, reinterpret_cast<typenode*>(a->next)->value))
				{
					tmp = b->next;
					b->next = tmp->next;
					tmp->next = a->next;
					a->next = tmp;
					a = tmp;
				}
				else
				{
					a = a->next;
				}
			}
			if(b->next)
			{
				a->next = b->next;
				b->next = nullptr;
				while(a->next != nullptr)
				{
					a = a->next;
				}
				this->tail = a;
			}

			this->lSize += other.lSize;
			other.lSize = 0;
			other.tail = &other.head;
		}

		/**
		 * \brief Moves all elements from other to *this
		 *
		 * Moves all elements to before the element pointed to by the pos
		 * \param[in] pos iterator to element before which the elements will be moved. May be end()
		 * \param[in] other List from which the elements are moved
		 * \remarks Complexity linear in other.size()
		 * No references are invalidated
		 * begin() iterators to other remain valid but now point to end() of other
		 * pos now points to the first element moved
		 */
		void splice(const_iterator pos, list& other)
		{
			if(this == &other) return;
			other.tail->next = pos.pnode->next;
			pos.pnode->next = other.head.next;
			this->lSize += other.lSize;
			other.lSize = 0;
			if(pos.pnode == this->tail) this->tail = other.tail;
			other.tail = &other.head;
			other.head.next = nullptr;
		}

		/**
		 * \brief Moves an element from other to *this
		 *
		 * Moves an element pointed to by it to before the element pointed to by the pos
		 * \param[in] pos iterator to element before which the element will be moved. May be end()
		 * \param[in] other List from which the elements are moved
		 * \param[in] it iterator to element to be moved
		 * \remarks Complexity constant
		 * No references are invalidated
		 * pos now points to moved element
		 * it now points to the next element in other
		 */
		void splice(const_iterator pos, list& other, const_iterator it)
		{
			if(it.pnode->next == nullptr) return;
			auto tmp = it.pnode->next;
			it.pnode->next = it.pnode->next->next;
			if(it.pnode->next == other.tail) other.tail = it.pnode;
			++this->lSize;
			tmp->next = pos.pnode->next;
			pos.pnode->next = tmp;
			if(pos.pnode == this->tail) this->tail = tmp;
			--other.lSize;
		}

		/**
		 * \brief Moves the elements from other to *this
		 *
		 * Moves the elements in range [first,last) to before the element pointed to by the pos
		 * \param[in] pos iterator to element before which the elements will be moved. May be end()
		 * \param[in] other List from which the elements are moved
		 * \param[in] first iterator to the first element to be moved
		 * \param[in] last iterator beyond the last element to be moved
		 * \remarks Complexity constant if *this==other, otherwise linear in std::distance(first,last)
		 * Results are undefined if pos is in range [first,last)
		 * No references are invalidated
		 * pos now points to the first element inserted
		 * first now points to the element previously pointed to by last
		 * last now points to the element previously pointed to by pos
		 */
		void splice(const_iterator pos, list& other, const_iterator first, const_iterator last)
		{
			auto tmp = last.pnode->next;
			if(this == &other)
			{
				if(last.pnode == this->tail) this->tail = first.pnode;
				if(pos.pnode == this->tail) this->tail = last.pnode;
				last.pnode->next = pos.pnode->next;
				pos.pnode->next = first.pnode->next;
				first.pnode->next = tmp;
			}
			else
			{
				{
					size_type count = 0;
					auto tmp = first;
					while((tmp++) != last) ++count;
					this->lSize += count;
					other.lSize -= count;
				}
				last.pnode->next = pos.pnode->next;
				pos.pnode->next = first.pnode->next;
				first.pnode->next = tmp;
				if(last.pnode == other.tail) other.tail = first.pnode;
				if(pos.pnode == this->tail) this->tail = last.pnode;
			}
		}

		/**
		 * \brief Removes elements equal to value from the list
		 *
		 * Uses operator== to compare the elements
		 * \param[in] value Value to which the elements are compared
		 * \remarks Complexity linear in this->size()
		 * References to removed elements are invalidated
		 * Iterators to removed elements now point to their respective next element
		 * Iterators to elements following removed elements are invalidated
		 */
		void remove(const T& value)
		{
			this->remove_if([&value](const T& e)->bool {return e == value; });
		}

		/**
		 * \brief Removes elements according to the predicate p
		 *
		 * p should have following signatue: bool(const T&), const is not required, but p must not modify tested elements
		 * \param[in] p predicate used to check if an element should be removed
		 * \remarks Complexity linear in this->size()
		 * References to removed elements are invalidated
		 * Iterators to removed elements now point to their respective next element
		 * Iterators to elements following removed elements are invalidated
		 */
		template< class UnaryPredicate >
		void remove_if(UnaryPredicate p)
		{
			auto it = this->begin();
			while(it != this->end())
			{
				if(p(*it)) it = this->erase(it);
				else ++it;
			}
		}

		/**
		 * \brief Reverser the order of elements in the list
		 *
		 * \remarks Complexity linear in this->size()
		 * No references are invalidated
		 * Iterators remain valid but they now point to different elements
		 * end() iterators are now equal to std::next(begin())
		 * begin() iterators remain valid and point to the first element in the list
		 */
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

		/**
		 * \brief Removes consecutive duplicate elements from the list
		 *
		 * Uses operator== to compare elements
		 * \remarks Complexity linear in this->size()
		 * References to removed elements are invalidated
		 * Iterators to removed elements now point to their respective next element
		 * Iterators to elements following removed elements are invalidated
		 */
		void unique()
		{
			this->unique([](const T& lhs, const T& rhs)->bool {return lhs == rhs; });
		}

		/**
		 * \brief Removes consecutive duplicate elements from the list
		 *
		 * Elements are compared using given predicate p
		 * p should have following signature bool(const T&,const T&), const is not required, but p must not modify compared elements
		 * \remarks Complexity linear in this->size()
		 * References to removed elements are invalidated
		 * Iterators to removed elements now point to their respective next element
		 * Iterators to elements following removed elements are invalidated
		 */
		template< class BinaryPredicate >
		void unique(BinaryPredicate p)
		{
			auto second = this->begin();
			auto first = second++;
			while(second != this->end())
			{
				if(p(*first, *second)) second = this->erase(second);
				else
				{
					++first;
					++second;
				}
			}
		}

		/**
		 * \brief Sorts contents of the list
		 *
		 * Uses operator< to compare the elements
		 * Uses bubble sort algorithm
		 * \remarks Complexity quadratic in this->size() (i.e n^2 where n is this->size())
		 * No references are invalidated
		 * Iterators remain valid but now point to different elements
		 * begin() iterators now point to first element in the list
		 */
		void sort()
		{
			this->sort([](const T& lhs, const T& rhs)->bool {return lhs < rhs; });
		}

		/**
		 * \brief Sorts contents of the list
		 *
		 * Elements are compared using given comparator comp
		 * comp should have following signature bool(const T&,const T&), const is not required, but comp must not modify compared elements
		 * Uses bubble sort algorithm
		 * \remarks Complexity quadratic in this->size() (i.e n^2 where n is this->size())
		 * No references are invalidated
		 * Iterators remain valid but now point to different elements
		 * begin() iterators now point to first element in the list
		 */
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
					if(comp(reinterpret_cast<typenode*>(b->next)->value, reinterpret_cast<typenode*>(a->next)->value))
					{
						tmp = b->next;
						b->next = tmp->next;
						tmp->next = b;
						a->next = tmp;
						a = tmp;
						swapped = true;
					}
					else
					{
						a = b;
						b = b->next;
					}
				}
			}
		}
	};

	template< class T, class Alloc >
	bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if(lhs.size() != rhs.size()) return false;
		for(auto a = lhs.begin(), b = rhs.begin(), end = lhs.end(); a != end; ++a, ++b)
		{
			if(*a != *b) return false;
		}
		return true;
	}

	template< class T, class Alloc >
	bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if(lhs.size() != rhs.size()) return true;
		for(auto a = lhs.begin(), b = rhs.begin(), end = lhs.end(); a != end; ++a, ++b)
		{
			if(*a != *b) return true;
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
		for(; (a != aend) && (b != bend); ++a, ++b)
		{
			if(*a < *b) return true;
			if(*b < *a) return false;
		}
		return (a == aend) && (b != bend);
	}

	template< class T, class Alloc >
	bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template< class T, class Alloc >
	bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		auto a = lhs.begin(), b = rhs.begin(), aend = lhs.end(), bend = rhs.end();
		for(; (a != aend) && (b != bend); ++a, ++b)
		{
			if(*a > *b) return true;
			if(*b > *a) return false;
		}
		return (a != aend) && (b == bend);
	}

	template< class T, class Alloc >
	bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}

#endif // !UJ_LIST_HPP

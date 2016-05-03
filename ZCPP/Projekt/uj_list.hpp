/**
 * uj::list by Piotr Grudzien
 */

#ifndef UJ_LIST_HPP
#define UJ_LIST_HPP

#include<memory>
#include<iterator>
#include<stdexcept>
#include<limits>

namespace uj
{
	template<typename T, typename Allocator = std::allocator<T>>
	class list
	{
	private:
		struct lnode
		{
			lnode* next = nullptr;
		};

		struct typenode : lnode
		{
			T value;

			template<typename... Args>
			typenode(Args&&... args): value(std::forward<Args>(args)...)
			{}
		};
	
	public:
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
				return reinterpret_cast<typenode*>(this->pnode->next)->value;
			}
			
			pointer operator->() const noexcept
			{
				return &reinterpret_cast<typenode*>(this->pnode->next)->value;
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

			friend bool operator==(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode == rhs.pnode;
			}
			
			friend bool operator!=(const citer& lhs, const citer& rhs) noexcept
			{
				return lhs.pnode != rhs.pnode;
			}
			
			citer next() const noexcept
			{
				return citer(this->pnode->next);
			}
		};
		
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
			iter() = default;
			~iter() = default;
			iter(lnode* p) : citer(p) {}
			iter(const iter&) = default;
			iter(iter&&) = default;
			iter& operator=(const iter&) = default;
			iter& operator=(iter&&) = default;

			reference operator*() const noexcept
			{
				return reinterpret_cast<typenode*>(this->pnode->next)->value;
			}

			pointer operator->() const noexcept
			{
				return &reinterpret_cast<typenode*>(this->pnode->next)->value;
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
		lnode head;
		lnode* tail = &this->head;
		size_t lSize = 0;
		node_allocator_type alloc;
		
		template<typename... Args>
		typenode* getNode(Args&&... args)
		{
			typenode* node;
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
/*
	template<typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args)
	{
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
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
		
		template<typename InIterator>
		list(InIterator first, InIterator last, const Allocator& alloc = Allocator()):
			alloc(alloc)
		{
			this->insert(this->begin(),first,last);
		}
			
		list(const list& other):
			alloc(NodeAlloc::select_on_container_copy_construction(other.alloc))
		{
			this->insert(this->begin(),other.begin(),other.end());
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
				this->assing(other.begin(),other.end());
			}
			return *this;
		}

		void assing(size_type count, const T& value)
		{
			this->clear();
			this->insert(this->begin(),count,value);
		}
		
		template<typename InIterator>
		void assing(InIterator first, InIterator last)
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
		}
		
		void splice(const_iterator pos, list& other, const_iterator it)
		{
			if(it.pnode->next == nullptr) return;
			auto tmp = it.pnode->next;
			it.pnode->next = it.pnode->next->next;
			if(it.pnode->next==other.tail) other.tail = it.pnode;
			--this->lSize;
			tmp->next=pos.pnode->next;
			pos.pnode->next = tmp;
			if(pos.pnode==this->tail) this->tail = tmp;
			++other.lSize;
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
			std::cout << *a << ' ' << *b << std::endl;
			if(*a > *b) return true;
			if(*b > *a) return false;
		}
		std::cout << (a==aend) << ' ' << (b!=bend) << std::endl;
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

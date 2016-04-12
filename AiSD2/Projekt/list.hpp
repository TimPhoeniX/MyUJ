/**
 * 
 */

#ifndef CTL_FORWARDLIST_HPP
#define CTL_FORWARDLIST_HPP

#include<memory>
#include<iterator>
#include<iostream>
#include<stdexcept>

namespace uj
{
	class list;
	class citer;
	class iter;
	
	class lnode
	{
		lnode() = default;
		lnode(lnode* n): next(n){};
		lnode next* = nullptr;
		void null()
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
	}
	
	template<typename T>
	class citer
	{
	public:
		using value_type = T;
		using pointer = const value_type*;
		using reference = const value_type&;
		using difference_type = long;
		using iterator_category = std::forward_iterator_tag;
		
	protected:
		lnode* pnode = nullptr;
		
	public:
		citer() = default;
		citer(lnode* p): pnode(p){}
		citer(const citer<T>& i) = default;
		citer(citer<T>&& i) = default;
		
		citer<T>& operator=(const citer<T>& x)
		{
			if(this == &x) return;
			this->pnode=x.pnode;
			return *this;
		}
		
		citer<T>& operator=(citer<T>&& x)
		{
			if(this == &x) return;
			this->pnode=x.pnode;
			return *this;
		}

		reference operator*() const noexcept
		{
			return reinterpret_cast<typenode<T>*>(lnode)->value;
		}
		
		pointer operator->() const noexcept
		{
			return &reinterpret_cast<typenode<T>*>(lnode)->value;
		}
		
		citer<T>& operator++() noexcept
		{
			this->pnode=this->pnode->next;
			return *this;
		}
		
		citer<T> operator++(int) noexcept
		{
			citer<T> tmp(*this);
			this->pnode=this->pnode->next;
			return tmp;
		}
		
		bool operator==(const citer<T>& x) const noexcept
		{
			return this->pnode == x.pnode;
		}
		
		bool operator!=(const citer<T>& x) const noexcept
		{
			return this->pnode != x.pnode;
		}
		
		citer<T> next()
		{
			if(this->pnode)
				return citer<T>(this->pnode->next);
			else
				return citer<T>(nullptr);
		}
	};
	
	template<typename T>
	inline bool operator==(const ForwardListIterator<T>& a, const ForwardListIterator<T>& b) noexcept
	{
		return a.pnode==b.pnode;
	}
	
	template<typename T>
	inline bool operator!=(const ForwardListIterator<T>& a, const ForwardListIterator<T>& b) noexcept
	{
		return a.pnode!=b.pnode;
	}
	
	
	
	template<typename T>
	class ForwardListIterator
	{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::forward_iterator_tag iteratorCategory;
		typedef ForwardListIterator<T> Self;
		typedef ForwardListNode<T> TypeNode;
		
		TypeNode* Node = nullptr;
		
		ForwardListIterator()
		{
		}
		
		ForwardListIterator(TypeNode* p)
		: Node(p)
		{
		}
		
		ForwardListIterator(const Self& x)
		: Node(x.pnode)
		{
		}
		
		Self& operator=(const Self& x) 
		{
			this->pnode=x.pnode;
			return *this;
		}
		
		reference operator*() const noexcept
		{
			return *reinterpret_cast<value_type*>(&(this->pnode->data));
		}
		
		pointer operator->() const noexcept
		{
			return reinterpret_cast<value_type*>(&(this->pnode->data));
		}
		
		Self& operator++() noexcept
		{
			this->pnode=this->pnode->next;
			return *this;
		}
		
		Self operator++(int) noexcept
		{
			Self tmp(*this);
			this->pnode=this->pnode->next;
			return tmp;
		}
		
		bool operator==(const Self& x) const noexcept
		{
			return this->pnode == x.pnode;
		}
		
		bool operator!=(const Self& x) const noexcept
		{
			return this->pnode != x.pnode;
		}
		
		Self next()
		{
			if(this->pnode)
				return Self(this->pnode->next);
			else
				return Self(nullptr);
		}
	};
	
	
	template<typename T>
	class ForwardList
	{
	public:
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t SizeType;
		typedef ForwardListIterator<value_type> iterator;
		typedef ForwardListIterator<value_type> const_iterator;
		
	private:
		typedef ForwardListNode<value_type> Node;
		typedef typename std::allocator<value_type>::template rebind<value_type>::other TypeAllocator;
		typedef typename std::allocator<value_type>::template rebind<Node>::other NodeAllocator;
		
		Node* Head = nullptr;
		Node* Tail = nullptr;
		SizeType Size = 0;
		TypeAllocator TAlloc = TypeAllocator();
		NodeAllocator NAlloc = NodeAllocator();
		
		Node* GetNode()
		{
			auto tmp = this->NAlloc.allocate(1);
			return std::addressof(*tmp);
		}
		
		template<typename... Args>
		Node* MakeNode(Args&&... args)
		{
			Node* tmp = this->GetNode();
			::new (reinterpret_cast<void*>(tmp)) Node;
			this->TAlloc.construct(reinterpret_cast<value_type*>(&(tmp->data)),std::forward<Args>(args)...);
			return tmp;
		}
		
		void FreeNode(Node* n)
		{
			this->NAlloc.deallocate(n,1);
		}
		
		Node* EraseAfter(Node* pos)
		{
			auto tmp = pos->next;
			if(tmp==this->Tail) this->Tail=pos;
			pos->next=tmp->next;
			this->TAlloc.destroy(reinterpret_cast<value_type*>(&tmp->data));
			tmp->~Node();
			this->FreeNode(tmp);
			--this->Size;
			return pos->next;
		}
		
	public:
		ForwardList()
		{
		}
		
		ForwardList(ForwardList<value_type>&& f)
		: Head(f.Head), Tail(f.Tail), Size(f.Size)
		{
			f.Head = nullptr;
			f.Tail = nullptr;
			f.Size = 0;
		}
		
		~ForwardList()
		{
			this->Clear();
		}
		
		SizeType GetSize() const
		{
			return this->Size;
		}
		
		bool Empty() const
		{
			return this->Size == 0;
		}
		
		reference Front()
		{
			if(this->Size == 0) throw std::out_of_range("Front called on empty list");
			return *reinterpret_cast<value_type*>(&this->Head->data);
		}
		
		iterator begin()
		{
			return iterator(Head);
		}
		
		iterator end()
		{
			return iterator(nullptr);
		}
		
		const_iterator begin() const
		{
			return const_iterator(Head);
		}
		
		const_iterator end() const
		{
			return const_iterator(nullptr);
		}
		
		const_iterator cbegin()
		{
			return const_iterator(Head);
		}
		
		const_iterator cend()
		{
			return const_iterator(nullptr);
		}
		
		value_type PopFront()
		{
			if(this->Size == 0) throw std::out_of_range("PopFront called on empty list");
			auto tmp = this->Head;
			if(tmp==this->Tail) this->Tail=nullptr;
			auto val = reinterpret_cast<value_type&&>(tmp->data);
			this->Head=tmp->next;
			--this->Size;
			this->TAlloc.destroy(&tmp->data);
			tmp->~Node();
			this->FreeNode(tmp);
			return val;
		}
		
		value_type PopBack()
		{
			if(this->Size == 0) throw std::out_of_range("PopBack called on empty list");
			if(Head!=Tail)
			{
				auto val = reinterpret_cast<value_type&&>(this->Tail->data);
				auto i = this->begin();
				while(i.next() != Tail) ++i;
				this->EraseAfter(i.pnode);
				return val;
			}
			else
			{
				return this->PopFront();
			}
		}
		
		void PushFront(const value_type& e)
		{
			auto tmp = this->MakeNode(e);
			tmp->next = this->Head;
			this->Head=tmp;
			++this->Size;
			if(this->Tail == nullptr) this->Tail = this->Head;
		}
		
		void PushBack(const value_type& e)
		{
			if(this->Tail==nullptr) return this->PushFront(e);
			auto tmp = this->MakeNode(e);
			this->Tail->next=tmp;
			this->Tail=tmp;
			++this->Size;
		}
		
		//Ugly, but will do for now.
		void Clear()
		{
			if(this->Size == 0) return;
			while(this->Head != this->Tail)
			{
				this->EraseAfter(this->Head);
			}
			this->PopFront();
		}
		
		void Insert(SizeType i, const value_type& e)
		{
			if(i==0) return this->PushFront(e);
			else if(i==this->Size) return this->PushBack(e);
			else if(i > this->Size) return;
			else
			{
				auto it = this->begin();
				while(--i) ++it;
				auto tmp = this->MakeNode(e);
				tmp->next = it.pnode->next;
				it.pnode->next = tmp;
				++this->Size;
			}
		}
		
		reference Get(SizeType i)
		{
			if(i >= this->Size) throw std::out_of_range("Get called with i >= Size");
			auto tmp = this->begin();
			while(i--) ++tmp;
			return *tmp;
		}
		
		const_reference Get(SizeType i) const 
		{
			if(i >= this->Size) throw std::out_of_range("Get called with i >= Size");
			auto tmp = this->begin();
			while(i--) ++tmp;
			return *tmp;
		}
		
		iterator Find(const value_type& e)
		{
			for(auto tmp = this->begin(); tmp != this->end(); ++tmp)
			{
				if(*tmp == e) return tmp;
			}
			return iterator(nullptr);
		}
		
		const_iterator Find(const value_type& e) const
		{
			for(auto tmp = this->begin(); tmp != this->end(); ++tmp)
			{
				if(*tmp == e) return tmp;
			}
			return const_iterator(nullptr);
		}
		
		void Erase(SizeType i)
		{
			if(i == 0)
			{
				this->PopFront();
			}
			else if(i == this->Size-1)
			{
				this->PopBack();
			}
			else if(i >= this->Size)
			{
			}
			else 
			{
				auto it = this->begin();
				while(--i) ++it;
				this->EraseAfter(it.pnode);
			}
		}

		void Erase(const value_type& e)
		{
			auto it = this->Head;
			int i = 0;
			while(this->Head != nullptr && it->getData() != e)
			{
				it = it->next;
				++i;
			}
			this->Erase(i);
		}
		
		void Print(std::ostream& out = std::cout) const
		{
			auto i = this->begin();
			while(i!=this->end())
			{
				out << *(i++) << ' ';
			}
		}
		
		friend std::ostream& operator<<(std::ostream& out, const CTL::ForwardList<value_type>& L)
		{
			L.Print(out);
			return out;
		}
	};
}

#endif
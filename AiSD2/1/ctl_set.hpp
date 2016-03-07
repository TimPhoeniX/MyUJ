/**
 * Conceptual Template Library
 * Abstract Set by Piotr Grudzien
 */
#ifndef _CTL_SET_HPP_
#define _CTL_SET_HPP_

#include <set>
#include <iostream>

// namespace CTL
// {
	template<typename T>
	class AbstractSet
	{
	public:		
		virtual ~AbstractSet()
		{
		}
		
		virtual AbstractSet<T>* Sum(AbstractSet<T>* other) = 0;
		virtual AbstractSet<T>* Difference(AbstractSet<T>* other) = 0;
		virtual AbstractSet<T>* Intersection(AbstractSet<T>* other) = 0;
		virtual bool Insert(const T& val) = 0;
		virtual bool Delete(const T& val) = 0;
		virtual bool IsMember(const T& val) = 0;
		virtual void Print() = 0;
	};
	
	template<typename T>
	class Set: public AbstractSet<T>
	{
	private:
		std::set<T> Impl;
	public:
		Set()
		{
		}
		
		Set(const Set<T>& other): Impl(Set<T>(other).Impl)
		{
		}
		
		virtual AbstractSet<T>* Sum(AbstractSet<T>* other) override
		{
			AbstractSet<T>* ret = new Set(*this);
			for(auto& it: ((Set<T>*)other)->Impl)
			{
				ret->Insert(it);
			}
			return ret;
		}
			
		virtual AbstractSet<T>* Difference(AbstractSet<T>* other) override
		{
			AbstractSet<T>* ret = new Set(*this);
			for(auto& it: ((Set<T>*)other)->Impl)
			{
				ret->Delete(it);
			}
			return ret;
		}
		virtual AbstractSet<T>* Intersection(AbstractSet<T>* other) override
		{
			AbstractSet<T>* ret = new Set(*this);
			for(auto& it: ((Set<T>*)other)->Impl)
			{
				if(!other->IsMember(it))
				{
					ret->Delete(it);
				}
			}
			return ret;
		}
		
		virtual bool Insert(const T& val)
		{
			return (this->Impl.insert(val)).second;
		}
		
		virtual bool Delete(const T& val)
		{
			return this->Impl.erase(val)!=0;
		}
			
		virtual bool IsMember(const T& val)
		{
			return this->Impl.find(val)!=this->Impl.end();
		}
		
		virtual void Print()
		{
			for(auto& it: this->Impl)
			{
				std::cout << it << ' ';
			}
			std::cout << std::endl;
		}
	};
// }
#endif
#include <cppunit/TestResult.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TextOutputter.h>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>
#include "uj_list.hpp"

class Constructors : public CppUnit::TestFixture
{
public:
	void def()
	{
		uj::list<int> list;
		CPPUNIT_ASSERT(list.empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), list.size());
	}

	void empty_copy()
	{
		uj::list<int> lista;
		uj::list<int> listb(lista);
		CPPUNIT_ASSERT(lista == listb);
		CPPUNIT_ASSERT(listb.empty());
		CPPUNIT_ASSERT(lista.empty());
		CPPUNIT_ASSERT_EQUAL(lista.size(), listb.size());
	}

	void element_copy()
	{
		int tab[5]{ 0,1,2,3,4 };
		uj::list<int> lista(tab,tab+5);
		uj::list<int> listb(lista);
		CPPUNIT_ASSERT(lista == listb);
		CPPUNIT_ASSERT(!listb.empty());
		CPPUNIT_ASSERT(!lista.empty());
		CPPUNIT_ASSERT_EQUAL(lista.size(), listb.size());
	}

	void range()
	{
		int tab[5]{ 0,1,2,3,4 };
		uj::list<int> list(tab, tab + 5);
		CPPUNIT_ASSERT(!list.empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), list.size());
	}

	void count()
	{
		uj::list<int> lia(5u);
		CPPUNIT_ASSERT(!lia.empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), lia.size());
		for(auto& it : lia)
		{
			CPPUNIT_ASSERT_EQUAL(it, int());
		}

		uj::list<int> lib(6u, 6);
		CPPUNIT_ASSERT(!lib.empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(6), lib.size());
		for(auto& it : lib)
		{
			CPPUNIT_ASSERT_EQUAL(it, 6);
		}

		uj::list<int> lic(0u, 0);
		CPPUNIT_ASSERT(lic.empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), lic.size());
		for(auto& it : lic)
		{
			CPPUNIT_ASSERT_EQUAL(it, 0);
		}
	}
};

class Alloc : public CppUnit::TestCase
{
public:
	void runTest() override
	{
		uj::list<int> l;
		CPPUNIT_ASSERT_NO_THROW(l.get_allocator());
	}
};

class ListTest : public CppUnit::TestFixture
{
protected:
	uj::list<int>* l = nullptr;

public:
	void setUp() override
	{
		this->l = new uj::list<int>();
	}

	void tearDown() override
	{
		delete this->l;
	}
};

class Assign : public ListTest
{
private:
	int array[10]{ 0,1,2,3,4,5,6,7,8,9 };

public:
	void count()
	{
		l->assign(5u, 5);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(5, it);
		}

		l->assign(0u, 0);
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void range()
	{
		l->assign(array, array + 10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}

		l->assign(array, array);
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void oper()
	{
		uj::list<int> o(this->array, this->array + 10);
		l->operator=(o);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(o.size(), l->size());
		CPPUNIT_ASSERT(o == *l);

		o.clear();
		l->operator=(o);
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(o.size(), l->size());
		CPPUNIT_ASSERT(o == *l);

	}
};

class Accessors : public ListTest
{
public:
	void empty()
	{
		CPPUNIT_ASSERT(l->empty());
		l->push_back(5);
		CPPUNIT_ASSERT(!l->empty());
	}

	void one()
	{
		l->assign(1u, 1);
		CPPUNIT_ASSERT_EQUAL(1, l->front());
		CPPUNIT_ASSERT_EQUAL(1, l->back());
		CPPUNIT_ASSERT_EQUAL(l->front(), l->back());
	}

	void two()
	{
		int array[]{ 1,2 };
		l->assign(array, array + 2);
		CPPUNIT_ASSERT_EQUAL(1, l->front());
		CPPUNIT_ASSERT_EQUAL(2, l->back());
	}
};

class Iterators : public ListTest
{
public:
	void empty()
	{
		uj::list<int>::iterator a = l->begin();
		uj::list<int>::iterator b = l->end();
		CPPUNIT_ASSERT(a == b);
	}

	void iterating()
	{
		int array[]{ 0,1,2,3,4,5,6,7,8,9 };
		l->assign(array, array + 10);
		int* arr = array;
		for(auto b = l->begin(), e = l->end(); b != e; ++b)
		{
			CPPUNIT_ASSERT_EQUAL(*(arr++), *b);
		}
	}

	void const_iterating()
	{
		int array[]{ 0,1,2,3,4,5,6,7,8,9 };
		l->assign(array, array + 10);
		int* arr = array;
		auto cl = const_cast<const uj::list<int>*>(l);
		for(auto b = cl->begin(), e = cl->end(); b != e; ++b)
		{
			CPPUNIT_ASSERT_EQUAL(*(arr++), *b);
		}
	}
};

class Capacity : public ListTest
{
public:
	void empty()
	{
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void max()
	{
		CPPUNIT_ASSERT_EQUAL(std::numeric_limits<uj::list<int>::size_type>::max(), l->max_size());
	}

	void elems()
	{
		int array[]{ 0,1,2,3,4,5,6,7,8,9 };
		l->assign(array, array + 10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
	}
};

class Modifiers : public ListTest
{
	int array[10]{ 0,1,2,3,4,5,6,7,8,9 };
	int inserts[9]{ 5,7,7,5,7,7,7,7,5 };
public:
	void clear()
	{
		l->assign(array, array + 10);
		l->clear();
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
		for(auto it : *l)
		{
			CPPUNIT_FAIL("Should not iterate");
			if(it) return; //Just to remove warnings
		}
	}

	void insert_e()
	{
		l->insert(l->begin(), 6u, 7);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(6), l->size());
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(7, it);
		}
	}

	void insert_m()
	{
		l->assign(array, array + 10);
		auto third = l->begin();
		++++third;
		auto inserted = l->insert(third, 5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);
	}

	void insert_f()
	{
		l->assign(array, array + 10);
		auto inserted = l->insert(l->begin(), 5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);
		CPPUNIT_ASSERT_EQUAL(5, l->front());
	}

	void insert_b()
	{
		l->assign(array, array + 10);
		auto inserted = l->insert(l->end(), 5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);
		CPPUNIT_ASSERT_EQUAL(5, l->back());
	}
	
	void insert_r()
	{
		l->insert(l->begin(), array, array+10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase_f()
	{
		l->assign(array, array + 10);
		l->erase(l->begin());
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = array + 1;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase_m()
	{
		l->assign(array, array + 10);
		l->erase(std::find(l->begin(), l->end(), 5));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		CPPUNIT_ASSERT((std::find(l->begin(), l->end(), 5) == l->end()));
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (*t == 5) ++t;
		}
	}

	void erase_b()
	{
		l->assign(array, array + 10);
		l->erase(std::find(l->begin(), l->end(), 9));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase_5f()
	{
		l->assign(array, array + 10);
		l->erase(l->begin(), std::find(l->begin(), l->end(), 5));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = array + 5;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase_5b()
	{
		l->assign(array, array + 10);
		l->erase(std::find(l->begin(), l->end(), 5), l->end());
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase_5m()
	{
		l->assign(array, array + 10);
		l->erase(std::find(l->begin(),l->end(),3),std::find(l->begin(),l->end(),8));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if(*t==3) t+=5;
		}
	}

	void push_back_e()
	{
		l->push_back(99);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(1), l->size());
		CPPUNIT_ASSERT_EQUAL(99, l->front());
		CPPUNIT_ASSERT_EQUAL(99, l->back());
	}

	void push_back_n()
	{
		l->assign(array, array + 10);
		l->push_back(99);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(99, l->back());
		int* t = array;
		for (auto& it : *l)
		{
			if (it == 99) return;
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void pop_back_1()
	{
		l->push_back(99);
		l->pop_back();
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void pop_back_m()
	{
		l->assign(array, array + 10);
		l->pop_back();
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		CPPUNIT_ASSERT_EQUAL(8, l->back());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void push_front_e()
	{
		l->push_front(99);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(1), l->size());
		CPPUNIT_ASSERT_EQUAL(99, l->front());
		CPPUNIT_ASSERT_EQUAL(99, l->back());
	}

	void push_front_n()
	{
		l->assign(array, array + 10);
		l->push_front(99);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(99, l->front());
		int* t = new int(99);
		for (auto& it : *l)
		{
			if (*t == 99)
			{
				CPPUNIT_ASSERT_EQUAL(*t, it);
				delete t; t = array;
			}
			else CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void pop_front_1()
	{
		l->push_back(99);
		l->pop_front();
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void pop_front_m()
	{
		l->assign(array, array + 10);
		l->pop_front();
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		CPPUNIT_ASSERT_EQUAL(1, l->front());
		int* t = array+1;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void resize_less()
	{
		l->assign(array, array + 10);
		l->resize(5);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void resize_eq()
	{
		l->assign(array, array + 10);
		l->resize(10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void resize_more()
	{
		l->assign(array, array + 10);
		l->resize(15,72);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(15), l->size());
		int* t = array;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == array + 10) t = new int[5]{ 72,72,72,72,72 };
		}
		t -= 5;
		delete[] t;
	}

	void swap_m()
	{
		uj::list<int> a(array, array + 10);
		uj::list<int> b(inserts, inserts + 5);
		l->operator=(a);
		uj::list<int> s(b);

		l->swap(s);

		CPPUNIT_ASSERT((*l == b));
		CPPUNIT_ASSERT((s == a));
	}

	void swap_f()
	{
		uj::list<int> a(array, array + 10);
		uj::list<int> b(inserts, inserts + 5);
		l->operator=(a);
		uj::list<int> s(b);

		swap(*l,s);

		CPPUNIT_ASSERT((*l == b));
		CPPUNIT_ASSERT((s == a));
	}
};

class Operations : public ListTest
{
	uj::list<int>* m = nullptr;

	int arra[10]{ 0,1,2,3,4,5,6,7,8,9 };
	int arrb[10]{ 5,6,7,8,9,10,11,12,13,14 };
	int mergd[20]{ 0,1,2,3,4,5,5,6,6,7,7,8,8,9,9,10,11,12,13,14 };

public:
	void setUp()
	{
		this->ListTest::setUp();
		m = new uj::list<int>();
	}

	void tearDown()
	{
		this->ListTest::tearDown();
		delete m;
	}

	void merge_a12()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->merge(*m);
		
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = mergd;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void merge_a21()
	{
		l->assign(arrb, arrb + 10);
		m->assign(arra, arra + 10);

		l->merge(*m);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = mergd;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void merge_d12()
	{
		std::greater<int> g;
		std::sort(arra, arra + 10,g);
		std::sort(arrb, arrb + 10,g);
		std::sort(mergd, mergd + 20,g);
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->merge(*m,g);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = mergd;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		std::sort(arra, arra + 10);
		std::sort(arrb, arrb + 10);
		std::sort(mergd, mergd + 20);
	}
	void merge_d21()
	{
		std::greater<int> g;
		std::sort(arrb, arrb + 10, g);
		std::sort(arra, arra + 10, g);
		std::sort(mergd, mergd + 20, g);
		l->assign(arrb, arrb + 10);
		m->assign(arra, arra + 10);

		l->merge(*m, g);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = mergd;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		std::sort(arra, arra + 10);
		std::sort(arrb, arrb + 10);
		std::sort(mergd, mergd + 20);
	}

	void splice_f()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(l->begin(),*m);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = arrb;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arrb + 10) t = arra;
		}
	}

	void splice_m()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(std::find(l->begin(),l->end(),4), *m);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arra + 4) t = arrb;
			else if(t == arrb + 10) t = arra + 4;
		}
	}

	void splice_b()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(l->end(), *m);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(20), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), m->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arra + 10) t = arrb;
		}
	}

	void splice_1f()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(l->begin(), *m, std::find(m->begin(), m->end(), 11));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(!m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), m->size());
		int* t = arrb+6;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arrb + 7) t = arra;
		}
	}

	void splice_1m()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(std::find(l->begin(), l->end(), 2), *m, std::find(m->begin(), m->end(), 11));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(!m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), m->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arra + 2) t = arrb+6;
			else if(t == arrb + 7) t = arra+2;
		}
	}

	void splice_1b()
	{
		l->assign(arra, arra + 10);
		m->assign(arrb, arrb + 10);

		l->splice(l->end(), *m, std::find(m->begin(), m->end(), 11));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT(!m->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(11), l->size());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), m->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (t == arra + 10) t = arrb + 6;
		}
	}

	void splice_if()
	{
		l->assign(arra, arra + 10);
		
		l->splice(l->begin(), *l, std::find(l->begin(), l->end(), 7));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* temp = new int[10]{ 7,0,1,2,3,4,5,6,8,9 }, *t = temp;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		delete[] temp;
	}

	void splice_ib()
	{
		l->assign(arra, arra + 10);

		l->splice(l->end(), *l, std::find(l->begin(), l->end(), 6));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* temp = new int[10]{ 0,1,2,3,4,5,7,8,9,6 }, *t = temp;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		delete[] temp;
	}

	void splice_ff()
	{
		l->assign(arra, arra + 10);

		l->splice(std::find(l->begin(), l->end(), 3), *l,l->begin());

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* temp = new int[10]{ 1,2,0,3,4,5,6,7,8,9 }, *t = temp;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		delete[] temp;
	}

	void splice_fb()
	{
		l->assign(arra, arra + 10);

		l->splice(std::find(l->begin(), l->end(), 5), *l, std::find(l->begin(), l->end(), 9));

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* temp = new int[10]{ 0,1,2,3,4,9,5,6,7,8 }, *t = temp;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		delete[] temp;
	}

	void remove_f()
	{
		l->assign(arra, arra + 10);
		l->remove(0);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = arra+1;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void remove_m()
	{
		l->assign(arra, arra + 10);
		l->remove(5);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
			if (*t == 5) ++t;
		}
	}

	void remove_b()
	{
		l->assign(arra, arra + 10);
		l->remove(9);

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void remove_if_odd()
	{
		l->assign(arra, arra + 10);
		l->remove_if([](int a)->bool {return (a%2)==1; });

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			if ((*t)%2==1) ++t;
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void remove_if_even()
	{
		l->assign(arra, arra + 10);
		l->remove_if([](int a)->bool {return !(a % 2); });

		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			if ((*t) % 2 == 0) ++t;
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void reverse_s()
	{
		l->assign(arra,arra+10);
		std::sort(arra,arra+10,std::greater<int>());
		l->reverse();
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		std::sort(arra,arra+10);
	}

	void reverse_u()
	{
		std::random_shuffle(arra,arra+10);
		l->assign(arra,arra+10);
		l->reverse();
		std::reverse(arra,arra+10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		std::sort(arra,arra+10);
	}
	
	void unique()
	{
		int duplicates[] {1,2,2,2,1,4,5,4,6,6,6};
		int after[] {1,2,1,4,5,4,6};
		l->assign(duplicates,duplicates+10);
		l->unique();
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(7), l->size());
		int* t = after;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}
	
	void unique_p()
	{
		l->assign(arra,arra+10);
		l->unique(std::less<int>());
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(1), l->size());
		int* t = arra;
		for (auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void sort()
	{
		std::random_shuffle(arra, arra + 10);
		l->assign(arra, arra + 10);
		std::sort(arra, arra + 10);
		l->sort();
		CPPUNIT_ASSERT(std::is_sorted(l->begin(), l->end()));
	}

	void sort_p()
	{
		std::random_shuffle(arra, arra + 10);
		l->assign(arra, arra + 10);
		std::sort(arra, arra + 10);
		l->sort(std::greater<int>());
		CPPUNIT_ASSERT(std::is_sorted(l->begin(), l->end(), std::greater<int>()));
	}
};

class Comparators : public ListTest
{
	uj::list<int>* t = nullptr;
	int arr1[5]{ 0,1,2,3,4 };
	int arr2[5]{ 3,4,5,6,7 };
public:
	void setUp() override
	{
		this->ListTest::setUp();
		t = new uj::list<int>();
	}

	void tearDown() override
	{
		this->ListTest::tearDown();
		delete t;
	}

	void eq()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT((*l == *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT(!(*l == *t));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT(!(*l == *t));
	}

	void uneq()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT(!(*l != *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT((*l != *t));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT((*l != *t));
	}

	void less()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT(!(*l < *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT((*l < *t));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT((*t < *l));
	}

	void less_eq()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT((*l <= *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT((*l <= *t));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT((*t <= *l));
	}

	void greater()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT(!(*l > *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT((*t > *l));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT((*l > *t));
	}

	void greater_eq()
	{
		l->assign(arr1, arr1 + 5);
		t->assign(arr1, arr1 + 5);
		CPPUNIT_ASSERT((*l >= *t));
		t->assign(arr2, arr2 + 5);
		CPPUNIT_ASSERT((*t >= *l));
		t->assign(arr1, arr1 + 4);
		CPPUNIT_ASSERT((*l >= *t));
	}

};

int main()
{
	CppUnit::TextTestRunner runner;
	runner.setOutputter(new CppUnit::TextOutputter(&runner.result(), std::cout));
	
	CppUnit::TestSuite* constructors = new CppUnit::TestSuite("Constructor tests");
	constructors->addTest(new CppUnit::TestCaller<Constructors>("Default Constructor", &Constructors::def));
	constructors->addTest(new CppUnit::TestCaller<Constructors>("Copy Constructor on empty", &Constructors::empty_copy));
	constructors->addTest(new CppUnit::TestCaller<Constructors>("Copy Constructor with elements", &Constructors::element_copy));
	constructors->addTest(new CppUnit::TestCaller<Constructors>("Range Constructor", &Constructors::range));
	constructors->addTest(new CppUnit::TestCaller<Constructors>("Count Constructor", &Constructors::count));

	CppUnit::TestSuite* assign = new CppUnit::TestSuite("Assignment tests");
	assign->addTest(new CppUnit::TestCaller<Assign>("Count assignment", &Assign::count));
	assign->addTest(new CppUnit::TestCaller<Assign>("Range assignment", &Assign::range));
	assign->addTest(new CppUnit::TestCaller<Assign>("Operator assignment", &Assign::oper));

	CppUnit::TestSuite* accessors = new CppUnit::TestSuite("Accessors tests");
	accessors->addTest(new CppUnit::TestCaller<Accessors>("Empty access", &Accessors::empty));
	accessors->addTest(new CppUnit::TestCaller<Accessors>("Single element access", &Accessors::one));
	accessors->addTest(new CppUnit::TestCaller<Accessors>("More element access", &Accessors::two));

	CppUnit::TestSuite* iterators = new CppUnit::TestSuite("Iterators tests");
	iterators->addTest(new CppUnit::TestCaller<Iterators>("Empty list iterators", &Iterators::empty));
	iterators->addTest(new CppUnit::TestCaller<Iterators>("Iterating over list", &Iterators::iterating));
	iterators->addTest(new CppUnit::TestCaller<Iterators>("Iterating over const list", &Iterators::const_iterating));

	CppUnit::TestSuite* capacity = new CppUnit::TestSuite("Capacity tests");
	capacity->addTest(new CppUnit::TestCaller<Capacity>("Empty", &Capacity::empty));
	capacity->addTest(new CppUnit::TestCaller<Capacity>("Max Size", &Capacity::max));
	capacity->addTest(new CppUnit::TestCaller<Capacity>("With elements", &Capacity::elems));

	CppUnit::TestSuite* modifiers = new CppUnit::TestSuite("Modifying tests");
	modifiers->addTest(new CppUnit::TestCaller<Modifiers>("Clear", &Modifiers::clear));

	CppUnit::TestSuite* insert = new CppUnit::TestSuite("Insert");
	insert->addTest(new CppUnit::TestCaller<Modifiers>("Insert to empty", &Modifiers::insert_e));
	insert->addTest(new CppUnit::TestCaller<Modifiers>("Insert at front", &Modifiers::insert_f));
	insert->addTest(new CppUnit::TestCaller<Modifiers>("Insert at middle", &Modifiers::insert_m));
	insert->addTest(new CppUnit::TestCaller<Modifiers>("Insert at back", &Modifiers::insert_b));
	insert->addTest(new CppUnit::TestCaller<Modifiers>("Insert range", &Modifiers::insert_r));
	modifiers->addTest(insert);

	CppUnit::TestSuite* erase = new CppUnit::TestSuite("Erase");
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase front", &Modifiers::erase_f));
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase middle", &Modifiers::erase_m));
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase back", &Modifiers::erase_b));
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase many from front", &Modifiers::erase_5f));
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase many from middle", &Modifiers::erase_5m));
	erase->addTest(new CppUnit::TestCaller<Modifiers>("Erase many from back", &Modifiers::erase_5b));
	modifiers->addTest(erase);

	CppUnit::TestSuite* push_back = new CppUnit::TestSuite("Push_back");
	push_back->addTest(new CppUnit::TestCaller<Modifiers>("Push_back on empty", &Modifiers::push_back_e));
	push_back->addTest(new CppUnit::TestCaller<Modifiers>("Push_back on non-empty", &Modifiers::push_back_n));
	modifiers->addTest(push_back);

	CppUnit::TestSuite* pop_back = new CppUnit::TestSuite("Pop_back");
	pop_back->addTest(new CppUnit::TestCaller<Modifiers>("Pop_back on 1 elements", &Modifiers::pop_back_1));
	pop_back->addTest(new CppUnit::TestCaller<Modifiers>("Pop_back on with many elements", &Modifiers::pop_back_m));
	modifiers->addTest(pop_back);

	CppUnit::TestSuite* push_front = new CppUnit::TestSuite("Push_front");
	push_front->addTest(new CppUnit::TestCaller<Modifiers>("Push_front on empty", &Modifiers::push_front_e));
	push_front->addTest(new CppUnit::TestCaller<Modifiers>("Push_front on non-empty", &Modifiers::push_front_n));
	modifiers->addTest(push_front);

	CppUnit::TestSuite* pop_front = new CppUnit::TestSuite("Pop_front");
	pop_front->addTest(new CppUnit::TestCaller<Modifiers>("Pop_front on 1 elements", &Modifiers::pop_front_1));
	pop_front->addTest(new CppUnit::TestCaller<Modifiers>("Pop_front on with many elements", &Modifiers::pop_front_m));
	modifiers->addTest(pop_front);

	CppUnit::TestSuite* resize = new CppUnit::TestSuite("Resize");
	resize->addTest(new CppUnit::TestCaller<Modifiers>("Resize with less", &Modifiers::resize_less));
	resize->addTest(new CppUnit::TestCaller<Modifiers>("Resize with equal", &Modifiers::resize_eq));
	resize->addTest(new CppUnit::TestCaller<Modifiers>("Resize with more", &Modifiers::resize_more));
	modifiers->addTest(resize);

	CppUnit::TestSuite* swap = new CppUnit::TestSuite("Swap");
	swap->addTest(new CppUnit::TestCaller<Modifiers>("Swap member function", &Modifiers::swap_m));
	swap->addTest(new CppUnit::TestCaller<Modifiers>("Swap free function", &Modifiers::swap_f));
	modifiers->addTest(swap);


	CppUnit::TestSuite* operations = new CppUnit::TestSuite("Operations tests");

	CppUnit::TestSuite* merge = new CppUnit::TestSuite("Merge");
	merge->addTest(new CppUnit::TestCaller<Operations>("Merge ascending order 1 to 2 ", &Operations::merge_a12));
	merge->addTest(new CppUnit::TestCaller<Operations>("Merge ascending order 2 to 1 ", &Operations::merge_a21));
	merge->addTest(new CppUnit::TestCaller<Operations>("Merge descending order 1 to 2 ", &Operations::merge_d12));
	merge->addTest(new CppUnit::TestCaller<Operations>("Merge descending order 2 to 1 ", &Operations::merge_d21));
	operations->addTest(merge);

	CppUnit::TestSuite* splice = new CppUnit::TestSuite("Splice");
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice all to front", &Operations::splice_f));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice all to middle", &Operations::splice_m));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice all to back", &Operations::splice_b));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 to front", &Operations::splice_1f));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 to middle", &Operations::splice_1m));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 to back", &Operations::splice_1b));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 inside to front", &Operations::splice_if));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 inside to back", &Operations::splice_ib));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 inside from front", &Operations::splice_ff));
	splice->addTest(new CppUnit::TestCaller<Operations>("Splice 1 inside from back", &Operations::splice_fb));
	operations->addTest(splice);

	CppUnit::TestSuite* remove = new CppUnit::TestSuite("Remove/_if");
	remove->addTest(new CppUnit::TestCaller<Operations>("Remove front", &Operations::remove_f));
	remove->addTest(new CppUnit::TestCaller<Operations>("Remove middle", &Operations::remove_m));
	remove->addTest(new CppUnit::TestCaller<Operations>("Remove back", &Operations::remove_b));
	remove->addTest(new CppUnit::TestCaller<Operations>("Remove_if odd", &Operations::remove_if_odd));
	remove->addTest(new CppUnit::TestCaller<Operations>("Remove_if even", &Operations::remove_if_even));
	operations->addTest(remove);

	CppUnit::TestSuite* reverse = new CppUnit::TestSuite("Reverse");
	remove->addTest(new CppUnit::TestCaller<Operations>("Reverse sorted", &Operations::reverse_s));
	remove->addTest(new CppUnit::TestCaller<Operations>("Reverse unsorted", &Operations::reverse_u));
	operations->addTest(reverse);

	CppUnit::TestSuite* unique = new CppUnit::TestSuite("Unique");
	unique->addTest(new CppUnit::TestCaller<Operations>("Unique value", &Operations::unique));
	unique->addTest(new CppUnit::TestCaller<Operations>("Unique predicate", &Operations::unique_p));
	operations->addTest(unique);

	CppUnit::TestSuite* sort = new CppUnit::TestSuite("Sort");
	sort->addTest(new CppUnit::TestCaller<Operations>("Sort", &Operations::sort));
	sort->addTest(new CppUnit::TestCaller<Operations>("Sort predicate", &Operations::sort_p));
	operations->addTest(sort);
	
	CppUnit::TestSuite* comparators = new CppUnit::TestSuite("comparators");
	comparators->addTest(new CppUnit::TestCaller<Comparators>("==", &Comparators::eq));
	comparators->addTest(new CppUnit::TestCaller<Comparators>("!=", &Comparators::uneq));
	comparators->addTest(new CppUnit::TestCaller<Comparators>("<", &Comparators::less));
	comparators->addTest(new CppUnit::TestCaller<Comparators>("<=", &Comparators::less_eq));
	comparators->addTest(new CppUnit::TestCaller<Comparators>(">", &Comparators::greater));
	comparators->addTest(new CppUnit::TestCaller<Comparators>(">=", &Comparators::greater_eq));


	runner.addTest(constructors);
	runner.addTest(new Alloc());
	runner.addTest(assign);
	runner.addTest(accessors);
	runner.addTest(iterators);
	runner.addTest(capacity);
	runner.addTest(modifiers);
	runner.addTest(operations);
	runner.addTest(comparators);

	runner.run("",true,true,false);
}

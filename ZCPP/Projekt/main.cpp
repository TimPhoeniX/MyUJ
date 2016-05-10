#include <cppunit/TestResult.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TextOutputter.h>
#include <algorithm>
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
		l->assing(5u, 5);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(5, it);
		}

		l->assing(0u, 0);
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
	}

	void range()
	{
		l->assing(array, array + 10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		int* t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}

		l->assing(array, array);
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
		//Weird, but ok.
		CPPUNIT_ASSERT_NO_THROW(l->front());
		CPPUNIT_ASSERT_NO_THROW(l->back());
	}

	void one()
	{
		l->assing(1u, 1);
		CPPUNIT_ASSERT_EQUAL(1, l->front());
		CPPUNIT_ASSERT_EQUAL(1, l->back());
		CPPUNIT_ASSERT_EQUAL(l->front(), l->back());
	}

	void two()
	{
		int array[]{ 1,2 };
		l->assing(array, array + 2);
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
		l->assing(array, array + 10);
		int* arr = array;
		for(auto b = l->begin(), e = l->end(); b != e; ++b)
		{
			CPPUNIT_ASSERT_EQUAL(*(arr++), *b);
		}
	}

	void const_iterating()
	{
		int array[]{ 0,1,2,3,4,5,6,7,8,9 };
		l->assing(array, array + 10);
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
		l->assing(array, array + 10);
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
		l->assing(array, array + 10);
		l->clear();
		CPPUNIT_ASSERT(l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(0), l->size());
		for(auto it : *l)
		{
			CPPUNIT_FAIL("Should not iterate");
			if(it) return; //Just to remove warnings
		}
	}

	void insert()
	{
		l->insert(l->begin(), 6u, 7);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(6), l->size());
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(7,it);
		}

		auto third = l->begin();
		++++third;
		auto inserted = l->insert(third,5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(7), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);

		inserted = l->insert(l->begin(), 5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(8), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);
		CPPUNIT_ASSERT_EQUAL(5, l->front());

		inserted = l->insert(l->end(), 5);
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		CPPUNIT_ASSERT_EQUAL(5, *inserted);
		CPPUNIT_ASSERT_EQUAL(5, l->back());

		int* t = inserts;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}

		l->clear();
		l->insert(l->begin(), array, array+10);
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(10), l->size());
		t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
	}

	void erase()
	{
		l->assing(array, array + 10);
		l->erase(l->begin());
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		int* t = array+1;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		
		l->assing(array, array + 10);
		l->erase(std::find(l->begin(),l->end(),5));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		CPPUNIT_ASSERT( (std::find(l->begin(),l->end(),5) == l->end()) );
		
		l->assing(array, array + 10);
		l->erase(std::find(l->begin(),l->end(),9));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(9), l->size());
		t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		
		l->assing(array, array + 10);
		l->erase(l->begin(),std::find(l->begin(),l->end(),5));
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		t = array+5;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
		
		l->assing(array, array + 10);
		l->erase(std::find(l->begin(),l->end(),5),l->end());
		CPPUNIT_ASSERT(!l->empty());
		CPPUNIT_ASSERT_EQUAL(uj::list<int>::size_type(5), l->size());
		t = array;
		for(auto& it : *l)
		{
			CPPUNIT_ASSERT_EQUAL(*(t++), it);
		}
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
	assign->addTest(new CppUnit::TestCaller<Accessors>("Empty access", &Accessors::empty));
	assign->addTest(new CppUnit::TestCaller<Accessors>("Single element access", &Accessors::one));
	assign->addTest(new CppUnit::TestCaller<Accessors>("More element access", &Accessors::two));

	CppUnit::TestSuite* iterators = new CppUnit::TestSuite("Iterators tests");
	assign->addTest(new CppUnit::TestCaller<Iterators>("Empty list iterators", &Iterators::empty));
	assign->addTest(new CppUnit::TestCaller<Iterators>("Iterating over list", &Iterators::iterating));
	assign->addTest(new CppUnit::TestCaller<Iterators>("Iterating over const list", &Iterators::const_iterating));

	CppUnit::TestSuite* capacity = new CppUnit::TestSuite("Capacity tests");
	assign->addTest(new CppUnit::TestCaller<Capacity>("Empty", &Capacity::empty));
	assign->addTest(new CppUnit::TestCaller<Capacity>("Max Size", &Capacity::max));
	assign->addTest(new CppUnit::TestCaller<Capacity>("With elements", &Capacity::elems));

	CppUnit::TestSuite* modifiers = new CppUnit::TestSuite("Modifying tests");
	assign->addTest(new CppUnit::TestCaller<Modifiers>("Clear", &Modifiers::clear));
	assign->addTest(new CppUnit::TestCaller<Modifiers>("Insert", &Modifiers::insert));
	assign->addTest(new CppUnit::TestCaller<Modifiers>("Erase", &Modifiers::erase));

	runner.addTest(constructors);
	runner.addTest(new Alloc());
	runner.addTest(assign);
	runner.addTest(accessors);
	runner.addTest(iterators);
	runner.addTest(capacity);
	runner.addTest(modifiers);

	runner.run("",true,true,false);
}
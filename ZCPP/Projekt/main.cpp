#include <cppunit/TestResult.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TextOutputter.h>
#include "uj_list.hpp"
#include <list>

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

class Empty : public CppUnit::TestCase
{
private:
	uj::list<int>* list = nullptr;
public:
	Empty() :TestCase("empty() test"){}

	void setUp() override
	{
		list = new uj::list<int>();
	}

	void tearDown() override
	{
		delete list;
	}

	void runTest() override
	{
		CPPUNIT_ASSERT(list->empty());
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

	runner.addTest(constructors);
	runner.addTest(new Alloc());

	runner.run("",true,true,false);
}
#ifndef _TEST_LIST_HPP_
#define _TEST_LIST_HPP_

#include <cassert>
#include <initializer_list>
#include <typeinfo>
#include <exception>

template<template<typename> class L, class T>
void IntegrityCheck(const L<T>& List, std::initializer_list<T> Contents)
{
	assert( List.GetSize() == Contents.size() );
	auto LiT = List.Begin();
	auto CiT = Contents.begin();
	while(CiT != Contents.end())
	{
		assert( *(LiT++) == *(CiT++) );
	}
}

template<template<typename> class L, class T>
void TestList()
{
	L<T> List;
	
	assert( List.Empty() == true );
	assert( List.GetSize() == 0 );
	
	IntegrityCheck(List, {});
	
	List.PushFront(1);
	List.PushBack(2);
	List.PushFront(3);
	List.PushBack(4);
	List.PushFront(5);
	List.PushBack(6);
	
	assert( List.Empty() == false );
	IntegrityCheck(List, {5,3,1,2,4,6} );
	
	assert( List.PopFront() == 5 );
	
	IntegrityCheck(List, {3,1,2,4,6});
	
	assert( List.PopBack() == 6 );
	
	IntegrityCheck(List, {3,1,2,4});
	
	//Method shall not fail nor modify contents on size limited(for now) ArrayList when inserting elements to full list
	//For compatibility with the rest of the list functionality shall not be tested here
	List.Insert(0lu,7);
	List.Insert(List.GetSize(),8);
	List.Insert(List.GetSize()/2lu,9);
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	//Find() returns iterator to first element equal to given arg, replaces expected index_of()
	assert( *List.Find(3) == 3 );
	assert( *List.Find(8) == 8 );
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	// index_of may be simulated by std::distance(), until apriopriate method is implemented
	assert( std::distance(List.Begin(), List.Find(9)) == 3 );
	
	assert( List.Get(5) == 4 );
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	//Find shall return End() when given element is not found
	assert( List.Find(999) == List.End() );
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	//Erase replaces expected remove(). Remove() is reserved for method removing each instance of given element;
	//Erase shall erase element of given index (starting from 0). Method shall not fail nor modify arrray when given index out of range
	List.Erase(100);
	List.Erase(-100);
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	//Get returns by reference, thus it shall throw when given index out of range;
	try
	{
		List.Get(100);
	}
	catch(std::exception& e)
	{
		assert( typeid(e) == typeid(std::out_of_range) );
	}
	
	try
	{
		List.Get(-100);
	}
	catch(std::exception& e)
	{
		assert( typeid(e) == typeid(std::out_of_range) );
	}
	
	IntegrityCheck(List, {7,3,1,9,2,4,8});
	
	std::cout << "Expected contents 1: 7 3 1 9 2 4 8 " << std::endl;
	std::cout << "  Actual contents 1: " << List <<std::endl;
	
	List.Clear();
	
	IntegrityCheck(List, {});
	
	//PopBack and PopFront returns an element by value, thus they shall throw when called on empty list.
	try
	{
		List.PopBack();
	}
	catch(std::exception& e)
	{
		assert( typeid(e) == typeid(std::out_of_range) );
	}
	
	try
	{
		List.PopFront();
	}
	catch(std::exception& e)
	{
		assert( typeid(e) == typeid(std::out_of_range) );
	}
	
	IntegrityCheck(List, {});
	
	return;
}

#endif
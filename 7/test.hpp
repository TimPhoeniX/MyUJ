#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <cassert>
#include <initializer_list>

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
	
	List.PushFront(1);
	List.PushBack(2);
	List.PushFront(3);
	List.PushBack(4);
	List.PushFront(5);
	List.PushBack(6);
	
	assert( List.Empty() == false );
	IntegrityCheck(List, {5,3,1,2,4,6} );
	
	return;
}

#endif
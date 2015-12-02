#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "ctl_proto_hashmap.hpp"
#include <cassert>
#include <iostream>

void AssertMap()
{
	CTL::UnorderedMapPrototype<int, double> m;
	
	assert( m.getMaxListLen()==0 );
	
	assert( m.Insert(1, 0.5) );
	
	assert( !m.Insert(1, 1.5) );
	
	assert( m.Find(1) == 0.5 );
	
	try
	{
		m.Find(5);
	}
	catch(std::out_of_range& e)
	{
	}
	
	assert( m.getMaxListLen()==1 );
	
	assert( m.getMedianListLen()==0 );
	
	m.Delete(1);
	
	assert( m.getMaxListLen()==0 );
	
	for(int i = 0; i < 10000; ++i)
	{
		assert( m.Insert(i,double(i)) );
	}
	
	//Since std::hash is implementation dependant making it impossible to assert a proper expression.
}

#endif
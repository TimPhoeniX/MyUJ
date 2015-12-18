#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "ctl_stack.hpp"
#include <cassert>

void AssertStack()
{
	CTL::Stack<int> S;
	assert( S.Empty() );
	assert( S.GetSize() == 0 );
	
	S.Push(5);
	assert( !S.Empty() );
	assert( S.GetSize() == 1 );
	assert( S.Top() == 5 );
	
	S.Push(3);
	assert( !S.Empty() );
	assert( S.GetSize() == 2 );
	assert( S.Top() == 3 );
	
	S.Push(1);
	assert( !S.Empty() );
	assert( S.GetSize() == 3 );
	assert( S.Top() == 1 );
	
	S.Push(-1);
	assert( !S.Empty() );
	assert( S.GetSize() == 4 );
	assert( S.Top() == -1 );
	
	assert( S.Pop() == -1 );
	assert( !S.Empty() );
	assert( S.GetSize() == 3 );
	assert( S.Top() == 1 );
	
	assert( S.Pop() == 1 );
	assert( !S.Empty() );
	assert( S.GetSize() == 2 );
	assert( S.Top() == 3 );
	
	assert( S.Pop() == 3 );
	assert( !S.Empty() );
	assert( S.GetSize() == 1 );
	assert( S.Top() == 5 );
	
	assert( S.Pop() == 5 );
	assert( S.Empty() );
	assert( S.GetSize() == 0 );
}

#endif
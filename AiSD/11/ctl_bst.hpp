/**
 * Conceptual Template Library by Piotr Grudzień
 * Binary Search Tree
 * TODO: Include allocator support
 */
#ifndef _CTL_BST_HPP_
#define _CTL_BST_HPP_

namespace CTL
{
	template<typename T>
	class BSTNode
	{
	public:
		using ValueType = T;
		
	private:
		ValueType Value;
		BSTNode* Left = nullptr;
		BDTNode* Right = nullptr;
		
	public:
		BSTNode(const ValueType& t)
		: Value(t)
		{
		}
		
		BSTNode(ValueType&& t)
		: Value(std::move(t))
		{
		}
		
		BSTNode(const BSTNode& n) //Copies node, shares subtrees with original
		: Value(n.Value), Left(n.Left), Right(n.Right)
		{
		}
		
		BSTNode(BSTNode&& n)
		: Value(std::move(n.Value)), Left(n.Left), Right(n.Right)
		{
			n.Right = nullptr;
			n.Left = nullptr;
		}
		
		~BSTNode()
		{
			delete this->Left;
			delete this->Right;
		}
		
		void Unhook()
		{
			this->Right = nullptr;
			this->Left = nullptr;
		}
	}
}

#endif _CTL_BST_HPP_
#ifndef _OCTREE_HPP_
#define _OCTREE_HPP_

#include<memory>
#include<list>
#include<iostream>
#include<initializer_list>

namespace Octree
{
	template<typename T>
	class OCTNode;
	template<typename T>
	class OCTREE;
	
	template<typename T> using ONodePtr=std::shared_ptr<class OCTNode<T>>;
	template<typename T> using ONodeParentPtr=std::weak_ptr<class OCTNode<T>>;
	template<typename T> using ONodeList=std::list<ONodePtr<T>>;
	template<typename T> using ONodeIt=typename ONodeList<T>::iterator;
	using u_int=unsigned int;
	using UIntInitList=std::initializer_list<u_int>;
	
	template<typename T>
	class OCTNode : public std::enable_shared_from_this<class OCTNode<T>>
	{
		friend class OCTREE<T>;
// 		class id_not_found : std::exception
// 		{
// 			const char* what() const noexcept;
// 		};
	private:
		u_int ID;
		T Value;
		char hasChildren=0;
		ONodeParentPtr<T> parentPtr;
		ONodeList<T> Children;
		
		OCTNode(u_int id,ONodePtr<T> parent);
		OCTNode(u_int id,ONodePtr<T> parent, T value);

		void printTree(u_int level) const;
		void printNode() const;

		ONodePtr<T> findID(u_int id);
		bool findIDIt(u_int id, ONodeIt<T>& iter);
		ONodePtr<T> addNode(u_int id);
		ONodePtr<T> addNode(u_int id, T value);
	public:
		~OCTNode();
	};

	template<typename T>
	class OCTREE
	{
	private:
		u_int ID_Counter=0;
		ONodePtr<T> Root;
	public:
		OCTREE();
		OCTREE(u_int nodes);
		OCTREE(UIntInitList nodes);
		OCTREE(u_int nodes, T value);
		OCTREE(UIntInitList nodes, T value);
		~OCTREE();

		ONodePtr<T> findID(u_int id) const;
		ONodePtr<T> addNode(u_int id);
		ONodePtr<T> addNode(u_int id, T value);
		void addNode(UIntInitList IDs);
		void addNode(UIntInitList IDs, T value);
		void addMore(u_int more);
		
		void removeNode(u_int id);
		void removeNode(UIntInitList to_remove);
		void print() const;
		void printNode(u_int id) const;
		
		T getVal(u_int id) const;
		T setVal(u_int id, T value);
	};
}

#endif
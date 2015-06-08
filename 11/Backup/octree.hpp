#ifndef _OCTREE_HPP_
#define _OCTREE_HPP_

#include<memory>
#include<list>
#include<iostream>
#include<initializer_list>

using ONodePtr=std::shared_ptr<class OCTNode>;
using ONodeParentPtr=std::weak_ptr<class OCTNode>;
using u_int=unsigned int;
using UIntInitList=std::initializer_list<u_int>;

class OCTree;

class OCTNode : public std::enable_shared_from_this<class OCTNode>
{
	friend class OCTree;
// 	class id_not_found : std::exception
// 	{
// 		const char* what() const noexcept;
// 	};
private:
	u_int ID;
	int Value;
	char hasChildren=0;
	ONodeParentPtr parentPtr;
	std::list<ONodePtr> Children;
	
	OCTNode(int id,ONodePtr parent,int val=0);

	void printTree(u_int level) const;
	void printNode() const;

	ONodePtr findID(u_int id);
	ONodePtr addNode(u_int ID,int val);
public:
	~OCTNode();
};

class OCTree
{
private:
	u_int ID_Counter=0;
	ONodePtr Root;
public:
	OCTree();
	OCTree(u_int nodes, int val=0);
	OCTree(UIntInitList nodes, int val=0);
	~OCTree();

	ONodePtr findID(u_int id) const;
	ONodePtr addNode(u_int ID, int val=0);
	void addNode(UIntInitList IDs, int val=0);
	void addMore(u_int more);
	
	void removeNode(u_int ID);
	void removeNode(UIntInitList to_remove);
	void print() const;
	void printNode(u_int ID) const;
	
	int getVal(int ID) const;
	int setVal(int ID, int val);
};

#endif
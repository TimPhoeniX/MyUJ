#include "octree.hpp"

// const char* OCTNode::id_not_found::what() const noexcept
// {
// 	return "Given ID not found";
// }

OCTNode::OCTNode(int id, ONodePtr parent, int val): ID(id), Value(val), parentPtr(parent) {}
OCTNode::~OCTNode()
{
// 	Children.clear();
//	std::cout << "Destroyed Node ID=" << ID << '\n';
}

ONodePtr OCTNode::findID(u_int id)
{
	ONodePtr tmp=nullptr;
	if(id==ID) tmp=shared_from_this();
	else
	{
		for(auto nd : Children)
		{
			tmp=nd->findID(id);
			if(tmp) break;
		}
	}
//	if(tmp==nullptr) throw id_not_found();
	return tmp;
}

ONodePtr OCTNode::addNode(u_int id, int val)
{
	if(hasChildren<8)
	{
		Children.emplace_back(new OCTNode(id,shared_from_this(),val));
		hasChildren=Children.size();
		return Children.back();
	}
	else
	{
		std::cout << "Cannot add more children to node ID=" << ID << '\n';
		return nullptr;
	}
}
void OCTNode::printTree(u_int level) const
{
	for(u_int i=0;i<level;++i) std::cout<<"    ";
	printNode();
	for(auto it: Children)
	{
		it->printTree(level+1);
	}
}
void OCTNode::printNode() const
{
	std::cout << "Node " << ID << "|" << Value <<" Children: ";
	if(Children.empty())
	{
		std::cout << "None";
	}
	else for(auto it: Children)
	{
		std::cout << it->ID << "|" << it->Value << ", ";
	}
	std::cout << '\n';
}

OCTree::OCTree(): Root(new OCTNode(ID_Counter++,nullptr)) {}
OCTree::OCTree(u_int nodes, int val): Root(new OCTNode(ID_Counter++,nullptr))
{
	while(ID_Counter<=nodes)
	{
		addNode((ID_Counter-1)/8,val);
	}
}
OCTree::OCTree(UIntInitList nodes,int val): Root(new OCTNode(ID_Counter++,nullptr))
{
	for(auto it: nodes)
	{
		addNode(it,val);
	}
}
OCTree::~OCTree()
{
//	Root.reset();
//	std::cout<<"Destroyed OCTree\n";
}

ONodePtr OCTree::findID(u_int ID) const
{
	auto tmp=Root->findID(ID);
	if(!tmp) 
	{
		std::cout << "No node ID=" << ID <<" found!\n";
	}
	return tmp;
}
ONodePtr OCTree::addNode(u_int ID, int val)
{
	auto tmp=findID(ID);
	if(tmp)
	{
		tmp=tmp->addNode(ID_Counter++,val);
	}
	return tmp;		
}
void OCTree::addNode(UIntInitList IDs, int val)
{
	for(auto it: IDs)
	{
		addNode(it,val);
	}
}
void OCTree::addMore(u_int more)
{
	for(u_int i=0;i<more;++i)
	{
		addNode((ID_Counter-1)/8);
	}
}
void OCTree::removeNode(u_int ID)
{
	if(ID==0)
	{
		std::cout << "Cannot remove Root\n";
		return;
	}
	auto tmp=findID(ID);
	if(tmp)
	{
		tmp=tmp->parentPtr.lock();
		for(auto it=tmp->Children.begin();it!=tmp->Children.end();++it)
		{
			if(ID==(*it)->ID)
			{
				std::cout << "Removing Node ID=" << ID << " and it's children\n";
				tmp->Children.erase(it);
				return;
			}
		}
	}
}
void OCTree::removeNode(UIntInitList to_remove)
{
	for(auto it: to_remove)
	{
		removeNode(it);
	}
}
void OCTree::print() const
{
	std::cout << "Node print format ID|Value\n";
	Root->printTree(0);
}
void OCTree::printNode(u_int ID) const
{
	auto tmp=findID(ID);
	if(tmp)
	{
		std::cout << "Node print format ID|Value\n";
		tmp->printNode();
	}
}
int OCTree::getVal(int ID) const
{
	auto tmp=findID(ID);
	return tmp ? tmp->ID : 0;
}
int OCTree::setVal(int ID, int val)
{
	auto tmp=findID(ID);
	return tmp ? (tmp->ID=val) : 0;
}
const char* Octree::id_not_found::what() const noexcept
{
	return "id_not_found";
}

template<typename T>
Octree::OCTNode<T>::OCTNode(u_int id, ONodePtr<T> parent): ID(id), parentPtr(parent) {}
template<typename T>
Octree::OCTNode<T>::OCTNode(u_int id, ONodePtr<T> parent, const T& value): ID(id), Value(value), parentPtr(parent) {}
template<typename T>
Octree::OCTNode<T>::~OCTNode()
{
// 	Children.clear();
//	std::cout << "Destroyed Node ID=" << ID << '\n';
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTNode<T>::findID(u_int id)
{
	ONodePtr<T> tmp=nullptr;
	if(id==ID) tmp=this->shared_from_this();
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
template<typename T>
bool Octree::OCTNode<T>::findIDIt(u_int id, ONodeIt<T>& iter)
{
	ONodeIt<T> tmp=Children.begin();
	while(tmp!=Children.end())
	{
		if((*tmp)->ID==id)
		{
			iter=tmp;
			return true;
		}
		else ++tmp;
	}
	if(tmp==Children.end())
	{
		bool flag=false;
		for(auto it: Children)
		{
			flag=it->findIDIt(id,iter);
			if(flag) return true;
		}
	}
	return false;
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTNode<T>::addNode(u_int id)
{
	if(hasChildren<8)
	{
		Children.emplace_back(new OCTNode<T>(id,this->shared_from_this()));
		hasChildren=Children.size();
		return Children.back();
	}
	else
	{
		std::cout << "Cannot add more children to node ID=" << ID << '\n';
		return nullptr;
	}
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTNode<T>::addNode(u_int id, const T& value)
{
	if(hasChildren<8)
	{
		Children.emplace_back(new OCTNode<T>(id,this->shared_from_this(),value));
		hasChildren=Children.size();
		return Children.back();
	}
	else
	{
		std::cout << "Cannot add more children to node ID=" << ID << '\n';
		return nullptr;
	}
}
template<typename T>
void Octree::OCTNode<T>::printTree(u_int level) const
{
	for(u_int i=0;i<level;++i) std::cout<<"    ";
	printNode();
	for(auto it: Children)
	{
		it->printTree(level+1);
	}
}
template<typename T>
void Octree::OCTNode<T>::printNode() const
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
template<typename T>
Octree::OCTREE<T>::OCTREE(): Root(new OCTNode<T>(ID_Counter++,nullptr)) {}
template<typename T>
Octree::OCTREE<T>::OCTREE(u_int nodes): Root(new OCTNode<T>(ID_Counter++,nullptr))
{
	while(ID_Counter<=nodes)
	{
		addNode((ID_Counter-1)/8);
	}
}
template<typename T>
Octree::OCTREE<T>::OCTREE(u_int nodes, const T& value): Root(new OCTNode<T>(ID_Counter++,nullptr))
{
	while(ID_Counter<=nodes)
	{
		addNode((ID_Counter-1)/8,value);
	}
}
template<typename T>
Octree::OCTREE<T>::OCTREE(Octree::UIntInitList nodes): Root(new OCTNode<T>(ID_Counter++,nullptr))
{
	for(auto it: nodes)
	{
		addNode(it);
	}
}
template<typename T>
Octree::OCTREE<T>::OCTREE(Octree::UIntInitList nodes, const T& value): Root(new OCTNode<T>(ID_Counter++,nullptr))
{
	for(auto it: nodes)
	{
		addNode(it,value);
	}
}
template<typename T>
Octree::OCTREE<T>::~OCTREE()
{
//	Root.reset();
//	std::cout<<"Destroyed OCTREE\n";
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTREE<T>::findID(u_int id) const
{
	ONodePtr<T> tmp=Root->findID(id);
	if(!tmp) 
	{
		std::cout << "No node ID=" << id <<" found!\n";
	}
	return tmp;
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTREE<T>::addNode(u_int id, const T& value)
{
	ONodePtr<T> tmp=findID(id);
	if(tmp)
	{
		tmp=tmp->addNode(ID_Counter++,value);
	}
	return tmp;		
}
template<typename T>
Octree::ONodePtr<T> Octree::OCTREE<T>::addNode(u_int id)
{
	ONodePtr<T> tmp=findID(id);
	if(tmp)
	{
		tmp=tmp->addNode(ID_Counter++);
	}
	return tmp;		
}
template<typename T>
void Octree::OCTREE<T>::addNode(Octree::UIntInitList IDs, const T& value)
{
	for(auto it: IDs)
	{
		addNode(it,value);
	}
}
template<typename T>
void Octree::OCTREE<T>::addNode(Octree::UIntInitList IDs)
{
	for(auto it: IDs)
	{
		addNode(it);
	}
}
template<typename T>
void Octree::OCTREE<T>::addMore(u_int more)
{
	for(u_int i=0;i<more;++i)
	{
		addNode((ID_Counter-1)/8);
	}
}
template<typename T>
void Octree::OCTREE<T>::addMore(u_int more, const T& value)
{
	for(u_int i=0;i<more;++i)
	{
		addNode((ID_Counter-1)/8,value);
	}
}
template<typename T>
void Octree::OCTREE<T>::removeNode(u_int id)
{
	if(id==0)
	{
		std::cout << "Cannot remove Root\n";
		return;
	}
	ONodeIt<T> tmp;
	if(Root->findIDIt(id, tmp))
	{
		std::cout << "Removing Node ID=" << id << " and it's children\n";
		(*tmp)->parentPtr.lock()->Children.erase(tmp);
	}
	else
	{
		std::cout << "No removable Node ID=" << id << " found\n";
	}
// 	ONodePtr<T> tmp=this->findID(id);
// 	if(tmp)
// 	{
// 		tmp=tmp->parentPtr.lock();
// 		for(auto it=tmp->Children.begin();it!=tmp->Children.end();++it)
// 		{
// 			if(ID==(*it)->ID)
// 			{
// 				
// 				tmp->Children.erase(it);
// 				return;
// 			}
// 		}
// 	}
}
template<typename T>
void Octree::OCTREE<T>::removeNode(Octree::UIntInitList to_remove)
{
	for(auto it: to_remove)
	{
		this->removeNode(it);
	}
}
template<typename T>
void Octree::OCTREE<T>::print() const
{
	std::cout << "Node print format ID|Value\n";
	Root->printTree(0);
}
template<typename T>
void Octree::OCTREE<T>::printNode(u_int id) const
{
	ONodePtr<T> tmp=this->findID(id);
	if(tmp)
	{
		std::cout << "Node print format ID|Value\n";
		tmp->printNode();
	}
}
template<typename T>
const T& Octree::OCTREE<T>::getVal(u_int id) const throw(std::exception)
{
	ONodePtr<T> tmp=this->findID(id);
	if(tmp) return tmp->Value;
	else throw (id_not_found());
}
template<typename T>
const T& Octree::OCTREE<T>::setVal(u_int id, const T& value) throw(std::exception)
{
	ONodePtr<T> tmp=this->findID(id);
	if(tmp) return tmp->Value=value;
	else throw (id_not_found());
}
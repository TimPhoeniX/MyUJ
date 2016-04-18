#include "CTL/Graph/Graph.hpp"
#include <iostream>

int main()
{
	CTL::Vertex<char>* vs = new CTL::Vertex<char>[10];
	CTL::Graph<char> g;
	for (int i = 0; i < 10; ++i)
	{
		(vs + i)->SetLabel('a' + char(i));
		g.AddVertex(vs + i);
	}
	g.AddEdge(vs, vs + 1);
	g.AddEdge(vs, vs + 2);
	g.AddEdge(vs + 1, vs + 2);
	g.AddEdge(vs+1, vs+3);
	g.AddEdge(vs+1, vs+4);
	g.AddEdge(vs+4, vs+5);
	g.AddEdge(vs+5, vs+6);
	g.AddEdge(vs+5, vs+7);
	g.AddEdge(vs+6, vs+8);
	g.AddEdge(vs+6, vs+9);
	g.AddEdge(vs+4, vs+8);

	std::cout << "DFS Start" << std::endl;
	
	g.DFS();
	
	for (size_t j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			g.PrintPath(vs + j, vs + i, std::cout) << std::endl;
		}
	}
}

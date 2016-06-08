#include <iostream>
#include <string>
#include <limits>
#include <iterator>
#include <stdexcept>
#include "CTL/Graph/Graph.hpp"

int main(int argc, char** argv)
{
	if(argc!=3) throw std::runtime_error("Invalid argc");
	CTL::Graph<char, CTL::Graphs::Directed > g;
	unsigned int V = 0;
	std::cin >> V;
	char a, b;
	for (unsigned int i = 0; i < V; ++i)
	{
		std::cin >> a;
		g.AddVertex(a);
	}
	std::cin >> V;
	double w = 0.;
	for (unsigned int i = 0; i < V; ++i)
	{
		std::cin >> a >> b >> w;
		g.AddEdge(g.FindVertex(a), g.FindVertex(b), w);
	}
	w = 0.;
	auto vert = g.FindVertex(argv[2][0]);
	switch(argv[1][1])
	{
		case 'd':
		{
			g.Dijkstra(vert);
		} break;
		case 'b':
		{
			if(!g.BellmanFord(vert)) std::cout << "!\n";
		}
	}

	for (auto e : g)
	{
		std::cout << e->Label() << ' ' << (e->Distance()<100000?e->Distance():100000.) << '\n';
	}
}
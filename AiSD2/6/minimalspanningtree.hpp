MST Kruskal
{
	A={};
	foreach v in G.V
		Create-Set(v);
	sort(G.E) // less wage
	foreach (u,v) in G.E\
	{
		if (Su=Find-Set(u))!=(Sv=Find-Set(v))
		{
			A = A Sum (u,v)
			Union(Su,Sv)
		}
	}
	return A;
}

MST Prim
{
	foreach v in G.V
	{
		v.key = inf;
		v.p=nullptr;
	}
	v0.key = 0;
	foreach v in G.V
		Q.push(v);
	while(!Q.empty())
	{
		u=Q.top();
		foreach v in u.Adjacent()
		{
			if v in Q && w(u,v) < v.key
			{
				v.p = u;
				v.key = w(u,v);
			}
		}
		q.pop();
	}
	
}
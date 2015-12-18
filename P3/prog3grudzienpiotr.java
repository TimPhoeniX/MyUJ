class PathFinder
{
	private boolean[][][] tracker; // For dealing with loops
	private boolean[][][] lab; // Reducing reference copying
	private Indices fin; // Same as the one above;
	
	public boolean find( boolean[][][] labyrinth, Indices start, Indices finish )
	{
		boolean result = false;
		this.lab = labyrinth;
		this.fin = finish;
		if(this.lab==null || start==null || this.fin == null ||
			this.lab.length<=0 || this.lab[0].length<=0 || this.lab[0][0].length<=0 ||
			this.checkIndicesBounds(start) ||
			this.checkIndicesBounds(this.fin) ||
			!this.checkIndices(this.fin)) {}
		else
		{
			this.tracker = new boolean[this.lab.length][this.lab[0].length][this.lab[0][0].length]; // More memory required, but it's faster
			result = this.findRecursively(start);
			this.tracker = null;
		}
		this.fin = null;
		this.lab = null;
		return result;
	}
	
	private boolean findRecursively(Indices start)
	{
		if(!this.checkIndices(start)) return false;
		else
		{
			this.visit(start);
			return PathFinder.compareIndices(start,this.fin) ||
				( start.firstIndex > 0 && !this.visited(PathFinder.tryIndices(start,-1,0,0)) //Checking for unvisited cell
				&& this.findRecursively(PathFinder.tryIndices(start,-1,0,0)) ) || // Actual recursion occuring
				(start.firstIndex < (lab.length-1) && !this.visited(PathFinder.tryIndices(start,1,0,0))
				&& this.findRecursively(PathFinder.tryIndices(start,1,0,0)) ) ||
				( start.secondIndex > 0 && !this.visited(PathFinder.tryIndices(start,0,-1,0))
				&& this.findRecursively(PathFinder.tryIndices(start,0,-1,0)) ) ||
				( start.secondIndex < (lab[0].length-1) && !this.visited(PathFinder.tryIndices(start,0,1,0))
				&& this.findRecursively(PathFinder.tryIndices(start,0,1,0)) ) ||
				( start.thirdIndex > 0 && !this.visited(PathFinder.tryIndices(start,0,0,-1))
				&& this.findRecursively(PathFinder.tryIndices(start,0,0,-1)) ) ||
				( start.thirdIndex < (lab[0][0].length-1) && !this.visited(PathFinder.tryIndices(start,0,0,1))
				&& this.findRecursively(PathFinder.tryIndices(start,0,0,1)) );
		}
	}

	public static boolean compareIndices(Indices indices1, Indices indices2)
	{
		if(indices1==indices2) return true;
		else
		return indices1.firstIndex==indices2.firstIndex
			&& indices1.secondIndex==indices2.secondIndex
			&& indices1.thirdIndex==indices2.thirdIndex;
	}
	
	public static Indices tryIndices(Indices i, int first, int second, int third)
	{
		return PathFinder.makeIndices(i.firstIndex+first,i.secondIndex+second,i.thirdIndex+third);
	}
	
	public static Indices makeIndices(int first, int second, int third)
	{
		Indices indices = new Indices();
		indices.firstIndex=first;
		indices.secondIndex=second;
		indices.thirdIndex=third;
		return indices;
	}

	private boolean checkIndicesBounds(Indices i)
	{
		return i.firstIndex < 0 || i.firstIndex >= this.lab.length ||
			i.secondIndex < 0 || i.secondIndex >= this.lab[0].length ||
			i.thirdIndex < 0 || i.thirdIndex >= this.lab[0][0].length;
	}

	private boolean checkIndices(Indices i)
	{
		return this.lab[i.firstIndex][i.secondIndex][i.thirdIndex];
	}
	
	private void visit(Indices i)
	{
		this.tracker[i.firstIndex][i.secondIndex][i.thirdIndex] = true;
	}
	
	private boolean visited(Indices i)
	{
		return this.tracker[i.firstIndex][i.secondIndex][i.thirdIndex];
	}
}
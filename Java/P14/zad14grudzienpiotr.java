import java.util.*;

class Roads implements RoadsInterface
{
	private Map<Integer, Set<Integer>> roads = new HashMap<>();
	private Set<Integer> visited = null;
	
	private boolean Pathfinder(int from, int to)
	{
		if(Integer.compare(from,to)==0) return true;
		else
		{
			boolean found = false;
			this.visited.add(from);
			for(Integer i : this.roads.get(from) )
			{
				found = this.Pathfinder(i,to);
				if(found) break;
			}
			return found;
		}
	}
	
	public void addRoad( List<Integer> via )
	{
		for(int i = 0; i < via.size(); ++i)
		{
			Integer in = via.get(i);
			Set<Integer> set = this.roads.get(in);
			if(set==null)
			{
				set = new HashSet<>();
				this.roads.put(in,set);
			}
			try{ set.add(via.get(i+1)); }
			catch( Exception e ){}
		}
	}
	
	public void roadWorks( int from, int to )
	{
		Set<Integer> set = this.roads.get(from);
		if(set!=null)
		{
			set.remove(to);
		}
	}
	
	public boolean isPassage( int from, int to )
	{
		this.visited = new HashSet<>();
		Set<Integer> set = this.roads.keySet();
		return (set.contains(from) && set.contains(to) && this.Pathfinder(from,to));
	}
}

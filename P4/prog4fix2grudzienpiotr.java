import java.util.ArrayList;

class PlatypusFinder extends PlatypusAbstractFinder
{
	private ArrayList<AbstractRoom> visited = null;
	private AbstractRoom roomWithPlatypus = null;
	
	public void find( AbstractRoom entranceToTheBuilding )
	{
		this.roomWithPlatypus = null;
		this.visited = new ArrayList<AbstractRoom>();
		if(entranceToTheBuilding==null) return;
		this.roomWithPlatypus = this.findRecursively(entranceToTheBuilding);
		this.visited = null;
	}
	
	public  AbstractRoom getRoomWithPlatypus()
	{
		return roomWithPlatypus;
	}
	
	private boolean ifVisited(AbstractRoom room) //For dealing with nasty .equals on some AbstractRoom implementations.
	{
		for(int i = 0; i < this.visited.size(); ++i)
		{
			if(room==this.visited.get(i))
			{
				return true;
			}
		}
		return false;
	}
	
	private AbstractRoom findRecursively(AbstractRoom room)
	{
		if(room.hasPlatypus()) return room;
		else
		{
			this.visited.add(room);
			AbstractRoom temporary = null; 
			AbstractRoom[] doors = room.getDoors();
			if(doors==null) return null;
			for(int i = 0; i < doors.length; ++i)
			{
				if(doors[i]==null || this.ifVisited(doors[i])) continue;
				temporary = this.findRecursively(doors[i]);
				if(temporary!=null) break;
			}
			return temporary;
		}
	}
}
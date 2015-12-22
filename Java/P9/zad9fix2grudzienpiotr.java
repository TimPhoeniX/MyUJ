import java.util.*;



class HotelReservation implements HotelReservationInterface
{
	Map<Integer,Integer> Rooms = null;
	Map<Integer,Integer> FreeRooms = null;
	
	private boolean RequirementsPossible(Map<Integer,Integer> requirements)
	{
		if(requirements == null) return true;
		for(Map.Entry<Integer,Integer> e : requirements.entrySet())
		{
			Integer i = this.Rooms.get(e.getKey());
			if(i == null) return false;
			if(e.getValue() > i) return false;
		}
		return true;
	}
	
	private boolean enoughRooms(Map<Integer,Integer> requirements)
	{
		if(requirements == null) return true;
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				Integer i = this.FreeRooms.get(e.getKey());
				if(i == null) return false;
				if(e.getValue() > i) return false;
			}
		}
		return true;
	}
	
	private void takeRooms(Map<Integer,Integer> requirements)
	{
		if(requirements == null) return;
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				this.FreeRooms.put(e.getKey(),new Integer(this.FreeRooms.get(e.getKey())-e.getValue()));
			}
		}
	}
	
	private void freeRooms(Map<Integer,Integer> requirements)
	{
		if(requirements == null) return;
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				this.FreeRooms.put(e.getKey(),new Integer(this.FreeRooms.get(e.getKey())+e.getValue()));
			}
			this.FreeRooms.notifyAll();
		}
	}
	
	public void setNumberOfRooms(Map<Integer,Integer> sizeNumber)
	{
		this.Rooms = sizeNumber;
		this.FreeRooms = new TreeMap<Integer,Integer>(sizeNumber);
	}
	
	public Map<Integer,Integer> getNumberOfFreeRooms()
	{
		return this.FreeRooms;
	}
	
	public void reservation(Map<Integer,Integer> requirements, StayAtTheHotel obj)
	{
		if(obj == null) return;
		if(!this.RequirementsPossible(requirements))
		{
			return;
		}
		synchronized( this.FreeRooms )
		{
			while(!this.enoughRooms(requirements))
			{
				try{ this.FreeRooms.wait();}
				catch(InterruptedException e) { }
			}
			this.takeRooms(requirements);
		}
		long time = obj.getPeriodOfTime();
		obj.start();
		try{ Thread.sleep(time); }
		catch(InterruptedException e) { }
		obj.stop();
		this.freeRooms(requirements);
	}
	
}
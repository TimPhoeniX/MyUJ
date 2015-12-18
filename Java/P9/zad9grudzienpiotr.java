import java.util.*;



class HotelReservation implements HotelReservationInterface
{
	Map<Integer,Integer> Rooms = null;
	Map<Integer,Integer> FreeRooms = null;
	
// 	class StayAtTheHotelHandler implements Runnable
// 	{
// 		HotelReservationInterface.StayAtTheHotel stay = null;
// 		Map<Integer,Integer> req = null;
// 		
// 		public StayAtTheHotelHandler(Map<Integer,Integer> requirements, HotelReservationInterface.StayAtTheHotel obj)
// 		{
// 			this.req = requirements;
// 			this.stay = obj;
// 		}
// 		
// 		public void run()
// 		{
// 			long time = this.stay.getPeriodOfTime();
// 			this.stay.start();
// 			try{ Thread.sleep(time); }
// 			catch(InterruptedException e) { }
// 			this.stay.stop();
// 			HotelReservation.this.freeRooms(this.req);
// 		}
// 	}
	
	private boolean RequirementsPossible(Map<Integer,Integer> requirements)
	{
		for(Map.Entry<Integer,Integer> e : requirements.entrySet())
		{
			Integer i = this.Rooms.get(e.getKey());
			if(i == null) return false;
			if(e.getValue().intValue() > i.intValue()) return false;
		}
		return true;
	}
	
	private boolean enoughRooms(Map<Integer,Integer> requirements)
	{
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				Integer i = this.FreeRooms.get(e.getKey());
				if(i == null) return false;
				if(e.getValue().intValue() > i.intValue()) return false;
			}
		}
		return true;
	}
	
	private void takeRooms(Map<Integer,Integer> requirements)
	{
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				this.FreeRooms.put(e.getKey(),new Integer(this.FreeRooms.get(e.getKey()).intValue()-e.getValue().intValue()));
			}
		}
	}
	
	private void freeRooms(Map<Integer,Integer> requirements)
	{
		synchronized( this.FreeRooms )
		{
			for(Map.Entry<Integer,Integer> e : requirements.entrySet())
			{
				this.FreeRooms.put(e.getKey(),new Integer(this.FreeRooms.get(e.getKey()).intValue()+e.getValue().intValue()));
			}
			this.FreeRooms.notifyAll();
		}
	}
	
	public void setNumberOfRooms(Map<Integer,Integer> sizeNumber)
	{
		this.Rooms = sizeNumber;
		this.FreeRooms = new TreeMap<Integer,Integer>
		(
			new Comparator<Integer>()
			{
				public int compare(Integer lhs, Integer rhs)
				{
					return Integer.compare(rhs,lhs);
				}
			}
		);
		for(Map.Entry<Integer,Integer> e : this.Rooms.entrySet())
		{
			this.FreeRooms.put(e.getKey(),e.getValue());
		}
	}
	
	public Map<Integer,Integer> getNumberOfFreeRooms()
	{
		return this.FreeRooms;
	}
	
	public void reservation(Map<Integer,Integer> requirements, StayAtTheHotel obj)
	{
		if(!this.RequirementsPossible(requirements))
		{
			return;
		}
		synchronized( this.FreeRooms )
		{
			while(!this.enoughRooms(requirements))
			{
				try{ this.FreeRooms.wait();
				}
				catch(InterruptedException e) { }
			}
//			Thread handler = new Thread(this.new StayAtTheHotelHandler(requirements,obj));
			this.takeRooms(requirements);
//			handler.start();
		}
		long time = obj.getPeriodOfTime();
		obj.start();
		try{ Thread.sleep(time); }
		catch(InterruptedException e) { }
		obj.stop();
		this.freeRooms(requirements);
	}
	
}
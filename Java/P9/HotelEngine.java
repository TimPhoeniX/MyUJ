import java.util.*;

class Stay implements HotelReservationInterface.StayAtTheHotel, Runnable
{
	private long time = 0;
	private long count = 0;
	private HotelReservationInterface Hotel = null;
	private Map<Integer,Integer> Req = null;
	
	public Stay(long t, Map<Integer,Integer> req, HotelReservationInterface hotel)
	{
		this.time = t;
		this.Req = req;
		this.Hotel = hotel;
	}
	
	public long getPeriodOfTime()
	{
		return this.time;
	}
	
	public void start()
	{
		System.out.println(this.Hotel.getNumberOfFreeRooms());
		this.count = (new Date()).getTime();
	}
	
	public void stop()
	{
		this.count = (new Date()).getTime()-this.count;
		if( count < time || time+time*.1 < count)
			System.err.println("Error - Expected time: "+this.time+", Was: "+this.count);
		else System.out.println("OK - Expected time: "+this.time+", Was: "+this.count);
	}
	
	public void run()
	{
		this.Hotel.reservation(this.Req,this);
	}
	
}

class HotelEngine
{
	HotelReservationInterface Hotel;
	
	public HotelEngine(HotelReservationInterface h)
	{
		this.Hotel = h;
	}
	
	public void setRandomHotelRooms()
	{
		Random r = new Random();
		Map<Integer,Integer> rooms = new HashMap<>();
		int lim = 4+r.nextInt(5);
		for(int i = 1; i <= lim; ++i)
		{
			rooms.put(i,3+r.nextInt(6));
		}
		this.Hotel.setNumberOfRooms(rooms);
	}
	
	public void setRooms(int[][] req)
	{
		this.Hotel.setNumberOfRooms(HotelEngine.getRooms(req));
	}
	
	public static Map<Integer,Integer> getRooms(int[][] req)
	{
		Random r = new Random();
		Map<Integer,Integer> rooms = new HashMap<>();
		for(int i = 0; i < req.length; ++i)
		{
			rooms.put(req[i][0],req[i][1]);
		}
		return rooms;
	}
	
	public static Map<Integer,Integer> getRandomRooms()
	{
		Random r = new Random();
		Map<Integer,Integer> rooms = new HashMap<>();
		int lim = 1+r.nextInt(5);
		while(lim-- > 0)
		{
			rooms.put(1+r.nextInt(8),1+r.nextInt(4));
		}
		return rooms;
	}
	
	public Thread getRandomStayThread()
	{
		Random r = new Random();
		return new Thread(new Stay(500*(1+r.nextInt(20)),HotelEngine.getRandomRooms(),this.Hotel));
	}
	
	public Thread getStayThread(long time, Map<Integer,Integer> rooms)
	{
		return new Thread(new Stay(time,rooms,this.Hotel));
	}
}

class HotelReservationTester
{
	public static void main(String[] args)
	{
		HotelEngine Hotel = new HotelEngine(new HotelReservation());
		Hotel.setRooms(new int[][]{{8,9},{7,9},{6,9},{5,9},{4,9},{3,9},{2,9},{1,9}});
		int Guests = 50;
		while(Guests-- > 0)
		{
			Hotel.getRandomStayThread().start();
		}
	}
}
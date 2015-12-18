import java.util.*;

class Value implements ValueI
{
	private float Val = 0.0f;
	
	public Value()
	{	
	}
	
	public Value(float val)
	{
		this.Val = val;
	}

	public float getValue()
	{
		return this.Val;
	}

	public String toString()
	{
		return "val: "+this.Val;
	}

	@Override
	public boolean equals(Object v)
	{
		if(v==null) return false;
		return ( this==v ? true : this.Val==((Value)v).Val );
	}
}

class Start
{
	public static void main(String[] args)
	{
		ObjectExchangeInterface objex = new ObjectExchange();
		
		// 1 getRegisteredUsers returns null when no users registered yet
		System.out.println( objex.getRegisteredUsers()==null ? "1 OK" : "Error at 1");
		
		// 2 registering users
		String user1 = "abstractUser1", user2 = "AbstractUser2", user3 = "abstractUser3";
		
		System.out.println( objex.registerUser(user1)  ? "2a OK" : "Error at 2a");
		System.out.println( !objex.registerUser(user1) ? "2b OK" : "Error at 2b");
		System.out.println( objex.registerUser(user2)  ? "2c OK" : "Error at 2c");
		
		// 3 checking set of registeres users
		Set<String> users = new HashSet<>(); users.add(user1); users.add(user2);
		
		System.out.println( objex.getRegisteredUsers().containsAll(users) ? "3a OK" : "Error at 3a");
		System.out.println( users.containsAll(objex.getRegisteredUsers()) ? "3b OK" : "Error at 3b");
		
		// 4 Adding Objects
		Value onea  = new Value(1.5f);
		Value oneb  = new Value(1.5f);
		Value two   = new Value(2.5f);
		Value three = new Value(3.5f);
		
		System.out.println( !objex.addObjectToSystem(user3,two)  ? "4a OK" : "Error at 4a");
		System.out.println( !objex.addObjectToSystem(user3,null) ? "4b OK" : "Error at 4b");
		System.out.println( !objex.addObjectToSystem(user1,null) ? "4c OK" : "Error at 4c");
		System.out.println(  objex.addObjectToSystem(user1,onea) ? "4d OK" : "Error at 4d");
		System.out.println(  objex.addObjectToSystem(user1,oneb) ? "4e OK" : "Error at 4e");
		System.out.println(  objex.addObjectToSystem(user1,onea) ? "4f OK" : "Error at 4f");
		System.out.println(  objex.addObjectToSystem(user1,oneb) ? "4g OK" : "Error at 4g");
		System.out.println(  objex.addObjectToSystem(user1,onea) ? "4h OK" : "Error at 4h");
		System.out.println(  objex.addObjectToSystem(user1,two)  ? "4i OK" : "Error at 4i");
		System.out.println(  objex.addObjectToSystem(user1,three)? "4j OK" : "Error at 4j");
		System.out.println(  objex.addObjectToSystem(user1,two)  ? "4k OK" : "Error at 4k");
		
		// 5 geting sorted lists
		System.out.println( objex.getSortedListOfObjects(user1)!=null ? "5a OK" : "Error at 5a");
		System.out.println( objex.getSortedListOfObjects(user2)==null ? "5b OK" : "Error at 5b");
		System.out.println( objex.getSortedListOfObjects(user3)==null ? "5c OK" : "Error at 5c");
		System.out.println( "[val: 3.5, val: 2.5, val: 2.5, val: 1.5, val: 1.5, val: 1.5, val: 1.5, val: 1.5]".equals(objex.getSortedListOfObjects(user1).toString()) ? "5d OK" : "Error at 5d" );
		
		// 6 getting map
		Set<ValueI> obj = new HashSet<>(); obj.add(onea); obj.add(oneb); obj.add(two); obj.add(three);
		System.out.println( objex.getSortedMap(user3)==null ? "6a OK" : "Error at 6a");
		System.out.println( objex.getSortedMap(user2)==null ? "6b OK" : "Error at 6b");
		System.out.println( objex.getSortedMap(user1).keySet().containsAll(obj) ? "6c OK" : "Error at 6c");
		System.out.println( obj.containsAll(objex.getSortedMap(user1).keySet()) ? "6d OK" : "Error at 6d");
		System.out.println( "[3, 2, 2, 1]".equals(objex.getSortedMap(user1).values().toString()) ? "6e OK" : "Error at 6e" );
		
		// 7 deregistering users
		users.remove(user2);
		
		System.out.println( !objex.deregisterUser(user3) ? "7a OK" : "Error at 7a");
		System.out.println(  objex.deregisterUser(user2) ? "7b OK" : "Error at 7b");
		System.out.println( objex.getRegisteredUsers().containsAll(users) ? "7c OK" : "Error at 7c");
		System.out.println( users.containsAll(objex.getRegisteredUsers()) ? "7d OK" : "Error at 7d");
		System.out.println(  objex.deregisterUser(user1) ? "7e OK" : "Error at 7e");
		System.out.println( objex.getRegisteredUsers()==null ? "7f OK" : "Error at 7f");
	}
}
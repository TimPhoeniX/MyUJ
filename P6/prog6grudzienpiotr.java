import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.Comparator;

class ObjectExchange implements ObjectExchangeInterface
{
	private Set<String> Usernames = null;
	private Map<String, List<ValueI>> Values = null;
	
	public ObjectExchange()
	{
		this.Usernames = new TreeSet<>();
		this.Values = new HashMap<>();
	}
	
	public boolean registerUser(String username)
	{
		if( username == null || !this.Usernames.add(username) ) return false;
		this.Values.put(username,new ArrayList<>()); //ArrayList has specilaized sort() so it should be faster
		return true;
	}
	
	public Set<String> getRegisteredUsers()
	{
		return ( this.Usernames.isEmpty() ? null : this.Usernames );
	}
	
	public boolean deregisterUser(String username)
	{
		if( username == null || !this.Usernames.contains(username) ) return false;
		this.Usernames.remove(username);
		this.Values.put(username,new ArrayList<>()); //ArrayList has specialized sort() so it should be faster
		return true;
	}
	
	public <T extends ValueI> boolean addObjectToSystem(String username, T obj)
	{
		if( obj == null || username == null || !this.Usernames.contains(username) ) return false;
		this.Values.get(username).add(obj);
		return true;
	}
	
	public List<ValueI> getSortedListOfObjects(String username)
	{
		if( username != null )
		{
			List<ValueI> handle = this.Values.get(username);
			if(handle != null && !handle.isEmpty())
			{
				handle.sort(new Comparator<ValueI>()
					{
						public int compare(ValueI a, ValueI b)
						{
							return Float.compare(b.getValue(),a.getValue()); //Please, work;
						}
					}
				);
				return handle;
			}
		}
		return null;
	}
	
	public Map<ValueI, Integer> getSortedMap(String username)
	{
		if( username == null || !this.Usernames.contains(username)) return null;
		List<ValueI> handle = this.Values.get(username);
		if(handle.isEmpty()) return null;
		Set<ValueI> lookup = new HashSet<>();
		Map<ValueI,Integer> holder = new HashMap<>();
		for(ValueI val : handle)
		{
			boolean tmp = lookup.add(val);
			if(tmp)
			{
				holder.put(val, 1);
			}
			else
			{
				holder.put(val,holder.get(val).intValue()+1);
			}
		}
		List<Map.Entry<ValueI,Integer>> sorter = new ArrayList<>(holder.entrySet());
		sorter.sort(new Comparator<Map.Entry<ValueI,Integer>>()
			{
				public int compare(Map.Entry<ValueI,Integer> a, Map.Entry<ValueI,Integer> b)
				{
					return Integer.compare(b.getValue(),a.getValue()); //Please, work;
				}
			}
		);
		Map<ValueI,Integer> returned = new LinkedHashMap<>();
		for(Map.Entry<ValueI,Integer> entry : sorter)
		{
			returned.put(entry.getKey(),entry.getValue());
		}
		return returned;
	}
}
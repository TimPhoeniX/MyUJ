class TheRoom extends AbstractRoom
{
	private boolean hasPlatypus;
	private AbstractRoom[] theDoors;
	private String identifier;
	
	public void setPlatypus(boolean p)
	{
		this.hasPlatypus=p;
	}

	public void addDoors(AbstractRoom[] doors)
	{
		this.theDoors = doors;
	}

	public boolean hasPlatypus()
	{
		return this.hasPlatypus;
	}

	public AbstractRoom[] getDoors()
	{
		return this.theDoors;
	}
}

class PlatypusFinderTester
{
    private static int counter;

    static
    {
        counter = 0;
    }

	private static void checkForPlatypus(AbstractRoom check, String expectedResult)
	{
		String output = (check!=null?(check.hasPlatypus()?"OK":"No platypus in the room"):"404");
        
        	System.out.print(++counter + ": ");

       		if(output.equals(expectedResult))
            		System.out.println("\u001B[32mCORRECT\u001B[0m: " + output);
        	else
            		System.out.println("\u001B[31mERROR\u001B[0m: " + output);
	}
	
	public static void main(String[] argv)
	{
		PlatypusAbstractFinder Finder = new PlatypusFinder();
        
        	TheRoom a = new TheRoom();
		TheRoom b = new TheRoom();
        	TheRoom c = new TheRoom();
		TheRoom d = new TheRoom();
		TheRoom e = new TheRoom();
		TheRoom f = new TheRoom();
        	TheRoom g = new TheRoom();
        	TheRoom h = new TheRoom();
		
////////////////////////////////  1

		a.addDoors(new AbstractRoom[] {b});
		b.addDoors(new AbstractRoom[] {c});
        	c.setPlatypus(true);
        
		Finder.find(a);
		checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
		c.setPlatypus(false);

////////////////////////////////  2

		b.addDoors(new TheRoom[] {c,d,e});
		c.addDoors(new TheRoom[] {b,d,e});
		d.addDoors(new TheRoom[] {c,b,e});
		e.addDoors(new TheRoom[] {c,d,b,f});
		f.addDoors(new TheRoom[] {a});
		f.setPlatypus(true);
        
		Finder.find(a);
		checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
		f.setPlatypus(false);
        
////////////////////////////////  3

		Finder.find(a);
		checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        
////////////////////////////////  4
		
        	Finder.find(null);
		checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        
////////////////////////////////  5


        	a.addDoors(new AbstractRoom[] {null});
        
        	Finder.find(a);
        	checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        
        
////////////////////////////////  6


        a.addDoors(new TheRoom[] {b,c,h, null});
        b.addDoors(new TheRoom[] {c, null});
        h.addDoors(new TheRoom[] {null,f});
        g.addDoors(new TheRoom[] {h,e});
        f.addDoors(new TheRoom[] {g,h});
        e.addDoors(new TheRoom[] { null,d});
        
        d.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        d.setPlatypus(false);
        
        
////////////////////////////////  7
        
        a.addDoors(new TheRoom[] {d});
        b.addDoors(new TheRoom[] {a});
        c.addDoors(new TheRoom[] {});
        d.addDoors(new TheRoom[] {b,e});
        e.addDoors(new TheRoom[] {a,c});
        
        c.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        c.setPlatypus(false);
        
////////////////////////////////  8

        a.addDoors(new TheRoom[] {});
        b.addDoors(new TheRoom[] {a,d,c});
        c.addDoors(new TheRoom[] {d});
        d.addDoors(new TheRoom[] {});
        e.addDoors(new TheRoom[] {a});
        
        e.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        e.setPlatypus(false);
        
////////////////////////////////  9

        a.addDoors(new TheRoom[] {a});
        b.addDoors(new TheRoom[] {a,d,c,b});
        c.addDoors(new TheRoom[] {d,c});
        d.addDoors(new TheRoom[] {d});
        e.addDoors(new TheRoom[] {a,e});
        
        e.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        e.setPlatypus(false);
        
////////////////////////////////  10

        a.addDoors(new TheRoom[] {f,c,c});
        b.addDoors(new TheRoom[] {c,a,e,c});
        c.addDoors(new TheRoom[] {a,b,d});
        d.addDoors(new TheRoom[] {a});
        e.addDoors(new TheRoom[] {f,d});
        f.addDoors(new TheRoom[] {a,d});
        g.addDoors(new TheRoom[] {});
        h.addDoors(new TheRoom[] {});
        
        b.setPlatypus(true);
        e.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        b.setPlatypus(false);
        e.setPlatypus(false);        
                
////////////////////////////////  11

        a.addDoors(new TheRoom[] {b,g});
        b.addDoors(new TheRoom[] {b,null,c,null});
        c.addDoors(new TheRoom[] {b,f,d});
        d.addDoors(new TheRoom[] {e,null});
        e.addDoors(new TheRoom[] {c});
        f.addDoors(new TheRoom[] {g,h});
        g.addDoors(new TheRoom[] {f});
        h.addDoors(new TheRoom[] {e,null});
        
        h.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        h.setPlatypus(false);
        
                
////////////////////////////////  12

        a.addDoors(new TheRoom[] {b});
        b.addDoors(new TheRoom[] {c});
        c.addDoors(new TheRoom[] {d});
        d.addDoors(new TheRoom[] {e});
        e.addDoors(new TheRoom[] {f});
        f.addDoors(new TheRoom[] {g});
        g.addDoors(new TheRoom[] {h});
        h.addDoors(new TheRoom[] {a});
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"404");

        
                
////////////////////////////////  13

        a.addDoors(new TheRoom[] {b});
        b.addDoors(new TheRoom[] {a,a});
        c.addDoors(new TheRoom[] {b,h});
        d.addDoors(new TheRoom[] {b,e,f});
        e.addDoors(new TheRoom[] {});
        f.addDoors(new TheRoom[] {});
        g.addDoors(new TheRoom[] {});
        h.addDoors(new TheRoom[] {d});
        
        h.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        h.setPlatypus(false);
        
                
////////////////////////////////  14

        a.addDoors(new TheRoom[] {a,b,c,d,e,f,g,h});
        b.addDoors(new TheRoom[] {c,h});
        c.addDoors(new TheRoom[] {d});
        d.addDoors(new TheRoom[] {e});
        e.addDoors(new TheRoom[] {f});
        f.addDoors(new TheRoom[] {g});
        g.addDoors(new TheRoom[] {});
        h.addDoors(new TheRoom[] {g});
        
        h.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        h.setPlatypus(false);
        
////////////////////////////////  15

        a.addDoors(new TheRoom[] {b});
        b.addDoors(new TheRoom[] {c});
        c.addDoors(new TheRoom[] {});
        d.addDoors(new TheRoom[] {});
        e.addDoors(new TheRoom[] {});
        f.addDoors(new TheRoom[] {});
        g.addDoors(new TheRoom[] {});
        h.addDoors(new TheRoom[] {});
        
        a.setPlatypus(true);
        
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"OK");
        a.setPlatypus(false);
        
        
////////////////////////////////  16

        a.addDoors(new TheRoom[] {});
        b.addDoors(new TheRoom[] {});
        c.addDoors(new TheRoom[] {});
        d.addDoors(new TheRoom[] {});
        e.addDoors(new TheRoom[] {});
        f.addDoors(new TheRoom[] {});
        g.addDoors(new TheRoom[] {});
        h.addDoors(new TheRoom[] {});
                
        Finder.find(a);
        checkForPlatypus(Finder.getRoomWithPlatypus(),"404");
        
        
		//Expected output: 
        //1: OK 
        //2: OK 
        //3: 404 
        //4: 404 
        //5: 404 
        //6: OK 
        //7: OK 
        //8: 404 
        //9: 404 
        //10: OK
        //11: OK
        //12: 404
        //13: 404
        //14: OK
        //15: OK
        //16: 404
	}
}
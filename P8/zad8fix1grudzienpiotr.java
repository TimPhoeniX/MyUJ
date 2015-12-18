import java.util.*;

class Position
{
	public int x;
	public int y;
	
	Position(int a, int b)
	{
		this.x=a;
		this.y=b;
	}
	
	@Override
	public boolean equals( Object o )
	{
		if( o instanceof Position)
		{
			Position p = (Position)o;
			return ( this.x==p.x && this.y==p.y );
		}
		return false;
	}
	
	public int hashCode()
	{
		return 10000*x+y;
	}
	
	public String toString()
	{
		return "["+x+":"+y+"]";
	}
}

class WyjatkowySaper implements WyjatkowySaperPlayerInterface
{
	private WyjatkowySaperGameInterface Game = null;
	private int Size = 0;
	private int[][] Minefield = null;
	private Set<Position> ToCheck = new HashSet<>();
	private Queue<Position> Pass = null;
	private Set<Position> Undeterminable = new HashSet<>();
	private Set<Position> Mines = new HashSet<>();
	private Random GrimReaper = new Random();
	
	public WyjatkowySaper()
	{
	}
	
	public void setGameInterface( WyjatkowySaperGameInterface gi )
	{
		this.Game = gi;
	}
	
	public void getSize( int min )
	{
		int tries = 0, a = 0, b = 0;
		boolean Bisection = false;
		try{ this.Game.rozmiarPlanszyDoGry( min ); }
		catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p )
		{ tries = p.poczatkowaLiczbaProb; }
		catch( WyjatkowySaperGameInterface.ZaDuzy z) {}
		catch( WyjatkowySaperGameInterface.ZaMaly z) {}
		a = min-1;
		b = a+(int)Math.pow(2,tries);
		while(tries > 1)
		{
			try{ this.Game.rozmiarPlanszyDoGry( b ); this.Size = b; return; }
			catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p ) {}
			catch( WyjatkowySaperGameInterface.ZaDuzy z) { Bisection = true; break; }
			catch( WyjatkowySaperGameInterface.ZaMaly z) { a = b; b = a+(int)Math.pow(2,--tries); }
		}
		while(tries-- > 1)
		{
			try{ this.Game.rozmiarPlanszyDoGry( (a+b)/2 ); this.Size = (a+b)/2; return; }
			catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p ) {}
			catch( WyjatkowySaperGameInterface.ZaDuzy z) { b = (a+b)/2; }
			catch( WyjatkowySaperGameInterface.ZaMaly z) { a = (a+b)/2; }
		}
		if(Bisection)
		{
			try{ this.Game.rozmiarPlanszyDoGry( (a+b)/2 ); this.Size = (a+b)/2; return; }
			catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p ) {}
			catch( WyjatkowySaperGameInterface.ZaDuzy z) { this.Size = a+1; }
			catch( WyjatkowySaperGameInterface.ZaMaly z) { this.Size = b-1; }
		}
		else
		{
			try{ this.Game.rozmiarPlanszyDoGry( b ); this.Size = b; return; }
			catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p ) {}
			catch( WyjatkowySaperGameInterface.ZaDuzy z) { this.Size = b-1; }
			catch( WyjatkowySaperGameInterface.ZaMaly z) { this.Size = b+1; }
		}
		
// 		catch( WyjatkowySaperGameInterface.PoczatkowaLiczbaProb p ) {}
// 		catch( WyjatkowySaperGameInterface.ZaDuzy z) {}
// 		catch( WyjatkowySaperGameInterface.ZaMaly z) {}
	}
	
	private void Printfield()
	{
		for(int[] row : this.Minefield)
		{
			for(int i : row)
			{
				System.out.print(i+"\t");
			}
			System.out.println();
		}
	}
	
	private void CorrectFoundMine( int x, int y )
	{
		try
		{
			if(this.Minefield[x][y] > 0 && this.Minefield[x][y] < 9) --this.Minefield[x][y];
		}
		catch(ArrayIndexOutOfBoundsException e) {}
	}
	
	private void FoundMine( Position p )
	{
	//	System.out.println("Mine at "+p);
		this.Mines.add(p);
		this.Minefield[p.x][p.y]=-1;
		this.Undeterminable.remove(p);
		this.CorrectFoundMine(p.x-1,p.y-1);
		this.CorrectFoundMine(p.x-1,p.y);
		this.CorrectFoundMine(p.x-1,p.y+1);
		this.CorrectFoundMine(p.x,p.y-1);
		this.CorrectFoundMine(p.x,p.y+1);
		this.CorrectFoundMine(p.x+1,p.y-1);
		this.CorrectFoundMine(p.x+1,p.y);
		this.CorrectFoundMine(p.x+1,p.y+1);
	}
	
	private void FoundMine( int x, int y )
	{
	//	System.out.println("Mine at ["+x+":"+y+"]");
		this.Mines.add(new Position(x,y));
		this.Minefield[x][y]=-1;
		this.Undeterminable.remove(new Position(x,y));
		this.CorrectFoundMine(x-1,y-1);
		this.CorrectFoundMine(x-1,y);
		this.CorrectFoundMine(x-1,y+1);
		this.CorrectFoundMine(x,y-1);
		this.CorrectFoundMine(x,y+1);
		this.CorrectFoundMine(x+1,y-1);
		this.CorrectFoundMine(x+1,y);
		this.CorrectFoundMine(x+1,y+1);
	}
	
	private int CountMines( Position p )
	{
		int count =0;
		if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == -1) ++count;
		if( p.x > 0 && this.Minefield[p.x-1][p.y] == -1) ++count;
		if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == -1) ++count;
		if( p.y > 0 && this.Minefield[p.x][p.y-1] == -1) ++count;
		if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == -1) ++count;
		if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == -1) ++count;
		if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == -1) ++count;
		if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == -1) ++count;
		return count;
	}
	
	private int CountUnkown( Position p )
	{
		int count =0;
		if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == 9) ++count;
		if( p.x > 0 && this.Minefield[p.x-1][p.y] == 9) ++count;
		if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == 9) ++count;
		if( p.y > 0 && this.Minefield[p.x][p.y-1] == 9) ++count;
		if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == 9) ++count;
		if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == 9) ++count;
		if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == 9) ++count;
		if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == 9) ++count;
		return count;
	}
	
	private ArrayList<Position> ListUnknown( Position p )
	{
		ArrayList<Position> u  = new ArrayList<>();
		if(p!=null)
		{
			if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == 9) u.add(new Position(p.x-1,p.y-1));
			if( p.x > 0 && this.Minefield[p.x-1][p.y] == 9) u.add(new Position(p.x-1,p.y));
			if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == 9) u.add(new Position(p.x-1,p.y+1));
			if( p.y > 0 && this.Minefield[p.x][p.y-1] == 9) u.add(new Position(p.x,p.y-1));
			if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == 9) u.add(new Position(p.x,p.y+1));
			if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == 9) u.add(new Position(p.x+1,p.y-1));
			if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == 9) u.add(new Position(p.x+1,p.y));
			if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == 9) u.add(new Position(p.x+1,p.y+1));
		}
		else
		{
			for(int x = 0; x < this.Size; ++x)
			{
				for(int y = 0; y < this.Size; ++y)
				{
					if(this.Minefield[x][y]==9) u.add(new Position(x,y));
				}
			}
		}
		return u;
	}
	
	private void MarkMines( Position p )
	{
		if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == 9) this.FoundMine(p.x-1,p.y-1);
		if( p.x > 0 && this.Minefield[p.x-1][p.y] == 9) this.FoundMine(p.x-1,p.y);
		if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == 9) this.FoundMine(p.x-1,p.y+1);
		if( p.y > 0 && this.Minefield[p.x][p.y-1] == 9) this.FoundMine(p.x,p.y-1);
		if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == 9) this.FoundMine(p.x,p.y+1);
		if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == 9) this.FoundMine(p.x+1,p.y-1);
		if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == 9) this.FoundMine(p.x+1,p.y);
		if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == 9) this.FoundMine(p.x+1,p.y+1);
	}
	
	
	private void CheckPosition(Position p) throws WyjatkowySaperGameInterface.ToJestWyjscie
	{
		try
		{ 
			this.Game.sprawdzam(p.x, p.y);
			this.Minefield[p.x][p.y]=0;
		}
		catch( WyjatkowySaperGameInterface.Bum b )
		{
			this.Minefield[p.x][p.y]=-1;
		}
		catch( WyjatkowySaperGameInterface.UwagaMiny m )
		{
			if(this.Minefield[p.x][p.y] != 0)
			this.Minefield[p.x][p.y]=m.ileMinWPoblizu-this.CountMines(p);
		}
	}
	
	public void start( int index1, int index2 )
	{
		try
		{
			this.getSize( Integer.max(index1+1, index2+1) );
			this.Minefield = new int[this.Size][this.Size];
			for(int[] row : this.Minefield) Arrays.fill(row,9);
			this.ToCheck.add(new Position(index1,index2));
			while(true) // Loop exits by exception or no exit found.
			{
				boolean Undetermined = true;
			//	System.out.println(iter);
				this.Pass = new LinkedList<>(this.ToCheck);
				for(Position p : this.Pass)
				{
					this.CheckPosition(p);
					switch(this.Minefield[p.x][p.y])
					{
						case -1:
						{
							Undetermined = false;
						//	System.out.println("Bum");
						//	System.err.println("Err check: Pre Explosion at"+p+" : "+this.Minefield[p.x][p.y]);
							Game.nastepnySaper();
							this.Undeterminable.remove(p);
							this.FoundMine(p);
							this.Mines.remove(p);
							this.CheckPosition(p);
						//	System.err.println("Err check: Post Explosion at"+p+": "+this.Minefield[p.x][p.y]);
						}
						case 0:
						{
							Undetermined = false;
							this.Minefield[p.x][p.y]=0;
							this.Undeterminable.remove(p);
							this.ToCheck.remove(p);
							if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == 9) this.ToCheck.add(new Position(p.x-1,p.y-1));
							if( p.x > 0 && this.Minefield[p.x-1][p.y] == 9) this.ToCheck.add(new Position(p.x-1,p.y));
							if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == 9) this.ToCheck.add(new Position(p.x-1,p.y+1));
							if( p.y > 0 && this.Minefield[p.x][p.y-1] == 9) this.ToCheck.add(new Position(p.x,p.y-1));
							if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == 9) this.ToCheck.add(new Position(p.x,p.y+1));
							if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == 9) this.ToCheck.add(new Position(p.x+1,p.y-1));
							if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == 9) this.ToCheck.add(new Position(p.x+1,p.y));
							if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == 9) this.ToCheck.add(new Position(p.x+1,p.y+1));
						}
						default:
						{
							if( this.Minefield[p.x][p.y]==this.CountUnkown(p) )
							{
								Undetermined = false;
								this.MarkMines(p);
								this.Minefield[p.x][p.y]=0;
							}
							if( p.x > 0 && p.y > 0 && this.Minefield[p.x-1][p.y-1] == 9) this.Undeterminable.add(new Position(p.x-1,p.y-1));
							if( p.x > 0 && this.Minefield[p.x-1][p.y] == 9) this.Undeterminable.add(new Position(p.x-1,p.y));
							if( p.x > 0 && p.y < this.Size-1 && this.Minefield[p.x-1][p.y+1] == 9) this.Undeterminable.add(new Position(p.x-1,p.y+1));
							if( p.y > 0 && this.Minefield[p.x][p.y-1] == 9) this.Undeterminable.add(new Position(p.x,p.y-1));
							if( p.y < this.Size-1 && this.Minefield[p.x][p.y+1] == 9) this.Undeterminable.add(new Position(p.x,p.y+1));
							if( p.x < this.Size-1 && p.y > 0 && this.Minefield[p.x+1][p.y-1] == 9) this.Undeterminable.add(new Position(p.x+1,p.y-1));
							if( p.x < this.Size-1 && this.Minefield[p.x+1][p.y] == 9) this.Undeterminable.add(new Position(p.x+1,p.y));
							if( p.x < this.Size-1 && p.y < this.Size-1 && this.Minefield[p.x+1][p.y+1] == 9) this.Undeterminable.add(new Position(p.x+1,p.y+1));
						}
					}
				}
				if(Undetermined)
				{
				//	System.err.println("Undeterminable case encountered");
					if(this.Undeterminable.isEmpty())
					{
						ArrayList<Position> list = new ArrayList<>();
						for(Position p : this.Mines)
						{
							if( this.CountUnkown(p) > 0 ) list.add(p);
						}
						if(list.isEmpty())
						{
							list = this.ListUnknown(null);
							if(list.isEmpty())
							{
								break;
							}
						}
						this.ToCheck.add(list.get(this.GrimReaper.nextInt(list.size())));
					}
					else
					{
						Position investigate = null;
						double minMineProbability = 1;
						double MineProbability = 0;
						for(Position pos : this.Undeterminable)
						{
							MineProbability = (double)this.Minefield[pos.x][pos.y]/(double)this.CountUnkown(pos);
							if(MineProbability < minMineProbability) 
							{
								minMineProbability=MineProbability;
								investigate = pos;
							}
						}
						ArrayList<Position> list = this.ListUnknown(investigate);
						if(list.isEmpty())
						{
							break;
						}
						this.ToCheck.add(list.get(this.GrimReaper.nextInt(list.size())));
					}
				}
			//	this.Printfield();
			//	System.out.println(this.ToCheck+" "+this.Undeterminable);
			}
		}
		catch( WyjatkowySaperGameInterface.ToJestWyjscie w) { }
		catch( WyjatkowySaperGameInterface.NieMaJuzNikogo n) { }
	//	this.Printfield();
	//	System.out.println(this.ToCheck+" "+this.Undeterminable);
	}}
import java.util.Random;

public class ExceptionalSapperEngine implements WyjatkowySaperGameInterface
{
	private int Tries = 0;
	private boolean Init = false;
	private int Sappers = 0;
	private int[][] Minefield = null;
	private Random rnd = new Random();
	
	public ExceptionalSapperEngine(int tries, int sappers, int[][] minefield)
	{
		this.Tries = tries;
		this.Sappers = sappers;
		this.Minefield = minefield;
	}
	
	public void nastepnySaper() throws NieMaJuzNikogo
	{
		if( this.Sappers == 0 ) throw new NieMaJuzNikogo();
	}
	
	public void rozmiarPlanszyDoGry( int propozycja ) throws ZaDuzy, ZaMaly, PoczatkowaLiczbaProb
	{
		if(this.Init)
		{
			if(this.Tries == 0)
			{
				if(this.rnd.nextBoolean())
					throw new ZaDuzy();
				else throw new ZaMaly();
			}
			else 
			{
				--this.Tries;
				if( propozycja > this.Minefield.length ) throw new ZaDuzy();
				if( propozycja < this.Minefield.length ) throw new ZaMaly();
			}
		}
		else
		{
			this.Init = true;
			throw new PoczatkowaLiczbaProb(this.Tries);
		}
	}
	
	private boolean CorrectPostExplosion( int index1, int index2 )
	{
		try
		{
			if(this.Minefield[index1][index2] < 0) return true;
			else if(this.Minefield[index1][index2] > 0 && this.Minefield[index1][index2] < 9)
			{
				--this.Minefield[index1][index2];
			}
			return false;
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			return false;
		}
	}
	
	private int ExplosionHelper( int index1, int index2 )
	{
		int NearbyMines = 0;
		if(this.CorrectPostExplosion(index1-1,index2-1)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1-1,index2)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1-1,index2+1)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1,index2-1)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1,index2+1)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1+1,index2-1)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1+1,index2)) ++NearbyMines;
		if(this.CorrectPostExplosion(index1+1,index2+1)) ++NearbyMines;
		return NearbyMines;
	}
	
	public void sprawdzam( int index1, int index2 ) throws UwagaMiny, Bum, ToJestWyjscie
	{
		try
		{
			if( this.Minefield[index1][index2] > 0 && this.Minefield[index1][index2] <= 8 )
			{
				throw new UwagaMiny(this.Minefield[index1][index2]);
			}
			if( this.Minefield[index1][index2] == 9 )
			{
				throw new ToJestWyjscie();
			}
			if( this.Minefield[index1][index2] < 0 )
			{
				--this.Sappers;
				this.Minefield[index1][index2] = this.ExplosionHelper(index1,index2);
				throw new Bum();
			}
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			--this.Sappers;
			throw new Bum();
		}
	}
}
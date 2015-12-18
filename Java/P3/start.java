class Start
{
	public static void main(String[] argv)
	{
		PathFinder path = new PathFinder();
		boolean[][][] l = new boolean[3][3][3];
		l[0][0][0]=true;  l[0][0][1]=false; l[0][0][2]=true;
		l[0][1][0]=false; l[0][1][1]=true;  l[0][1][2]=false;
		l[0][2][0]=true;  l[0][2][1]=false; l[0][2][2]=true;
		l[1][0][0]=true;  l[1][0][1]=false; l[1][0][2]=true;
		l[1][1][0]=true;  l[1][1][1]=true;  l[1][1][2]=false;
		l[1][2][0]=true;  l[1][2][1]=false; l[1][2][2]=true;
		l[2][0][0]=true;  l[2][0][1]=false; l[2][0][2]=true;
		l[2][1][0]=false; l[2][1][1]=true;  l[2][1][2]=true;
		l[2][2][0]=true;  l[2][2][1]=false; l[2][2][2]=true;
		Indices a = PathFinder.makeIndices(0,0,2);
		Indices t = PathFinder.makeIndices(0,0,1);
		Indices b = PathFinder.makeIndices(0,0,0);
		Indices c = PathFinder.makeIndices(0,2,-5);
		Indices d = PathFinder.makeIndices(0,5,4);
		Indices e = PathFinder.makeIndices(1,1,2);
		System.out.println(path.find(l,a,b)+" "+path.find(l,b,a)+" "+path.find(l,c,d)+" "+path.find(l,a,e)+" "+path.find(l,e,a));
		boolean[][][] tab = new boolean[5][5][5];
		tab[1][0][0] = true;
		tab[1][0][1] = true;
		tab[1][1][1] = true;
			
			//div
			tab[1][1][2] = true;
					
		tab[2][1][1] = true;
		tab[2][1][2] = true;
		
			//div
			tab[3][1][2] = true;
			tab[4][1][2] = true;
			tab[4][1][3] = true;
			tab[4][1][4] = true;
			tab[4][2][4] = true;
			tab[4][3][4] = true;
			
		tab[2][1][3] = true;
		tab[2][2][3] = true;
		
			//div
			tab[1][3][3] = true;
			tab[0][3][3] = true;
			
				//div
				tab[0][3][2] = true;
				tab[0][3][1] = true;
				tab[0][3][0] = true;
						
			tab[0][4][3] = true;
			
		tab[2][3][3] = true;
		tab[3][3][3] = true;
		tab[3][3][4] = true;
		Indices x = PathFinder.makeIndices(1,0,0);
		Indices y = PathFinder.makeIndices(0,3,0);
		System.out.println(path.find(tab,x,y)+" "+path.find(tab,y,x));
		boolean[][][] Killer = new boolean[16][16][16];
		for(int i1 = 0; i1 < Killer.length; ++i1)
			for(int i2=0; i2 < Killer[i1].length; ++i2)
				for(int i3=0; i3 < Killer[i1][i2].length; ++i3)
					Killer[i1][i2][i3] = true;
		System.out.println(path.find(Killer,PathFinder.makeIndices(0,0,0),PathFinder.makeIndices(15,15,15)));
	}
}
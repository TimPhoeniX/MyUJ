class Kalkulator implements KalkulatorI
{
	
	
	private AccumulatorI AccA;
	private AccumulatorI AccB;
	
	public void setAccumulatorA(AccumulatorI a)
	{
		AccA=a;
	}
	
	public void setAccumulatorB(AccumulatorI a)
	{
		AccB=a;
	}
	
	public void swapAccumulators()
	{
		AccumulatorI tmp = AccA;
		AccA = AccB;
		AccB = tmp;
	}
	
	public int getA()
	{
		if(AccA == null) return Integer.MIN_VALUE;
		return AccA.getValue();
	}
	
	public int addA(int i)
	{
		if(AccA == null) return Integer.MIN_VALUE;
		AccA.setValue( AccA.getValue()+i );
		return AccA.getValue();
	}
	
	public int subA(int i)
	{
		if(AccA == null) return Integer.MIN_VALUE;
		AccA.setValue( AccA.getValue()-i);
		return AccA.getValue();
	}
	
	public void zeroA()
	{
		if(AccA != null) AccA.setValue(0);
	}
}

class Accumulator implements KalkulatorI.AccumulatorI
	{
		private int Val = 0;
		
		public void setValue(int acc)
		{
			this.Val = acc;
		}
		
		public int getValue()
		{
			return Val;
		}
	}
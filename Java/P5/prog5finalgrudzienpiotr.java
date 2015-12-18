import java.util.Stack;

class RPNLogic implements RPNLogicInterface
{
	private Stack<Boolean> Bools = null;
	private boolean Err = false;
	
	private boolean isAvailable()
	{
		if(this.Bools.empty())
		{
			this.Err = true;
			return false;
		}
		return true;
	}
	
	RPNLogic()
	{
		Bools = new Stack<Boolean>();
	}
	
	public void truee()
	{
		this.Bools.push(new Boolean(true));
	}
	
	public void falsee()
	{
		this.Bools.push(new Boolean(false));
	}
	
	public void and()
	{
		Boolean A = null, B = null;
		if(this.isAvailable())
			A = this.Bools.pop();
		else return;
		if(this.isAvailable())
			B = this.Bools.pop();
		else return;
		this.Bools.push(new Boolean(Boolean.logicalAnd(A,B)));
	}
	
	public void or()
	{
		Boolean A = null, B = null;
		if(this.isAvailable())
			A = this.Bools.pop();
		else return;
		if(this.isAvailable())
			B = this.Bools.pop();
		else return;
		this.Bools.push(new Boolean(Boolean.logicalOr(A,B)));
	}
	
	public void not()
	{
		Boolean A = null;
		if(this.isAvailable())
			A = this.Bools.pop();
		else return;
		this.Bools.push(new Boolean(!A.booleanValue()));
	}
	
	public void vote3()
	{
		int f=0, t=0;
		for(int i = 0; i < 3; ++i)
		{
			if(this.isAvailable())
				if(this.Bools.pop())
					++t;
				else
					++f;
			else return;
		}
		if(t>f) 
			this.Bools.push(new Boolean(true));
		else
			this.Bools.push(new Boolean(false));
	}
	
	public void vote5()
	{
		int f=0, t=0;
		for(int i = 0; i < 5; ++i)
		{
			if(this.isAvailable())
				if(this.Bools.pop())
					++t;
				else
					++f;
			else return;
		}
		if(t>f) 
			this.Bools.push(new Boolean(true));
		else
			this.Bools.push(new Boolean(false));
	}
	
	public void clear()
	{
		this.Bools = new Stack<Boolean>();
		this.Err = false;
	}
	public Boolean result()
	{
		if(this.isAvailable())
			if(this.Err!=true)
				return this.Bools.peek();
		return null;
	}
	}

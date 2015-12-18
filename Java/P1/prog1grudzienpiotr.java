import java.util.Random;

class Start
{
	public static void main(String[] args)
	{
		final int RANGE_MIN=0; final int RANGE_MAX=75;
		int SumOfNumbers=0, RandomNumber=0;
		double SetAverage=0, StandardDeviation=0;
		Random IntRandomizer = new Random();
		for(int SetSizeNumber=100;SetSizeNumber<=10000;SetSizeNumber*=10)
		{
			SumOfNumbers=0; RandomNumber=0; SetAverage=0; StandardDeviation=0;
			for(int i=0;i<SetSizeNumber;++i)
			{
				RandomNumber = RANGE_MIN;
				RandomNumber=IntRandomizer.nextInt(RANGE_MAX-RANGE_MIN+1);
				SumOfNumbers+=RandomNumber;
				StandardDeviation+=(double)Math.pow(RandomNumber,2);
			}
			SetAverage=((double)SumOfNumbers)/SetSizeNumber;
			StandardDeviation=Math.sqrt((StandardDeviation-SetSizeNumber*Math.pow(SetAverage,2))/(SetSizeNumber*(SetSizeNumber-1)));
			System.out.println(SetSizeNumber+" "+SumOfNumbers+" "+SetAverage+" "+StandardDeviation);
		}
	}
}
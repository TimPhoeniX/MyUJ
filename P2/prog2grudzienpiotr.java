import java.util.Random;

class Start
{
	public static void main(String[] args)
	{
		final int RANGE_MIN=1; final int RANGE_MAX=100; final int INTERVAL=4; final int NUM_OF_INTERVALS = 25;
		Random RandomIntGenerator = new Random();
		int RandomizedInt = 0;
		for(int NumberOfRandomInts = 1000; NumberOfRandomInts <= 100000; NumberOfRandomInts*=10)
		{
			int[] IntervalCount = new int[NUM_OF_INTERVALS];
			for(int i = 0; i<NumberOfRandomInts; ++i)
			{
				RandomizedInt = (RANGE_MIN+RandomIntGenerator.nextInt(RANGE_MAX-RANGE_MIN+1));
				++IntervalCount[((RandomizedInt-1)/INTERVAL)];
			}
			int TotalCount = 0;
			double StandardDeviation = 0;
			int MinimumCount = NumberOfRandomInts;
			int MaximumCount = 0;
			for(int j = 0; j<NUM_OF_INTERVALS; ++j)
			{
				if(IntervalCount[j] < MinimumCount) MinimumCount = IntervalCount[j];
				if(IntervalCount[j] > MaximumCount) MaximumCount = IntervalCount[j];
				TotalCount+=IntervalCount[j];
				StandardDeviation+=Math.pow(IntervalCount[j],2);
			}
			double AverageCount = ((double)TotalCount)/NUM_OF_INTERVALS;
			StandardDeviation=Math.sqrt( (StandardDeviation-NUM_OF_INTERVALS*Math.pow(AverageCount,2))/(NUM_OF_INTERVALS*(NUM_OF_INTERVALS-1)) );
			System.out.println(NumberOfRandomInts+" "+AverageCount+" "+StandardDeviation+" "+MaximumCount+" "+MinimumCount);
		}
	}
}
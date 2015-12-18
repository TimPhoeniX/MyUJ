public class Fibonacci {
	public static void main(String[] args) {
		long lo = 1L;
		long hi = 1L;
		final long MAX = 10000000000L;

		System.out.println( "Oto kilka pierwszych wyrazow ciagu Fibonacciego" );

		System.out.println(lo);

		while ( hi < MAX ) {

		System.out.println(hi);
		hi = lo + hi; 
		lo = hi - lo; 
		}
	}
}
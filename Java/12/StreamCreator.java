import java.util.Arrays;
import java.util.stream.Stream;


class StreamCreator {
	
	private static void test( Stream<String> stst ) {
		System.out.println( "-----------------------");
		stst.forEach( System.out::println );
	}
	
	public static void main(String[] args) {
		String[] tablica = "Ala ma kota i psa i jeszcze jednego kota.".split(" ") ;
		
		// tablica -> strumien
		test(  Stream.of( tablica ) );

		test( Stream.of( "Ala", "nie", "ma", "slonia", "i", "jest", "jej", "przykro"));
		
		test( Arrays.stream( tablica, 1, 3 ) );
		
		test( Stream.generate( () -> "To samo w nieskonczonosc").limit(10 ));
	}
}

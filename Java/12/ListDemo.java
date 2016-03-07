import java.util.Arrays;
import java.util.List;

public class ListDemo {
	public static void main(String[] args) {
		final List<String> krasnoludy = Arrays.asList( "Thorin", "Oin", "Glóin", "Balin", 
				"Dwalin", "Fíli", "Kíli", "Dori", "Nori", "Ori", "Bifur", "Bofur", "Bombur" );
		
		// Dla krasnoludow : forEach( Consumer< ? super String > )
	
		krasnoludy.forEach( name -> System.out.println( name ) );
		krasnoludy.forEach( System.out::println );
	}
}

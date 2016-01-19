import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class ImagesWebTester {

	private ImagesWebFinderInterface iwfi;
	private Map<String, Set<String>> result;

	@Before
	public void start() {
		iwfi = new ImagesWebFinder();
		PMO_SystemOutRedirect.startRedirectionToNull();
	}

	private void startTest(String url) {
		try {
			result = iwfi.getImages(url);
			assertNotNull( "Nie bylem az tak paskudny, nie ma powodu do pojawienia sie NULL", result );
		} catch (Exception e) {
			PMO_SystemOutRedirect.returnToStandardStream();
			fail("W trakcie analizy strony o adresie " + url
					+ " pojawil sie wyjatek" + e.getMessage());
		} finally {
			PMO_SystemOutRedirect.returnToStandardStream();
		}
		System.err.println(this.result);
	}

	private void testKeys( Set<String> keys ) {
		for ( String key : keys ) {
			assertTrue( "Wynik powinien zawierac typ " + key, result.containsKey( key ));
		}
	}
	
	private void testKey( String key, Set<String> values ) {
		Set<String> resultV = result.get(key);
		assertNotNull( "Klucz jest poprawny, powinny byc wartosci", resultV );
		assertEquals( "Dla klucza " + key + " powinno byc " + values.size() + " wartosci w mapie",
				values.size(), resultV.size() );
		for ( String value : values ) {
			assertTrue( "Wynik powinien zawierac zrodlo " + value, resultV.contains( value ));
		}
	}
	
	@Test
	public void simpleTest() {
		startTest( "http://149.156.41.217/Piotr.Oramus/dydaktyka/Zadanie13/h1.html"); 
		
		testKeys( new HashSet<String>() {{ add( "gif"); add( "png"); }} );
		testKey( "gif", new HashSet<String>() {{ add("allOK1.gif" ); }} );
		testKey( "png", new HashSet<String>() {{ add("allOK1.png" ); add("allOK2.png"); }} );
	}

	@Test
	public void simpleWithPathsTest() {
		startTest( "http://149.156.41.217/Piotr.Oramus/dydaktyka/Zadanie13/h2.html"); 
		
		testKeys( new HashSet<String>() {{ add( "gif"); add( "png"); }} );
		testKey( "gif", new HashSet<String>() {{ add("allOK1.gif" ); }} );
		testKey( "png", new HashSet<String>() {{ add("images/allOK1.png" ); add("images/allOK2.png"); }} );
	}
	
	@Test
	public void notSoSimpleTest() {
		startTest( "http://149.156.41.217/Piotr.Oramus/dydaktyka/Zadanie13/h3.html"); 
		
		testKeys( new HashSet<String>() {{ add( "gif"); add( "png"); }} );
		testKey( "gif", new HashSet<String>() {{ add("allOK1.gif" ); }} );
		testKey( "png", new HashSet<String>() {{ add("images/allOK1.png" ); add("images/allOK2.png"); }} );
	}
	

}

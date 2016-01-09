import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.Before;
import org.junit.Test;


public class PMO_Test {
	RoadsInterface ri;
	
	@Before 
	public void ini() {
		ri = new Roads();
	}
	
	@Test
	public void test1A() {
		// 1 -> 5 -> 3 -> 7 -> 9
		List<Integer> li = new ArrayList<>( Arrays.asList( new Integer[] { 1, 5, 3, 7, 9 } ) ); 
		ri.addRoad( li );
		
		assertTrue( "Droga 1-5 powinna byc dostepna", ri.isPassage( 1, 5 ) );
		assertTrue( "Droga 1-3 powinna byc dostepna", ri.isPassage( 1, 3 ) );
		assertTrue( "Droga 3-9 powinna byc dostepna", ri.isPassage( 3, 9 ) );
		assertTrue( "Droga 1-9 powinna byc dostepna", ri.isPassage( 1, 9 ) );
	}

	@Test
	public void test1B() {
		// 1 -> 5 -> 3 -> 7 -> 9
		List<Integer> li = new ArrayList<>( Arrays.asList( new Integer[] { 1, 5, 3, 7, 9 } ) ); 
		ri.addRoad( li );
		
		assertFalse( "Drogi 2-4 nie ma, bo nie ma takich lokalizacji", ri.isPassage( 2, 4 ) );
		assertFalse( "Drogi 9-1 nie ma, jest z 1 do 9", ri.isPassage( 9, 1 ) );
	}
	
	
	@Test
	public void test2A() {
		// 1 -> 5 -X- 3 -> 7 -> 9
		// 1 -> 2 --> 3
		List<Integer> li = new ArrayList<>( Arrays.asList( new Integer[] { 1, 5, 3, 7, 9 } ) ); 
		List<Integer> li2 = new ArrayList<>( Arrays.asList( new Integer[] { 1, 2, 3 } ) ); 
		ri.addRoad( li );
		ri.roadWorks( 5, 3 );
		ri.addRoad( li2 );
		
		assertTrue( "Droga 1-3 powinna byc dostepna", ri.isPassage( 1, 3 ) );
		assertTrue( "Droga 1-9 powinna byc dostepna", ri.isPassage( 1, 9 ) );
		assertTrue( "Droga 2-3 powinna byc dostepna", ri.isPassage( 2, 3 ) );
		assertTrue( "Droga 1-2 powinna byc dostepna", ri.isPassage( 1, 3 ) );
	}

	@Test
	public void test2B() {
		// 1 -> 5 -X- 3 -> 7 -> 9
		// 1 -> 2 --> 3
		List<Integer> li = new ArrayList<>( Arrays.asList( new Integer[] { 1, 5, 3, 7, 9 } ) ); 
		List<Integer> li2 = new ArrayList<>( Arrays.asList( new Integer[] { 1, 2, 3 } ) ); 
		ri.addRoad( li );
		ri.roadWorks( 5, 3 );
		ri.addRoad( li2 );
		ri.isPassage(8,21);
		assertFalse( "Droga 5-3 nie jest dostepna",   ri.isPassage( 5, 3 ) );		
		assertFalse( "Droga 5-9 nie jest dostepna",   ri.isPassage( 5, 9 ) );
	}

}

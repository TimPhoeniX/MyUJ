import static org.junit.Assert.*;
import static org.junit.Assume.*;

import org.junit.Before;
import org.junit.Test;

public class KalkulatorTest
{
	private KalkulatorI ki;
	private KalkulatorI.AccumulatorI acci;
	private KalkulatorI.AccumulatorI bacci;
	
	public KalkulatorTest()
	{
	}
	
	private void AddingAccumulatorA()
	{
		assertTrue("getA nie zwraca oczekiwanej wartosci", ki.getA() == Integer.MIN_VALUE);
		ki.setAccumulatorA(acci);
		assertFalse("setAccumulatorA nie ustawia poprawnie akumulatora A", ki.getA()==Integer.MIN_VALUE);
	}
	
	private void AddingAccumulatorB()
	{
		assertTrue("getA nie zwraca oczekiwanej wartosci", ki.getA() == Integer.MIN_VALUE);
		ki.setAccumulatorB(bacci);
		assertEquals("setAccumulatorB() nie powinien ustawiac akumulatora A",Integer.MIN_VALUE, ki.getA());
	}
	
	private void SetAccumulators()
	{
		ki.setAccumulatorA(acci);
		ki.setAccumulatorB(bacci);
	}
	
	@Before
	public void createCalculator()
	{
		ki = new Kalkulator();
		acci = new Accumulator();
		bacci = new Accumulator();
	}
	
	@Test
	public void AccgetValue()
	{
		assertEquals("Domyslna wartosc akumulator nie wynosi 0, badz getValue() nie zwraca aktualnej zawartosci akumulatora", 0, acci.getValue() );
	}
	
	@Test
	public void AccsetValue()
	{
		acci.setValue(9);
		assertEquals("setValue(9) powinno ustawic zawartosci akumulatora na 9, badz getValue() nie zwraca aktualnej zawartosci akumulatora", 9, acci.getValue() );
	}
	
	@Test
	public void NoAccumulator_getA()
	{
		assertTrue("getA() nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.getA()==Integer.MIN_VALUE);
	}

	@Test
	public void NoAccumulator_addA0()
	{
		assertTrue("addA(0) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.addA(0)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_subA0()
	{
		assertTrue("subA(0) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.subA(0)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_addA2()
	{
		assertTrue("addA(2) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.addA(2)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_subA2()
	{
		assertTrue("subA(2) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.subA(2)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_addA3()
	{
		assertTrue("addA(-2) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.addA(-2)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_subA3()
	{
		assertTrue("subA(-2) nie zwraca Integer.MIN_VALUE przy nieustawionym akumulatorze", ki.subA(-2)==Integer.MIN_VALUE);
	}
	
	@Test
	public void NoAccumulator_getAnull()
	{
		try
		{
			ki.getA();
		}
		catch(Exception e)
		{
			fail("getA() rzuca wyjatek przy nieustawionym akumulatorze A");
		}
	}
	
	@Test
	public void NoAccumulator_addAnull()
	{
		try
		{
			ki.addA(1);
		}
		catch(Exception e)
		{
			fail("addA() rzuca wyjatek przy nieustawionym akumulatorze A");
		}
	}
	
	@Test
	public void NoAccumulator_subAnull()
	{
		try
		{
			ki.subA(1);
		}
		catch(Exception e)
		{
			fail("subA() rzuca wyjatek przy nieustawionym akumulatorze A");
		}
	}
	
	@Test
	public void NoAccumulator_zeroAnull()
	{
		try
		{
			ki.zeroA();
		}
		catch(Exception e)
		{
			fail("zeroA() rzuca wyjatek przy nieustawionym akumulatorze A");
		}
	}
	
	@Test
	public void NoAccumulator_swapnull()
	{
		try
		{
			ki.swapAccumulators();
		}
		catch(Exception e)
		{
			fail("swapAccumulators() rzuca wyjatek przy nieustawionych akumulatorach");
		}
	}
	
	@Test
	public void NoAccumulator_setAnull()
	{
		try
		{
			ki.setAccumulatorA(acci);
		}
		catch(Exception e)
		{
			fail("setAccumulatorA() rzuca wyjatek przy ustawianiu akumulatora A");
		}
	}
	
	@Test
	public void NoAccumulator_setBnull()
	{
		try
		{
			ki.setAccumulatorB(bacci);
		}
		catch(Exception e)
		{
			fail("setAccumulatorB() rzuca wyjatek przy ustawianiu akumulatora B");
		}
	}
	
	@Test
	public void NoAccumulator_swapAnull()
	{
		AddingAccumulatorA();
		try
		{
			ki.swapAccumulators();
		}
		catch(Exception e)
		{
			fail("swapAccumulators() rzuca wyjatek przy nieustawionym akumulatorze B");
		}
	}
	
	@Test
	public void NoAccumulator_swapBnull()
	{
		AddingAccumulatorB();
		try
		{
			ki.swapAccumulators();
		}
		catch(Exception e)
		{
			fail("swapAccumulators() rzuca wyjatek przy nieustawionym akumulatorze A");
		}
	}
	
	@Test
	public void Addition1()
	{
		ki.setAccumulatorA(acci);
		assertEquals("addA(5) nie zwraca oczekiwanej zawartosci akumulatora A", 5, ki.addA(5) );
	}
	
	@Test
	public void Addition2()
	{
		AddingAccumulatorA();
		ki.addA(5);
		assertEquals("getA() nie zwraca oczekiwanej zawartosci akumulatora A po wykonaniu addA(5)", 5, ki.getA() );
	}
	
	@Test
	public void Addition3()
	{
		ki.setAccumulatorA(acci);
		ki.addA(5);
		assertEquals("Kalkulator metoda addA(5) zle zmienia zawartosc akumulatora A, badz zmienia zawartosc innego akumulatora niz podanego przez setAccumulatorA()", 5, acci.getValue() );
	}
	
	@Test
	public void MutlipleAdditions1()
	{
		AddingAccumulatorA();
		ki.addA(4);
		assertEquals("addA(6) wykonany po add(4) nie zwraca oczekiwanej zawartosci akumulatora A", 10, ki.addA(6) );
	}
	
	@Test
	public void MutlipleAdditions2()
	{
		AddingAccumulatorA();
		ki.addA(4);
		ki.addA(6);
		assertEquals("addA(4) i addA(6) nie dodaja 10 do akumulatora A", 10, ki.getA() );
	}
	
	@Test
	public void NAddition1()
	{
		AddingAccumulatorA();
		assertEquals("addA(-5) nie zwraca oczekiwanej zawartosci akumulatora A", -5 , ki.addA(-5) );
	}
	
	@Test
	public void NAddition2()
	{
		AddingAccumulatorA();
		ki.addA(-5);
		assertEquals("getA() nie zwraca oczekiwanej zawartosci akumulatora A po wykonaniu addA(-5)", -5, ki.getA() );
}
	
	@Test
	public void NAddition3()
	{
		ki.setAccumulatorA(acci);
		ki.addA(-5);
		assertEquals("Kalkulator metoda addA(-5) zle zmienia zawartosc akumulatora A, badz zmienia zawartosc innego akumulatora niz podanego przez setAccumulatorA()", -5, acci.getValue() );
	}
	
	@Test
	public void NMutlipleAdditions1()
	{
		AddingAccumulatorA();
		ki.addA(-4);
		assertEquals("addA(-6) wykonany po add(-4) nie zwraca oczekiwanej zawartosci akumulatora A", -10, ki.addA(-6) );
		assertEquals("addA(-4) i addA(-6) nie dodaja -10 do akumulatora A badz getA() zle zwraca po wykonaniu poprzednich metod", -10, ki.getA() );
	}
	
	@Test
	public void NMutlipleAdditions2()
	{
		AddingAccumulatorA();
		ki.addA(-4);
		ki.addA(-6);
		assertEquals("addA(-4) i addA(-6) nie dodaja -10 do akumulatora A badz getA() zle zwraca po wykonaniu poprzednich metod", -10, ki.getA() );
	}
	
	@Test
	public void Substraction1()
	{
		AddingAccumulatorA();
		assertEquals("subA(5) nie zwraca oczekiwanej zawartosci akumulatora A", -5, ki.subA(5) );
	}
	
	@Test
	public void Substraction2()
	{
		AddingAccumulatorA();
		ki.subA(5);
		assertEquals("getA() nie zwraca oczekiwanej zawartosci akumulatora A po wykonaniu subA(5)", -5, ki.getA() );
	}
	
	@Test
	public void Substraction3()
	{
		ki.setAccumulatorA(acci);
		ki.subA(5);
		assertEquals("Kalkulator metoda subA(5) zle zmienia zawartosc akumulatora A, badz zmienia zawartosc innego akumulatora niz podanego przez setAccumulatorA()", -5, acci.getValue() );
	}
	
	@Test
	public void MutlipleSubstractions1()
	{
		AddingAccumulatorA();
		ki.subA(4);
		assertEquals("subA(6) wykonany po subA(4) nie zwraca oczekiwanej zawartosci akumulatora A", -10, ki.subA(6) );
	}
	
	@Test
	public void MutlipleSubstractions2()
	{
		AddingAccumulatorA();
		ki.subA(4);
		ki.subA(6);
		assertEquals("subA(4) i subA(6) nie odejmuja 10 od akumulatora A badz getA() zle zwraca po wykonaniu poprzednich metod",-10, ki.getA() );
	}
	
	@Test
	public void NSubstraction1()
	{
		AddingAccumulatorA();
		assertEquals("subA(-5) nie zwraca oczekiwanej zawartosci od akumulatora A", 5, ki.subA(-5) );
	}
	
	@Test
	public void NSubstraction2()
	{
		AddingAccumulatorA();
		ki.subA(-5);
		assertEquals("getA() nie zwraca oczekiwanej zawartosci akumulatora A po wykonaniu subA(-5)", 5, ki.getA() );
	}
	
	@Test
	public void NSubstraction3()
	{
		ki.setAccumulatorA(acci);
		ki.subA(-5);
		assertEquals("Kalkulator metoda subA(-5) zle zmienia zawartosc akumulatora A, badz zmienia zawartosc innego akumulatora niz podanego przez setAccumulatorA()", 5, acci.getValue() );
	}
	
	@Test
	public void NMutlipleSubstractions1()
	{
		AddingAccumulatorA();
		ki.subA(-4);
		assertEquals("subA(-6) wykonany po subA(4) nie zwraca oczekiwanej zawartosci akumulatora A", 10, ki.subA(-6) );
	}
	
	@Test
	public void NMutlipleSubstractions2()
	{
		AddingAccumulatorA();
		ki.subA(-4);
		ki.subA(-6);
		assertEquals("subA(-4) i subA(-6) nie odejmuja -10 od akumulatora A, badz getA() zle zwraca po wykonaniu poprzednich metod", 10, ki.getA() );;
	}
	
	@Test
	public void NonChangingOp1()
	{
		AddingAccumulatorA();
		int tmp = ki.getA();
		ki.addA(3);
		ki.subA(3);
		assertEquals("addA(3) i subA(3) nie powinny zmienic zawartosci akumulatora A, badz getA() zle zwraca po wykonaniu poprzednich metod", tmp, ki.getA() );
	}
	
	@Test
	public void NonChangingOp2()
	{
		AddingAccumulatorA();
		int tmp = ki.getA();
		ki.addA(-3);
		ki.subA(-3);
		assertEquals("addA(-3) i subA(-3) nie powinny zmienic zawartosci akumulatora A, badz getA() zle zwraca po wykonaniu poprzednich metod", tmp, ki.getA() );
	}
	
	@Test
	public void NonChangingOp3()
	{
		AddingAccumulatorA();
		int tmp = ki.getA();
		ki.addA(3);
		ki.addA(-3);
		assertEquals("addA(3) i addA(-3) nie powinny zmienic zawartosci akumulatora A, badz getA() zle zwraca po wykonaniu poprzednich metod", tmp, ki.getA() );
	}
	
	@Test
	public void NonChangingOp4()
	{
		AddingAccumulatorA();
		int tmp = ki.getA();
		ki.subA(3);
		ki.subA(-3);
		assertEquals("subA(3) i subA(-3) nie powinny zmienic zawartosci akumulatora A, badz getA() zle zwraca po wykonaniu poprzednich metod", tmp, ki.getA() );
	}
	
	@Test 
	public void ZeroingA1()
	{
		AddingAccumulatorA();
		acci.setValue(123);
		ki.zeroA();
		assertEquals("zeroA() nie zeruje akumulatora A", 0, acci.getValue());
	}
	
	@Test 
	public void ZeroingA2()
	{
		AddingAccumulatorA();
		acci.setValue(123);
		ki.zeroA();
		assertEquals("zeroA() nie zeruje akumulatora A, badz getA() zle zwraca po wykonaniu poprzedniej metody", 0, ki.getA() );
	}
	
	@Test 
	public void BgetA()
	{
		SetAccumulators();
		ki.addA(999);
		assertEquals("addA() nie powinien dodawac liczb do akumulatora B", 0, bacci.getValue() );
	}
	
	@Test 
	public void BaddA()
	{
		SetAccumulators();
		ki.addA(999);
		assertEquals("addA() nie powinien dodawac liczb do akumulatora B", 0, bacci.getValue() );
	}
	
	@Test
	public void BsubA()
	{
		SetAccumulators();
		ki.subA(999);
		assertEquals("subA() nie powinien odejmowac liczb od akumulatora B", 0, bacci.getValue() );
	}
	
	@Test
	public void BzeroA()
	{
		SetAccumulators();
		acci.setValue(44);
		bacci.setValue(44);
		ki.zeroA();
		assertEquals("zeroA() nie powinien zerowac akumulatora B", 44, bacci.getValue() );
	}
	
	@Test
	public void Swap1()
	{
		AddingAccumulatorA();
		acci.setValue(7);
		ki.swapAccumulators();
		assertEquals("swapAccumulators() nie zamienia akumulatora A na B przy braku akumulatora B", Integer.MIN_VALUE, ki.getA());
	}
	
	@Test
	public void Swap2()
	{
		acci.setValue(7);
		AddingAccumulatorA();
		ki.swapAccumulators();
		ki.swapAccumulators();
		assertEquals("Po dwukrotnym swapAccumulators akumulator A powinien byc znow akumulatorem A i nie powinien miec zmienionej wartosci", 7, ki.getA());
	}
	
	@Test
	public void Swap3()
	{
		AddingAccumulatorB();
		ki.swapAccumulators();
		assertEquals("setAccumulatorB() nie ustawil akumulatora B badz swapAccumulators() nie zamienil akumulatora B na kalkulator A przy nieustawionym A", 0, ki.getA());
	}
	
	@Test
	public void Swap4()
	{
		SetAccumulators();
		bacci.setValue(341);
		ki.swapAccumulators();
		assertEquals("setAccumulatorB() nie ustawil akumulatora B badz swapAccumulators() nie zamienil akumulatora B na kalkulator A", 341, ki.getA());
	}
	
	@Test
	public void resetA1()
	{
		AddingAccumulatorA();
		ki.setAccumulatorA(null);
		assertEquals("setAccumulatorA(null) nie usuwa akumulatora A",Integer.MIN_VALUE,ki.getA());
	}
	
	@Test
	public void resetA2()
	{
		AddingAccumulatorA();
		ki.addA(5);
		ki.setAccumulatorA(bacci);
		assertEquals("setAccumulatorA() nie ustawia akumulatora A na inny, jesli zostal wczesniej ustawiony",0,ki.getA());
	}
	
	@Test
	public void resetB1()
	{
		AddingAccumulatorB();
		ki.setAccumulatorB(null);
		ki.swapAccumulators();
		assertEquals("setAccumulatorB(null) nie usuwa akumulatora B",Integer.MIN_VALUE,ki.getA());
	}
	
	@Test
	public void resetB2()
	{
		AddingAccumulatorB();
		bacci.setValue(52);
		ki.setAccumulatorB(acci);
		ki.swapAccumulators();
		assertEquals("setAccumulatorA() nie ustawia akumulatora A na inny, jesli zostal wczesniej ustawiony",0,ki.getA());
	}
	
}
// javac8 -cp junit-4.12.jar:. KalkulatorTest.java
// java8 -cp junit-4.12.jar:hamcrest-core-1.3.jar:. org.junit.runner.JUnitCore KalkulatorTest
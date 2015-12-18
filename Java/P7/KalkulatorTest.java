
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result; 
import org.junit.runner.notification.Failure;
import static org.hamcrest.CoreMatchers.*;

public class KalkulatorTest {

private KalkulatorI a;
private KalkulatorI.AccumulatorI b;
private KalkulatorI.AccumulatorI c;
private KalkulatorI.AccumulatorI d;
private Integer argumentNull = null;
private int argumentInt = 2;
private int argumentInt2 = 3;
private double argumentFloat = 3.14;

@Test
public void ZwracaniegetA(){
  a = new Kalkulator();
  assertEquals("getA zwraca zla wartosc gdy nie ma akumulatora", Integer.MIN_VALUE, a.getA());
}

@Test	
public void ZwracaniegetABrakAkumulatora(){
  try{
    a = new Kalkulator();
    a.getA();
}
catch(NullPointerException e){
  fail("Nie zabezpieczony getA() przed działaniem przed ustawieniem akumulatora");
}
}

@Test(expected = NullPointerException.class)
public void DodawanieNaNiczym(){
  a.addA(argumentInt);
}

@Test
public void ZwracanieaddA(){
  a = new Kalkulator();
  assertEquals("addA zwraca zla wartosc gdy nie ma akumulatora", Integer.MIN_VALUE, a.addA(argumentInt));
}

@Test
public void RobotaSetAccumulatorA(){
 a = new Kalkulator();
 b = new Accumulator();
  a.setAccumulatorA(b);
  assertEquals("setAccumulatorA nic nie zrobil", a.getA(), b.getValue());
}

@Test
public void RobotaSetAccumulatorA2(){
 a = new Kalkulator();
 b = new Accumulator();
  a.setAccumulatorB(b);
  assertNotEquals("setAccumulatorA robi to co set", a.getA() , b.getValue());
}


@Test
public void RobotaSetAccumulatorB(){
 a = new Kalkulator();
 b = new Accumulator();
 a.setAccumulatorB(b);
 assertNotEquals("setAccumulatorB robi nie to co trzeba", a.getA(), b.getValue());
}

@Test
public void RobotaSwapAccumulators(){
 a = new Kalkulator();
 b = new Accumulator();
 c = new Accumulator();
 a.setAccumulatorA(b);
 a.setAccumulatorB(c);
 a.addA(argumentInt);
 a.swapAccumulators();
 a.addA(argumentInt2);
 a.swapAccumulators();
 assertNotEquals("swapAccumulators robi nie tak jak trzeba", c.getValue(), a.getA());
}

@Test
public void ZwracaniezeroA(){
  a = new Kalkulator();
  a.setAccumulatorA(b);
  a.zeroA();
  assertNotEquals("zeroA zwraca zla wartosc po wstawieniu akumulatora", 0, a.getA());
  a.addA(argumentInt);
 }

 @Test
public void ZwracaniezeroAPoAddA(){
  a = new Kalkulator();
  a.setAccumulatorA(b);
  a.addA(argumentInt);
  a.zeroA();
  assertNotEquals("zeroA zwraca zla wartosc po dodawaniu", 0, a.getA());
 }
 
 
 @Test
public void ZwracaniezeroAPoSubA(){
  a = new Kalkulator();
  a.setAccumulatorA(b);
  a.subA(argumentInt);
  a.zeroA();
  assertNotEquals("zeroA zwraca zla wartosc po odejmowaniu", 0, a.getA());
}

@Test(expected = NullPointerException.class)
public void ZerowanieBezAkumulatora(){
a.zeroA();
}


@Test
public void ZerowanieNaNiczym(){
try{
  a = new Kalkulator();
  a.zeroA();
   }
catch (NullPointerException e){ 
  fail("Nie zabezpieczony zeroA() przed działaniem przed ustawieniem akumulatora");
  }
}

@Test
public void ZwracaniesubA(){
  a = new Kalkulator();
  b = new Accumulator();
  a.setAccumulatorA(b);
  assertEquals("subA zwraca zla wartosc", -2, a.subA(argumentInt));
}

@Test
public void ZleDzialanieaddA(){
  a = new Kalkulator();
  b = new Accumulator();
  a.setAccumulatorA(b);
  assertEquals("addA zwraca zla wartosc", 2, a.addA(argumentInt));
}

@Test
public void OdejmowanieNaNiczym(){
try{
  a = new Kalkulator();
  a.subA(argumentInt); 
   }
catch (NullPointerException e){ 
  fail("Nie zabezpieczony subA() przed działaniem przed ustawieniem akumulatora");
  }
}

@Test
public void ZleDzialaniegetA(){
  a = new Kalkulator();
  a.setAccumulatorA(b);
  assertEquals("getA zwraca zla wartosc po wstawieniu akumulatora", a.addA(argumentInt), a.getA());
}

@Test
public void WiecejDzialan(){
  a = new Kalkulator();
  c = new Accumulator();
  try{
    a.setAccumulatorA(c);
    a.addA(2);
    a.addA(5);
    a.addA(15);
    a.subA(2);
    assertEquals("Zla wartosc przy wiekszej ilosci dzialan", a.getA(), 20);
 }
  catch ( Exception e ){ 
  fail("wystopil nieoczekiwany wyjatek");
  }
}

@Test
public void ZlyAkumulatorToPewnieStatic(){
  b = new Accumulator();
  try{
    b.setValue(argumentInt);
  }
  catch( AssertionError e ){
    fail("Cos nie tak z akumulatorem, zapewne masz tam przeszkadzającego statica");
  }
}

@Test
public void BrakAkumulatora(){
 try{
  d = new Accumulator();
    }
  catch( NullPointerException e ){
  fail("Brak akumulatora");
    }
}

}
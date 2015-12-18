import java.lang.reflect.*;

abstract class Osoba {
  String imie;
  String nazwisko;
  String numerPesel = "1234567890";
  
  public String toString(){
     return "Oto osoba: " + imie + " " + nazwisko + " " + numerPesel;
  }
  public String podajPesel() {
     return numerPesel;
  }
}

class Pracownik extends Osoba {
   public Pracownik() { 
      imie = "John"; nazwisko = "Doe"; 
   }
   public Pracownik( String i, String n ) { 
      imie = i; nazwisko = n; 
      numerPesel = "987654321234"; 
   }
   public Pracownik( String i, String n, String pesel ) { 
      imie = i; nazwisko = n; 
      numerPesel = pesel;
   }
}

class Prawnik extends Osoba {
   public Prawnik() { 
      imie = "John"; nazwisko = "Doe"; 
   }
   public Prawnik( String i, String n ) { 
      imie = i; nazwisko = n; 
      numerPesel = "987654321234"; 
   }
   public Prawnik( String i, String n, String pesel ) { 
      imie = i; nazwisko = n; 
      numerPesel = pesel;
   }
  public String podajPesel() {
     return "To sa dane osobowe, wiec ich nie podam.";
  }
}

class Start {
  private static void test( String nazwaKlasy ) throws Exception {
  
     System.out.println( "----------- NazwaKlasy to " + nazwaKlasy );
   
     System.out.println( "*** Podejscie I" );
     Class<?> c = Class.forName( nazwaKlasy );  
     System.out.println( c );        // typ znany jest dopiero w trakcie pracy programu
     System.out.println( c.newInstance() ); 

     System.out.println( "*** Podejscie II" );
     Class<? extends Osoba> cOsoba = Class.forName( nazwaKlasy ).asSubclass( Osoba.class );
     Osoba o = cOsoba.newInstance();
     System.out.println( cOsoba );        // o typie juz cos wiemy w trakcie kompilacji
     System.out.println( o );
     
     System.out.println( "*** Podejscie III" );
     
     // poszukajmy wszystkich konstruktorow
     
     System.out.println( "------ Konstruktory -------" );
     Constructor[] consts = cOsoba.getConstructors();
     
     for ( Constructor cnst : consts ) {
         System.out.println( cnst );
     }
     
     // wybieramy jeden konkretny konstruktor
     
     System.out.println( "------ Konstruktor ( 3 x String ) ------- ");
     Constructor<? extends Osoba> c3str = cOsoba.getConstructor( java.lang.String.class, 
        java.lang.String.class, java.lang.String.class );
     System.out.println( c3str );
     
     // tworzymy obiekt
     Osoba kowalski = c3str.newInstance( "Jan", "Kowalski", "123-123-123-12" );
     
     System.out.println( kowalski );
     
     // wybieramy metode, ktora chcemy uruchomic
     Method me = cOsoba.getMethod( "podajPesel", (java.lang.Class<?>[] )null );
     System.out.println( "Metoda zwraca : " + me.getReturnType() );
     System.out.println( "Ruchamiamy metode na rzecz pewnego obiektu: " + me.invoke( kowalski ) );  
  }
  
  public static void main( String[] argv ) throws Exception {
      test( "Pracownik" );
      test( "Prawnik" );
  }
}
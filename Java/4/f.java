class Pole {
	protected double pole;

	public Pole( double pole_ini ) {
	   pole = pole_ini;
	}

	public String toString() {
	   return new String( "Tu Pole: pole = " + pole ) ;
	} 
}

class PoleExt extends Pole {
	protected double pole; // ukrycie pola z nadklasy

	public PoleExt( double pole_ini ) {
	   super( pole_ini / 2.0 ); // tu jest dzielenie przez 2 !!!
	   pole = pole_ini;         // operacja na polu lokalnym
	}

	public String toString() {
	   return new String( "Tu PoleExt: pole = " + pole + " oraz super.pole = " + super.pole ) ;
	} 
}

class Start {
	public static void main( String[] argv ) {
		Pole p = new Pole( 1.0 );
		System.out.println( "Oto Pole " + p );
		PoleExt pe = new PoleExt( 2.0 );
		System.out.println( "Oto PoleExt " + pe );
	}
}
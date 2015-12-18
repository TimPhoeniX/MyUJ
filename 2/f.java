class Simple {
	public double x;
	public String toString() {
		String s = "Oto ja: metoda toString() klasy Simple. Chce tylko powiedziec, ze x = " + x;
		return s;
	}
}

class Start {
	public static void main( String[] argv ) {
		Simple[]  simple_array = new Simple[1000];
	}
}
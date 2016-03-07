import java.util.function.Supplier;

class Closure {

	private static void doSth(Supplier<String> s) {
		System.out.println(s.get());
	}

	public static void main(String[] args) {
		int i = 123;
		for ( ; i < 321; i++ ) // mina
		doSth(() -> "a" + i);

		for (String arg : args)
			doSth(arg::toString);
	}
}

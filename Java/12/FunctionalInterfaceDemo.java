import java.util.function.IntConsumer;

// http://docs.oracle.com/javase/8/docs/api/java/util/function

// IntConsumer { void accept(int value); }

public class FunctionalInterfaceDemo {

	private static void accept(IntConsumer ic) {
		ic.accept(10);
	}

	static class Standard implements IntConsumer {
		public void accept(int value) {
			System.out.println("Tu Standard::accept(int)");
			System.out.println(value);
		}
	}
	
	static class Standard2 {
		public Standard2(int value ) {
			System.out.println("Tu Standard2(int) " + value );
		}		
	}

	public static void main(String[] args) {

		accept(new Standard());

		accept(new IntConsumer() {

			@Override
			public void accept(int value) {
				System.out.println(value);
			}
		});

		accept((int value) -> System.out.println(value));
		accept((value) -> System.out.println(value));
		accept(value -> System.out.println(value));

		Standard s = new Standard();
		accept(s::accept);

		accept(Standard2::new);
	}

}

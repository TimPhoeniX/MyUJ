import java.util.Arrays;
import java.util.stream.Stream;

class StreamMethods {

	private static void test(Stream<String> stst) {
		System.out.println("-----------------------");
		stst.forEach(System.out::println);
	}

	public static void main(String[] args) {
		String[] tablica = "Ala ma kota i psa i jeszcze jednego kota."
				.split(" ");
		Stream<String> stst = Stream.of(tablica);

		test(stst.filter(s -> s.matches("^j.+"))); // fitrowanie slowa
													// zaczynajace sie od j

		int[] tablicaI = new int[] { 1, 2, 3, 4, 5, 6, 7 };

		// przetwarzenie 1:1
		test(Arrays.stream(tablicaI, 0, tablicaI.length).mapToObj(
				Integer::toString));

		// przetwarzanie 1:N
		test(Arrays.stream(tablicaI, 0, tablicaI.length)
				.mapToObj(Integer::toString)
				.flatMap(s -> Stream.of(new String[] { s, ">" + s, "<" + s })));

	}
}

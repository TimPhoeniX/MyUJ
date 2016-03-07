import java.util.ArrayList;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Random;
import java.util.function.Function;
import java.util.function.Predicate;

public class SimpleShow {

	private static List<Integer> li = new ArrayList<>();

	private static void init() {
		Random r = new Random();
		for (int i = 0; i < 10000000; i++)
			li.add(r.nextInt());
	}

	private static void show(Object[] il) {
		for (Object i : il)
			System.out.println((Integer) i);
	}

	private static Predicate<Integer> higherOrderFunction(int limit) {
		return t -> t > limit;
	}

	private static final Function<Integer, Predicate<Integer>> lambdaFromLambda = limit -> t -> t > limit;

	public static void main(String[] args) {
		init();

		System.out.println("Ile mamy: " + li.stream().count());

		// ile jest mniejszych od 0
		System.out.println("Ile mamy mniejszych od 0: "
				+ li.stream().filter(li -> li < 0).count());
		// show( li.stream().filter( li -> li < 0 ).toArray() );

		// ile wiekszych od Integer.MAX_VALUE / 2
		System.out.println("Ile mamy wiekszych od polowy wartosci MAX: "
				+ li.stream().filter(li -> li > (Integer.MAX_VALUE / 2))
						.count());

		// ile wiekszych od 1000
		System.out.println("Ile mamy wiekszych od 1000: "
				+ li.stream().filter(higherOrderFunction(1000)).count());

		// ile wiekszych od 2000
		System.out.println("Ile mamy wiekszych od 2000: "
				+ li.stream().filter(lambdaFromLambda.apply(2000)).count());

		// minimum
		System.out.println("Minimum: "
				+ li.stream().min((l1, l2) -> l1.compareTo(l2)).get());

		IntSummaryStatistics stats = li.stream().mapToInt(i -> i)
				.summaryStatistics();

		System.out.println("Max : " + stats.getMax());
		System.out.println("Min : " + stats.getMin());
		System.out.println("Sum : " + stats.getSum());
		System.out.println("Avg : " + stats.getAverage());
	}

}

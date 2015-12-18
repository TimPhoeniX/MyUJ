import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

 class Start {
	static class Zadanie implements Callable<String> {
		private int length;

		public Zadanie(int length) {
			this.length = length;
		}

		@Override
		public String call() throws Exception {
			String result = "";

			long t0 = System.currentTimeMillis();

			for (int i = 0; i < length; i++) {
				result += "x";
			}

			return "Length: " + result.length() + " required time: "
					+ ((System.currentTimeMillis() - t0)) + " msec.";
		}

	}

	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();

		List<Callable<String>> tasks = new ArrayList<Callable<String>>();

		tasks.add(new Zadanie(1000));
		tasks.add(new Zadanie(2000));
		tasks.add(new Zadanie(5000));
		tasks.add(new Zadanie(10000));
		tasks.add(new Zadanie(25000));
		tasks.add(new Zadanie(50000));
		tasks.add(new Zadanie(100000));
		tasks.add(new Zadanie(120000));
		tasks.add(new Zadanie(140000));
		tasks.add(new Zadanie(160000));

		try {
			List<Future<String>> results = exec.invokeAll(tasks);
			for (Future<String> result : results) {
				System.out.println(result.get());
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		
		exec.shutdown();
	}

}
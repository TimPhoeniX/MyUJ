import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.Logger;

class LoggerAndFiles {
	public static void main(String[] args) throws SecurityException,
			IOException {
		Logger log = Logger.getLogger("LoggerAndFiles");
		log.setLevel(Level.ALL);
		Handler handler = new FileHandler("output.log", 5000, 5);
		handler.setLevel(Level.ALL);
		log.addHandler(handler);

		for (int i = 0; i < 100; i++) {
			LoggerShow.logSth(log);
		}
	}
}

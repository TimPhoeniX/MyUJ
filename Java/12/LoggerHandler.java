import java.util.logging.ConsoleHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.Logger;


class LoggerHandler {
	public static void main(String[] args) {
		Logger log = Logger.getLogger( "LoggerHandler" );
		log.setLevel( Level.ALL );
		log.setUseParentHandlers( false );  // do sprawdzenia !!!!
		Handler handler = new ConsoleHandler();
		handler.setLevel( Level.ALL );
		log.addHandler( handler );
		LoggerShow.logSth( log );
	}
}

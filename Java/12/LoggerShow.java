import java.util.logging.Level;
import java.util.logging.Logger;

class LoggerShow {
	public static void logSth(Logger log) {
		System.out.println( "----------------------------------");
		log.entering("LoggerShow", "logSth", new Object[] { log });

		System.out.println( "LOGGER_NAME > " + log.getName() );
		
		// sa gotowe metody:
		log.severe("7. Komunikat poziomu SEVERE");
		log.warning("6. Komunikat poziomu WARNING");
		log.info("5. Komunikat poziomu INFO");
		log.config("4. Komunikat poziomu CONFIG");

		// mozna tez i tak:
		log.log(Level.FINE, "3. Komunikat poziomu FINE");
		log.log(Level.FINER, "2. Komunikat poziomu FINER");
		log.log(Level.FINEST, "1. Komunikat poziomu FINEST");

		log.exiting("LoggerShow", "logSth");
	}
	
	public static void main(String[] args) {
		
		Logger log = Logger.getGlobal();
		log.setLevel( Level.FINER );
		
		logSth( log );
		
		log = Logger.getLogger( "LoggerShow" );
//		log.setLevel( Level.FINER );
		
		logSth( log );
		
		// java8 -Djava.util.logging.config.file=log.prop LoggerShow
	}
}

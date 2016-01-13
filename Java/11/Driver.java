import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Enumeration;

/*
 * 
 * Fragment kodu zrodlowego
 * 
public class JDBC implements Driver
{
    public static final String PREFIX = "jdbc:sqlite:";

    static {
        try {
            DriverManager.registerDriver(new JDBC());
        }
        catch (SQLException e) {
            e.printStackTrace();
        }
    }
*/
    
public class Driver {
	public static void main(String[] args) {
		try {
			Class.forName( "sun.jdbc.odbc.JdbcOdbcDriver" );		
			Class.forName( "org.sqlite.JDBC" );		
			Class.forName( "org.postgresql.Driver" );
			Class.forName( "com.mysql.jdbc.Driver" );
		} 
		catch ( ClassNotFoundException e ) {
			e.printStackTrace();
		}

		// przegladamy zarejestrowane sterowniki do bazy danych
		Enumeration<java.sql.Driver> drivers = DriverManager.getDrivers();
		
		for (  ; drivers.hasMoreElements();)
		       System.out.println( drivers.nextElement() );

		// ustanawiamy polaczenie z baza danych
		try {
			Connection con = DriverManager.getConnection( "jdbc:sqlite:/tmp/sample.db" );
			System.out.println( "\nPolaczenie z baza danych con = " + con );
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
	}
}

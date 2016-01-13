import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Metainfo {
	
	public static void main(String[] args) {
		try {
			Class.forName( "org.sqlite.JDBC" );		
		} 
		catch ( ClassNotFoundException e ) {
			e.printStackTrace();
		}

		Connection con = null;
		try {
			con = DriverManager.getConnection( "jdbc:sqlite:/tmp/sample.db" );
			System.out.println( "\nPolaczenie z baza danych con = " + con );

			DatabaseMetaData md = con.getMetaData();
			
			System.out.println( "Meta dane: " );
			System.out.println( "* Wersja                  : " + md.getDatabaseProductVersion() );
			System.out.println( "* Nazwa bazy danych       : " + md.getDatabaseProductName() );
			System.out.println( "* Nazwa sterownika        : " + md.getDriverName() );
			System.out.println( "* Wersja sterownika       : " + md.getDriverVersion() );
			System.out.println( "- - - - - - - - - - - - - - " );
			System.out.println( "* Wsparcie dla tranzakcji : " + md.supportsTransactions() );
			System.out.println( "* Wsparcie dla GROUP BY   : " + md.supportsGroupBy() );			
			System.out.println( "* Wsparcie dla UNION      : " + md.supportsUnion() );	
			System.out.println( "* Wsparcie dla OUTER JOIN : " + md.supportsOuterJoins() );	
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if ( con != null )
				try {
					con.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
	}
}

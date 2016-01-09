import java.util.List;

/**
 * Interfejs prostego systemu oferujacego mozliwosc
 * wykonania testu mozliwosci przejscia pomiedzy
 * dwoma lokalizacjami. 
 * Lokalizacje jednoznacznie okreslane sa
 * za pomoca identyfikatorow liczbowych.
 * Informacje o dostepnych 
 * drogach dostarczane sa przez uzytkownika systemu.
 * System zaklada, ze wszystkie wprowadzone drogi sa jednokierunkowe,
 * czyli istnienie polaczenia z A do B nie oznacza,
 * ze z B do A droga istnieje.
 */
public interface RoadsInterface {
	/**
	 * Dodaje do systemu jednokierunkowa droge. 
	 * Droga moze przechodzic 
	 * przez wiele lokalizacji.
	 * Lista lokalizacji nie moze zawierac petli.
	 * 
	 * @param via - lista lokalizacji polaczonych droga.
	 */
	void addRoad( List<Integer> via );
	
	/**
	 * Metoda usuwa mozliwosc przejazdu pomiedzy dwoma
	 * sasiednimi lokalizacjami (sasiednimi, tzn. ze blokowana
	 * jest wylacznie droga, ktora bezposrednio prowadzi z "from" do
	 * "to" nie przechodzac przez zadna inna lokalizacje. Objazd
	 * nadal moze byc mozliwy.
	 * 
	 * @param from - lokalizacja startowa
	 * @param to - lokalizacja koncowa
	 */
	void roadWorks( int from, int to );
	
	/**
	 * Metoda wykonuje test mozliwosci przejscia pomiedzy
	 * dwoma lokalizacjami
	 * 
	 * @param from lokalizacja startowa
	 * @param to lokalizacja docelowa
	 * @return true - droga istnieje, false - nie ma polaczenia
	 * pomiedzy podanymi w zapytaniu lokalizacjami
	 */
	boolean isPassage( int from, int to );
}

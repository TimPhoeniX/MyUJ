import java.util.Map;
import java.util.Set;


public interface ImagesWebFinderInterface {
	/**
	 * Metoda odczytuje kod HTML strony internetowej 
	 * wskazanej przez URL i odnajduje w niej
	 * wszystkie wystapienia znacznika &lt;img&gt;,
	 * z ktorego wyczytuje zawartosc pola <tt>src</tt>.
	 * Metoda zwraca mape zawierajaca jako klucz
	 * rozszerzenie obrazka (np. jpg, png, gif)
	 * wartoscia dla klucz jest zbior lokalizacji
	 * obrazkow danego typu (czyli tego co
	 * podano jako <tt>src</tt>).
	 * <br><br>
	 * Przyklad:
	 * <br>
	 * Strona:
	 * <pre>
	 * &lt;http&gt;
	 * &lt;body&gt;
	 * &lt;img src="slon.png"&gt;
	 * &lt;p&gt;Lorem ipsum dolor sit amet enim. 
	 * Etiam ullamcorper. Suspendisse a pellentesque dui, non felis. 
	 * Maecenas malesuada &lt;img src="koty/pers.png"&gt; elit lectus felis, malesuada ultricies. 
	 * Curabitur et ligula. &lt;img src="psy/bulgot.gif"&gt; Ut molestie a, ultricies porta urna. 
	 * Vestibulum commodo volutpat a, convallis ac, laoreet enim.&lt;/p&gt;
	 * src=cos.png
	 * &lt;/body&gt;
	 * &lt;/http&gt;
	 * </pre>
	 * <p>Mapa:</p>
	 * <pre>
	 * "png" -&gt; { "slon.png", "koty/pers.png" }
	 * "gif" -&gt; { "psy/bulgot.gif" } 
	 * </pre>
	 * 
	 * Oczywiscie znaki cudzyslowia w samej mapie maja <b>nie</b> wystepowac, w powyzszym
	 * przykladzie sa tylko jako podkreslenie, ze chodzi o typ <tt>String</tt>.
	 * Prosze zwrocic uwage na brak "cos.png" - znacznik <tt>src</tt> wprawdzie jest, ale
	 * to nie jest poprawne ladowanie obrazka.
	 * 
	 * Mapa nie ma byc w zaden szczegolny sposob porzadkowana. Kolejnosc kluczy/elementow
	 * moze byc dowolna.
	 * 
	 * @param URL adres strony internetowej do analizy
	 * @return mapa, ktorej kluczem jest typ obrazka, a wartoscia
	 * zbior lokalizacji obrazkow danego typu zawartych w stronie.
	 */
	Map< String, Set<String> > getImages( String URL );
}

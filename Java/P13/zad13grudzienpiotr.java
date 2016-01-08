import java.util.*;
import java.net.*;
import java.io.*;
import javax.swing.text.html.*;
import javax.swing.text.html.parser.*;

class ImagesWebFinder implements ImagesWebFinderInterface
{
	public Map< String, Set<String> > getImages( String URL )
	{
		Map< String, Set<String>> map = new HashMap<>();
		URL url = null;
		URLConnection con = null;
		BufferedReader read = null;
		try
		{ 
			url = new URL(URL);
			con = url.openConnection();
			read = new BufferedReader(new InputStreamReader(con.getInputStream()));
		}
		catch(Exception e) { }
		
		HTMLEditorKit kit = new HTMLEditorKit();
		HTMLDocument doc = (HTMLDocument)kit.createDefaultDocument();
		HTMLEditorKit.Parser pars = new ParserDelegator();
		HTMLEditorKit.ParserCallback callb = doc.getReader(0);
		
		try{ pars.parse(read, callb, true); }
		catch(Exception e) { }
		
		for(HTMLDocument.Iterator it = doc.getIterator(HTML.Tag.IMG); it.isValid(); it.next())
		{
			AttributeSet attr  =it.getAttributes();
			String imgsrc = (string)attr.getAttribute(HTML.Attribute.SRC);
			if(imgsrc!=null)
			{
				
			}
		}
		
		return map;
	}
}
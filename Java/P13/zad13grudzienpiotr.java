import java.util.*;
import java.net.*;
import java.io.*;
import javax.swing.text.*;
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
//			url = new URL(URL);
//			con = url.openConnection();
//			read = new BufferedReader(new InputStreamReader(con.getInputStream()));
			read = new BufferedReader(new FileReader(URL));
		}
		catch(Exception e) { System.err.println("err"); }
		
		HTMLEditorKit kit = new HTMLEditorKit();
		HTMLDocument doc = (HTMLDocument)kit.createDefaultDocument();
		HTMLEditorKit.Parser pars = new ParserDelegator();
		HTMLEditorKit.ParserCallback callb = doc.getReader(0);
		
		try{ pars.parse(read, callb, true); }
		catch(Exception e) { System.err.println("err"); }
		
		for(HTMLDocument.Iterator it = doc.getIterator(HTML.Tag.IMG); it.isValid(); it.next())
		{
			AttributeSet attr  =it.getAttributes();
			String imgsrc = (String)attr.getAttribute(HTML.Attribute.SRC);
			if(imgsrc!=null)
			{
				String[] arr = imgsrc.split("[.]+");
				String key = arr[arr.length-1];
				Set<String> set = map.get(key);
				if(set==null)
				{
					set = new HashSet<>();
					map.put(key,set);
				}
				set.add(imgsrc);
			}
		}
		
		return map;
	}
	
	public static void main(String[] args)
	{
		ImagesWebFinderInterface i = new ImagesWebFinder();
		System.err.println(i.getImages("h1.html"));
	}
}
import javax.xml.transform.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.lang.reflect.*;
import java.util.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

class ObjectToDOM implements ObjectToDOMInterface
{
	private static final Set<Class> wrappers = new HashSet<>(Arrays.asList(
    Boolean.class, Character.class, Byte.class,
	Short.class, Integer.class, Long.class,
	Float.class, Double.class, String.class));
	private Document doc = null;
	
	private boolean isWrapperType(Class cl)
	{
		return wrappers.contains(cl);
	}

	
	private Element Appender(Field f, Object o)
	{
		Class<?> cl = f.getType();
		Element n = this.doc.createElement(f.getName());
		if(cl.isPrimitive() || this.isWrapperType(cl) )
		{
			n.setAttribute("type",cl.getSimpleName());
			try
			{
				if(cl.isPrimitive())
				{
					cl = f.get(o).getClass();
				}
				n.appendChild(doc.createTextNode( cl.cast(f.get(o)).toString()));
			}
			catch(Exception e) { }
		}
		else
		{
			n.setAttribute("type","Object");
			Element name = this.doc.createElement("className");
			try{ cl = f.get(o).getClass();}
			catch(Exception e) { }
			Text className = this.doc.createTextNode(cl.getSimpleName());
			n.appendChild(name).appendChild(className);
			Element state = this.doc.createElement("classState");
			n.appendChild(state);
			Field[] fs = cl.getFields();
			
			for(Field fi : fs)
			{
				if(Modifier.isPublic(fi.getModifiers()))
				{
					try{ state.appendChild(this.Appender(fi,f.get(o))); }
					catch( Exception e) { }
				}
			}
		}
		return n;
	}
	
	public Document getDocument( Object o )
	{
		this.doc = null;
		try
		{
			this.doc = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
		}
		catch(Exception e) { }
		Class<?> cl = o.getClass();
		Element root = this.doc.createElement("object");
		Element name = this.doc.createElement("className");
		Text className = this.doc.createTextNode(cl.getSimpleName());
		root.appendChild(name).appendChild(className);
		this.doc.appendChild(root);
		Element state = this.doc.createElement("classState");
		root.appendChild(state);
		Field[] fs = cl.getFields();
		
		for(Field fi : fs)
		{
			if(Modifier.isPublic(fi.getModifiers()))
			{
				state.appendChild(this.Appender(fi,o));
			}
		}
		Document holder = this.doc;
		this.doc = null;
		return holder;
	}
}
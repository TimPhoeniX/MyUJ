import javax.xml.transform.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.lang.reflect.*;
import java.util.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;


interface inter
{
	public void test();
}

class test1 implements inter
{
	public Integer in = 0;
	public int i = 0;
	
	public test1( int i , int in )
	{
		this.in = in;
		this.i = i;
	}
	
	public void test()
	{
	}
}

class test2
{
	public test1 a = new test1(1,2);
	public test1 b = new test1(3,4);
	public test1 c = null;
	public inter d = new test1(6,4);
	
	public test2()
	{
	}
}

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
			if(cl.isPrimitive())
			{
				try
				{
					cl = f.get(o).getClass();
					n.appendChild(doc.createTextNode( cl.cast(f.get(o)).toString()));
				}
				catch(Exception e) { }
			}
			else
			{
				try
				{
					n.appendChild(doc.createTextNode( cl.cast(f.get(o)).toString()));
				}
				catch(Exception e) { }
			}
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
	
	public static void main(String[] args) throws TransformerException
	{
		ObjectToDOM DOMer = new ObjectToDOM();
		Document doc = DOMer.getDocument(new test2());
		
		TransformerFactory tf = TransformerFactory.newInstance();
		Transformer t = tf.newTransformer();
		StreamResult result =  new StreamResult(System.out);
		
		t.setOutputProperty(OutputKeys.INDENT, "yes");
		t.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		
		t.transform( new DOMSource( doc ), result);
	}
}
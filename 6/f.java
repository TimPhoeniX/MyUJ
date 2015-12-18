class Start {
   static <T> T showAndReturnStatic( T ref ) {
      System.out.println( ref.toString() );
      return ref;
   }

   <T> T showAndReturnNStatic( T ref ) {
      System.out.println( ref.toString() );
      return ref;
   }

   public static void main( String[ ] argv ) {
      Start s = new Start();
   
      Integer i  = Start.<Integer>showAndReturnStatic( new Integer( 123 ) );
      Double d   = s.<Double>showAndReturnNStatic( new Double( 123.123 ) );
      String str = showAndReturnStatic( "A B C D E F G H" );
      String sti = Start.<String>showAndReturnStatic( "A B C D E F G H" );       // mina

      showAndReturnStatic( i );
      s.showAndReturnNStatic( d );
   }
}
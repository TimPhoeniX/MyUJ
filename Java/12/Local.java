
class Local {
	static class LambdaTester {
		void doSth( Runnable run ) {
			run.run();
		}
		@Override
		public String toString() {
			return "To ja Lambda Tester";
		}
	}
	
	@Override
	public String toString() {
		return "To ja Local";
	}
	
	private void callTest() {
		LambdaTester lt = new LambdaTester();
		lt.doSth( () -> System.out.println( this.toString() ) );	
		
		lt.doSth( () -> {
//			String lt = "kot";  // mina !!!!!
			System.out.println( lt );
		});
	}
	
	public static void main(String[] args) {
		Local l = new Local();
		l.callTest();		
	}	
}

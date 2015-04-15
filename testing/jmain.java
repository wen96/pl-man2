import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class jmain {
    
    public static void main (String[] argv) {
    	try{
    	 System.out.println("CARAPAN");
    	 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    	 String input;
    	 input=br.readLine();
    	 if (input.equals("COCAINUM")){
    		 System.out.println("BIEN");
    	 }else{
    		 System.out.println("MAL");
    	 }
    	} catch (IOException io){
    		
    	}
    }
}
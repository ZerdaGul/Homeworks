/**
 * The test2 class is designed to demonstrate and test the functionality
 * of the JavaSet and JavaVector classes in the homework package.
 * It includes tests for adding elements, checking equality between sets,
 * iterating over sets, removing elements, and writing set and vector data
 * to files.
 *
 * @author Zerda Gül
 * @version 1.0
 */

package homework;

import java.lang.IllegalArgumentException;
import java.io.FileOutputStream;
import java.io.IOException;


public class test2 {
    @SuppressWarnings("unchecked")

    /**
     * The main method to execute the tests for JavaSet and JavaVector.
     *
     * @param args Command line arguments (not used in this example).
     */
    public static void main(String[] args) {
        try { //son
            // Test JavaSet
            JavaSet<Integer> set1 = new JavaSet<Integer>();
            JavaSet<Integer> set2 = new JavaSet<Integer>();
            try{
                set1.add(1);
                set1.add(2);
                set1.add(3);
    
                
                set2.add(2);
                set2.add(1);
                set2.add(3);
            }
            catch(IllegalArgumentException e){
                System.out.println(e);
            }

	    boolean val= set1.equals(set2);	
            System.out.println("Is set1 equal to set2: "+val);

    
            System.out.println("Original Set: " + set1);
    
            // Test iterator
            var iterator = set1.getIterator();
            while (iterator.hasNext()) {
                System.out.println("Iterator: " + iterator.next());
            }
    
            // Test remove
            set1.remove(2);
    
            System.out.println("Set after removing element: " + set1);

            FileOutputStream out= new FileOutputStream("set1file.txt");
            if(out!=null){
                out.write(set1.toString().getBytes());
            }
            out.close();    
    
            // Test adding an element that already exists (should throw IllegalArgumentException)
            set1.add(3); // This should throw an exception
        } catch (IllegalArgumentException e) {
            System.out.println(e);
        }catch (IOException e) {
            System.out.println(e);
        }
    
        try {
            // Test JavaVector
            JavaVector<String> vector = new JavaVector<>();
            vector.add("A");
            vector.add("B");
            vector.add("C");
    
            System.out.println("Original Vector: " + vector);
    
            // Test iterator
            var vectorIterator = vector.getIterator();
            while (vectorIterator.hasNext()) {
                System.out.println("Vector Iterator: " + vectorIterator.next());
            }
    
            // Test remove
            vector.remove("B");
    
            System.out.println("Vector after removing element: " + vector);
    
            // Test adding an element
            vector.add("D");
    
            System.out.println("Vector after adding element: " + vector);


            FileOutputStream out= new FileOutputStream("vectorfile.txt");
            if(out!=null){
                out.write(vector.toString().getBytes());
            }
            out.close();  

        } catch (IllegalArgumentException e) {
            System.out.println(e);
        }catch (IOException e) {
            System.out.println(e);
        }
    }
    



}

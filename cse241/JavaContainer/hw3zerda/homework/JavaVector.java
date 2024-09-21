
package homework;
import java.util.NoSuchElementException;

/**
 * A simple implementation of a vector using an array.
 *
 * @param <T> the type of elements in the vector
 */
public class JavaVector<T> implements JavaContainer<T>{
    
    private Object[] vector;
    private int size;

    /**
     * Constructs an empty vector with an initial capacity of 10.
     */
    public JavaVector(){
        size=0;
        vector= new Object[10];
    }

    /**
     * Adds the specified element to the vector.
     *
     * @param element the element to be added to the vector
     */
    public void add(T element){
        if(element==null){
            System.out.println("Geçersiz veri tipi. Eleman eklenemedi.");
            return;
        }
        if(size>=vector.length){
            var newVector= new Object[size*2];
            for(int i=0; i<vector.length;i++){
                newVector[i]= vector[i];
            }
            vector=newVector;
        }
        vector[size]=element;
        size++;
    }

    /**
     * Removes the specified element from the vector.
     *
     * @param element the element to be removed from the vector
     */
    public void remove(T element) {
        for (int i = 0; i < size; i++) {
            if (vector[i] != null && vector[i]==element) {
                for (int j = i; j < size - 1; j++) {
                    vector[j] = vector[j + 1];
                }
                vector[size - 1] = null;
                size--;
                break;
            }
        }
    }


    /**
     * Returns the number of elements in the vector.
     *
     * @return the number of elements in the vector
     */
    public int size() {
        return size;
    }

    /**
     * Returns an iterator over the elements in the vector.
     *
     * @return an iterator over the elements in the vector
     */
    public JavaIterator<T> getIterator() {
        return new VectorIterator();
    }

    /**
     * An iterator implementation for iterating over elements in the vector.
     */
    public class VectorIterator implements JavaIterator<T>{
        private int currentIndex;
        
        /**
         * Constructs an iterator for the vector.
         */
        VectorIterator() {
            currentIndex = 0;
        }

        /**
         * Checks if there is a next element in the iterator.
         *
         * @return true if there is a next element, false otherwise
         */
        public boolean hasNext(){
            return currentIndex<size;
        }

        /**
         * Returns the next element in the iterator and advances the iterator.
         *
         * @return the next element in the iterator
         * @throws NoSuchElementException if there are no more elements in the vector
         */
        public T next() {
            if (hasNext()) {
                return (T) vector[currentIndex++];
            } else {
                throw new NoSuchElementException();
            }
        }
    }

    /**
     * Returns a string representation of the vector.
     *
     * @return a string representation of the vector
     */
    public String toString() {
        String result = "[";
        for (int i = 0; i < size; i++) {
            result += vector[i];
            if (i < size - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

}

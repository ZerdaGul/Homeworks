package homework;
/**
 * JavaContainer
 * @author : Zerda Gül
 * @description : Java Container Interface 
 * @version 1.0.0 
 */
public interface JavaContainer <T>{
    
    /**
     * Adds an element to the container.
     *
     * @param element the element to be added
     */
    public void add(T elem);

    /**
     * Removes the specified element from the container.
     *
     * @param element the element to be removed
     */
    public void remove(T elem);
    /**
     * Returns the number of elements in the container.
     *
     * @return the number of elements in the container
     */
    public int size();
    
    public boolean equals(Object obj);

    /**
     * Returns the type which is set
     *
     * @return the type which is set
     */
   /* public String getElementType();//

    /**
     * An iterator interface for iterating over elements in the container.
     *
     * @param <T> the type of elements in the iterator
     */
    public interface JavaIterator<T> {
        /**
         * Checks if there is a next element in the iterator.
         *
         * @return true if there is a next element, false otherwise
         */
        boolean hasNext();

        /**
         * Returns the next element in the iterator and advances the iterator.
         *
         * @return the next element in the iterator
         */
        T next();
    }

    

}

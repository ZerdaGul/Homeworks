package homework;
import java.util.NoSuchElementException;

/**
 * A simple implementation of a set using an array.
 *
 * @param <T> the type of elements in the set
 */
public class JavaSet<T> implements JavaContainer<T> {
    
    private Object[] set; 
    private int size;

    /**
     * Constructs an empty set with an initial capacity of 10.
     */
    public JavaSet() {
        set = new Object[10];
        size = 0;
    }

    /**
     * Adds the specified element to the set if it is not already present.
     * Throws an IllegalArgumentException if the element is already in the set.
     *
     * @param element the element to be added to the set
     * @throws IllegalArgumentException if the element is already in the set
     */
    public void add(T element) {
        if(element==null){
            System.out.println("Geçersiz veri tipi. Eleman eklenemedi.");
            return;
        }
        for(int i=0; i<set.length;i++){
            if(set[i]==element){
                throw new IllegalArgumentException("there is an element same as this in the set.");
            }
        }
        if (size >= set.length) {
            var newSet = new Object[size * 2];
            for (int i = 0; i < size; i++) {
                newSet[i] = set[i];
            }
            set = newSet;
        }
        set[size++] = element;
    }

    /**
     * Removes the specified element from the set.
     *
     * @param element the element to be removed from the set
     */
    public void remove(T element) {
        for (int i = 0; i < size; i++) {
            if (set[i] != null && set[i]==element) {
                for (int j = i; j < size - 1; j++) {
                    set[j] = set[j + 1];
                }
                set[size - 1] = null;
                size--;
                break;
            }
        }
    }


    /**
     * Returns the number of elements in the set.
     *
     * @return the number of elements in the set
     */
    public int size() {
        return size;
    }

    /**
     * Returns a string representation of the set.
     *
     * @return a string representation of the set
     */
    public String toString() {
        String result = "{";
        for (int i = 0; i < size; i++) {
            result += set[i];
            if (i < size - 1) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

    /**
     * Checks if the specified element is included in the set.
     *
     * @param element the element to be checked
     * @return true if the element is included in the set, false otherwise
     */
    public boolean is_included(Object element){
        JavaIterator<T> iterator = getIterator();
        while (iterator.hasNext()) {
            if(iterator.next()==element){
                return true;
            }
        }
        return false;
    }

    /**
     * Checks if this set is equal to another object.
     *
     * @param obj the object to compare with
     * @return true if the sets are equal, false otherwise
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        JavaSet<?> otherSet = (JavaSet<?>) obj;
        if (size != otherSet.size) {
            return false;
        }
        for(int i = 0; i < size; i++){
            if(!is_included(otherSet.set[i])){
                return false;
            }
        }
        return true;
    }

    /**
     * Returns an iterator over the elements in the set.
     *
     * @return an iterator over the elements in the set
     */
    public JavaIterator<T> getIterator() {
        return new SetIterator();
    }

    private class SetIterator implements JavaIterator<T> {
        private int currentIndex;

        /**
         * Constructs an iterator for the set.
         */
        SetIterator(){currentIndex=0;}

        /**
         * Checks if there is a next element in the iterator.
         *
         * @return true if there is a next element, false otherwise
         */
        public boolean hasNext() {
            return currentIndex < size;
        }

        /**
         * Returns the next element in the iterator and advances the iterator.
         *
         * @return the next element in the iterator
         * @throws NoSuchElementException if there are no more elements in the set
         */
        public T next() {
            if (hasNext()) {
                return (T) set[currentIndex++];
            } else {
                throw new NoSuchElementException();
            }
        }
    }
}


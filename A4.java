import java.util.Arrays;

public class A4 {

    public static void main(String[] args) {
        
        // Set the limit size for the arrays (256MB)
        int MAX_SIZE = 256 * 1024 * 1024;

        // Define the memory stride in bytes 
        int STRIDE = 64; 
        
        // Loop through increasing array sizes from 4 KB to MAX_SIZE
        for (int i = 4096; i <= MAX_SIZE; i *=2){
            // Allocate an int array matching the current size in bytes
            int[] arr = new int [i/4]; // Divide by 4 since each int is 4 bytes

        }
    }
}

import java.util.Arrays;

public class A4 {

    public static void main(String[] args) {
        
        // Set the limit size for the arrays (256MB)
        int MAX_SIZE = 256 * 1024 * 1024;

        // Define the memory stride in bytes 
        int STRIDE = 64; 
        
        int step = STRIDE / 4;

        // Loop through increasing array sizes from 4 KB to MAX_SIZE
        for (int i = 4096; i <= MAX_SIZE; i *=2){
            // Allocate an int array matching the current size in bytes
            int[] arr = new int [i/4]; // Divide by 4 since each int is 4 bytes

            long start = System.nanoTime();

            // Access one value per 64-byte cache line to load data into cache
            for (int j = 0; j<arr.length; j += step){
                arr[j]++;
            }

            long end = System.nanoTime();

            // Calculate and print total access time (in ms) for the current array size
            double timeMs = (end-start) / 1_000_000.0;
            System.out.printf("%8d KB\t%.4f ms\n", i / 1024, timeMs);
        }
    }
}

import java.util.Arrays;

public class A4 {

    public static void main(String[] args) {
        
        // Set the limit size for the arrays (256MB)
        int MAX_SIZE = 512 * 1024 * 1024;
        int totalAccesses = MAX_SIZE/4;

        // Define the memory stride in bytes 
        int STRIDE = 64; 
        
        int step = STRIDE / 4; // since each int is 4 bytes, step = 16 ints

        // Number of times to repeat the measurement for averaging
        int LOOPS = 10;

        // Loop through increasing array sizes from 4 KB to MAX_SIZE
        for (int i = 4096; i <= MAX_SIZE; i *=2){
            // Allocate an int array matching the current size in bytes
            int[] arr = new int [i/4]; // Divide by 4 since each int is 4 bytes

            long totalTime = 0;
            int accessSum = 0; // used to accumulate reads/writes so JIT can't skip the loop


            // Run the same test multiple times to get an average result since it will mitigate the effect of outliers
            for (int k = 0; k < LOOPS; k++){
                long start = System.nanoTime();
                
                // Repeat the “touch-every-cache-line” loop enough times so that each array (regardless of its size) sees roughly 'totalAccesses' int-accesses
                for (int accessed = 0; accessed < totalAccesses; accessed += arr.length) {
                    // Full pass over this array
                    for (int j = 0; j < arr.length; j += step) {
                        arr[j]++;
                        accessSum += arr[j]; // Add each value to accessSum so the loop can’t be removed by the compiler
                    }
                }
            

                long end = System.nanoTime();
                totalTime += (end-start); // Compute time taken 
            }
            

            // Calculate and print average access time (in ms) for the current array size
            double averageAccessTime = totalTime / (LOOPS * 1_000_000.0);
            System.out.printf("%8d KB\t%.4f ms\n", i / 1024, averageAccessTime);
        }
    }
}

#include <emmintrin.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE (256 * 1024 * 1024)  // 256MB max test size
#define LINE_SIZE 64                 // typical cache line size
#define REPEAT 10                    // number of repetitions per size

int main(int argc, const char** argv)
{
    srand(time(NULL));
    int junk = 0;
    register uint64_t time1, time2;
    volatile uint8_t* addr;
    uint64_t total_time;
    int accesses;

    // Allocate a large array
    uint8_t* array = (uint8_t*)malloc(MAX_SIZE);
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int size = 4096; size <= MAX_SIZE; size *= 2) {
        accesses = size / LINE_SIZE;
        total_time = 0;

        // Allocate and shuffle access indices
        int* indices = (int*)malloc(accesses * sizeof(int));
        for (int i = 0; i < accesses; i++) {
            indices[i] = i * LINE_SIZE;
        }
        // Shuffle
        for (int i = accesses - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;
        }

        for (int r = 0; r < REPEAT; r++) {
            // Flush the cache
            for (int i = 0; i < size; i += LINE_SIZE) {
                _mm_clflush(&array[i]);
            }
            _mm_mfence();

            for (int i = 0; i < accesses; i++) {
                addr = &array[indices[i]];
                time1 = __rdtscp(&junk);
                junk = *addr;
                time2 = __rdtscp(&junk) - time1;
                total_time += time2;
            }
        }

        double avg_time = (double)total_time / (REPEAT * accesses);
        printf("Size: %8d bytes, Avg access time: %.2f cycles\n", size, avg_time);

        free(indices);
    }

    free((void*)array);
    return 0;
}

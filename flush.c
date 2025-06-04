#include <intrin.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_SIZE (128 * 1024 * 1024)
#define LINE_SIZE 64

int main(int argc, const char** argv)
{
	int junk = 0;
	register uint64_t time1, time2;
	volatile uint8_t* addr;
	uint64_t total_time;
	int i;
	int size;
	int accesses;

	

	////initialize the array
	//for (i = 0; i < 10; i++) array[i * 4096] = 1;
	//
	////FLUSH the array from the CPU cache
	//for (i = 0; i < 10; i++) _mm_clflush(&array[i * 4096]);
	//
	////Access some of the array items
	//
	//array[3 * 4096] = 100;
	//array[7 * 4096] = 200;

	//Compute the CPU cycles taken to access each item
	for (int size = 4096; size < MAX_SIZE; size *= 2) {
		//addr = &array[i * 4096];
		//time1 = __rdtscp(&junk);
		//junk = *addr;
		//time2 = __rdtscp(&junk) - time1;

		printf("Testing size: %d bytes (%.2f KB)\n", size, size / 1024.0);
	}
	return 0;
}


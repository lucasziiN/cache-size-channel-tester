#include <intrin.h>
#include <stdio.h>
#include <stdint.h>

uint8_t array[256*4096];	//Array to cache	
int temp;
unsigned char secret = 54;	//Secret value to steal

/*cache hit threshold assumed */

#define DELTA 1024

//flushes the array from the cache
//void flushSideChannel()	
//{ 
//	int j;
//	for (j = 4096; j < 128 * 1024 * 1024; j *= 2) {
//		int i;
//		for (i = 0; i < 256; i++) {
//			int index = (i * j + DELTA) % sizeof(array);
//			array[index] = 1;
//			_mm_clflush(&array[index]);
//		}
//		
//	}
//	
//}

// Retrieve the secret value by accessing the corresponding array item
void victim()
{
	temp = array[secret*4096 + DELTA];
}

void reloadSideChannel()
{
	int junk = 0;
	register uint64_t time1, time2;
	volatile uint8_t *addr;
	int i;
	
	//Compute the CPU cycles taken to access each item
	for (i = 0; i<256; i++)
	{
		addr = &array[i*4096 + DELTA];
		time1 = __rdtscp(&junk);
		junk = *addr;
		time2 = __rdtscp(&junk) - time1;
		
		printf("Access time for array[%d*4096 +%d]: %d CPU cycles \n", i, DELTA, (int)time2);
		
	
	}
}
int main(int argc, const char **argv)
{
	flushSideChannel();
	victim();
	reloadSideChannel();
	return(0);
}


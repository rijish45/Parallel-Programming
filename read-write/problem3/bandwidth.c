#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#define num_elements 400000000

uint64_t *array;
uint64_t *array_two;
struct timespec start_time, end_time;


double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array() {
  for (int i = 0; i < num_elements; i++) {
    array[i] = rand()%10 + 1;
  }
  for (int i = 0; i < num_elements; i++) {
    array_two[i] = rand()%5 + 1;
  }
 }

void write_traffic(uint64_t * array){
  int i;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for (i = 0; i < (num_elements); i++){
    array[i] = 5;
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void read_write_one_traffic(uint64_t * array){
  clock_gettime(CLOCK_MONOTONIC, &start_time);
   for (int i = 0; i < (num_elements); i++){
    array[i] = array[i+1];
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
}

void read_write_two_traffic(uint64_t * array, uint64_t * array_two){
  clock_gettime(CLOCK_MONOTONIC, &start_time);
   for (int i = 0; i < (num_elements); i++){
    array[i] = array[i] + array_two[i];
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
}


int main(int argc, char *argv[]) {

  array = malloc(num_elements * sizeof(uint64_t));
  array_two = malloc(num_elements*sizeof(uint64_t));
  init_array();

  write_traffic(array);
  double elapsed_ns = calc_time(start_time, end_time);
  printf("Write traffic only\n");
  printf("Time = %f ns\n", elapsed_ns);
  printf("Average ns per write = %f\n", (elapsed_ns)/num_elements);
  printf("Bandwidth for write is = %f GBPS\n", (((double)num_elements*8)/(elapsed_ns)));
  printf("\n");


  read_write_one_traffic(array);
  printf("1:1 Read and Write traffic\n");
  elapsed_ns = calc_time(start_time, end_time);
  printf("Time = %f ns\n", elapsed_ns);
  printf("Average ns per operation for 1:1 read and write = %f\n", (elapsed_ns)/(num_elements*2));
  printf("Bandwidth for 1:1 read and write is = %f GBPS\n", (((double)num_elements*8*2)/(elapsed_ns)));
  printf("\n");


  read_write_two_traffic(array, array_two);
  printf("2:1 Read and Write traffic\n");
  elapsed_ns = calc_time(start_time, end_time);
  printf("Time = %f ns\n", elapsed_ns);
  printf("Average ns per operation for 2:1 read and write = %f\n", (elapsed_ns)/(num_elements*3));
  printf("Bandwidth for 2:1 read and write is = %f GBPS\n", (((double)num_elements*8*3)/(elapsed_ns)));
  


  free(array);

}

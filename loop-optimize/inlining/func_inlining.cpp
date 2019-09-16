#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>

double calc_time(struct timeval start, struct timeval end) {
  double start_sec = (double)start.tv_sec*1000000.0 + (double)start.tv_usec;
  double end_sec = (double)end.tv_sec*1000000.0 + (double)end.tv_usec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
};

//int add(int a, int b)__attribute__((always_inline));
int add(int a, int b) {
  return (a+b);
}

int main(int argc, char *argv[])
{
  int i, sum, N;

  if (argc < 2) {
    std::cout << "Usage: ./func_inlining <array_size>" << std::endl;
    return -1;
  }

  N = atoi(argv[1]);

  if ((N != 10000000) && (N != 100000000)) {
    std::cout << "Program argument must be 10,000,000 or 100,000,000." << std::endl;
    return -1;
  }

  std::vector<int> a(N);
  std::vector<int> b(N);
  std::vector<int> c(N);

  for (int i=0; i < N; i++) {
    c[i] = 0; 
    a[i] = i+1;
    b[i] = i+3;
  }

  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  for (int i=0; i < N; i++) {
    c[i] = add(a[i], b[i]);
  }
  gettimeofday(&end_time, NULL);

  sum = 0;
  for (int i=0; i < N; i++) {
    sum += c[i];
  }
  
  std::cout << "checksum=" << sum << std::endl;

  double elapsed_us = calc_time(start_time, end_time);
  double elapsed_ms = elapsed_us / 1000.0;
  std::cout << "Time=" << elapsed_ms << " milliseconds" << std::endl;

  return 0;
}

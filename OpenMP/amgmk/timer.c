#include "headers.h"

#ifndef CALC_TIME_H
#define CALC_TIME_H

double calc_time(struct timespec start, struct timespec end) {
  double start_sec =
      (double)start.tv_sec * 1000000000.0 + (double)start.tv_nsec;
  // printf("start sec = %lf\n", start_sec);
  double end_sec = (double)end.tv_sec * 1000000000.0 + (double)end.tv_nsec;
  // printf("end sec = %lf\n", end_sec);

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}
#endif // CALC_TIME_H


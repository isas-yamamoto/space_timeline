#include <stdio.h>
#include <stdlib.h>
#include <SpiceUsr.h>
#include "define.h"

void show_pos(const char* target, SpiceDouble* state) {
  printf("%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
	 target,state[0],state[1],state[2],state[3],state[4],state[5]);
}

int main(int argc, char** argv) {
  SpiceChar* targets[] = {"SUN","MERCURY","VENUS","EARTH","MARS",
			  "JUPITER BARYCENTER",
			  "URANUS BARYCENTER",
			  "NEPTUNE BARYCENTER",
			  "PLUTO BARYCENTER",
			  "MOON",
			  NULL};
  SpiceDouble lat, lon;
  SpiceDouble et, lt, state[6];
  int i;
  
  if (argc != 4) {
    fprintf(stderr, "usage: %s yyyy-mm-ddThh:mm:ss lat[deg] lon[deg]\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  const char* utc = argv[1];
  lat = atof(argv[2]);
  lon = atof(argv[3]);
  
  furnsh_c("isac.meta");
  utc2et_c(utc, &et);
  for (i=0; targets[i] != NULL; ++i) {
    spkezr_c(targets[i],et, "J2000", "NONE", "EARTH", state, &lt);
    show_pos(targets[i], state);
  }
  if (getMyLocation(et, lat, lon, state,"IAU_EARTH")) {
    show_pos("MYPOS", state);
  }
  
  return EXIT_SUCCESS;
}

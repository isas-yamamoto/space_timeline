#include <stdio.h>
#include <stdlib.h>
#include <SpiceUsr.h>
#include "define.h"

void show_pos(const char* target, SpiceDouble* state) {
  printf("%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
	 target,state[0],state[1],state[2],state[3],state[4],state[5]);
}

int main(int argc, char** argv) {
  SpiceChar utcstr[LEN];
  SpiceChar* targets[] = {"SUN","MERCURY","VENUS","EARTH","MARS",
			  "JUPITER BARYCENTER",
			  "URANUS BARYCENTER",
			  "NEPTUNE BARYCENTER",
			  "PLUTO BARYCENTER",
			  "MOON",
			  NULL};
  SpiceDouble lat, lon;
  SpiceDouble et, lt, state[6], earth[6];
  int i;
  
  if (argc != 8) {
    fprintf(stderr, " usage: %s kernel-file obs ref-frame earth-frame yyyy-mm-ddThh:mm:ss lat[deg] lon[deg]\n", argv[0]);
    fprintf(stderr, "    ex: %s isac.meta EARTH J2000 IAU_EARTH 2000-01-01T00:00:00 35.66 139.68\n", argv[0]);
    fprintf(stderr, "output: target,x,y,z,vx,vy,vz\n");
    return EXIT_FAILURE;
  }
  
  furnsh_c(argv[1]);  
  const char* obs = argv[2];
  const char* ref = argv[3];
  const char* earth_frm = argv[4];
  const char* utc = argv[5];
  lat = atof(argv[6]);
  lon = atof(argv[7]);
  
  utc2et_c(utc, &et);

  // show UTC
  et2utc_c( et, "ISOC", 0, LEN, utcstr);
  printf("%s\n", utcstr);

  // show my location
  if (getMyLocation(et, lat, lon, state, earth_frm, ref)) {
    spkezr_c("EARTH",et, ref, "NONE", obs, earth, &lt);
    vadd_c(earth,state,state);
    show_pos("MYPOS", state);
  }

  // show planets' location
  for (i=0; targets[i] != NULL; ++i) {
    spkezr_c(targets[i],et, ref, "NONE", obs, state, &lt);
    show_pos(targets[i], state);
  }
  
  return EXIT_SUCCESS;
}

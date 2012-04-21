#include <SpiceUsr.h>
#include <string.h>
#include "define.h"

int getMyLocation(SpiceDouble et, SpiceDouble lat, SpiceDouble lon, SpiceDouble* st, const SpiceChar* frame, const SpiceChar* ref) {
  SpiceDouble angles[3];
  SpiceInt axes   [3] = { 3, 2, 3 };
  SpiceInt center  = 500000;
  SpiceInt frclass = 4;
  SpiceInt frclsid = 1500000;
  SpiceInt frcode  = 1500000;
  
  SpiceDouble z_axis[3]={0.0, 0.0, 1.0};
  SpiceDouble pv_mypos[6];
  SpiceDouble rmat[3][3];
  
  SpiceDouble radii_earth[3];
  SpiceInt dim;
  SpiceDouble colat;
  
  bodvrd_c("EARTH", "RADII", 3, &dim, radii_earth);
  
  colat = 90.0 - lat;
  
  angles[0] = -lon;
  angles[1] = -colat;
  angles[2] = 180.0;
  
  pipool_c ( "FRAME_MYTOPO",            1,                 &frcode      );
  pcpool_c ( "FRAME_1500000_NAME",      1,             7,  "MYTOPO"     );
  pipool_c ( "FRAME_1500000_CLASS",     1,                 &frclass     );
  pipool_c ( "FRAME_1500000_CLASS_ID",  1,                 &frclsid     );
  pipool_c ( "FRAME_1500000_CENTER",    1,                 &center      );
  pcpool_c ( "OBJECT_500000_FRAME",     1,             7,  "MYTOPO"     );
  pcpool_c ( "TKFRAME_MYTOPO_RELATIVE", 1, strlen(frame),  frame        );
  pcpool_c ( "TKFRAME_MYTOPO_SPEC",     1,             7,  "ANGLES"     );
  pcpool_c ( "TKFRAME_MYTOPO_UNITS",    1,             8,  "DEGREES"    );
  pipool_c ( "TKFRAME_MYTOPO_AXES",     3,                 axes         );
  pdpool_c ( "TKFRAME_MYTOPO_ANGLES",   3,                 angles       );
  
  // Observing Position from the EARTH CENTER
  pxform_c("MYTOPO", ref, et, rmat);
  mxv_c(rmat, z_axis, pv_mypos);
  vscl_c(radii_earth[0], pv_mypos, st);
  
  return TRUE;
}

#ifndef __DEFINE_H__
#define __DEFINE_H__

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

int getMyLocation(SpiceDouble et, SpiceDouble lat, SpiceDouble lon, SpiceDouble* st, const SpiceChar* frame, const SpiceChar* ref);

#endif

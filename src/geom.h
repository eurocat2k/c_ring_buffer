#ifndef __GEOM_H__
#define __GEOM_H__

#ifdef __cplusplus
extern "C" {
#endif

//
#define SYS_CENTER_LON 19.2322222222222
#define SYS_CENTER_LAT 47.4452777777778
//

#define EXCENTRICITY (0.081819190842622)
#define PI (3.14159265358979323846)
#define RADIAN_PER_DEGREE ((PI) / (180.0))
#define KM_EARTH_RADIUS (6378.137)
#define KM_TO_NM (1.8519993258723)
#define NM_TO_KM ((1.0) / (KM_TO_NM))
#define NAUTICAL_MILE (1851.9993258723)
#define M_TO_NM ((1.0) / (NAUTICAL_MILE))
#define NM_TO_M ((1.0) / (M_TO_NM))
#define NMPS_TO_MPS (NAUTICAL_MILE)
#define NMPH_TO_NMPS (3600.0)
#define NMPS_TO_NMPH ((1.0) / (NMPH_TO_NMPS))
#define MPS_TO_NMPS ((1.0) / (NAUTICAL_MILE))
#define NM_EARTH_RADIUS ((KM_EARTH_RADIUS) / (KM_TO_NM))

#ifdef __cplusplus
}
#endif

#endif // __GEOM_H__

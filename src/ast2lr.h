#ifndef __AST2LR_H__
#define __AST2LR_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_LR_MSG_LENGTH
#define MAX_LR_MSG_LENGTH 256
#endif

#ifndef CALLSIGN_LENGTH
#define CALLSIGN_LENGTH 8
#endif

#ifndef DEP_LENGTH
#define DEP_LENGTH 4
#endif

#ifndef DES_LENGTH
#define DES_LENGTH 4
#endif

#ifndef ATYP_LENGTH
#define ATYP_LENGTH 4
#endif

#ifndef WTC_LENGTH
#define WTC_LENGTH 1
#endif

#ifndef MAX_STATUS_OCTETS
#define MAX_STATUS_OCTETS 5
#endif

#ifndef MAX_MODE3A_OCTETS
#define MAX_MODE3A_OCTETS 2
#endif

#ifndef MAX_ICAO_ADDR_LENGTH
#define MAX_ICAO_ADDR_LENGTH 3
#endif

typedef enum { DESC = -1, LEVEL = 0, CLIMB = 1 } attitude_t;

typedef struct mode3a_t mode3a_t;

typedef struct trk_status_t trk_status_t;

typedef struct ast_to_lr_t ast_to_lr_t;

int Convert_ASTCAT62_TO_LRTGT(const void *sdata, void *dst);
int Convert_ASTCAT65_TO_LRNS(const void *sdata, void *dst);

#ifdef __cplusplus
}
#endif

#endif // __AST2LR_H__

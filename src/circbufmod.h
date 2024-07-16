// !! Under construction
#ifndef __CIRCBUFMOD_H__
#define __CIRCBUFMOD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef MAX
#define MAX(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })
#endif

#ifndef MIN
#define MIN(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })
#endif

typedef struct cbuf_mod_t cbuf_mod_t;
typedef cbuf_mod_t *cbuf_mod_handle_t;
/**
 * @brief Constructor, create circular buffer handler object with size parameter which has to
 *        be a 2^N value where N >= 3.
 * 
 * @param size modulo (2 ** N), where N >= 3
 * @return cbuf_mod_handle_t handler object
 */
cbuf_mod_handle_t Circular_Buf_Modulo_Create(size_t size);
/**
 * @brief Destructor of the cbuf object
 * 
 * @param cbuf 
 */
void Circular_Buf_Modulo_Free(cbuf_mod_handle_t cbuf);

#ifdef __cplusplus
}
#endif

#endif // __CIRCBUFMOD_H__
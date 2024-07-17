#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__
/**
 * @brief Dumps data in classic hexdump format
 *
 * @param src the data buffer to be displayed
 * @param nbytes number of octets to be printed.
 */
void HexDump(const void *src, size_t nbytes);

#endif  /* __HEXDUMP_H__ */

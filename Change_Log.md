# Change logs

17.07.24  Initial veriosn

18.07.24  Bugfixed version:
> Running memory checks with valgrind I discovered few *'weird'* memory errors such as use of uninitialised or unaddressable values in system calls.
  It turned out that if I allocate the ring buffer object along with the array - which will hold incoming data chunks - it will leak when I
  initilize the whole chunk of memory either with ***memset(3)*** or at creation with ***calloc(3)*** though. These errors come up when the program tries to
  print out the buffer content from another function - such as HexDump and the ***printf(3)***

> Therefore I changed the constructor - separating the object and the data array in it - first allocating memory for the object, then separately allocate
  the data buffer and attache to the pointer if allocation success.

## Old version
```
  cbuf object (allocated with attributes and buffer):
  +-------------+  ------------------\
  |  dataSize   |  <= size_t         |
  |-------------|                    |
  |  sizeMask   |  <= size_t         |
  |-------------|                    |
  | maxCapacity |  <= size_t         | offset = sizeof attributes
  |-------------|                    |
  |    tail     |  <= size_t         |
  |-------------|                    |
  |    head     |  <= size_t         |
  |-------------| <-----------------/  
  |    data     |  <= (void *) or (uint8_t *) pointer 
  |-------------| cbuf->data = cbuf + offset
  |     ...     |
  |-------------|
  |             |
  +-------------+ cbuf->data + maxCapacity
```
## new version
```
cbuf object (with attributes only):
  +-------------+                     data memory allocated separately
  |  dataSize   |  <= size_t    /---> +-------------+ 0
  |-------------|               |     |             |
  |  sizeMask   |  <= size_t    |     |-------------|
  |-------------|               |     |     ...     |
  | maxCapacity |  <= size_t    |     |-------------|
  |-------------|               |     |             |
  |    tail     |  <= size_t    |     |-------------|
  |-------------|               |     |             |
  |    head     |  <= size_t    |     +-------------+ maxCapacity
  |-------------| --------------/
  |    data     |  <= (void *) or (uint8_t *) pointer
  +-------------+
```
> In the first case **valgrind** reports memory leaks due tu uninitialized heap allocation, the second case there is
  no error. 

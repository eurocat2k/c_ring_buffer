# C ring-buffer
Ring buffer written In C useful ADT for system programming. In my case various TCP clients use this facility to reconstruct segmented data packages.

## Ring Buffer version #1

[Ring buffer verion #1](README_ringbuffer_v1.md) - 

  In this version the program reorganizes - by relocating the fragments - the contents of the buffer. Follow the progress below explained a simple scenario.

  De buffer before storing anything in it, has 8 octets capacity without overflow.
```
  Buffer: [ | | | | | | | ]
           ^
           tail & head points to the same index.
```
  After pushing 5 characters, the buffer shall be in the following state
```
  Buffer: [A|B|C|D|E| | | ]
           ^         ^
           |         head index
           tail index
```
  We pop off 3 characters, then the following events happen:
  
  **Step one**: pop off characters
```
  Buffer: [ | | |D|E| | | ]
                 ^   ^
                 |   head index
                 tail index
```
  **Step two**: relocate remaining chunk to the buffer's beginning. Then set the new indexes for both *tail* and *head*.
```
  Buffer: [D|E| | | | | | ]
           ^   ^
           |   head index
           tail index
```
  Imagine if the next read cycle the incoming data size equals with the remaining empty cells. After the read, both
  *tail* and *head* indexes will point to the same position: buffer index 0, and the program reports the buffer is
  *FULL*.

  So, every time - after a *POP* action, the *tail* index going to be set to 0 - beginning the buffer - and set the
  *head* index set to the appropriate distance from tail - as buffer's dataSize dictates.

## Ring Buffer version #2

[Ring buffer verion #2](README_ringbuffer_v2.md) - uses buffer size strictly aligned to 2^N - where N >= 3. - (*8, 16, 32 .. 65536*)

  The main trick is, how the program handles boundary checks as it performed by bit masking. See example below:
```
  Buffer: [ | | | | | | | | ] - max capacity 8 octets, sizeMask = 8 - 1 (7) 
           ^
           *head* and *tail* points to the beginning of the buffer.
```
  Binary representation:

    Capacity: 1000
    maskSize: 0111

  Imagine the following scenario, *tail* points to 5th index, and *head* points to 6th index in the buffer.
```
  Buffer: [ | | |D|E|F| | ]
                 ^     ^
                 |     head
                 tail
```
  We intend to push 5 characters into the buffer. The *computation* happens like this: 6 + 4 = 10, 10 & 7 => 2.
```
    Binary: 1 0 1 0 <- new head value after pushing 4 new characters (10).
AND   Mask: 0 1 1 1 <- the size mask (1 0 0 0  - 0 0 0 1 = 0 1 1 1 ) (7).
--------------------
            0 0 1 0 <- the new head index after AND operation (2)
```
  The next five characters are going to be the set of the following alphabets: 'G' 'H' 'I' 'J'

  So, the contents of the buffer will look like this:
```
  Buffer: [I|J| |D|E|F|G|H]
               ^ ^
               | tail.
               head after pushing 4 characters points to 2nd index.
```
## Memory check for TEST1
```
cc -O2 -ggdb -std=c99 -pedantic test1.c circbufmod.c hexdump.c -o test1 && valgrind -s --track-origins=yes --leak-check=full ./test1
==23627== Memcheck, a memory error detector
==23627== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==23627== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
==23627== Command: ./test1
==23627== 
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 0
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
Address   00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f  Ascii           
========  =======================  =======================  ================
00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00 |................|
========  =======================  =======================  ================
]

Step 1: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 5
        DATA SIZE   = 5
        SIZE MASK   = 0x0F
Address   00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f  Ascii           
========  =======================  =======================  ================
00000000  41 42 43 44 45 00 00 00  00 00 00 00 00 00 00 00 |ABCDE...........|
========  =======================  =======================  ================
]

...
        POPPED OUT DATA: RS
Step 9: After popped 2 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 3
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
Address   00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f  Ascii           
========  =======================  =======================  ================
00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00 |................|
========  =======================  =======================  ================
]

==23627== 
==23627== HEAP SUMMARY:
==23627==     in use at exit: 4,096 bytes in 1 blocks
==23627==   total heap usage: 3 allocs, 2 frees, 4,160 bytes allocated
==23627== 
==23627== LEAK SUMMARY:
==23627==    definitely lost: 0 bytes in 0 blocks
==23627==    indirectly lost: 0 bytes in 0 blocks
==23627==      possibly lost: 0 bytes in 0 blocks
==23627==    still reachable: 0 bytes in 0 blocks
==23627==         suppressed: 4,096 bytes in 1 blocks
==23627== 
==23627== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
--23627-- 
--23627-- used_suppression:      1 MEMCHECK-LIBX-REACHABLE-2 /usr/local/libexec/valgrind/default.supp:603 suppressed: 4,096 bytes in 1 blocks
==23627== 
==23627== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

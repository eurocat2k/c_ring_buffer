# RING BUFFER VERSION #2

### About test program of the version #2
0. Create a circular buffer object - with its buffer as well - on the heap (size: 16 octets).
1. Push 5 characters into the buffer: *'A'..'E'*. Display buffer's attributes and contents.
2. Pop off 3 characters and print buffer.
3. Push 5 characters into buffer and print.
4. Pop off 2 characters then print.
5-6. Push total 9 characters and print.
7-8. Pop off total 12 characters and print.
9. Pop off the remaining (2) characters and print.
10. Free up cbuffer object, and return from the program.

### Build and run 1st variant
```
cc -O2 -g test1.c circbufmod.c hexdump.c -o test1 && ./test1
```
### Expected output
```
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 0
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00  ................                                                      
====== =======================   =======================  ================

]

Step 1: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 5
        DATA SIZE   = 5
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 41 42 43 44 45 00 00 00   00 00 00 00 00 00 00 00  ABCDE...........                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: ABC
Step 2: After popped 3 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 5
        DATA SIZE   = 2
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 44 45 00 00 00   00 00 00 00 00 00 00 00  ...DE...........                                                      
====== =======================   =======================  ================

]

Step 3: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 10
        DATA SIZE   = 7
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 44 45 46 47 48   49 4A 00 00 00 00 00 00  ...DEFGHIJ......                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: DE
Step 4: After popped 2 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 10
        DATA SIZE   = 5
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 46 47 48   49 4A 00 00 00 00 00 00  .....FGHIJ......                                                      
====== =======================   =======================  ================

]

Step 5: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 15
        DATA SIZE   = 10
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 46 47 48   49 4A 4B 4C 4D 4E 4F 00  .....FGHIJKLMNO.                                                      
====== =======================   =======================  ================

]

Step 6: After pushed 4 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 3
        DATA SIZE   = 14
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 51 52 53 00 00 46 47 48   49 4A 4B 4C 4D 4E 4F 50  QRS..FGHIJKLMNOP                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: FGHIJK
Step 7: After popped 6 characters.
CBUF INFO: [
        TAIL OFFSET = 11
        HEAD OFFSET = 3
        DATA SIZE   = 8
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 51 52 53 00 00 00 00 00   00 00 00 4C 4D 4E 4F 50  QRS........LMNOP                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: LMNOPQ
Step 8: After popped 6 characters.
CBUF INFO: [
        TAIL OFFSET = 1
        HEAD OFFSET = 3
        DATA SIZE   = 2
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 52 53 00 00 00 00 00   00 00 00 00 00 00 00 00  .RS.............                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: RS
Step 9: After popped 2 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 3
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00  ................                                                      
====== =======================   =======================  ================

]

```


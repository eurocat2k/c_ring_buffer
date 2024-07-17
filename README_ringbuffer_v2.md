# RING BUFFER VERSION #2

### About test program of the version #2
1. Create a circular buffer object - with its buffer as well - on the heap (size: 16 octets).
2. Push 5 characters into the buffer: 'A'..'E'. Display buffer's attributes and contents.
3. Pop off 2 characters and print buffer.
4. Push 5 characters into buffer and print.
5. Pop off 2 characters then print. 5-6. Push total 9 characters and print. 7-8. Pop off total 12 characters and print.
6. Pop off the remaining (2) characters and print.
Free up cbuffer object, and return from the program.
Build and run 1st variant
cc -O2 -g test.c circbuf.c hexdump.c -o test && ./test
Expected output


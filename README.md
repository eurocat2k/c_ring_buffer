# C ring-buffer
Ring buffer written In C useful ADT for system programming. In my case various TCP clients use this facility to reconstruct segmented data packages.

## Ring Buffer version #1

[Ring buffer verion #1](README_ringbuffer_v1.md) - 

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
  The next five characters are going to be the set of the following alphabets: 'G' 'H' 'I' 'J'

  So, the contents of the buffer will look like this:
```
  Buffer: [I|J| |D|E|F|G|H]
               ^ ^
               | tail.
               head after pushing 4 characters points to 2nd index.
```


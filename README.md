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
  
  Step one: pop off characters
```
  Buffer: [ | | |D|E| | | ]
                 ^   ^
                 |   head index
                 tail index
```
  Step two: relocate remaining chunk to the buffer's beginning. Then set the new indexes for both *tail* and *head*.
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


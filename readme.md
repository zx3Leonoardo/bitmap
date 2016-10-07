# BitMap Compression and Decompression Experiment

## Experimental Method
---
This program uses **MAH** coding Method to compress the ip Data given, store the encoded data into memroy, and wait to be searched. When a query request occurs, the program searches the database with key words and respond with query results to users.

## How to use
### Clone me first

``` shell

$ git clone git@github.com:fancz2002/bitmap.git

```

### Make

``` shell

$ cd bitmap && make

```

### And enjoy
``` shell
$ ./bitmap.out
```

## Usage

### Query Format

Input 8 integers(0-255) indicating the 8 blocks of the source ip and destination ip, Press Enter.

Then the program does the rest of it and return with your result.

``` shell
mark@ubuntu:~/Documents$ ./bitmap
ip_data has been saved
bitmap has been established
bitmap has been compressed
please input the ip address:
(missing address please type -1)
0 0 0 0 0 0 0 0
from 0,0,0,0 to 0,0,0,0
from 0,0,0,0 to 0,0,0,0
from 0,0,0,0 to 0,0,0,0
from 0,0,0,0 to 0,0,0,0
4 records found
continue or not?  y/n
n

```
### And ...

Continue to search or quit the program.

## Authors
Qin Zixin
Xiong Zheng
Fan Chengze

from Tsinghua University

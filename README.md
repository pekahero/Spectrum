# The idea of the program.

1) The goal of the program is to calculate spectrum of new set of vectors, which are calculated as combinations of starting ones. 
Spectrum is basicaly just amount of new vectors with certan number of "1"s. So, if n is vectors' length, spectrum interval is [0,n]. 
This program reads data from file in form of string lines, that consist of "0"s and "1"s.Each line is binary vector. 
 
2) New vectors being all possible combinations of summarising old ones, means that we can interpret each sum as combination of "0"s and "1"s. 
So, if number of starting vectors is k. We need  2^k combinations of length k to work with. 
It means we can use Gray code. It won't change the result, we just rearrange combinations without changing any combination. 
In Grey code each new combination is previos one, but with one digit changed. 
This way we dont need to calculate each individual sum, we can just calculate first one and then add only one vector to this sum, so we get second one. 
And each next new vector would be previos one plus one of old ones. 
It doesn't matter if changed digit is "0" or "1": result is the same for "+1" or "-1" when modulo is 2. 

3) When new vector is calculated, there is no reason to store it, just to calculate number of "1"s in it. And increase value in respected index by 1.
When spectrum is calculated, result is written to file like: "index"\t"index's value".

# How to run program.
Program takes arguments of command line. Necessary arguments to run program:
 - "-i <filename>" - key -i and name of a file to read vectors from, ".txt" format.
 - "-o <filename>" - key -o and name of a file to write vectors to, ".txt" format.

Optional arguments:
 - "-t <filename>" - key -t and name of a file to compare result file with, ".txt" format.

# Files.
- linear-subspace-spectrum.cpp - main executable file.
- linear-capsule.cpp - file for all spectrum calculation related functions.
- linear-capsule.h - respected functions declarations and libraries.
- write-read-files.cpp - all reading from/writing to files related functions.
- write-read-files.h - respected functions declarations and libraries.
- files-comparison.cpp - finction for comparison of two files.
- files-comparison.h - respected function declaration and libraries.

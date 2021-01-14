The goal of the program is to calculate spectrum of new set of vectors calculated as combinations of starting ones.
Spectrum is basicaly just amount of new vectors of each number of "1"s. So, if n is vectors length, spectrum interval is [0,n].
This program reads data from file in form of string lines, that consist of "0"s and "1"s.Each line is binary vector. 
Then program converts all binary vectors to decimal numbers, because it's easy to store them this way.
Then program calculate new vectors based on starting ones.
New vectors are sums: combinations with no repeating of starting vectors with coefficients "0" and "1", like multipliers of taking part in sum or not.
Sum is binary XOR. Coefficients(multipliers) are easy to represent like truth table. Each row of table is a set of multipliers to use in current sum.
So, if number of starting vectors is k. We need  2^k combinations to work with. It is a lot, so thread are used here.
When new vector is calculated, there is no reason to store it, just to calculate number of "1"s in it. And increase value in respected index by 1.
When spectrum is calculated, result is written to file like: "index"\t"index's value".

Plans: 
1) Represent multipliers by Grey code would help to recalculate just one position each time.
2) Bitset representaton of vectors instead of ull.



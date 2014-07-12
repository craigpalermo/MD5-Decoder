MD5-Decoder
===========

This program reveals the plain text of an MD5 digest by generating/hashing permutations and comparing the results.

## Disclaimer
Since this program uses a brute-force method of finding a match (generates a permutation of characters, hashes the string, then compares that to the input hash), it is extremely inefficient for input strings longer than 7 characters.

It is also useless if you're trying to decode a salted hash, because this program doesn't know or care how your hash was salted. Sorry, it's not very nice.

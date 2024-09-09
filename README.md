# Huffman_coding

implements a binary tree based compression and decompression system, which calculates the number of times each character in an input text file is used, generates a code, compresses and decompresses it, and finally calculates the compression rate.

## Features

- Calculate character frequency and generate Hoffman tree for compression based on the frequency.
- Supports to compress and output coded strings into `.enc` files.
- Uncompresses and restores text file contents.
- Use `<bitset>` for bit packing to avoid the problem that encoded bits cannot be divided by 8.

## Known Issues

- During the packing process of `<bitset>`, occasional error will be caused by `char` conversion problem. Temporarily, we can reduce the error rate by converting the code to `string` and then put it into `bitset`, but the problem has not been solved completely.
- When trying to support EASCII characters, we encountered the problem of converting negative numbers to EASCII characters, which prevented us from outputting the code properly, so we finally backed off to the version that only supports ASCII characters.
- Currently there are five files generated during execution, of which only three are necessary for output, and the other two are temporary files generated to solve the memory overuse problem.
- The choice of files to compress is written in the code, not chosen at execution time

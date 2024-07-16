# Compress-File
A file compression and decompression programme, written in pure C, uses the Huffman algorithm to efficiently encode data. It is designed to reduce file size by replacing frequently occurring characters with shorter codes and rare characters with longer codes

* Compression:
Reads the input file and analyses the frequency of each symbol.
Creates a Huffman tree where each leaf represents a symbol and the weight of a node corresponds to the frequency of the symbol.
Generates Huffman codes for each symbol based on the tree structure.
Replaces the characters in the source file with the corresponding Huffman codes.
Saves the compressed file including the Huffman tree for later decompression.

* Decompression:
Reads the compressed file and reconstructs the Huffman tree.
Uses the tree to decode a sequence of bits into the original characters.
Restores and saves the original file.

## Building the Project
### Linux 
```
git clone https://github.com/licht8/compress-file.git
chmod +x BUILD.sh && chmod +x RUN.sh
```
In order to start building follow this command: 
``` 
./BUILD.sh
 ```
this command will create a new build directory for the object and executable files

and then just run the script: 
```
./RUN.sh
```
(**build** folder also contains the logs directory, which contains logs.)

### Windows

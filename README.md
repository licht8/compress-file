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

# Requirements for Building the Program
## Linux
* Install the GCC compiler:
```
sudo apt-get update
sudo apt-get install gcc
```
* Install Make:
```
sudo apt-get install make
```
* Make sure you have permissions to run scripts:
```
chmod +x BUILD.sh && chmod +x RUN.sh
```

## Windows
* Install GCC Compiler:
Install MinGW (Minimalist GNU for Windows), which includes GCC

* Install Make:
Install MinGW (Minimalist GNU for Windows), which includes Make or use Chocolatey:
```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
```
```
choco install make
```
* Allow PowerShell scripts to run:
```
Set-ExecutionPolicy -ExecutionPolicy Unrestricted -Scope CurrentUser
```

# Building the Project
## Linux 
```
git clone https://github.com/licht8/compress-file.git
cd compress-file
chmod +x BUILD.sh && chmod +x RUN.sh
./BUILD.sh
 ```
the last command will create a new build directory for the object and executable files

and then just run the script: 
```
./RUN.sh
```
(**build** folder also contains the logs directory.)


## Windows
```
git clone https://github.com/licht8/compress-file.git
cd compress-file
.\BUILD.ps1
```
and run the script afterwards by following this command:
```
.\RUN.ps1
```

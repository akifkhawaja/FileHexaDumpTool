# Hexadecimal Memory Dump Tool
This C program allows users to load a file, display its contents in both hexadecimal and ASCII format (similar to a hex dump), and provide useful metadata such as the file size. It includes error handling to check if the file exists, file size limits, and options to exit the program.

## Features:
- File Loading: Prompts the user to enter the file name (up to 9 characters) and loads its content into memory. Handles both successful file loading and errors (e.g., file not found or file too large).
- Memory Dump: Displays the loaded file in a human-readable hex dump format, showing both the hexadecimal values and their ASCII equivalents.
- Exit Handling: Allows users to exit the program by entering 'q'.
- Error Checking: Verifies file length and handles input errors (e.g., too many characters in the file name).

## How to Use:
1. Clone the repository.
2. Compile the program using gcc:

```
gcc -o memdump memdump.c
```
3. Run the program:
```
./memdump
```
4.Enter the name of the file you want to load. For example:
```
Enter the name of the file (9 max characters), 'q' to exit: file.bin
```
5. The program will display the file's contents in hexadecimal and ASCII format, followed by the size of the file.
## Example Output:
```
0000  48 65 6c 6c 6f 20 77 6f 72 6c 64 21 0a               Hello world!
The size of the file is ==> 12
```


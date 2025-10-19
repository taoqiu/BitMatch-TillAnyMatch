# ConBitMatch Complex Event Matching Algorithm

ConBitMatch is a complex event matching algorithm based on the skip-till-any-match strategy, achieving comprehensive coverage of matching patterns.

**Note: Due to anonymous submission requirements, we are providing only the source code of the ConBitMatch algorithm.**

## Compilation Guide

### Method 1: Command Line Compilation

#### Using MSVC:
1. Navigate to the directory containing ConBitMatch source files:
2. Compile using the following command:
   
cl /EHsc /std:c++20 /O2 *.cpp /Fe:ConBitMatch.exe

#### Notes:
- The `/std:c++20` flag enables C++20 standard required by the code
- Ensure you're using the **x64** version of the command prompt for 64-bit compilation


### Using GCC/MinGW

#### Prerequisites:
- GCC 10 or higher

#### Steps:
1. Open terminal/command prompt
2. Navigate to the source directory
3. Compile using:

g++ -std=c++20 -O2 -o ConBitMatch.exe *.cpp

### Method 3: Integration into Existing Projects
1. Copy all ConBitMatch source files (.cpp and .h) to your project directory
2. Add the files to your project:
- In Visual Studio: Right-click project → "Add" → "Existing Item"
- In other IDEs: Use the appropriate method to add external source files
3. Ensure your project is configured for C++20 standard
4. Include the necessary headers in your code
5. The main algorithm entry point is in the `bitParallelMatch` source file

## Input/Output Structure
- Event streams serving as input examples are stored in the "data" folder
- Query patterns are stored in the "query" folder
- Both folders are located at the same level directory
- Detailed matching results are stored in the "result" folder, which is also located at the same level directory

## Configuration
The configuration properties of ConBitMatch are set in the document `config.txt`. The specific content structure is as follows:

1. **First line**: Relative address of the input query file
2. **Second line**: Relative address of the input event stream file
3. **Third line**: Number of times the program is executed in a loop (facilitates measuring average running time)
4. **Fourth line**: Size of the time slice (default unit: seconds) - adjustable based on specific dataset
5. **Last line**: Relative address for saving detailed matching results

After the program outputs all matching result information, you can enter any content to end the program execution.

# ConBitMatch-TillAnyMatch

ConBitMatch is a complex event matching algorithm based on the skip-till-any-match strategy, achieving comprehensive coverage of matching patterns.

## Environment Setup
Please load this project using the Visual Studio 2022 IDE in a Windows environment for smooth execution.

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

## Important Note
When debugging, please set the SDL check in the properties of the solution in VS2022 to "No".

## Execution
After modifying the file path in the `RunConBitMatch.bat` file to the new storage path (current location of the file), you can run the ConBitMatch program under default configuration conditions by clicking on the `RunConBitMatch` file.

After the program outputs all matching result information, you can enter any content to end the program execution.

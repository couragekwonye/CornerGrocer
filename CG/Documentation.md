# Corner Grocer Item Tracking Documentaion
![alt text](image.png)

# Introduction 

This item tracker program is designed to automate frequency analysis, provide multiple reporting views, 
And persist a back up data file.
The frequency analysis includes reading a chronological list of purchased items 
from a `.txt` file and tally how many times each distinct item appears. 
The program provides multiple reporting viewssuch as single item look up, 
For frequency list, And a text histogram (visual bar of `*` for each items count). 
    
The input is a static file `CS210_Project_Three_Input_File.txt` containing one item per line, 
while the output in on disk backup file `CS210_Project_Three_Backup_File.txt` with every item 
and its total count.
A `std:map<std::string,int>` automatically sorts item names to ensure efficent lookups/increments. 
With a simple text based menu, robust to invalid selections, 
keeping the functionality focused on reading, counting, backing up; reporting 
purchase frequencies; by encapsulating it all in a single, menu‑driven executable—the 
program meets the Corner Grocer’s need to quickly understand buying patterns in 
order to optimize their produce layout. 


# Requirements
| Feature                   | Req. ID | Requirement                                                                                                                                      |
|---------------------------|---------|--------------------------------------------------------------------------------------------------------------------------------------------------|
| Read Input File           | FR1.1   | The program shall open and read from a text file named `CS210_Project_Three_Input_File.txt`.                                                      |
|                           | FR1.2   | It shall read the file line by line and ignore any empty lines.                                                                                  |
|                           | FR1.3   | If the file cannot be opened, the program shall print an error to `stderr` and exit with a nonzero status.                                        |
| Count Item Frequencies    | FR2.1   | The program shall maintain an in‑memory frequency map (`std::map<std::string,int>`) that increments the count for each item string read.         |
|                           | FR2.2   | Item names are treated case‑sensitively and must match exactly when querying.                                                                     |
| Write Backup File         | FR3.1   | After reading and counting, the program shall write all item counts to `CS210_Project_Three_Backup_File.txt` in the format `<item>: <count>`.      |
|                           | FR3.2   | If the backup file cannot be opened for writing, the program shall print an error to `stderr` and exit with a nonzero status.                     |
| Interactive Menu          | FR4.1   | Upon startup (after backup), display a console menu with four options:<br>1. Query frequency of a specific item<br>2. Display all frequencies<br>3. Display histogram<br>4. Exit |
|                           | FR4.2   | The user shall enter a choice (1–4). Any invalid choice shall prompt “Invalid choice” and re‑display the menu.                                     |
| Menu Option Behaviors     | FR5.1   | **Query Item:**<br>• Prompt “Enter the item to query:”<br>• Read a line of text.<br>• If found, display its count; otherwise display “Item not found.” |
|                           | FR5.2   | **Display All:**<br>Print every `<item>: <count>` pair, one per line.                                                                            |
|                           | FR5.3   | **Histogram:**<br>For each item, print the item name followed by a series of asterisks (`*`), one per unit of count.                              |
|                           | FR5.4   | **Exit:**<br>Print “Exiting program.” and terminate gracefully.                                                                                   |
    
# Architecture Overview
## Layered Structure
| Layer               | Responsibility                                                                                         |
|---------------------|--------------------------------------------------------------------------------------------------------|
| Presentation        | • Console I/O (menus, prompts, and formatted output)                                                   |
| Application         | • Orchestrates the overall program flow<br>• Coordinates between file I/O, business logic, and UI    |
| Domain (Business)   | • Builds and queries the frequency map<br>• Generates histograms and aggregates                       |
| Infrastructure      | • Reads from and writes to files using `ifstream`/`ofstream`                                           |

## Key Components
| Component           | Role                                                                                                                       |
|---------------------|----------------------------------------------------------------------------------------------------------------------------|
| MainController      | • Entry point (`main()`) and overall coordinator<br>• Calls FileReader, FrequencyService, BackupWriter, and ConsoleUI in sequence |
| FileReader          | • Opens and reads the input file line by line<br>• Skips empty lines<br>• Returns list of items                            |
| FrequencyService    | • Accepts item list and builds `map<string,int>`<br>• Provides methods to:<br>  – query single item<br>  – retrieve full map<br>  – produce histogram data |
| BackupWriter        | • Takes the frequency map and writes each `<item>: <count>` to a backup file                                              |
| ConsoleUI           | • Displays the interactive menu<br>• Reads user’s menu choice and additional input<br>• Invokes FrequencyService methods and formats the output |



# Design Details
classDiagram
Main program container
    class Program {
        - inputFileName: string
        - outputFileName: string
        - backupFileName: string
        - frequencyMap: map<string, int>
        + main(): int
        - readInput(): void
        - writeBackup(): void
        - showMenu(): void
        - queryItem(item: string): void
 
    }

    %% Standard library file stream classes
    class ifstream {
        + ifstream(filename: string)
        + open(filename: string): void
        + close(): void
        + eof(): bool
        + getline(str: string): bool
    }
    class ofstream {
        + ofstream(filename: string)
        + open(filename: string): void
        + close(): void
        + write(line: string): void
    }

    %% STL map template (specialized in Program)
    class map~<K, V>~ {
        + operator[](key: K): V&
        + find(key: K): iterator
        + begin(): iterator
        + end(): iterator
    }

    %% Relationships
    Program --> ifstream : uses to read input
    Program --> ofstream : uses to write backup
    Program --> map~<string,int>~ : uses to count frequencies

# User Guide
| Option | Description                                                                                                         |
|--------|---------------------------------------------------------------------------------------------------------------------|
| 1      | Query frequency – Prompts for an item name and displays its count. If not found, prints “Item not found.”           |
| 2      | Display all frequencies – Lists every item and its count.                                                          |
| 3      | Display histogram – For each item, prints a row of asterisks (`*`) equal to its count.                              |
| 4      | Exit – Terminates the program.                                                                                      |

## Sample Session




```
            $ ./ItemTracker

            === Corner Grocer Item Tracker ===
            1. Query frequency of a specific item
            2. Display all item frequencies
            3. Display histogram of item frequencies
            4. Exit
            Select an option (1-4): 1

            Enter the item to query: apple
            Frequency of apple: 5

            === Corner Grocer Item Tracker ===
            1. Query frequency of a specific item
            2. Display all item frequencies
            3. Display histogram of item frequencies
            4. Exit
            Select an option (1-4): 3

            === Item Frequencies ===
            apple: *****
            banana: ***
            carrot: **
            date: ****

            === Corner Grocer Item Tracker ===
            1. Query frequency of a specific item
            2. Display all item frequencies
            3. Display histogram of item frequencies
            4. Exit
            Select an option (1-4): 4
            Exiting program.
```
## Troubleshooting 
**Error opening file**: Ensure `CS250_Project_Three_Input_File.txt` exists in the working directory.
**Invalid Menu Choice**: Please enter a number between 1 and 4, any other input prompts an invalid choice






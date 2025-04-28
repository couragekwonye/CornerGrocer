#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <map>

using namespace std;

int main(){
    const string inputFileName = "Input_File.txt";
    const string outputFileName = "Output_File.txt";
    const string backupFileName = "Backup_File.txt";

    map<string, int> frequencyMap;
    ifstream inputFile(inputFileName);
    if (!inputFile){
        cerr << "Error opening input file: " << inputFileName << endl;
        return 1;  
    }

    string item;

    while (getline(inputFile, item)){
        if (item.empty()) continue; // Skip empty lines
        frequencyMap[item]++;
    }
    inputFile.close();

    ofstream backupFile(backupFileName);
    if (!backupFile){
        cerr << "Error opening backup file: " << backupFileName << endl;
        return 1;  
    }
    for (const auto& pair : frequencyMap){
        backupFile << pair.first << ": " << pair.second << endl;
    }
    backupFile.close();

    // -- Interactive Menu --
    int choice;
    choice = 0;


        
            cout << "\n=== Corner Grocer Item Tracker ===\n"
                << "1. Query frequency of a specific item\n"
                << "2. Display all item frequencies\n"
                << "3. Display histogram of item frequencies\n"
                << "4. Exit\n"
                << "Select an option (1-4): ";
            cin >> choice;
            while (choice >= 1 && choice <= 4) {
                

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            switch (choice) {
        
                case 1: {
                    string queryItem;
                    cout << "Enter the item to query: ";
                    getline(cin, queryItem);
                    auto it = frequencyMap.find(queryItem);
                    if (it != frequencyMap.end()) {
                        cout << "Frequency of " << queryItem << ": " << it->second << endl;
                    } else {
                        cout << "Item not found." << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "\n=== All Item Frequencies ===\n";
                    for (const auto& pair : frequencyMap) {
                        cout << pair.first << ": " << pair.second << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "\n=== Item Frequencies ===\n";
                    for (const auto& pair : frequencyMap) {
                        cout << pair.first << ": ";
                        for (int i = 0; i < pair.second; ++i) {
                            cout << "*";
                        }
                        cout << endl;
                    }
                    break;
                }
                case 4:
                    cout << "Exiting program." << endl;
                    break;

                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
        // While choice is not an integer between 1 and 4, prompt the user to enter a valid choice
     

        while (cin >> choice) {
            cout << "Invalid choice. Please try again." << endl;
        }
    
    
    return 0;

}
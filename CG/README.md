# Corner Grocer Item Tracker

An interactive C++ program for the Corner Grocer that reads a daily log of purchased items, builds a frequency map, writes a backup report, and lets you query or visualize item frequencies via a console menu. This helps the store optimize their produce layout based on what customers buy most often.

---

## Summary

Every day, the Corner Grocer generates a plain-text record of every item sold in chronological order. Management needed a quick way to know which items sell most often so they could arrange the produce section more effectively. This C++ program:

- Reads `Input_File.txt`
- Counts how many times each item appears (using `std::map<string,int>`)
- Saves a backup report (`Backup_File.txt`)
- Provides an interactive menu to:
  1. Query a specific item’s frequency  
  2. Display all frequencies  
  3. Show a histogram of sales  
  4. Exit  

This solves the “what’s selling?” problem without manual spreadsheet work.

---

## Areas of Success

- **Robust file I/O and error handling**  
  Checked for file-open failures with clear `cerr` messages, ensuring the program fails fast if inputs aren’t available.
- **Clean use of STL containers**  
  Leveraged `std::map` for automatic sorting and counting, which makes both lookup and iteration straightforward.
- **User-friendly interactive menu**  
  Designed a simple loop with numbered choices, plus a histogram option that gives an at-a-glance view of item popularity.

---

## Areas of Improvement

- **Modularize into functions/classes**  
  Splitting file reading, backup writing, and menu handling into separate functions (or even a `Tracker` class) would reduce duplication and improve testability.
- **Use `unordered_map` for large datasets**  
  If the item list grows very large, `std::unordered_map` would offer average O(1) lookups instead of O(log N).
- **Input validation & exception safety**  
  Currently the menu loop and `cin` logic could be tightened to guard against non-integer inputs without falling into infinite loops.
- **Unit tests & CI integration**  
  Adding a small suite of GoogleTest tests and hooking up GitHub Actions would catch regressions early.
- **Configuration & security**  
  Moving file names and menu text into a config file or command-line arguments avoids hard-coded paths and makes the tool more flexible.

---

## Challenges

- **Clearing `cin` state and handling invalid menu input**  
  It took some trial and error to get `cin.ignore(numeric_limits<streamsize>::max(), '\n')` placed correctly so that entering a letter or out-of-range number wouldn’t lock the loop. I consulted cppreference.com for details on stream states and re-read relevant StackOverflow threads.
- **Building a text-based histogram**  
  Generating asterisks proportionate to each count was conceptually simple, but formatting the output neatly required testing with real data. I used sample logs and iterated until the alignment felt right.
- **Support network**  
  I’ve bookmarked the official C++ reference (cppreference.com), joined a local C++ Slack channel, and keep a small cheat-sheet of common STL patterns handy.

---

##  Skills Acquired

- **File I/O patterns** (reading line by line, writing backups)
- **Standard library mastery** (maps, streams, loops)
- **Error handling best practices** (checking return states, clear user messages)
- **Designing interactive CLI tools** (menu loops, input parsing)
- **Iterative debugging techniques** (using test data and logging)

---

## Readability, Adaptibiliy, Maintenance

- **Meaningful names & constants**  
  File names are stored in `const string` variables; menu text is grouped together.
- **Single responsibility**  
  Each logical block (reading, counting, backing up, menu) stands on its own.
- **Comments & structure**  
  Top-of-file comments explain overall purpose; inline comments cover non-obvious details.
- **Future-proofing**  
  By using the STL and simple loops, it’s easy to swap `map` for `unordered_map`, add new menu options, or redirect input/output to different sources (e.g., a database) with minimal changes.

---



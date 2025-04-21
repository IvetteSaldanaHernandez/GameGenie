# 🎮 Game Genie 
## COP3530 Final Project
### Ivette Saldana Hernandez, Emilia Delaune, Tiffany Chen
This project filters and sorts video games using both a Hash Map and a Heap data structure.

It measures and compares the performance of each, then displays the results in a webpage.

## How to Run (in VS Code)
You need the Live Server Extension: https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer
1. Open the `GameGenie` project folder in Visual Studio Code
2. Go to `.vscode/tasks.json` and:
   - Uncomment these lines for your system
     - Mac:
       - "command": "clang++",
       - "main.out"
     - Windows:
       - "command": "C:\\mingw64\\bin\\g++.exe",
       - "main.exe"
3. Open `backend/main.cpp`.
4. Build the program:
   - Mac:
     - Press Cmd + Shift + B
     - Creates `main.out`
   - Windows:
     - Ctrl + Shift + B
     - Creates `main.exe`
5. Run the program in the terminal:
      - cd backend
      - `./main.out` (or `.\main.exe`)
   - Enter a genre, platform, and minimum rating when prompted
   - When it says "Have fun gaming!", it has created the output files:
     - `frontend/hash_output.json` and `frontend/hash_time.txt`
     - `frontend/heap_output.json` and `frontend/heap_time.txt`
7. Open the frontend:
   - Go to `frontend/webpage.html`
   - Right click and choose “Open with Live Server”
   - This will open the page in your browser and show the sorted game results

##### Extra
- Hash Map and Heap perform the same sorting task
- Execution times are measured and written to text files
- Make sure `games.json` is in the `backend/` folder so the program can read it
- Some games in the games.json dataset appear multiple times with slightly different formats or across different platforms. This is due to inconsistencies in the source data, and as a result, you may occasionally see duplicate game titles in the results

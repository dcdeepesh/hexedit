# Hexedit
Hexedit is a TUI-based hex editor.

![Hexedit with the binary itself as the file being viewed](https://github.com/dcdeepesh/hexedit/blob/master/Documentation/images/Home.png)

# Table of Contents
- [Building Hexedit](#building-hexedit)
- [Usage](#usage)
  - [Main screen](#main-screen)
  - [Navigation](#navigation)
  - [Input sequences](#input-sequences)
    - Save sequence
    - Exit (quit) sequence
  - [Modes](#modes)
    - Normal mode
    - Edit mode
- [Contributing](#contributing)
- [TODO](#todo)
- [Additional Notes](#additional-notes)

## Building Hexedit
Hexedit has a single dependency - curses, and uses CMake as the build system.
To build Hexedit, start from the project root (hexedit) and follow these steps:

**Building Hexedit with CMake**

Download [n]curses and CMake:
```sh
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install cmake
```

Build Hexedit:
```sh
# currently in hexedit
mkdir build
cd build
cmake ..   # this process will take some time
make       # so will this
```

**Building Hexedit manually**

While building Hexedit manually, or with some other build system, take care of these things:
- The final executable should be linked with curses (`g++ -lcurses ...`).
- It is recommended to use `-Wall`, `-Wextra` and `-pedantic` compiler options.

## Usage
To use Hexedit, provide the file name or the path to the file as a command line argument.
If no argument is provided, Hexedit will print a short helpful error msg and quit.
If the file is found and is readable, Hexedit opens (in [normal mode](#modes)).

### Main screen
The top line tells about the index in the current row.
The left column is an index for different columns.
The middle column has the file contents in hex (with a default of 16 columns).
The right column has file contents in ASCII.
Finally, there's a status bar at the bottom that gives information about the current mode, sequence, position etc.

The ASCII contents *do not* include extended ASCII.
All control characters, extended ASCII and other unprintable characters are displayed as a dot (`.`).
There is no distinction between actual dots (ASCII: 46, hex: 0x2E) and unprintable characters,
so you have to see the hex code to distinguish between them.

There is a marker (yellow by default) that indicates your current position in the table.
There are two markers, one in the hex data, and one at the corresponding ASCII character.

### Navigation
To move the marker, following keys can be used.
The keys have a map in the home row, which should be familiar if you have used vim.
The marker is not moved, if the movement would cause the marker to go outside the bounds of file contents.

- `k`, `Arrow Up`: Move up one cell
- `j`, `Arrow Down`: Move down one cell
- `h`, `Arrow Left`: Move left one cell
- `l`, `Arrow Right`: Move right one cell

### Input sequences
To perform actions like saving a file or exiting the editor, you need to use input sequences.
Input sequences are series of keystrokes without interruption.
e.g. If you press `s`, you start the save sequence.
Now if you press any key, it will be used as an input in the series.
If this key is a part of the sequence, the corresponding task is done, otherwise the sequence is terminated.
Which means that to exit an input sequence, just press any other key that is not a part of the sequence.

Following are the different input sequences in Hexedit:
- **Save sequence** (`s`) - This sequence deals with saving files. It has following actions:
  - `s` - Overwrite the currently opened file.
  - `n` - Create a new file named `mod_<fileName>` (e.g. `main.cpp` becomes `mod_main.cpp`).
- **Exit (quit) sequence** (`q`) - This sequence deals with quitting the editor.
If there are no unsaved changes, the editor exits immediately. If there are unsaved changes:
  - `q` - Ignore unsaved changes and quit editor.

### Modes
To perform interactive tasks such as editing a byte, you need to enter the corresponding mode.
Hexedit is in Normal Mode upon start.
To enter a mode, press the corresponding key in Normal mode.

Following are the modes in Hexedit:
- **Normal mode** - Upon start, Hexedit is in Normal mode.
A key pressed in normal mode either starts an input sequence, enters a mode, or is ignored if not a part of any sequence or mode.
**Note:** To enter a mode or start an input sequence, you need to be in the Normal mode, otherwise any further keystrokes are
considered part of the mode/sequence you are in. When you are in a sequence, pressing a key that is not a part of that sequence, brings the
editor to Normal mode.
- **Edit mode** (`e`) - When `e` is pressed in Normal mode, the editor goes into edit mode for the currently highlihted byte.
Following are the inputs for edit mode:
  - `Arrow Left`/`Arrow Right` - Move left/right in the current byte (cell).
  - `Enter` - Save changes, if any, and quit edit mode
  - `q` - Ignore any changes and quit edit mode
  
## Contributing
Contributions are welcome in the form of pull requests.
Contributors are requested to be specific about the problem their edits solve, 
keep the commits clean and provide sufficiently detailed commit messages.

## TODO
Note: This TODO list is in no way exhaustive.

- Command mode
- Change indicator
- Make status bar useful
- Optimize file save process

## Additional Notes
- Right now, the status bar is pretty much useless, but it will soon start displaying information
- In some terminal emulators, the some colors may not be accurate (esp. black; as in the picture at the beginning of this file)
- If Hexedit is used in a windowed terminal emulator, the effect of resizing the window while Hexedit is running is undefined.
It is recommended not to resize the window while Hexedit is running.
The default config of 16 columns fits without any problem in a standard 80x25 terminal.

#include "ArgParser/ArgParser.h"
#include "ArgParser/ArgParseException.h"
#include "Buffer.h"
#include "Global.h"
#include "Marker.h"
#include "Color.h"
#include "Base.h"
#include "Table.h"
#include "Mode.h"

#include <curses.h>
#include <iostream>
#include <string>

std::string HELP_MSG =
    "Hexedit version 1.0\n"
    "A TUI hex editor\n\n"
    "Usage: hexedit [OPTIONS] <file>\n"
    "Options:\n"
    "  -h, --help         Print this help message\n"
    "  -s, --std-colors   Use standard colors, instead of default terminal colors\n"
    "                     Enable this if there are issues with default colors.\n"
    "  -c <cols>,         Set the number of columns. Recommended: 4, 8, 16, 32.\n"
    "    --columns=<cols> There are no restrictions on this number, but columns\n"
    "                     wider than screen can misbehave.\n\n"
    "Note: If you're having color issues (e.g. when your terminal uses light mode),\n"
    "      use option '-s' or '--std-colors'";

std::string SHORT_HELP_MSG =
    "No file provided.\n"
    "Usage: hexedit [OPTIONS] <file>\n"
    "Use option '-h' or --help' to get complete help.";

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << SHORT_HELP_MSG << std::endl;
        return 1;
    }
    
    ArgParser ap(argc, argv, "hs", "c");
    try {
        ap.parse();
    } catch (ArgParseException e) {
        std::cout << e.what() << std::endl;
        return 2;
    }

    if (ap.isSwitchSet("h") || ap.isSwitchSet("help")) {
        std::cout << HELP_MSG << std::endl;
        return 0;
    }

    auto operands = ap.getOperands();
    if (operands.size() == 0) {
        std::cout << SHORT_HELP_MSG << std::endl;
        return 1;
    }

    std::string fileName = operands[0];
    bool stdColors = ap.isSwitchSet("s") || ap.isSwitchSet("std-colors");

    int columns = 16;
    if (ap.isDataOptSet("c"))
        columns = std::stoi(ap.getDataForOpt("c"));
    if (ap.isDataOptSet("columns"))
        columns = std::stoi(ap.getDataForOpt("columns"));
    G::cols = columns;
    
    initscr();
    G::height = LINES;
    G::width = COLS;
    curs_set(0);
    cbreak();
    noecho();
    Colors::init(stdColors);
    keypad(stdscr, TRUE);

    Buffer::load(fileName);
    Table::show();
    Marker::show();
    G::setStatusBarText("File Ready");
    Mode::normal();
    
    endwin();
    Buffer::finish();
    return 0;
}
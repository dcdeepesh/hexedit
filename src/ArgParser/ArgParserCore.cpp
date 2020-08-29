#include "ArgParser/ArgParser.h"
#include "ArgParser/ArgParseException.h"

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

void ArgParser::processOperand() {
    operands.push_back(*commonIter++);
}

void ArgParser::processSingleDash() {
    string arg = *commonIter;
    string::const_iterator sIter = arg.begin() + 1;    //skip the '-'

    //e.g. in '-gfwa', loop through all the switches until 'a',
    //as 'a' might be a data option!
    while(sIter + 1 != arg.end()) {
        //what if 'g', 'f' or 'w' is not a switch(e.g. data option)?
        if(!isSwitch(*sIter))
            throw ArgParseException("Invalid switch: " + string(1, *sIter));

        switchesSet.push_back(string(1, *sIter));
        ++sIter;
    }

    //we're now at 'a' in 'gfwa'
    if(isSwitch(*sIter))
        switchesSet.push_back(string(1, *sIter));
    else if(isDataOpt(*sIter)) {    //as we guessed, 'a' is a data option!
        ++commonIter;   //move forward to its data
        string data;
        bool comeback = false;

        if(commonIter == args.end())    //we hit the end without hitting data
            data = "";
        else {
            data = *commonIter;

            //if next argument is an option, set data to empty string
            if(data[0] == '-') {
                data = "";
                comeback = true;    //and we need to come back to process this option
            }
        }
        addDataOptPair(string(1, *sIter), data);

        //if this was an "option", the --commonIter below wil cancel the ++commonIter
        //outside this if-else block and commonIter will still point to this option,
        //which will then be processed according to the scheme in parse().
        if(comeback)
            --commonIter; 
    } else {    //oops, 'a' is neither a switch, nor a data option
        throw ArgParseException("Invalid option: " + string(1, *sIter));
    }

    if(commonIter != args.end())
        ++commonIter;   //if it's not the end, move on to next arg
}

void ArgParser::processDoubleDash() {
    string arg = *commonIter, data, opt;
    string::const_iterator sIter = arg.begin() + 2;     //skip the '--'

    //e.g. in 'ofile=out.txt', opt becomes 'ofile' after this loop...
    while(sIter != arg.end() && *sIter != '=')
        opt += *sIter++;

    //we hit the end of string without encountering '='; it's a switch
    if(sIter == arg.end()) {
        switchesSet.push_back(string(opt));
    } else {      //we have a '='; it's a data option
        ++sIter;    //skip the '='

        //...and data becomes 'out.txt' after this loop
        while(sIter != arg.end())
            data += *sIter++;

        addDataOptPair(opt, data);
    }

    ++commonIter;
}

bool ArgParser::isSwitch(const char option) {
    return std::find(allSwitches.begin(), allSwitches.end(), option) != allSwitches.end();
}

bool ArgParser::isDataOpt(const char option) {
    return std::find(allDataOpts.begin(), allDataOpts.end(), option) != allDataOpts.end();
}

void ArgParser::addDataOptPair(const string &opt, const string &data) {
    //if option already exists, throw exception
    for(std::pair<string, string> p : dataOptsSet)
        if(p.first == opt)
            throw ArgParseException("Re-occurence of data option");

    //otherwise add the pair
    dataOptsSet.push_back(std::make_pair(opt, data));
}

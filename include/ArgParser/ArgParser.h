#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <vector>
#include <utility>  //for std::pair

/**
 * Parses the arguments given in initialization process to
 * seperate different types of options(switches, data options),
 * associate data to the data options etc.
 * *Almost* equivalent to getopt() in *nix.
 */
class ArgParser {
public:
    /**
     * Creates an empty ArgParser. operator() should be called
     * on these empty-initialized objects before parsing them.
     */
    ArgParser();

    /**
     * Creates the object with all required data.
     *
     * @param argc argc from main()
     * @param argv argv from main()
     * @param switches A string containg all single-letter switches
     * @param dataOptions A string containg all single-letter data options
     *
     * e.g. ArgParser(argc, argv, "cgfTR", "hyIPo");
     */
    ArgParser(const int argc, char *argv[],
        const std::string switches, const std::string dataOptions);

    /**
     * Assigns required data to class members. Should be called if the
     * object was inilitally empty-initialized; no need otherwise.
     *
     * @param argc argc from main()
     * @param argv argv from main()
     * @param switches A string containg all single-letter switches
     * @param dataOptions A string containg all single-letter data options
     *
     * e.g. ArgParser ap; //empty-initialize
     *      ap(argc, argv, "cgfTR", "hyIPo");
     */
    void operator()(const int argc, char *argv[],
        const std::string switches, const std::string dataOptions);

    /**
     * Parses the arguments and stores results in the object.
     * Can be called only after providing required data via
     * constructor or operator().
     *
     * @throws ArgParseException If the required data was not provided earlier.
     */
    void parse();

    /**
     * Checks if the specified switch is set or not. The switch should NOT
     * be prefixed by '-' or '--'.
     *
     * @param svitch Switch to check
     * @return true if set false otherwise
     */
    bool isSwitchSet(const std::string svitch) const;

    /**
     * Checks if the specified data option is set or not. The data option
     * should NOT be prefixed by '-' or '--'.
     *
     * @param dataOption Option to check
     * @return true if set false otherwise
     */
    bool isDataOptSet(const std::string dataOption) const;

    /**
     * Checks if the specified option is set or not. Option can be switch
     * ot data option. The option should NOT be prefixed by '-' or '--'.
     *
     * @param option Option to check
     * @return true if set false otherwise
     */
    bool isSet(const std::string option) const;

    /**
     * Returns the data provided with specified data option.
     *
     * @param option Data option to check for data
     * @return Data provided with the option
     * @throws ArgParseException If the specified option is not a data option.
     */
    std::string getDataForOpt(const std::string option) const;
    
    /**
     * Returns a vector containing all single- and multi-letter switches.
     *
     * @return vector of all switches
     */
    std::vector<std::string> getSwitches() const;

    /**
     * Returns a vector containing all single- and multi-letter data options.
     *
     * @return vector of all data options
     */
    std::vector<std::string> getDataOptions() const;

    /**
     * Returns a vector containing all single- and multi-letter options.
     *
     * @return vector of all options
     */
    std::vector<std::string> getAllOptions() const;

    /**
     * Returns a vector containing all operands. Operands are arguments
     * that are neither options nor data to any options.
     *
     * @return vector of all operands
     */
    std::vector<std::string> getOperands() const;

private:
    std::vector<std::string>::const_iterator commonIter;
    std::string allSwitches, allDataOpts;
    std::vector<std::string> args, operands, switchesSet;
    std::vector<std::pair<std::string, std::string> > dataOptsSet;
    bool finalized;

    //private member functions are defined in Core file
    void processOperand();
    void processSingleDash();
    void processDoubleDash();

    bool isSwitch(const char option);
    bool isDataOpt(const char option);

    void addDataOptPair(const std::string &opt, const std::string &data);
};

#endif
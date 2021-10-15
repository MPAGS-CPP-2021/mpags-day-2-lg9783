#include "processCommandLine.hpp" 
#include <iostream>

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName)

{
    /* Parse command line arguments
    const std::vector<std::string>& cmdLineArgs: arguments
    bool& helpRequested: bool for help argument
    bool& versionRequested: bool for version argument
    std::string& inputFileName: input filename
    std::string& outputFileName: output filename

    return: bool whether options are succesfully parsed
    */

    const std::size_t nCmdLineArgs{cmdLineArgs.size()};
    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            helpRequested = true;
            return true;
        } else if (cmdLineArgs[i] == "--version") {
            versionRequested = true;
            return true;

        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
            return false;
        }
    }
    return true;
}

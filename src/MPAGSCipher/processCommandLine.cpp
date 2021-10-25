#include "processCommandLine.hpp"
#include <iostream>

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName,
                        std::string& cipher, bool& encrypt, unsigned int& key)

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
        } else if (cmdLineArgs[i] == "--cipher") {
            // Handle cipher type option
            // Next element is type unless "--cipher" is the last argument, then 'caeser' is default
            if (i == nCmdLineArgs - 1) {
                ++i;
            } else {
                // Got cipher name, so assign value and advance past it
                cipher = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "--key") {
            // Handle key type option
            // Next element is value unless "--key" is the last argument, then 0 is default
            if (i == nCmdLineArgs - 1) {
                ++i;
            } else {
                // Got key value, so assign value and advance past it
                key = std::stoul(cmdLineArgs[i + 1]);
                if (key > 25) {
                    std::cout << "Key must be in range 0-25\n";
                    return false;
                }
                ++i;
            }
        } else if (cmdLineArgs[i] == "--type") {
            // Handle encryption/decryption type option
            // Next element is value unless "--type" is the last argument, then encrypt is default
            if (i == nCmdLineArgs - 1) {
                ++i;
            } else {
                // Got key value, so assign value and advance past it
                if (cmdLineArgs[i + 1] == "encrypt") {
                    // It is encrypt by default
                    ++i;
                } else if (cmdLineArgs[i + 1] == "decrypt") {
                    encrypt = false;
                    ++i;
                } else {
                    std::cout << "incompatable encrypt/decrypt type provided"
                              << std::endl;
                    return false;
                }
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

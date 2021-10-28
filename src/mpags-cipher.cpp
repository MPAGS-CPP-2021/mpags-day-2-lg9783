#include "TransformChar.hpp"
#include "processCommandLine.hpp"
#include "runCaesarCipher.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    bool encrypt{true};
    unsigned int key{0};
    std::string cipher{""};

    // If there has been a failure with processinging command line arguments
    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested,
                            inputFile, outputFile, cipher, encrypt, key)) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --cipher NAME    Specify cipher type, default = 'Caeser'\n\n"
            << "  --key K          Key = K (0-25), default = 0 \n\n"
            << "  --type           'encrypt' or 'decrypt', default = 'encrypt'\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream in_file{inputFile};
        if (!in_file.good()) {
            std::cerr << "Incompatable input file ('" << inputFile << "')\n";
            return 1;
        } else {
            // loop over each character from user input
            while (in_file >> inputChar) {
                inputText += transformChar(inputChar);
            }
            in_file.close();
        }
    } else {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    // add cipher cases
    inputText = runCaesarCipher(inputText, key, encrypt);

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::ofstream out_file{outputFile};

        if (!out_file.good()) {
            std::cerr << "Incompatable output file ('" << outputFile << "')\n";
            return 1;
        } else {
            out_file << inputText;
            out_file.close();
        }
    } else {
        std::cout << inputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
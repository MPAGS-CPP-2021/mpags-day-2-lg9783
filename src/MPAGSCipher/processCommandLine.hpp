#include <vector>
#include <string>

#ifndef MAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MAGSCIPHER_PROCESSCOMMANDLINE_HPP


bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName);

#endif
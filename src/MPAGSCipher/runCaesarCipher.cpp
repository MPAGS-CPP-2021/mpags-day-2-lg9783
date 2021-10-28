#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::string runCaesarCipher(const std::string& inputText, const unsigned int& key, const bool& encrypt)
{
    /*
    Function to run the caesar cipher on an input string

    inputText: input string
    key: cipher key
    encrypt: bool for encryption (true) or decryption (false)
    */


    // Create a vector of the alphabet
    const std::vector<char> alphabet={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    std::string outputText{""};

    int newInd;

    for (char c : inputText){
        std::vector<char>::const_iterator itr =std::find(begin(alphabet), end(alphabet), c);

        if(encrypt){
            newInd =std::distance(alphabet.begin(), itr)+key;
            // std::cout<< newInd << std::endl;
        }
        else{
            newInd = std::distance(alphabet.begin(), itr)-key;
        }

        if((newInd<=25)&&(newInd>=0))
            {outputText += alphabet[newInd];} 

        else if(newInd%26>=0)
        {outputText += alphabet[newInd%26];}

        else if(newInd%26<0)
        {outputText += alphabet[26 + newInd%26];}
    }

    return outputText;
   
}


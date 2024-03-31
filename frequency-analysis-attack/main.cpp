#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
Read the content of the file and store in the buffer
*/
int readFile(const string& filename, char* &buffer) {

    // Open the File to Read
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return -1;
    }

    // Calculate the file size and create buffer
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    file.seekg(0, ios::beg);
    buffer = new char[file_size + 1]; // +1 for the null terminator

    // Read the data
    file.read(buffer, file_size);

    // Ensure null-termination
    buffer[file_size] = '\0';

    // Close the file
    file.close();
    return file_size;
}


int main()
{

    // Read the Cipher File
    char * cipherText;
    int countCharacters = readFile("cipher.txt", cipherText);
    if(countCharacters == -1){
        cout << "Unable to read the Cipher Text file. Please provide correct path!" << endl;
        return -1;
    }



    return 0;
}

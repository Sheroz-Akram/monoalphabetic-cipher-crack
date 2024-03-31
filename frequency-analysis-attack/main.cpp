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

    // Display the read details
    cout << "**** File Read Complete ****" << endl;
    cout << "Total Characters Read: " << file_size << endl;

    // Close the file
    file.close();
    return file_size;
}

/*

Do the frequency analysis and calculate the percentage of each character used

*/
void frequencyAnalysis(char * &alphabets, float * &frequency, char * cipherText, int cipherTextLength){

    // Find the Frequency of Each Letter and Calculate the percentage
    int totalCount = 0;
    for(int i = 0; i < 26; i++){
        int count = 0;
        for(int k = 0; k < cipherTextLength; k++){
            if(alphabets[i] == cipherText[k] || alphabets[i] - 32 == cipherText[k]){
                count++;
                totalCount++;
            }
        }
        frequency[i] = count * 1.0;
    }

    cout << endl << "**** Frequency Analysis Complete ****" << endl;
    cout << "Total Usable Characters (without Numbers & Special Characters): " << totalCount << endl;

    // Our Frequency Table
    cout << endl << "**** Frequency Table ****";
    for(int i = 0; i < 26; i++){
        if(i % 5 == 0){
            cout << endl;
        }
        cout << alphabets[i] << " : " << (int) frequency[i] << "\t|\t";
    }

    // Calculate the percentages
    for(int i = 0; i < 26; i++){
        frequency[i] = (frequency[i] * 100) / totalCount;
    }

    // Our Frequency Percentage Table
    cout << endl << endl << "**** Frequency Percentage Table ****";
    for(int i = 0; i < 26; i++){
        if(i % 5 == 0){
            cout << endl;
        }
        cout << alphabets[i] << " : " << (int) (frequency[i]) << "%" << "\t|\t";
    }
}

/*

Sort both arrays by their frequency

*/
void sortByFrequency(char * &alphabets, float * &frequency){
    for(int i = 0; i < 25 ; i++){
        for(int k = i + 1; k < 26; k++){
            if(frequency[i] < frequency[k]){

                // Swap the Values
                float temp = frequency[k];
                frequency[k] = frequency[i];
                frequency[i] = temp;

                // Swap the Alphabets
                char tempC = alphabets[k];
                alphabets[k] = alphabets[i];
                alphabets[i] = tempC;

            }
        }
    }


    // Frequency based letters
    cout  << endl << endl << "**** Letters sorted to frequency ****" << endl;
    for(int i = 0; i < 26 ; i++){
        cout << alphabets[i] << " " ;
    }
    cout << endl;
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

    // Now we do frequency analysis
    char * alphabets = new char[26];
    for (int i = 0; i < 26; i++) {
        alphabets[i] = 'a' + i;
    }
    float * frequencyPercentage = new float[26];

    frequencyAnalysis(alphabets, frequencyPercentage, cipherText, countCharacters);

    // Sort Arrays to their Respected frequency
    sortByFrequency(alphabets, frequencyPercentage);

    return 0;
}

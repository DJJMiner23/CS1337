//Dayne John - CS1337.003
//String Processing

//  changelog:
//  03/22/2021 - Dayne
//      set up the program to read the file
//      created a function to control the reading of the file
//      created a function to store the words and sentences into vectors
//  03/23/2021 - Dayne
//      created a function to report the number of characters and the number of words in each sentence
//  03/24/2021 - Dayne
//      created a function to analyze the sentences
//      created a function to display the sentence analysis
//      found a bug where the number of vowels, consonants, etc. was accumulating
//  03/25/2021 - Dayne
//      fixed the accumulating count bug by creating a function to reset the count
//      created a function to display the original sentence
//      created all functions to display each sentence in each particular case (Title, Toggle, Spongebob, etc.)
//  03/26/2021 - Dayne
//      reorganized the functions and gave more self-explanatory names to the functions
//      created a function to identify the exception words from the sentence
//  03/27/2021 - Dayne
//      added more comments to clarify each function's purpose
//      separated each function for their individual specific purpose
//      found a bug where my exception words were being printed twice in the sentence case with exceptions
//      fixed this by creating a function to remove duplicate exception words from the sentence
//  03/28/2021 - Dayne
//      made the program more user-friendly
//      improved the spacing of the program
//  notes:
//      This program will read multiple sentences from a text file and perform string manipulation on each sentence by converting each sentence to a specific case
//      such as: Sentence Case, Title Case, Toggle Case, Spongebob Case.
//      It will also report specifics about each sentence such as: the number of words, number of characters, number of vowels, number of consonants,
//      number of spaces, number of punctuation marks, and other characters.
//      In order to continue reading each sentence, the user must press the Enter key. If they don't they will be re-prompted until they press the Enter key.


#include <iostream> //for input and output
#include <ctime>   //for random number generator
#include <ctype.h>  //for toupper,tolower, isupper, ispunt, etc.
#include <string>   //for find()
#include <vector>   //for .push_back
#include <conio.h> ////for kbhit and getch
#include <fstream> //for file reading
using namespace std;

vector<string> sentences; //vector to store each sentence
vector<vector<string>> words; //vector to store each word
vector<string> exceptionWords; //vector to store exception words
int totalSentences; //to keep count of the amount of sentences
int previousSentence; //variable used to shift by one sentence
int numOfVowels, numOfConsonants, numOfPunctuations, numOfSpaces, numOfOtherCharacters; //to keep count of the number of spaces consonants, etc.
//**********************************************//
//bool showflowControl = false; used this for debugging to make the program talk to me

/* Showflow
void showflow(string msg) {
    if (showflowControl) {
        cout << "--- at: " << msg << endl;
    }
} Showflow */


ifstream inputFile("Tongue-Twisters.txt"); //this opens the file and I hardwired file name

//ReadTheFile
void ReadTheFile() {
    //showflow("ReadingTheFile");
    string temp; //temporary string
    getline(inputFile, temp); //get each individual sentence
    sentences.push_back(temp); //store it in sentences
    totalSentences++; //increment sentence count
    previousSentence = totalSentences-1;
    cout << "Original Sentence: " << temp << endl; //print the original sentence
    //showflow("ExitingReadTheFile");
} //ReadTheFile

//DisplayLengthOfSentenceInCharacters
void DisplayLengthOfSentenceInCharacters() {
    //showflow("Displaying Length of sentence in chars");
    cout << "Number of characters: " << sentences.at(previousSentence).length() << endl; //report number of characters in the sentence
    //showflow("Successfully Displayed Length of sentence in chars");
} //DisplayLengthOfSentenceInCharacters

//ReadTheWords
void ReadTheWords() {
    //showflow("ReadingTheWords");
    string currentSentence = sentences.at(previousSentence); //adjust to the correct sentence
    string temp = ""; //temporary string
    for(char character: currentSentence) {
        if(ispunct(character)) { //if character is punctuation then ignore and move on
            continue;
        } else if(character == ' ' || character == '.') {
            words.push_back(vector<string>()); //if it isn't then add this element to the words vector
            words[previousSentence].push_back(temp);
            temp = "";
        } else {
            temp = temp + character;
        }
    }
    //showflow("ExitingReadTheWords);
} //ReadTheWords

//DisplayNumberOfWords
void DisplayNumberOfWords() {
    //showflow("Displaying Number of words");
    cout << "Number of words: " << words[previousSentence].size()+1 << endl; //report the number of words in the sentence
    //showflow("Successfully displayed number of words");
} //DisplayNumberOfWords

//DisplayLongestWord
void DisplayLongestWord() {
    //showflow("DisplayingLongestWord");
    int maxLength = 0; //set the longest length of a word to 0
    string longestWord; //variable to store the longest word
    for(string word: words.at(previousSentence)) { //go through the words of the sentences
        if(word.length() > maxLength) { //if the current word's length is greater than 0
            maxLength = word.length(); //then set that to the longest length
            longestWord = word; //this is now the longest word
        }
    }

    cout << "Longest Word: " << longestWord << endl; //print out the longest word of the sentence
    //showflow("Successfully displayed the longest word");
} //DisplayLongestWord

//switchSentenceToLowerCase
string switchSentenceToLowerCase(string sentence) {
    //showflow("SwitchingSentenceToLowerCase");
    string lowerCase = ""; //temporary string
    for(char character: sentence) {
        lowerCase += tolower(character); //change the sentence to lower case
    }
    //showflow("SuccessfullySwitchedSentenceToLowerCase");
    return lowerCase;
} //switchSentenceToLowerCase

//CapitalizeSentence
string CapitalizeSentence(string sentence) {
    //showflow("Capitalizing Sentence");
    string upperCase = ""; //temporary string
    for(char character: sentence) {
        upperCase += toupper(character); //capitalize the sentence
    }
    //showflow("Successfully capitalized sentence");
    return upperCase;
} //CapitalizeSentence

//characterIsVowel
bool characterIsVowel(char character) {
    //showflow("CheckingIfCharacterIsVowel");
    string numOfVowels = "aeiouy"; //string to hold the set of vowels
    if(numOfVowels.find(tolower(character)) != -1) { //if we did find a vowel in the sentence
        return true; //it is a vowel
    } else { //if we didn't find a vowel in the sentence
        return false; //it's not a vowel
    }
    //showflow("Successfully check if character was a vowel");
} //characterIsVowel

//AnalyzeSentence
void AnalyzeSentence() {
    //showflow("AnalyzingSentence");
    string currentSentence = sentences.at(previousSentence); //adjust to the correct sentence
    for(char character: currentSentence) {
        if(ispunct(character) && character != ' ') { //if character is punctuation and not a space
            numOfPunctuations++; //then add to number of punctuations
        } else if(isspace(character)) { //if character is a space
            numOfSpaces++; //then add to number of spaces
        } else if(characterIsVowel(character)) { //if character is a vowel
            numOfVowels++; //then add to number of vowels
        } else if(isalpha(character)) { //if character is a consonant
            numOfConsonants++; //then add to number of consonant
        } else //otherwise if character is none of these
            numOfOtherCharacters++; //then add to number of other characters
    }
    //showflow("Sentence Successfully Analyzed");
} //AnalyzeSentence

//DisplaySentenceAnalysis
void DisplaySentenceAnalysis() { //display the number of vowels, consonants, spaces, punctuations, and other characters
    //showflow("DisplayingSentenceAnalysis");
    cout << "Vowels: " << numOfVowels << "; " << "Consonants: " << numOfConsonants << "; ";
    cout << "Spaces: " << numOfSpaces << "; " << "Punctuation Marks: " << numOfPunctuations << "; ";
    cout << "Others: " << numOfOtherCharacters << "." << endl;
    //showflow("SuccessfullyDisplayedSentenceAnalysis");
} //DisplaySentenceAnalysis

//resetCount
void resetCount() { //reset the number of vowels, consonants, spaces, punctuations, and others to 00 so it doesn't accumulate
    //showflow("Resetting Count");
    numOfVowels = 0;
    numOfConsonants = 0;
    numOfSpaces = 0;
    numOfPunctuations = 0;
    numOfOtherCharacters = 0;
    //showflow("Successfully reset count");
} //resetCount

//DisplaySentenceInTitleCase
void DisplaySentenceInTitleCase() {
    //showflow("DisplayingSentenceInTitleCase");
    string currentSentence = sentences.at(previousSentence); //adjust to the correct sentence
    string priorSentenceInLowerCase = switchSentenceToLowerCase(currentSentence); //convert the current sentence to all lower case
    priorSentenceInLowerCase[0] = toupper(priorSentenceInLowerCase[0]); // capitalize the first character
    for(int i = 1; i < priorSentenceInLowerCase.length()-1; i++) { //go through the sentence
        if(priorSentenceInLowerCase[i] == ' ' && !ispunct(priorSentenceInLowerCase[i+1]) && !isspace(priorSentenceInLowerCase[i+1])) { //if the character is not a space
            priorSentenceInLowerCase[i+1] = toupper(priorSentenceInLowerCase[i+1]); //capitalize the first character of each word in the sentence
        }
    }

    cout << "Title Case: " << priorSentenceInLowerCase << endl; //print title case
    //showflow("Successfully displayed sentence in Title Case");
} //DisplaySentenceInTitleCase

//DisplaySentenceInSentenceCase
void DisplaySentenceInSentenceCase() {
    //showflow("DisplayingSentenceInSentenceCase");
    string currentSentence = sentences.at(previousSentence); //adjust to the correct sentence
    string priorSentenceInLowerCase = switchSentenceToLowerCase(currentSentence); //convert the entire sentence to lower case
    priorSentenceInLowerCase[0] = toupper(priorSentenceInLowerCase[0]); //capitalize the first character
    cout << "Sentence Case: " << priorSentenceInLowerCase << endl; //print sentence case
    //showflow("Successfully displayed sentence in Sentence Case");
} //DisplaySentenceInSentenceCase

//IdentifyTheExceptionWords
void IdentifyTheExceptionWords() {
    //showflow("IdentifyingExceptionWords");
    vector<string> newWord = words.at(previousSentence); //store the words
    for(int i = 0; i < newWord.size(); i++) {
        string temp = ""; //temporary string to hold new exception word
        if(isupper(newWord.at(i)[0])) {
            temp += newWord.at(i)[0];
        }
        for(int j = 1; j < newWord.at(i).length(); j++) {
            if(isupper(newWord.at(i)[j])) {
                break;
            } else {
                temp += newWord.at(i)[j];
            }
        }
        if(temp == newWord.at(i)) {   //if the temporary string matches the word that we're currently at
            exceptionWords.push_back(temp); //then this is an exception word
        }

    }
    //showflow("Successfully identified exception words");
} //IdentifyTheExceptionWords

void makeDuplicateWordsLowercase(string &s) {
    for(string word: exceptionWords) { //go through the exception words vector
        string temp = ""; //temporary string to find the duplicate word
        int indexOfWord = s.find(word) + word.length();
        for(; indexOfWord < s.length(); indexOfWord++) {
            temp += s.at(indexOfWord);
            int newIndex = temp.find(word);
            if(newIndex != -1) {
                s.replace(newIndex + word.length(), word.length(), switchSentenceToLowerCase(word)); //if the new index is not equal to -1 then it is a duplicate so switch it to lower case
            }
        }

    }

}

void DisplaySentenceInSentenceCaseWithExceptions() {
    string currentSentence = sentences.at(previousSentence); //getting the most recent sentence
    string priorSentenceInLowerCase = switchSentenceToLowerCase(currentSentence); //change the sentence to lowercase
    for(int i = 0; i < priorSentenceInLowerCase.length()-1; i++) { //this is used to check two adjacent characters at a time
        if(priorSentenceInLowerCase[i] == ' ' && !ispunct(priorSentenceInLowerCase[i+1]) && !isspace(priorSentenceInLowerCase[i+1])) { //i is the current character and i+1 is the adjacent character
            for(string word: exceptionWords) { //loop through exception words
                if(toupper(priorSentenceInLowerCase[i+1]) == word[0]) { //this checks if the adjacent character in the sentence is the same as the first character in each word that is present in the exceptionWords vector
                    bool wordsDoNotMatch = false;
                    for(int j = 1; j < word.length(); j++) { //since the first character of each word has already been checked, we're checking the adjacent characters of that word
                        if(priorSentenceInLowerCase[i+1+j] != word[j]) { //compare the adjacent characters to the adjacent characters in the word to see if they are equivalent
                            wordsDoNotMatch = true;
                            break;
                        }
                    }
                    if(!wordsDoNotMatch) {
                        priorSentenceInLowerCase[i+1] = toupper((priorSentenceInLowerCase)[i+1]); //if they are equivalent, then we know that the word is an exception word so capitalize it
                    }
                }
            }
        }
    }
    priorSentenceInLowerCase[0] = toupper(priorSentenceInLowerCase[0]); //capitalize the first character of the sentence
    makeDuplicateWordsLowercase(priorSentenceInLowerCase);
    cout << "Sentence Case With Exceptions: " << priorSentenceInLowerCase << endl; //print sentence case with exceptions
    exceptionWords.clear(); //empty the vector

}

//DisplaySentenceInToggleCase
void DisplaySentenceInToggleCase() {
    //showflow("DisplayingSentenceInToggleCase");
    string currentSentence = sentences.at(previousSentence);
    string priorSentenceInUpperCase = CapitalizeSentence(currentSentence);
    priorSentenceInUpperCase[0] = tolower(priorSentenceInUpperCase[0]); // changing 1st char to lower
    for(int i = 1; i < priorSentenceInUpperCase.length()-1; i++) {
        if(priorSentenceInUpperCase[i] == ' ' && !ispunct(priorSentenceInUpperCase[i+1]) && !isspace(priorSentenceInUpperCase[i+1])) {
            priorSentenceInUpperCase[i+1] = tolower(priorSentenceInUpperCase[i+1]);
        }
    }
    cout << "Toggle Case: " << priorSentenceInUpperCase << endl;
    //showflow("Successfully displayed sentence in Toggle Case");
} //DisplaySentenceInToggleCase

//DisplaySentenceInSpongebobCase
void DisplaySentenceInSpongebobCase() {
    //showflow("DisplayingSentenceInSpongebobCase");
    string currentSentence = sentences.at(previousSentence);
    for(int i = 0; i < currentSentence.length(); i++) {
        int n = rand() % 2;
        if(n==1) { // if n is equal to 1 then convert the current letter of the word to uppercase
            currentSentence[i] = toupper(currentSentence[i]);
        } else { //otherwise convert it to lowercase
            currentSentence[i] = tolower(currentSentence[i]);
        }
    }
    cout << "Spongebob Case: " << currentSentence << endl;
    //showflow("Successfully displayed sentence in Spongebob Case");
} //DisplaySentenceInSpongebobCase

//ControlFileRead
void ControlFileRead() {
    char userInput;
    while(true) {
        cout << "\nPress the Enter key to continue..." << endl;
        cout << "---------------------------------------------" << endl;
        userInput = _getch();
        if(userInput == '\r') {
            ReadTheFile();
            system("COLOR 0B"); //change the color of the output
            DisplayLengthOfSentenceInCharacters();
            ReadTheWords();
            DisplayNumberOfWords();
            DisplayLongestWord();
            AnalyzeSentence();
            DisplaySentenceAnalysis();
            resetCount();
            DisplaySentenceInTitleCase();
            DisplaySentenceInSentenceCase();
            IdentifyTheExceptionWords();
            DisplaySentenceInSentenceCaseWithExceptions();
            DisplaySentenceInToggleCase();
            DisplaySentenceInSpongebobCase();
        } else if(userInput != '\r') {
            cout << "Invalid key pressed. \nPlease press the Enter key to continue..." << endl;
        }

        if(inputFile.eof()) {
            break;
        }
    }
    cout << "\nYou have reached the end of the file. Goodbye! " << endl; //let the user know they have reached the end of the file
    inputFile.close(); //close the file
} //ControlFileRead

//main
int main() {
    srand(time(NULL));
    cout << "Hello! Welcome to the String Processing Program!" << endl; //user-friendly message
    ControlFileRead();
    return 0;
} //main

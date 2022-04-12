// main.cpp
// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
using namespace std;

#include "csvstream.h"
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <set>
using namespace std;


int main (int argc, char *argv[]) {
    cout.precision(3);
    
    if (!(argc == 3 || argc == 4)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    if (argc == 4) {
        if (strcmp(argv[3], "--debug")) {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }
    }
    
    ifstream fileTrain;
    //training file
    fileTrain.open(argv[1]);
    
    if (!fileTrain.is_open()) {
        //error message if input file can't be opened
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    
    ifstream fileTest;
    fileTest.open(argv[2]);
    //testing file
    if (!fileTest.is_open()) {
        //error message if input file can't be opened
        cout << "Error opening file: " << argv[2] << endl;
        return 1;
    }

    class Classifier {
    private:
        int numberOfPosts;
        int numberOfTotalUniqueWords;
        bool debug;
        int numPostsWithW;
        string allWords;
        
    public:
        //1. open csvstream
        //2. read values from csvstream
        //3. store values in variables
        void ClassifierTrain(string file) {
            allWords = "";
            csvstream fileTrain(file);
            map<string, string> row;
            while (fileTrain >> row) {
                string post = row["content"];
                
                allWords = allWords + post + " ";
                numberOfPosts += 1;
            }
            set<string> words = unique_words(allWords);
            numberOfTotalUniqueWords = (int)words.size();
            
        }
        
        set<string> unique_words(const string& str) {
            istringstream source(str);
            set<string> words;
            string word;
            // Read word by word from the stringstream and insert into the set
            while (source >> word) {
                words.insert(word);
            }
            return words;
        }



        
    };
    
    //should we be iterating through the csv within the class
    //what sort of variables should we account for in the private interface for classifier
    //does csv stream account for the headder
    //where should we use the uniqueWords function (within class?)
    //code layout in general
    //is a set a vector?
    //should we have a set/vector for each post? should we then have an array of the sets

    
    /*
    XThe total number of posts in the entire training set.
    XThe number of unique words in the entire training set. (The vocabulary size.)
    For each word w, the number of posts in the entire training set that contain w.
    For each label , the number of posts with that label.
    For each label  and word , the number of posts with label  that contain .
     */
  // Open file
  csvstream csvin(argv[1]);

  // A row is a map<string, string>, key = column name, value = datum
  map<string, string> row;

  // Read file
  while (csvin >> row) {
    cout << "row:" << "\n";
    for (auto &col:row) {
      const string &column_name = col.first;
      const string &datum = col.second;
      cout << "  " << column_name << ": " << datum << "\n";
    }
  }



    return 0;
}


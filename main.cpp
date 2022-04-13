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
        int numberOfPosts; //1
        map <string, int> uniqueWords; //2,3
        map <string, int> uniqueLabels; //4
        map<pair<std::string, std::string>, int> part5; //5
        bool debug;
        vector<string> allTags;
        vector<string> allWords;
        
    public:
        void ClassifierTrain(string file) {
            csvstream fileTrain(file);
            map<string, string> row;
            if (debug==true) {
                cout << "training data:" << endl;
            }
            while (fileTrain >> row) {
                numberOfPosts++; //1
                if (uniqueLabels.find(row["tag"]) != uniqueLabels.end()) {//4
                    uniqueLabels[row["tag"]]++;
                }
                else {
                    uniqueLabels[row["tag"]] = 1;
                }

                if (debug==true) {
                    cout << "  label = " << row["tag"] << ", content = " << row["content"] << endl;
                }

                for (string wordContent : unique_words(row["content"])) {//2,3
                    if (uniqueWords.find(wordContent) != uniqueWords.end()) {
                        uniqueWords[wordContent] += 1;
                    }
                    else {
                        uniqueWords[wordContent] = 1;
                    }
                    //5
                    pair<string, string> tagContentPair;
                    tagContentPair.first = row["tag"];
                    tagContentPair.second = wordContent;

                    
                    if (part5.find(tagContentPair) != part5.end()) {
                        part5[tagContentPair] += 1;
                    }
                    else {
                        part5[tagContentPair] = 1;
                    }
                }
            }


            for (auto tagSingle : uniqueLabels) {
                allTags.push_back(tagSingle.first);
            }
            for (auto wordSingle : uniqueWords) {
                allWords.push_back(wordSingle.first);
            }


            sort(allTags.begin(), allTags.end());
            sort(allWords.begin(), allWords.end());

            cout << "trained on " << numberOfPosts << " examples" << endl;
            if (debug==true) {
                cout << "vocabulary size = " << uniqueWords.size() << endl;
            }

            cout << endl;
            if (debug==true) {
                cout << "classes:" << endl;
                for (string tag : allTags) {
                    cout << "  " << tag << ", " << uniqueLabels[tag] << 
                        " examples, log-prior = "
                        << log(static_cast<double>(uniqueLabels[tag])) / //what if uniquelabels[tag] is 0??? (no occuances of a specific tag
                            static_cast<double>(numberOfPosts) << endl;
                }

                vector<pair<string, string> > pairs;
                for (auto labelKey : part5) {
                    pairs.push_back(labelKey.first);
                }

                // info on each pair of {tag, word}
                cout << "classifier parameters:" << endl;

                vector<pair<string, string>> iterPairs;
                pair<string, string> specificPair;
                for (string tags : allTags) {
                    for (string words : allWords) {
                        specificPair.first = tags;
                        specificPair.second = words;
                        iterPairs.push_back(specificPair);
                    }
                }
                //count= and log likelihood stuff here
                cout << endl;
            }


        }
        bool operator() (int i, int j) { return (i < j); }
  
        
        void labelAmountFinder(set<string> labels, string file) {
            set<string>::iterator itr;
            for (itr = labels.begin(); itr != labels.end(); itr++) {
                int labelAmount = 0;
                csvstream fileTrain(file);
                map<string, string> row;
                while (fileTrain >> row) {
                    string post = row["tag"];
                    if (post.find(*itr)) {
                        labelAmount += 1;
                    }
                }
                uniqueLabels[*itr] = labelAmount;
            }
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


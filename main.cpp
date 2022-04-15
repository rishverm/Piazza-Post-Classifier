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
#include <cmath>
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
        map<pair<string, string>, int> part5; //5
        map<pair<string, string>, double> logLikelihoodMap; //testing
        map<string, double> logProbabilityMap; //testing
        map<string, double> logPriorMap;
        bool debug;
        vector<string> allTags;
        vector<string> allWords;
        
        
    public:
        
        
        void ClassifierTrain(string file, bool debug) {
            numberOfPosts = 0;
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
                    cout << "  label = " << row["tag"]
                    << ", content = " << row["content"] << endl;
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
                    double fraction = (static_cast<double>(uniqueLabels[tag]) /
                                       static_cast<double>(numberOfPosts));
                    double logPrior = log(fraction);
                    cout << "  " << tag << ", " << uniqueLabels[tag] << 
                        " examples, log-prior = "
                    << logPrior << endl;
                    logPriorMap[tag] = logPrior;
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
            
                for (auto pair : iterPairs) {
                    double fraction = 0;
                    double logLikelihood = 0;
                    if (part5[pair] != 0) {
                        fraction = (static_cast<double>(part5[pair]) /
                                    static_cast<double>(uniqueLabels[pair.first]));
                        logLikelihood = log(fraction);
                    }
                    
                    // Use when w does not occur in posts labeled C but does occur
                    // in the training data overall
                    else if (uniqueWords[pair.second] > 0) {
                        fraction = (static_cast<double>(uniqueWords[pair.second]) /
                                    static_cast<double>(numberOfPosts));
                        logLikelihood = log(fraction);
                    }
                        
                    //Use when w does not occur anywhere in the training set
                    
                    else {
                        fraction = (static_cast<double>(1) /
                                    static_cast<double>(numberOfPosts));
                        logLikelihood = log(fraction);
                    }
                    
                    
                    if (part5.find(pair) != part5.end()
                        && part5[pair] != 0) {
                        cout << "  " << pair.first << ":"
                        << pair.second << ", count = " <<
                        part5[pair] << ", log-likelihood = " <<
                        logLikelihood << endl;;
                    }
                    
                    logLikelihoodMap[pair] = logLikelihood;
                    
                }
                
                cout << endl;
                
            }
            
        
        }
        
        //map<pair<string, string>, double> logLikelihoodMap; //testing
        //map<string, double> logPriorMap;
        
        void ClassifierTest(string file) {
            int numCorrectPredictions = 0;
            int numTotalPredictions = 0;
            csvstream fileTest(file);
            map<string, string> row;
            //string predicted = "taco"; //IS THIS THE FIRST LABEL?
            //double maxLogProb = 10; //IS THIS THE LOG PROBABBILITY OF THE FIRST LABEL?
            
            cout << "test data:" << endl;
            //use vector of tags instead
            //put the log probabilities of each post into a map
            while (fileTest >> row) {
                ++numTotalPredictions;
                for (auto &it : allTags) {
                    logProbabilityMap[it] = logPriorMap[it];
                    pair<string, string> labelWordPair;
                    labelWordPair.first = it;
                    set<string>eachWord = unique_words(row["content"]);
                    
                    for (auto &word : eachWord) {
                        
                        
                        
                        labelWordPair.second = word;
                        
                        if (logLikelihoodMap[labelWordPair] == 0) {
                            logLikelihoodMap[labelWordPair] = log(static_cast<double>(1) /
                                                    static_cast<double>(numberOfPosts));
                        }
                        
                        logProbabilityMap[it] += logLikelihoodMap[labelWordPair];
                    }
                
                }
                
                string predicted = findMaxLogProbability(logProbabilityMap).first;
                double maxLogProb = findMaxLogProbability(logProbabilityMap).second;
                if (predicted == row["tag"]) {
                    ++numCorrectPredictions;
                }
                
                
                cout << "  correct = " << row["tag"] << ", predicted = "
                << predicted << ", log-probability score = " << maxLogProb << endl;
                cout << "  content = " << row["content"] << endl;
                cout << endl;
            }
            
            cout << "performance: " << numCorrectPredictions << " / " << numTotalPredictions << " posts predicted correctly" << endl;
            
                
                
            
          
        }
        // make a vector of pairs of the log probabilites
        //
        pair<string, double> findMaxLogProbability(map<string, double> logProbabilities) {
            pair<string, double> maxPair = *logProbabilities.begin();
            double maxLogProb = (*logProbabilities.begin()).second;
            for (auto &element : logProbabilities) {
                if (maxLogProb < element.second) {
                    maxLogProb = element.second;
                    maxPair = element;
                }
                
            }
            return maxPair;
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
    //argv[1] is training
    //argv[2] is testing
    Classifier * c = new Classifier;
    c->ClassifierTrain(argv[1], argv[3]);
    c->ClassifierTest(argv[2]);

    return 0;
}


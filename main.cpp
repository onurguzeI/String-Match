#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;



vector<string> splitSentences(string);
vector<string> splitStatements(string);
vector<string> splitWords(string);
void stringToUpper(string&);
int numberOfMatches(string&, string&);
vector<string> removeStopWords(vector<string>&);
int NoOfMatches(string&, vector<string>&);
void printVector(vector<string>&);
string concatenateWords(vector<string>&);
void printAnswer(string&, string&);
const string stopWords[] = {};
bool isEqual(string&, string&);

int main(int argc, char const *argv[]) {
    
    
    auto start = chrono::system_clock::now();
    vector<string> statements = splitStatements("statements.txt");
    vector<string> sentences = splitSentences("the_truman_show_script.txt");
    
    
    int index;
    
    
    
    for (int i = 0; i < statements.size(); i++) {
    
        cout << statements[i] << endl;
        index = NoOfMatches(statements[i], sentences);
        printAnswer(statements[i], sentences[index]);
    }

    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsedSeconds = end  - start;
    cout << "Run Time: "<< elapsedSeconds.count() <<" seconds"<< endl;

    return 0;
}

vector<string> splitSentences(string fileName) {
    //It splits the sentences by delimiter '.' in a given text file.
    ifstream myFile(fileName);
   vector<string> sentenceVector;
    string sentence;

    
    while (getline(myFile, sentence, '.'))
    {
        if (!sentence.empty())
            sentenceVector.push_back(sentence);
        }
    myFile.close();
    return sentenceVector;
}




vector<string> splitStatements(string fileName) {
    ifstream questionFile(fileName);
    vector<string> questionVector;
    string question;

    while(getline(questionFile, question)) {
        if (!question.empty())
            questionVector.push_back(question.substr(0,question.find('.')));
        //getting rid of the '?' by slicing the last element
    }

    questionFile.close();
    return questionVector;
}

vector<string> splitWords(string s) {
    istringstream sStream(s);
    vector<string> wordVector;
    string word;

    while (getline(sStream, word, ' ')) {
        if (!word.empty())
            wordVector.push_back(word);
    }
    return wordVector;
}

void stringToUpper (string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

int numberOfMatches(string& s1, string& s2) {d:
     
    vector<string> s1Words = splitWords(s1);
    vector<string> s2Words = splitWords(s2);

    int matchCount = 0;

    for (int i = 0; i < s1Words.size(); i++) {
        for (int j = 0; j < s2Words.size(); j++) {
            if (isEqual(s1Words[i], s2Words[j])) {
                s2Words.erase(s2Words.begin() + j);
                matchCount++;
                break;
            }
        }
    }
    
    
    return matchCount;

}

vector<string> removeStopWords(vector<string>& v1) {

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < v1.size(); j++) {
            stringToUpper(v1[j]);
            if (stopWords[i].compare(v1[j]) == 0)
                v1.erase(v1.begin() + j);
                }
    }

    return v1;
}

int NoOfMatches(string& question, vector<string>& sentences) {
    int max = 0, j, count;
    
    for (int i = 0; i < sentences.size(); i++) {
        count = numberOfMatches(question, sentences[i]);
        
       if  (count > max) {
            max = count;
            j = i;
        }
     
       }
    
    return j;
    
}

void printVector(vector<string>& v) {
    for (int i = 0; i < v.size(); i++)
       cout << v[i] << " ";
    cout << "\n";
}

    string concatenateWords(vector<string>& v1) {
    string s(" ");
    for (int i = 0; i < v1.size(); i++)
    s += v1[i] + " ";
        
    return s;
}

void printAnswer(string& question, string& sentence) {

    vector<string> questionWords = splitWords(question);
    vector<string> sentenceWords = splitWords(sentence);
    
questionWords = removeStopWords(questionWords);
//sentenceWords = removeStopWords(sentenceWords);

    
    for (int i = 0; i < questionWords.size(); i++) {
        for (int j = 0; j < sentenceWords.size(); j++) {
            if (isEqual(questionWords[i], sentenceWords[j])) {
                sentenceWords.erase(sentenceWords.begin() + j);
                
            }
      
        }
        
    }
   
    printVector(sentenceWords);
   
         cout<< "----------------------------------------------"<<endl;
         cout<< "----------------------------------------------"<<endl;
        
}



bool isEqual(string& s1, string& s2) {
    string shortString = s1.length() > s2.length() ? s2 : s1;
    string longString = s1.length() > s2.length() ? s1 : s2;
    for (int i = 0; i < shortString.length(); i++) {
        if (shortString[i] == longString[i]) {
            continue;
        }
        return 0;
    }
    return 1;
}

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

const std::string symbols("#@!$^&*()_+=;,.?/'{}[]|");
const std::string stopWords[] = {"A", "ABOUT", "ABOVE", "ABOVE", "ACROSS", "AFTER", "AFTERWARDS", "AGAIN", "AGAINST", "ALL", "ALMOST", "ALONE", "ALONG", "ALREADY", "ALSO","ALTHOUGH","ALWAYS","AM","AMONG", "AMONGST", "AMOUNGST", "AMOUNT", "AN", "AND", "ANOTHER", "ANY","ANYHOW","ANYONE","ANYTHING","ANYWAY", "ANYWHERE", "ARE", "AROUND", "AS","AT", "BACK","BE","BECAME", "BECAUSE","BECOME","BECOMES", "BECOMING", "BEEN", "BEFORE", "BEFOREHAND", "BEHIND", "BEING", "BELOW", "BESIDE", "BESIDES", "BETWEEN", "BEYOND", "BILL", "BOTH", "BOTTOM","BUT", "BY", "CALL", "CAN", "CANNOT", "CANT", "CO", "CON", "COULD", "COULDNT", "CRY", "DE", "DESCRIBE", "DETAIL", "DO", "DONE", "DOWN", "DUE", "DURING", "EACH", "EG", "EIGHT", "EITHER", "ELEVEN","ELSE", "ELSEWHERE", "EMPTY", "ENOUGH", "ETC", "EVEN", "EVER", "EVERY", "EVERYONE", "EVERYTHING", "EVERYWHERE", "EXCEPT", "FEW", "FIFTEEN", "FIFY", "FILL", "FIND", "FIRE", "FIRST", "FIVE", "FOR", "FORMER", "FORMERLY", "FORTY", "FOUND", "FOUR", "FROM", "FRONT", "FULL", "FURTHER", "GET", "GIVE", "GO", "HAD", "HAS", "HASNT", "HAVE", "HE", "HENCE", "HER", "HERE", "HEREAFTER", "HEREBY", "HEREIN", "HEREUPON", "HERS", "HERSELF", "HIM", "HIMSELF", "HIS", "HOW", "HOWEVER", "HUNDRED", "IE", "IF", "IN", "INC", "INDEED", "INTEREST", "INTO", "IS", "IT", "ITS", "ITSELF", "KEEP", "LAST", "LATTER", "LATTERLY", "LEAST", "LESS", "LTD", "MADE", "MANY", "MAY", "ME", "MEANWHILE", "MIGHT", "MILL", "MINE", "MORE", "MOREOVER", "MOST", "MOSTLY", "MOVE", "MUCH", "MUST", "MY", "MYSELF", "NAME", "NAMELY", "NEITHER", "NEVER", "NEVERTHELESS", "NEXT", "NINE", "NO", "NOBODY", "NONE", "NOONE", "NOR", "NOT", "NOTHING", "NOW", "NOWHERE", "OF", "OFF", "OFTEN", "ON", "ONCE", "ONE", "ONLY", "ONTO", "OR", "OTHER", "OTHERS", "OTHERWISE", "OUR", "OURS", "OURSELVES", "OUT", "OVER", "OWN","PART", "PER", "PERHAPS", "PLEASE", "PUT", "RATHER", "RE", "SAME", "SEE", "SEEM", "SEEMED", "SEEMING", "SEEMS", "SERIOUS", "SEVERAL", "SHE", "SHOULD", "SHOW", "SIDE", "SINCE", "SINCERE", "SIX", "SIXTY", "SO", "SOME", "SOMEHOW", "SOMEONE", "SOMETHING", "SOMETIME", "SOMETIMES", "SOMEWHERE", "STILL", "SUCH", "SYSTEM", "TAKE", "TEN", "THAN", "THAT", "THE", "THEIR", "THEM", "THEMSELVES", "THEN", "THENCE", "THERE", "THEREAFTER", "THEREBY", "THEREFORE", "THEREIN", "THEREUPON", "THESE", "THEY", "THICKV", "THIN", "THIRD", "THIS", "THOSE", "THOUGH", "THREE", "THROUGH", "THROUGHOUT", "THRU", "THUS", "TO", "TOGETHER", "TOO", "TOP", "TOWARD", "TOWARDS", "TWELVE", "TWENTY", "TWO", "UN", "UNDER", "UNTIL", "UP", "UPON", "US", "VERY", "VIA", "WAS", "WE", "WELL", "WERE", "WHAT", "WHATEVER", "WHEN", "WHENCE", "WHENEVER", "WHERE", "WHEREAFTER", "WHEREAS", "WHEREBY", "WHEREIN", "WHEREUPON", "WHEREVER", "WHETHER", "WHICH", "WHILE", "WHITHER", "WHO", "WHOEVER", "WHOLE", "WHOM", "WHOSE", "WHY", "WILL", "WITH", "WITHIN", "WITHOUT", "WOULD", "YET", "YOU", "YOUR", "YOURS", "YOURSELF", "YOURSELVES", "THE"};

std::vector<std::string> splitSentences(std::string);
std::vector<std::string> splitQuestions(std::string);
std::vector<std::string> splitWords(std::string);
void stringToUpper(std::string&);
int numberOfMatches(std::string&, std::string&);
std::vector<std::string> removeStopWords(std::vector<std::string>&);
int maxNoOfMatches(std::string&, std::vector<std::string>&);
void printVector(std::vector<std::string>&);
std::string concatenateWords(std::vector<std::string>&);
void printAnswer(std::string&, std::string&);
void trim(std::string&);
bool isEqual(std::string&, std::string&);

int main(int argc, char const *argv[]) {
    
    auto start = std::chrono::system_clock::now();

    
    std::vector<std::string> questions = splitQuestions("questions.txt");
    std::vector<std::string> sentences = splitSentences("truman.txt");
    
    int index;

    for (int i = 0; i < questions.size(); i++) {
        std::cout << questions[i] << std::endl;
        index = maxNoOfMatches(questions[i], sentences);
        printAnswer(questions[i], sentences[index]);
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedSeconds = end - start;
    std::cout << elapsedSeconds.count();

    // index = maxNoOfMatches(questions[5], sentences);

    // std::cout << questions[5] << std::endl;
    // std::cout << sentences[index];

    // printAnswer(questions[5], sentences[index]);


    return 0;
}

std::vector<std::string> splitSentences(std::string fileName) {
    //It splits the sentences by delimiter '.' in a given text file.
    std::ifstream myFile(fileName);
    std::vector<std::string> sentenceVector;
    std::string sentence;

    while (std::getline(myFile, sentence, '.')) {
        if (!sentence.empty())
            sentenceVector.push_back(sentence);
   }
    myFile.close();
    return sentenceVector;
}

std::vector<std::string> splitQuestions(std::string fileName) {
    std::ifstream questionFile(fileName);
    std::vector<std::string> questionVector;
    std::string question;

    while(std::getline(questionFile, question)) {
        if (!question.empty())
            questionVector.push_back(question.substr(0,question.find('?'))); //getting rid of the '?' by slicing the last element
    }

    questionFile.close();
    return questionVector;
}

std::vector<std::string> splitWords(std::string s) {
    std::istringstream sStream(s);
    std::vector<std::string> wordVector;
    std::string word;

    while (getline(sStream, word, ' ')) {
        if (!word.empty())
            wordVector.push_back(word);
    }
    return wordVector;
}

void stringToUpper(std::string& s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

int numberOfMatches(std::string& s1, std::string& s2) {
    // trim(s1);
    // trim(s2);
    // s1 = removeStopWords(s1);
    // s2 = removeStopWords(s2);

    std::vector<std::string> s1Words = splitWords(s1);
    std::vector<std::string> s2Words = splitWords(s2);

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

std::vector<std::string> removeStopWords(std::vector<std::string>& v1) {

    for (int i = 0; i < 319; i++) {
        for (int j = 0; j < v1.size(); j++) {
            stringToUpper(v1[j]);
            if (stopWords[i].compare(v1[j]) == 0)
                v1.erase(v1.begin() + j);
        }
    }

    return v1;
}

int maxNoOfMatches(std::string& question, std::vector<std::string>& sentences) {
    int max = 0, j, count;

    for (int i = 0; i < sentences.size(); i++) {
        count = numberOfMatches(question, sentences[i]);
        if (count > max) {
            max = count;
            j = i;
        }
    }
    return j;
    
}

void printVector(std::vector<std::string>& v) {
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";
}

std::string concatenateWords(std::vector<std::string>& v1) {
    std::string s("");
    for (int i = 0; i < v1.size(); i++)
        s += v1[i] + " ";
        
    return s;
}

void printAnswer(std::string& question, std::string& sentence) {

    std::vector<std::string> questionWords = splitWords(question);
    std::vector<std::string> sentenceWords = splitWords(sentence);
    
    questionWords = removeStopWords(questionWords);
    sentenceWords = removeStopWords(sentenceWords);

    
    for (int i = 0; i < questionWords.size(); i++) {
        for (int j = 0; j < sentenceWords.size(); j++) {
            if (isEqual(questionWords[i], sentenceWords[j])) {
                sentenceWords.erase(sentenceWords.begin() + j);
            }
        }
    }
    

    printVector(sentenceWords);
}

void trim(std::string& s) {
    int index;
    for (int i = 0; i < s.size(); i ++) {
        index = symbols.find(s[i]);
        if (index < symbols.length()) {
            s = s.substr(0,i) + s.substr(i + 1, s.length() - i);
            if (i > 0) i--;
        }
    }
}

bool isEqual(std::string& s1, std::string& s2) {
    std::string shortString = s1.length() > s2.length() ? s2 : s1;
    std::string longString = s1.length() > s2.length() ? s1 : s2;
    for (int i = 0; i < shortString.length(); i++) {
        if (shortString[i] == longString[i]) {
            continue;
        }
        return 0;
    }
    return 1;
}

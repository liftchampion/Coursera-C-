#include "generate_test.h"

using namespace std;

int MAX_WORDS = 10000;
int WORD_LENGHT = 100;
int DOCS_COUNT = 1000;
int DOC_SIZE = 1000;

int QUERY_SIZE = 10;
int QUERY_COUNT = 10000;

vector<string> GenerateWords(){
    vector<string> result;
    result.reserve(MAX_WORDS);
    for (int i = 0; i < MAX_WORDS; i++) {
        string word;
        for (int j = 0; j < WORD_LENGHT; j++) {
            word.push_back('a' + rand() % ('z' + 1 - 'a'));
        }
        result.push_back(move(word));
    }
    //cout << result << endl;
    return result;
}

string GenerateDoc(const vector<string>& words) {
    string doc;
    doc.reserve(DOC_SIZE * (WORD_LENGHT + 1));
    for (int i = 0; i < DOC_SIZE; i++) {
        doc += words[rand() % MAX_WORDS];
        doc.push_back(' ');
    }
    //cout << doc << endl;
    return doc;
}

string GenerateQuery(const vector<string>& words) {
    string query;
    query.reserve(QUERY_SIZE * (WORD_LENGHT + 1));
    for (int i = 0; i < QUERY_SIZE; i++) {
        query += words[rand() % MAX_WORDS];
        query.push_back(' ');
    }
    //cout << query.size() << endl;
    return query;
}

vector<string> GenerateDocs(const vector<string>& words) {
    //vector<string> words = GenerateWords();
    vector<string> docs;
    docs.reserve(DOCS_COUNT);
    srand(time(NULL));

    for (int i = 0; i < DOCS_COUNT; i++){
        docs.push_back(GenerateDoc(words));
    }
    return docs;
}

vector<string> GenerateQueries(const vector<string>& words) {
    //vector<string> words = GenerateWords();
    vector<string> queries;
    queries.reserve(QUERY_COUNT);
    srand(time(NULL));

    for (int i = 0; i < QUERY_COUNT; i++){
        queries.push_back(GenerateQuery(words));
    }
    //cout << queries << endl;
    return queries;
}

istringstream MakeStream(const vector<string>& items) {
    istringstream ss(Join('\n', items));
    //cout << "stream made" << endl;
    return ss;
}


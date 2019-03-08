#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

template<typename Iterator, typename Token>
Iterator MoveSpecialTokens(Iterator begin, Iterator end, bool parameter, Sentence<Token>& sentence) {
    auto it = begin;
    while (it != end) {
        //cerr << "in local while" << endl;

        if (it->IsEndSentencePunctuation() != parameter) {
            //cerr << "broken" << endl;
            break;
        }
        //cerr << *it << endl;
        sentence.push_back(move(*it));
        //cerr << *it << endl;
        it++;
    }
    //cout << sentence << endl;
    return it;
}

template<typename Iterator, typename Token>
Iterator MakeSentence(Iterator begin, Iterator end, Sentence<Token>& sentence) {
    auto it = begin;
    it = MoveSpecialTokens(it, end, false, sentence);
    //cout << "** " << sentence << endl;
    it = MoveSpecialTokens(it, end, true, sentence);
    //cout << "** " << sentence << endl;
    return it;
};
// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    auto begin = tokens.begin();
    auto end = tokens.end();
    vector<Sentence<Token>> sentences;
    while(begin != end) {
        //cerr << "in global while" << endl;
        Sentence<Token> sentence;
        //cout << "*** " << sentence << endl;
        begin = MakeSentence(begin, end, sentence);
        //cout << "*** " << sentence << endl;
        sentences.push_back(move(sentence));
    }
    return sentences;

}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                        })
    );
    //cerr << "1" << endl;

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                        })
    );
    //cerr << "2" << endl;
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                        })
    );
    //cerr << "3" << endl;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}

/*
 *
 * 5 aaaaa aaaab aaaaa abaaa abaaa
 * 22  - 22
 *
 * 3 hello world hello
 * 11  - 11
 *
 * 5 an apple a big apple
 * 13   - 13
 *
 * 3 aaaaa aaaab abaaa
 *
 */

#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;



class TreeNode {
public:
	TreeNode () {
		value = '#';
		num_words = 0;
		end_of_word = false;
	}
	void AddWord(string& word) {
		//cout << "Adding word " << word << " now letter is " << word[0] << endl;
		value = word[0];
		if (word.size() > 0) {   	// ??? ��� ���� � ��������� ������ �����??? Hello Hell
			num_words++;
		}

		word.erase(word.begin());
		if (word.size() > 0) {
			children[word[0]].AddWord(word);
		}
		else {
			end_of_word = true;
		}
	}
	void CountKeys (string& word, int& keys_economy) {
		if (value == '#') {				//����� �����
			keys_economy = -2;
		}
		else {							// ����� ������
			if (num_words > 1) {			//������ ��������������
				if (word.size() > 0) {			//� ��� �� ��������� ��� ������
					word.erase(word.begin());
					children[word[0]].CountKeys(word, keys_economy);
				}
				else {							//� ��� ��������� ��� ������
					keys_economy = 0;
				}
			}
			else {							//������ ������������
				if (word.size() > 1) {			//� ��� �� ��������� ��� ������
					if (keys_economy == -1) {		//� ��� ������ ����, ��� ����� ����� ������������
						word.erase(word.begin());
						keys_economy = word.size();
						children[word[0]].CountKeys(word, keys_economy);
					}
					else {							//� ��� �� ������ ����, ��� ����� ����� ������������
						word.erase(word.begin());
						children[word[0]].CountKeys(word, keys_economy);
					}
				}
				else {							//� ��� ��������� ��� ������
					if (end_of_word == false) {		//� � ���� ���� ��� ����� ����� (�� ���� ����� ��-���� �����)
						keys_economy = -2;
					}
					else {							//� � ���� ���� ���� ����� ����� (�� ���� ����� ����� ������������)
						if (keys_economy == -1) {		//�������� �������� �� �������� �� ����� �������
							keys_economy = 0;
						}
					}
				}
			}
		}
	}
	void Print () const {
		//cout << "Trying to print" << endl;
		cout << value << "(" << num_words << ")" << "<" << end_of_word << ">" << " ";
		for (const auto& child : children) {
			child.second.Print();
		}
	}
private:
	char value;
	int num_words;
	bool end_of_word;
	map<char, TreeNode> children;
};


class Forest {
public:
	void AddWord(string word) {
		//cout << "Adding word " << word << " now letter is " << word[0] << endl;
		trees[word[0]].AddWord(word);
	}
	int CountKeys(string& word){
		int word_size = word.size();
		int keys_economy = -1;
		string word_copy = word;
		trees[word[0]].CountKeys(word, keys_economy);
		if (keys_economy == -2) {  // ����� ����� (�� ��������� ����� ��� ������ �����)
			AddWord(word_copy);
			keys_economy = 0;
		}
		return word_size - keys_economy;
	}
	void Print () const {
		//cout << "Trying to print" << endl;
		for (const auto& tree : trees) {
			tree.second.Print();
		}
		cout << endl;
	}
private:
	map<char, TreeNode> trees;
};




int main() {
	string word = "hello";
	//cin >> word;

	Forest forest;
	int n;
	cin >> n;
	int num_keys = 0;
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		num_keys += forest.CountKeys(word);
		//cout << num_keys << endl;
		//forest.AddWord(word);
	}

	cout << num_keys;
	//forest.Print();
	return 0;
}

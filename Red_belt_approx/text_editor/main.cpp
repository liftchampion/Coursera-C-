#include <string>
#include <list>
#include <string_view>
#include "test_runner.h"
#include "profile.h"
using namespace std;



class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : cursor(data.end()) {}
  void Left() {
      if (cursor != data.begin()) {
          cursor--;
      }
  }
  void Right() {
      if (cursor != data.end()) {
          cursor++;
      }
  }
  void Insert(char token) {
      cursor = next(data.insert(cursor, token));
  }
  void Cut(size_t tokens = 1) {
      buffer.clear();
      size_t counter = 0;
      while (counter != tokens && cursor != data.end()) {
          buffer.insert(buffer.end(), *cursor);
          cursor = data.erase(cursor);
          counter++;
      }
  }
  void Copy(size_t tokens = 1) {
      buffer.clear();
      auto cursor_copy = cursor;
      size_t counter = 0;
      while (counter != tokens && cursor_copy != data.end()) {
          buffer.insert(buffer.end(), *cursor_copy);
          cursor_copy++;
          counter++;
      }
  }
  void Paste() {
      auto buffer_it = buffer.begin();
      while (buffer_it != buffer.end()) {
          Insert(*buffer_it);
          buffer_it++;
      }
  }
  string GetText() const {
      string str;
      str.reserve(data.size());
      for (auto it = data.begin(); it != data.end(); it++) {
          str.push_back(*it);
      }
      return str;
  }
  char GetCursor() {

      if (cursor != data.begin()) {
          return *prev(cursor);
      }
      else {
          return '-';
      }

  }
private:
    list<char> data;
    list<char>::iterator cursor;
    list<char> buffer;
};
/*
void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
    cout << editor.GetText() << "   " << editor.GetCursor() << endl;
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
      ASSERT_EQUAL(editor.GetText(), "hello, world");
      cout << "*" << editor.GetText() << "   " << editor.GetCursor() << endl;
    editor.Cut(first_part_len);
      cout << editor.GetText() << "   " << editor.GetCursor() << endl;
    ASSERT_EQUAL(editor.GetText(), "world");

    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
        cout << "**" <<editor.GetText() << "   " << editor.GetCursor() << endl;
    }

    TypeText(editor, ", ");
      ASSERT_EQUAL(editor.GetText(), "world, ");


    editor.Paste();
      cout << "***" <<editor.GetText() << "   " << editor.GetCursor() << endl;

      ASSERT_EQUAL(editor.GetText(), "world, hello, ");

    editor.Left();
    editor.Left();


    editor.Cut(3);



    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);

  Editor editor;
    {
        LOG_DURATION("Insert");
        for (int i = 0; i < 1000000; i++) {
            editor.Insert('a');
            editor.Left();
        }
    }
  return 0;
}*/
#pragma once

#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <utility>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "[";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "]";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << "(" << kv.first << " : " << kv.second << ")";
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
  os << "(" << p.first << " : " << p.second << ")";

  return os;
}

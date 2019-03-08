#pragma once

#include <iostream>
#include "date.h"
#include <memory>


using namespace std;

enum class Comparison {
	Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};

enum class LogicalOperation {
	Or, And
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
	virtual ~Node() {}
};

class EmptyNode: public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode: public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) const override;

	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode: public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event);
	bool Evaluate(const Date& date, const string& event) const override;

	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode: public Node {
public:
	LogicalOperationNode(const LogicalOperation& l_o,
						const shared_ptr<Node>& left, const shared_ptr<Node>& right);
	bool Evaluate(const Date& date, const string& event) const override;

	const LogicalOperation logical_operation_;
	const shared_ptr<Node> left_, right_;
};

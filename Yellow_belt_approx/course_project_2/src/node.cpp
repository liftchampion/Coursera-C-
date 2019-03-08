#include "node.h"
#include <vector>


using namespace std;

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
								: cmp_(cmp), date_(date) {}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
								: cmp_(cmp), event_(event) {}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& l_o,
						const shared_ptr<Node>& left, const shared_ptr<Node>& right)
								: logical_operation_(l_o), left_(left), right_(right) {}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	vector<int> date_checking = {date.GetYear(), date.GetMonth(), date.GetDay()};
	vector<int> date_border = {date_.GetYear(), date_.GetMonth(), date_.GetDay()};
	switch (cmp_) {
		case Comparison::Equal :
			return date_checking == date_border;
			break;
		case Comparison::NotEqual :
			return date_checking != date_border;
			break;
		case Comparison::Greater :
			return date_checking > date_border;
			break;
		case Comparison::GreaterOrEqual :
			return date_checking >= date_border;
			break;
		case Comparison::Less :
			return date_checking < date_border;
			break;
		case Comparison::LessOrEqual :
			return date_checking <= date_border;
			break;
		default:
			throw runtime_error("Unknown error in DateComparisonNode");
	}
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	switch (cmp_) {
		case Comparison::Equal :
			return event == event_;
			break;
		case Comparison::NotEqual :
			return event != event_;
			break;
		case Comparison::Greater :
			return event > event_;
			break;
		case Comparison::GreaterOrEqual :
			return event >= event_;
			break;
		case Comparison::Less :
			return event < event_;
			break;
		case Comparison::LessOrEqual :
			return event <= event_;
			break;
		default:
			throw runtime_error("Unknown error in EventComparisonNode");
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	switch (logical_operation_) {
		case LogicalOperation::And :
			return left_->Evaluate(date, event) && right_->Evaluate(date, event);
			break;
		case LogicalOperation::Or :
			return left_->Evaluate(date, event) || right_->Evaluate(date, event);
			break;
		default :
			throw runtime_error("Unknown error in LogicalOperationNode");
	}
}

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class FunctionPart {
public:
	FunctionPart (const char& new_method, const double& new_value) {
		method = new_method;
		value = new_value;
	}
	void Invert () {
		if (method == '+') {
				method = '-';
		}
		else if (method == '-') {
				method = '+';
		}
		else if (method == '*') {
				method = '/';
		}
		else if (method == '/') {
				method = '*';
		}
	}
	double Apply (const double& initial_value) const {
		double result = initial_value;
		if (method == '+') {
			result += value;
		}
		if (method == '-') {
			result -= value;
		}
		if (method == '*') {
			result *= value;
		}
		if (method == '/') {
			result /= value;
		}
		return result;
	}
private:
	char method;
	double value;
};

class Function {
public:
	void AddPart (const char& method, const double& value) {
		function.push_back({method, value});
	}
	double Apply (const double& initial_value) const {
		double result;
		result = initial_value;
		for (const auto& part : function) {
			result = part.Apply(result);
		}
		return result;
	}
	void Invert() {
		for (auto& part : function) {
			part.Invert();
		}
		reverse(begin(function), end(function));
	}
private:
	vector<FunctionPart> function;
};

/*struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('*', params.a);
  function.AddPart('-', image.freshness * params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 52) << endl;
  return 0;
}*/

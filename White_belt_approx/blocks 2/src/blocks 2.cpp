#include <cstdint>
#include <iostream>
using namespace std;


int main() {


	uint64_t num_blocks;
	uint64_t ro;
	cin >> num_blocks >> ro;
	//cout << num_blocks << " " << ro << endl;
	uint64_t total_volume = 0;
	for (int i = 0; i < num_blocks; i++) {
		uint64_t w;
		uint64_t h;
		uint64_t d;
		cin >> w >> h >> d;
		//cout << w << " " << h << " " << d << endl;
		uint64_t current_volume = w * h * d;
		total_volume += current_volume;
	}
	uint64_t total_mass = total_volume * ro;
	cout << total_mass;
	return 0;
}

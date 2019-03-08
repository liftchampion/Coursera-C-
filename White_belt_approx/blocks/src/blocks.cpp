#include <cstdint>
#include <iostream>
using namespace std;


int CountAndEraseZeroes(int& num) {
	int zeroes_count;
	while (num % 10 == 0) {
		zeroes_count++;
		if (num % 10 != 0) {
			break;
		}
		num /= 10;
	}
	return zeroes_count;
}


int main() {

	int zeroes_count = 0;

	int num_blocks;
	int ro;
	cin >> num_blocks >> ro;
	zeroes_count += CountAndEraseZeroes(num_blocks) + CountAndEraseZeroes(ro);
	int total_volume = 0;
	for (int i = 0; i < num_blocks; i++) {
		int w;
		int h;
		int d;
		cin >> w >> h >> d;
		zeroes_count += CountAndEraseZeroes(w) +
						CountAndEraseZeroes(h) +
						CountAndEraseZeroes(d);

		int current_volume = w * h * d;
		zeroes_count += CountAndEraseZeroes(current_volume);
		total_volume += current_volume;
		zeroes_count += CountAndEraseZeroes(total_volume);
	}
	uint64_t total_mass = total_volume * ro;
	cout << total_mass;
	for (int i = 0; i < zeroes_count; i++) {
		cout << "0";
	}
	return 0;
}

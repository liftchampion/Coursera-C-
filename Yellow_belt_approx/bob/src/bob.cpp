#include <iostream>
#include <fstream>
using namespace std;

int part(int *mass, int left, int right)
{
	int m=mass[(left+right)/2];
	do
	{
		while(mass[left] < m)
			left++;
		while(mass[right] > m)
			right--;
		if(left>=right)
			break;
		swap(mass[left], mass[right]);
	}
	while(left<right);
	return right;
}

int main()
{
    ifstream input ("kth.in");
    ofstream output("kth.out");
    int N, k, A, B, C;
    input >> N >> k >> A >> B >> C;
    int arr[N];
    input >> arr[0] >> arr[1];
    for(int i = 2; i < N; i++)
    {
    	arr[i] = A*arr[i-2]+B*arr[i-1]+C;
    }

    int left = 0, right = N-1;
    k--;
    while(1)
    {
    	int middle = part(arr, left, right);
    	if(k < middle)
    		right = middle;
    	else if (k > middle)
    	{
    		left =  middle+1;
    		k = k - left;
    	}
    	else
    	{
    		output << arr[middle];
    		break;
    	}

    }
    input.close();
    output.close();
    return 0;
}

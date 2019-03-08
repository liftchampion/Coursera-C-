#include <iostream>
#include <fstream>
using namespace std;

/*
 * 5
4 2 3 2 1
 *
 *
 */

void Merge(int *A, int start, int end, int *out)
{
	int middle, first, second, i=0;
	int *mass = new int[end-start+1];
	middle=(start+end)/2;
	first=start;
	second=middle+1;
	while(first<middle+1 && second<=end)
	{
		if(A[first]<=A[second])
		{
			mass[i]=A[first];
			first++;
			i++;
		}
		else
		{
			mass[i]=A[second];
			second++;
			i++;
			(*out)=(*out)+middle-first+1;
		}
	}
	if (first != middle+1)
	{
		for(int j = first; j <= middle; j++)
		{
			mass[i] = A[j];
			i++;
		}
	}
	else
	{
		for(int j = second; j <= end; j++)
		{
			mass[i] = A[j];
			i++;

		}
	}
	i=0;
	for (int j=start; j<=end; j++)
	{
		A[j]=mass[i];
		i++;
	}
}

void Sort(int *A, int first, int last, int *out, int N)
{
	if (first<last)
	{
		Sort(A, first, (first+last)/2, out, N);
		Sort(A, (first+last)/2+1, last, out, N);
		Merge(A, first, last, out);
	}
}



int main()
{

    int N;
	int out = 0;
    cin >> N;
    int *arr = new int[N];
    for(int i = 0; i < N; i++)
    {
    	cin >> arr[i];
    }
    Sort(arr, 0, N-1, &out, N);
    cout << out;
    delete []arr;

    return 0;
}

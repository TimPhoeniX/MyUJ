insertion_sort(int* A, int size)
{
//	for(int j=1; j< length(A);++j)
	for(int j=1; j< length(A);++j)
	{
		int key=A[j];
		int i=j-1;
		while i>=0 && A[i]>key)
		{
			A[i+1]=A[i];
			i=i-1;
		}
		A[i+1]=key;
	}
}
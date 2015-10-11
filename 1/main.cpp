#include <iostream>

int Find(int* Array, int A, int B, int Key)
{
    int Mid=((A+B)/2);
//	std::cout << "|| " << A << " " << Mid << " " << B << " ||";
    if(Array[Mid]==Key)
    {
        return Mid;
    }
    else
    {
        if(A>=B) return -100;
        else
		{
			if(Array[Mid]>Key) return Find(Array, A, Mid-1, Key);
			else return Find(Array, Mid+1, B, Key);
		}
    }
}

int* CreateArray(int ArraySize)
{
    int* Array=new int[ArraySize];
    for(int i=0;i<ArraySize;++i)
    {
        std::cin >> Array[i];
    }
    return Array;
}

int main(void)
{
    int NumberOfSets=0, NumberOfKeys=0, Key=0, ArraySize=0,*Array=nullptr;
    std::cin >> NumberOfSets;
    for(int i=0;i<NumberOfSets;++i)
    {
        std::cin >> ArraySize;
        Array=CreateArray(ArraySize);
        std::cin >> NumberOfKeys;
        for (int j = 0; j < NumberOfKeys; ++j)
        {
            std::cin >> Key;
            std::cout << Find(Array,0,ArraySize-1,Key) << " ";
        }
        std::cout << "\n";
		delete[] Array;
		}
	return 0;
}
#ifndef _CTL_SORT_HPP_
#define _CTL_SORT_HPP_

namespace CTL
{
	template<typename T, typename Compar>
	void MergeSort(T first, T last, Compar comp)
	{
		typedef std::iterator_traits<T>::value_type Type;
		if(first<last)
		{
			T mid=first+(last-first)/2;
			MergeSort(first,mid,comp);
			MergeSort(mid+1,last,comp);
			T result = new Type[first-last];
			T left=first, right=mid+1, resultIt=result;
			while(left !=mid+1 && right!=last)
			{
				if(comp(*left,*right) || !comp(*left,*right))
				{
					(*(resultIt++))=std::move(*(left++));
				}
				else
				{
					(*(resultIt++))=std::move(*(right++));
				}
		}	
	}
}

#endif
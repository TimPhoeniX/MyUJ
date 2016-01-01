/** Conceptual template Library by Piotr Grudzień
 * Natural Cubic Interpolation
 */

#ifndef _CTL_NCI_HPP_
#define _CTL_NCI_HPP_

#include <cmath>

namespace CTL
{
	template<typename T>
	class NCIFunction_CD // const distance
	{
	private:
		T Distance;
		T* EndPoints;
		T* Values;
		T* SecDerivative;
		
		
		T Acoef(const T x, const unsigned int i)
		{
			return (this->EndPoints[i+1]-x)/this->Distance;
		}
		
		T Bcoef(const T x, const unsigned int i)
		{
			return (x-this->EndPoints[i])/this->Distance;
		}
		
		T Ccoef(const T A)
		{
			return ( A*(A*A-A)*this->Distance*this->Distance/T(6) );
		}
		
		T Dcoef(const T B)
		{
			return ( B*(B*B-B)*this->Distance*this->Distance/T(6) );
		}
		
		void Interpolate(unsigned int p)
		{
			auto n = p-2;
			T* S = new T[n];
			for(unsigned int i = 0; i < n; ++i)
			{
				S[i]=(this->Values[i]-2*this->Values[i+1]+this->Values[i+2])*6/(this->Distance*this->Distance);
			}
			T* Sup = new T[n-1];
			Sup[0]=T(1)/T(4);
			for(unsigned int i = 1; i < n-1; ++i)
			{
				Sup[i]=T(1)/(T(4)-Sup[i-1]);
			}
			S[0]=S[0]/T(4);
			for(unsigned int i = 1; i < n; ++i)
			{
				S[i]=(S[i]-S[i-1])/(4-Sup[i-1]);
			}
			auto Sol = this->SecDerivative+1;
			Sol[n-1]=S[n-1];
			for(int i = n-2; i >= 0; --i)
			{
				Sol[i]=S[i]-Sup[i]*Sol[i+1];
			}
			delete[] S;
			delete[] Sup;
		}
		
	public:
		NCIFunction_CD(T first, T d, unsigned int p, T* v)
		: Distance(d), Values(v), SecDerivative(new T[p]{0})
		{
			this->EndPoints = new T[p];
			this->EndPoints[0] = first;
			for(unsigned int i = 1; i < p; ++i)
			{
				this->EndPoints[i]=this->EndPoints[i-1]+T(1);
			}
			this->Interpolate(p);
		}
		
		~NCIFunction_CD()
		{
			delete[] this->Values;
			delete[] this->SecDerivative;
			delete[] this->EndPoints;
		}
		
		T operator()(const T x)
		{
			int i = std::floor( (x-this->EndPoints[0])/this->Distance );
			auto A = this->Acoef(x,i);
			auto B = this->Bcoef(x,i);
			auto C = this->Ccoef(A);
			auto D = this->Dcoef(B);
			return ( A*this->Values[i]+B*this->Values[i+1]+C*this->SecDerivative[i]+D*this->SecDerivative[i+1] );
		}
	};
}
#endif
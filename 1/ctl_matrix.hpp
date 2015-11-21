/**
 * Conceptual Template Library by Piotr Grudzień
 * Numerical Matrix 
 */
#ifndef _CTL_MATRIX_HPP_
#define _CTL_MATRIX_HPP_

#include <stdexcept>
#include <iostream>
#include <cmath>

namespace CTL
{
	template<typename T>
	class Matrix
	{
	private:
		unsigned int Row = 1;
		unsigned int Col = 1;
		unsigned int Total = 1;
		T* Val = nullptr;
		
		T SumRC(const Matrix<T>& m, unsigned int r, unsigned int c) const
		{
			T tmp = 0;
			auto R = this->operator[](r);
			for(unsigned int i = 0; i < this->Col; ++i)
			{
				tmp += (R[i] * m[i][c]);
			}
			return  tmp;
		}
		
	public:
		Matrix( const unsigned int dim)
		: Row(dim), Col(dim), Total(Row*Col), Val(new T[this->Total]{})
		{
			for(unsigned int i = 0; i < dim; ++i)
				this->operator[](i)[i] = T(1);
		}
		
		Matrix( const unsigned int r, const unsigned int c)
		: Row(r), Col(c), Total(Row*Col), Val(new T[Total]{})
		{
		}
		
		Matrix( const Matrix<T>& m )
		: Row(m.Row), Col(m.Col), Total(m.Total), Val(new T[this->Total])
		{
			auto tp = this->Val;
			auto mp = m.Val;
			for(unsigned int i = 0; i < this->Total; ++i)
				*(tp++) = *(mp++);
		}
		
		Matrix( Matrix<T>&& m )
		: Row(m.Row), Col(m.Col), Total(m.Total), Val(m.Val)
		{
			m.Val = nullptr;
		}
		
		Matrix( std::istream& in = std::cin )
		{
			in >> this->Row >> this->Col;
			this->Total = this->Row*this->Col;
			this->Val = new T[this->Total];
			auto ptr = this->Val;
			for(unsigned int i = 0; i < this->Total; ++i)
			{
				in >> *(ptr++);
			}
		}
		
		Matrix<T>& operator=(Matrix<T>&& m)
		{
			delete[] this->Val;
			this->Val=m.Val;
			m.Val=nullptr;
			this->Row=m.Row;
			this->Col=m.Col;
			this->Total=m.Total;
			return *this;
		}
		
		Matrix<T>& operator=(const Matrix<T>& m)
		{
			if(this->Row != m.Row || this->Col != m.Col)
			{
				this->Row = m.Row;
				this->Col = m.Col;
				this->Total = m.Total;
				delete[] this->Val;
				this->Val = new T[Total];
			}
			auto end = this->Val + this->Total;
			auto tp = this-Val;
			auto mp = m.Val;
			while(tp!=end)
			{
				*(tp++)=*(mp++);
			}
			return *this;
		}
		
		~Matrix()
		{
			delete[] this->Val;
		}
		
		T* operator[](unsigned int row)
		{
			return this->Val+(row*this->Col);
		}
		
		const T* operator[](unsigned int row) const
		{
			return this->Val+(row*this->Col);
		}
		
		Matrix<T> operator+(const Matrix& m) const
		{
			if(this->Row == m.Row && this->Col == m.Col)
			{
				Matrix<T> tmp(this->Row, this->Col);
				auto p1 = tmp.Val;
				auto p2 = this->Val;
				auto p3 = m.Val;
				for(unsigned int i = 0; i< tmp.Total; ++i)
				{
					*(p1++)=(*(p2++)+*(p3++));
				}
				return tmp;
			}
			else throw std::range_error("Adding incompatibile matrices");
		}
		
		Matrix<T> operator-(const Matrix& m) const
		{
			if(this->Row == m.Row && this->Col == m.Col)
			{
				Matrix<T> tmp(this->Row, this->Col);
				auto p1 = tmp.Val;
				auto p2 = this->Val;
				auto p3 = m.Val;
				for(unsigned int i = 0; i< tmp.Total; ++i)
				{
					*(p1++)=(*(p2++)-*(p3++));
				}
				return tmp;
			}
			else throw std::range_error("Adding incompatibile matrices");
		}
		
		Matrix<T>& operator+=(const Matrix& m)
		{
			if(this->Row == m.Row && this->Col == m.Col)
			{
				auto p1 = this->Val;
				auto p2 = m.Val;
				for(unsigned int i = 0; i< this->Total; ++i)
				{
					*(p1++)+=*(p2++);
				}
				return *this;
			}
			else throw std::range_error("Adding incompatibile matrices");
		}
		
		Matrix<T>& operator-=(const Matrix& m)
		{
			if(this->Row == m.Row && this->Col == m.Col)
			{
				auto p1 = this->Val;
				auto p2 = m.Val;
				for(unsigned int i = 0; i< this->Total; ++i)
				{
					*(p1++)-=*(p2++);
				}
				return *this;
			}
			else throw std::range_error("Adding incompatibile matrices");
		}
		
		Matrix<T> operator*(const Matrix<T>& m) const
		{
			if(this->Col == m.Row)
			{
				Matrix<T> tmp(this->Row,m.Col);
				auto Cell = tmp.Val;
				for(unsigned int r = 0; r < tmp.Row; ++r)
				{
					for(unsigned int c = 0; c < tmp.Col; ++c)
					{
						*(Cell++)=this->SumRC(m,r,c);
					}
				}
				return tmp;
			}
			else throw std::range_error("Multiplying incompatibile matrices");
		}
		
		explicit operator T() const
		{
			return *this->Val;
		}
		
		Matrix<T>& operator*=(T val)
		{
			for(unsigned int i = 0; i < this->Total; ++i)
			{
				this->Val[i]*=val;
			}
			return *this;
		}
		
		Matrix<T>& operator/=(T val)
		{
			for(unsigned int i = 0; i < this->Total; ++i)
			{
				this->Val[i]/=val;
			}
			return *this;
		}
		
		Matrix<T> Transpose() const
		{
			Matrix<T> tmp(this->Col,this->Row);
			auto cell = this->Val;
			for(unsigned int r = 0; r < this->Row; ++r)
			{
				for(unsigned int c = 0; c < this->Col; ++c)
				{
					tmp[c][r]=*(cell++);
				}
			}
			return tmp;
		}
		
		void Print(std::ostream& out = std::cout) const
		{
			auto Cell = this->Val;
			for(unsigned int r = 0; r < this->Row; ++r)
			{
				out.precision(6);
				for(unsigned int c = 0; c < this->Col; ++c)
				{
					out << *(Cell++) << '\t';
				}
				out << '\n';
			}
		}
		
		void PrintDiagonal(std::ostream& out = std::cout) const
		{
			for(unsigned int i = 0; i < this->Col; ++i)
			{
				out.precision(9);
				out << this->operator[](i)[i] << '\t';
			}
		}
		
		friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
		{
			m.Print(out);
			return out;
		}
		
		
		Matrix<T> GivensRotation(const unsigned int i, const unsigned int j, const unsigned int c)
		{
			Matrix<T> givens(this->Row);
			auto ai = this->operator[](i)[c];
			auto aj = this->operator[](j)[c];
			//Speeding up a little bit
			auto l = 1./std::sqrt(ai*ai + aj*aj);
			givens[i][i]=( ai*l );
			givens[j][j]=( ai*l );
			givens[i][j]=( aj*l );
			givens[j][i]=(-aj*l );
			return givens;
		}
		
		//Tranposes in place;
		Matrix<T>& InplaceTransposeGivenRotation(const unsigned int i, const unsigned int j)
		{
			std::swap(this->operator[](i)[j],this->operator[](j)[i]);
			return *this;
		}
		
		bool CheckQRConvergnece()
		{
			for(unsigned int i = 0; i < this->Col-1; ++i)
			{
				if(this->operator[](i+1)[i] > T(0.1)) return false;
			}
			return true;
		}
		
		void QRAlgorithmSymmetricalTridiagonal()
		{
			while(!this->CheckQRConvergnece())
			{
				for(unsigned int i = 0; i < this->Col - 1; ++i)
				{
					auto givens = this->GivensRotation(i,i+1,i);
					(*this) = givens*(*this); 
					givens.InplaceTransposeGivenRotation(i,i+1);
					*this = this->operator*(givens);
				}
			}
		}
		
		//Unsafe
		void FillWith( const unsigned int rbegin, const unsigned int cbegin, const Matrix<T>& m )
		{
			for(unsigned int i = 0; i < m.Row; ++i)
				for(unsigned int j = 0; j < m.Col; ++j)
				{
					this->operator[](rbegin+i)[cbegin+j]=m[i][j];
				}
		}
		
		//Unsafe
		T VectorNorm() const
		{
			T norm = 0;
			if(this->Col == 1 || this->Col == 1)
			{
				auto cell = this->Val;
				for( unsigned int i = 0; i < this->Total; ++i)
				{
					norm+=( (*cell)*(*cell) );
					++cell;
				}
				norm = sqrt(norm);
			}
			return norm;
		}
		
		CTL::Matrix<T> TridiagonalizingHouseholder(const unsigned int c)
		{
			CTL::Matrix<T> vec(this->Row-c-1,1);
			for( unsigned int i = 0; i < vec.Row; ++i)
			{
				vec[i][0]=this->operator[](i+c+1)[c];
			}
			vec[0][0]-=(std::signbit(vec[0][0])?(-1):(1))*vec.VectorNorm();
			auto vet = vec.Transpose();
			Matrix<T> subm(vec.Row);
			auto norm = 2/T(vet*vec);
			subm-=( (vec*vet)*=norm);
			CTL::Matrix<T> householder(this->Col);
			householder.FillWith(c+1,c+1,subm);
			return householder;
		}
		
		void TridiagonalizeSymmetricHouseholder()
		{
			const unsigned int count = this->Row-2;
			for(unsigned int i = 0; i < count; ++i)
			{
				auto h = this->TridiagonalizingHouseholder(i);
				*this = h*(*this)*h;
			}
		}
	};
}
#endif // _CTL_MATRIX_HPP_
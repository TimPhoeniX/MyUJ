#ifndef _CTL_DATA_HPP_
#define _CTL_DATA_HPP_
#include <iostream>
#include <stdexcept>

namespace CTL
{
	template<typename T>
	class Data
	{
	private:
		T* DataPtr = nullptr;
		int Size = 0;
		
		void ReadStream(std::istream& stream)
		{
			for(int i = 0; i<this->Size; ++i)
			{
				stream >> this->DataPtr[i];
			}
		}
		
		
	public:
		int GetSize()
		{
			return this->size;
		}
		
		std::ostream& operator<<(std::ostream& stream) const
		{
			this->Print(stream);
			return stream;
		}
		
		friend std::ostream& operator<<(std::ostream& stream,const CTL::Data<T>& data)
		{
			return data.operator<<(stream);
		}
		
		void Clear()
		{
			delete[] this->DataPtr;
			this->Size = 0;
		}
		
		void Load(std::istream& stream = std::cin)
		{
			stream >> this->Size;
			this->DataPtr = new T[Size];
			this->ReadStream(stream);
		}
		
		void Load(const int size, std::istream& stream = std::cin)
		{
			this->Size = size;
			this->DataPtr = new T[Size];
			this->ReadStream(stream);
		}
		
		void Print(std::ostream& stream = std::cout) const
		{
			for(int i = 0; i<this->Size; ++i)
			{
				stream << this->DataPtr[i] << " ";
			}
		}
		
		Data() {}
		
		Data(std::istream& stream)
		{
			this->Load(stream);
		}
		
		Data(const int size, std::istream& stream = std::cin)
		: Size(size)
		{
			this->DataPtr = new T[Size];
			this->ReadStream(stream);
		}
		
		T& operator[](const int poz)
		{
			return this->DataPtr[poz];
		}
		
		T& at(const int poz)
		{
			if(poz < 0 || this->Size <= poz)
				throw std::out_of_range("CTL::Data range check");
			else
				return this->DataPtr[poz];
		}
		
		~Data()
		{
			delete[] this->DataPtr;
		}
		
	};
	
}

#endif
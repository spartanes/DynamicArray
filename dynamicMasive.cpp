#include <iostream>
#include <stdexcept>

class Vector 
{
private:
	unsigned int size = 0;
	int* dynamicArray = nullptr;
public:
	Vector(int sizeOffArray) { // Constructor
		size = sizeOffArray;
		dynamicArray = new int[size];
	}
	Vector(const Vector& other) 
	{
		size = other.size;
		dynamicArray = new int[size];
		for (unsigned int i = 0;i < size;++i) 
		{
			dynamicArray[i] = other.dynamicArray[i];
		}
	}
	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			delete[] dynamicArray;
			size = other.size;
			dynamicArray = new int[size];
			for (unsigned int i = 0; i < size; ++i)
			{
				dynamicArray[i] = other.dynamicArray[i];
			}
		}
		return *this;
	}
	~Vector() //Destructor
	{
		delete[] dynamicArray;
		dynamicArray = nullptr;
	}
	
	void set(int index, int newValue) 
	{
		if (index < 0 || static_cast<unsigned int>(index) >= size)
		{
			throw std::out_of_range("Vector set error: Index out of range!");
		}
		dynamicArray[index] = newValue;
	}
	
	int get(int index) const 
	{ 
		if (index < 0 || static_cast<unsigned int>(index) >= size)
		{
			throw std::out_of_range("Vector get error: Index out of range!");
		}
		return dynamicArray[index];
	}

	int& operator[](unsigned int index)
	{
		if (index >= size)
		{
			throw std::out_of_range("Vector [] error: Index out of range!");
		}
		return dynamicArray[index];
	}

	const int& operator[](unsigned int index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("Vector [] const error: Index out of range!");
		}
		return dynamicArray[index];
	}
	
	void resize(int newSize) 
	{
		int* dynamicArrayTemp = new int[newSize];
		for (int i = 0; i < size;i++) 
		{
			dynamicArrayTemp[i] = dynamicArray[i];
		}
		delete[] dynamicArray;
		dynamicArray = dynamicArrayTemp;
		size = newSize;
		dynamicArrayTemp = nullptr;
	}
};
int main() 
{
	Vector v(5);

	try
	{
		v.set(0, 10);
		std::cout << "v[0] = " << v.get(0) << std::endl;

		// Тест виходу за межі масиву
		std::cout << "Accessing element at index 100..." << std::endl;
		std::cout << v[100] << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
}


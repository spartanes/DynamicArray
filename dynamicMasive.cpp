#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Vector
{
private:
	unsigned int size = 0;
	T* dynamicArray = nullptr;

public:
	Vector() : size(0), dynamicArray(nullptr) {}

	Vector(int sizeOffArray)
	{
		size = sizeOffArray;
		dynamicArray = new T[size]();
	}

	Vector(const Vector& other)
	{
		size = other.size;
		dynamicArray = new T[size];
		for (unsigned int i = 0; i < size; ++i)
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
			dynamicArray = new T[size];
			for (unsigned int i = 0; i < size; ++i)
			{
				dynamicArray[i] = other.dynamicArray[i];
			}
		}
		return *this;
	}

	~Vector()
	{
		delete[] dynamicArray;
		dynamicArray = nullptr;
	}

	void set(int index, const T& newValue)
	{
		if (index < 0 || static_cast<unsigned int>(index) >= size)
		{
			throw std::out_of_range("Vector set error: Index out of range!");
		}
		dynamicArray[index] = newValue;
	}

	T get(int index) const
	{
		if (index < 0 || static_cast<unsigned int>(index) >= size)
		{
			throw std::out_of_range("Vector get error: Index out of range!");
		}
		return dynamicArray[index];
	}

	T& operator[](unsigned int index)
	{
		if (index >= size)
		{
			throw std::out_of_range("Vector [] error: Index out of range!");
		}
		return dynamicArray[index];
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("Vector [] const error: Index out of range!");
		}
		return dynamicArray[index];
	}

	void resize(int newSize)
	{
		T* dynamicArrayTemp = new T[newSize]();
		unsigned int elementsToCopy = (newSize < static_cast<int>(size)) ? newSize : size;

		for (unsigned int i = 0; i < elementsToCopy; i++)
		{
			dynamicArrayTemp[i] = dynamicArray[i];
		}
		delete[] dynamicArray;
		dynamicArray = dynamicArrayTemp;
		size = newSize;
		dynamicArrayTemp = nullptr;
	}

	unsigned int getSize() const { return size; }
};


template <typename T, std::size_t N>
class StaticArray
{
private:
	T data_[N]{};

public:
	StaticArray() = default;

	void set(int index, const T& newValue)
	{
		if (index < 0 || static_cast<std::size_t>(index) >= N)
		{
			throw std::out_of_range("StaticArray set error: Index out of range!");
		}
		data_[index] = newValue;
	}

	T get(int index) const
	{
		if (index < 0 || static_cast<std::size_t>(index) >= N)
		{
			throw std::out_of_range("StaticArray get error: Index out of range!");
		}
		return data_[index];
	}

	T& operator[](std::size_t index)
	{
		if (index >= N)
		{
			throw std::out_of_range("StaticArray [] error: Index out of range!");
		}
		return data_[index];
	}

	const T& operator[](std::size_t index) const
	{
		if (index >= N)
		{
			throw std::out_of_range("StaticArray [] const error: Index out of range!");
		}
		return data_[index];
	}

	constexpr std::size_t getSize() const { return N; }
};


int main()
{
	std::cout << "=== Test Vector<int> ===" << std::endl;
	Vector<int> vInt(3);
	vInt[0] = 100;
	vInt[1] = 200;
	std::cout << "vInt[0] = " << vInt[0] << ", vInt[1] = " << vInt[1] << std::endl;

	std::cout << "\n=== Test Vector<double> ===" << std::endl;
	Vector<double> vDouble(2);
	vDouble.set(0, 3.14159);
	std::cout << "vDouble.get(0) = " << vDouble.get(0) << std::endl;

	std::cout << "\n=== Test StaticArray<std::string, 3> ===" << std::endl;
	StaticArray<std::string, 3> sArray;
	sArray[0] = "C++";
	sArray[1] = "Templates";
	sArray[2] = "StaticArray";

	for (std::size_t i = 0; i < sArray.getSize(); ++i)
	{
		std::cout << "sArray[" << i << "] = " << sArray[i] << std::endl;
	}

	std::cout << "\n=== Exception Test ===" << std::endl;
	try
	{
		std::cout << sArray[10] << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}
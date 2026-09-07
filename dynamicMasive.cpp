#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Vector
{
private:
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
	T* dynamicArray = nullptr;

	void reallocate()
	{
		std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
		T* newData = new T[newCapacity]();

		for (std::size_t i = 0; i < size_; ++i)
		{
			newData[i] = dynamicArray[i];
		}

		delete[] dynamicArray;
		dynamicArray = newData;
		capacity_ = newCapacity;
	}

public:
	Vector() : size_(0), capacity_(0), dynamicArray(nullptr) {}

	explicit Vector(std::size_t initialSize)
		: size_(initialSize), capacity_(initialSize)
	{
		dynamicArray = new T[capacity_]();
	}

	Vector(const Vector& other)
		: size_(other.size_), capacity_(other.capacity_)
	{
		dynamicArray = new T[capacity_];
		for (std::size_t i = 0; i < size_; ++i)
		{
			dynamicArray[i] = other.dynamicArray[i];
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			delete[] dynamicArray;
			size_ = other.size_;
			capacity_ = other.capacity_;
			dynamicArray = new T[capacity_];
			for (std::size_t i = 0; i < size_; ++i)
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

	void push_back(const T& value)
	{
		if (size_ == capacity_)
		{
			reallocate();
		}
		dynamicArray[size_] = value;
		++size_;
	}

	void resize(std::size_t newSize)
	{
		if (newSize > capacity_)
		{
			T* newData = new T[newSize]();
			for (std::size_t i = 0; i < size_; ++i)
			{
				newData[i] = dynamicArray[i];
			}
			delete[] dynamicArray;
			dynamicArray = newData;
			capacity_ = newSize;
		}
		size_ = newSize;
	}

	T& operator[](std::size_t index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector [] error: Index out of range!");
		}
		return dynamicArray[index];
	}

	const T& operator[](std::size_t index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector [] const error: Index out of range!");
		}
		return dynamicArray[index];
	}

	std::size_t getSize() const { return size_; }
	std::size_t getCapacity() const { return capacity_; }

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector)
	{
		out << "[";
		for (std::size_t i = 0; i < vector.size_; ++i)
		{
			out << vector.dynamicArray[i];
			if (i + 1 < vector.size_)
			{
				out << ", ";
			}
		}
		out << "]";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector<T>& vector)
	{
		for (std::size_t i = 0; i < vector.size_; ++i)
		{
			in >> vector.dynamicArray[i];
		}
		return in;
	}
};

int main()
{
	std::cout << "=== Test Vector Push Back & Capacity ===" << std::endl;
	Vector<int> vec;

	for (int i = 1; i <= 5; ++i)
	{
		vec.push_back(i * 10);
		std::cout << "Pushed " << i * 10
			<< " | Size: " << vec.getSize()
			<< " | Capacity: " << vec.getCapacity() << std::endl;
	}

	std::cout << "\n=== Test Output Stream (operator<<) ===" << std::endl;
	std::cout << "Vector contents: " << vec << std::endl;

	std::cout << "\n=== Test Input Stream (operator>>) ===" << std::endl;
	Vector<int> inputVec(3);
	std::cout << "Enter 3 integers: ";
	std::cin >> inputVec;
	std::cout << "You entered: " << inputVec << std::endl;

}
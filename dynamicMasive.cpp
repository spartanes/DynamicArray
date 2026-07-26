#include <iostream>

class Vector 
{
private:
	unsigned int size = 0;
	int* dynamicArray = nullptr;
public:
	Vector(int sizeOffArray) 
	{ // Constructor
		size = sizeOffArray;
		dynamicArray = new int[size];
	}
	
	Vector(const Vector& other) //Copy constructor
	{
		size = other.size;
		dynamicArray = new int[size];
		for (unsigned int i = 0;i < size;++i) 
		{
			dynamicArray[i] = other.dynamicArray[i];
		}
	}

	Vector& operator=(const Vector& other) //copy assignment operator
	{
		if (this != &other) 
		{
			delete[] dynamicArray;
			size = other.size;
			dynamicArray = new int[size];
			for (unsigned int i = 0;i < size;++i) 
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
	
	void set(int index, int newValue) { dynamicArray[index] = newValue; } //set
	
	int get(int index) const { return dynamicArray[index]; } //get

	int& operator[](unsigned int index) { return dynamicArray[index]; } //not const operator
	
	const int& operator[](unsigned int index) const { return dynamicArray[index]; } //const operator
	
	bool operator==(const Vector& other)const //operator ==
	{
		if (size != other.size) { return false; }
		for (unsigned int i = 0;i < size;++i) 
		{
			if (dynamicArray[i] != other.dynamicArray[i]) { return false; }
		}
		return true;
	}

	bool operator!=(const Vector& other) const { return !(*this == other); } // operator !=
	
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
	Vector myVector(3);
	myVector.set(0, 10);
	myVector.set(1, 20);
	myVector.set(2, 30);

	std::cout << "Before resize, element 1: " << myVector.get(1) << std::endl;

	myVector.resize(5);
	myVector.set(3, 40);

	std::cout << "After resize, element 1: " << myVector.get(1) << std::endl;
	std::cout << "After resize, element 3: " << myVector.get(3) << std::endl;
}


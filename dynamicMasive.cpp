#include <iostream>

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
	~Vector() //Destructor
	{
		delete[] dynamicArray;
		dynamicArray = nullptr;
	}
	
	void set(int index, int newValue) 
	{
		dynamicArray[index] = newValue;
	}
	
	int get(int index) const 
	{ 
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


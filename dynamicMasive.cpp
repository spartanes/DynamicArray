#include <iostream>
#include <stdexcept>
#include <string>
#include <iterator>

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
	class Iterator
	{
	private:
		T* ptr_;

	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		Iterator(T* ptr = nullptr) : ptr_(ptr) {}

		reference operator*() const { return *ptr_; }
		pointer operator->() const { return ptr_; }

		Iterator& operator++()
		{
			++ptr_;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++ptr_;
			return temp;
		}

		Iterator& operator--()
		{
			--ptr_;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--ptr_;
			return temp;
		}

		Iterator& operator+=(difference_type n)
		{
			ptr_ += n;
			return *this;
		}

		Iterator& operator-=(difference_type n)
		{
			ptr_ -= n;
			return *this;
		}

		Iterator operator+(difference_type n) const { return Iterator(ptr_ + n); }
		Iterator operator-(difference_type n) const { return Iterator(ptr_ - n); }

		difference_type operator-(const Iterator& other) const { return ptr_ - other.ptr_; }

		reference operator[](difference_type n) const { return ptr_[n]; }

		bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
		bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
		bool operator<(const Iterator& other) const { return ptr_ < other.ptr_; }
		bool operator>(const Iterator& other) const { return ptr_ > other.ptr_; }
		bool operator<=(const Iterator& other) const { return ptr_ <= other.ptr_; }
		bool operator>=(const Iterator& other) const { return ptr_ >= other.ptr_; }
	};

	class ConstIterator
	{
	private:
		const T* ptr_;

	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		ConstIterator(const T* ptr = nullptr) : ptr_(ptr) {}

		reference operator*() const { return *ptr_; }
		pointer operator->() const { return ptr_; }

		ConstIterator& operator++()
		{
			++ptr_;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			++ptr_;
			return temp;
		}

		ConstIterator& operator--()
		{
			--ptr_;
			return *this;
		}

		ConstIterator operator--(int)
		{
			ConstIterator temp = *this;
			--ptr_;
			return temp;
		}

		ConstIterator& operator+=(difference_type n)
		{
			ptr_ += n;
			return *this;
		}

		ConstIterator& operator-=(difference_type n)
		{
			ptr_ -= n;
			return *this;
		}

		ConstIterator operator+(difference_type n) const { return ConstIterator(ptr_ + n); }
		ConstIterator operator-(difference_type n) const { return ConstIterator(ptr_ - n); }

		difference_type operator-(const ConstIterator& other) const { return ptr_ - other.ptr_; }

		reference operator[](difference_type n) const { return ptr_[n]; }

		bool operator==(const ConstIterator& other) const { return ptr_ == other.ptr_; }
		bool operator!=(const ConstIterator& other) const { return ptr_ != other.ptr_; }
		bool operator<(const ConstIterator& other) const { return ptr_ < other.ptr_; }
		bool operator>(const ConstIterator& other) const { return ptr_ > other.ptr_; }
		bool operator<=(const ConstIterator& other) const { return ptr_ <= other.ptr_; }
		bool operator>=(const ConstIterator& other) const { return ptr_ >= other.ptr_; }
	};

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

	Iterator begin() { return Iterator(dynamicArray); }
	Iterator end() { return Iterator(dynamicArray + size_); }

	ConstIterator begin() const { return ConstIterator(dynamicArray); }
	ConstIterator end() const { return ConstIterator(dynamicArray + size_); }

	ConstIterator cbegin() const { return ConstIterator(dynamicArray); }
	ConstIterator cend() const { return ConstIterator(dynamicArray + size_); }

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

template <typename T>
void insertion_sort(Vector<T>& vec)
{
	for (auto it = vec.begin() + 1; it != vec.end(); ++it)
	{
		T key = *it;
		auto j = it;

		while (j > vec.begin() && *(j - 1) > key)
		{
			*j = *(j - 1);
			--j;
		}
		*j = key;
	}
}

int main()
{
	std::cout << "=== Test Vector Iterators & Range-based For ===" << std::endl;
	Vector<int> vec;
	vec.push_back(40);
	vec.push_back(10);
	vec.push_back(30);
	vec.push_back(20);

	std::cout << "Vector before sort (range-based for): ";
	for (const auto& elem : vec)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "\n=== Test Insertion Sort using Iterators ===" << std::endl;
	insertion_sort(vec);

	std::cout << "Vector after sort: " << vec << std::endl;

	std::cout << "\n=== Test Iterators Arithmetic ===" << std::endl;
	auto it = vec.begin();
	std::cout << "First element: " << *it << std::endl;
	std::cout << "Element at index 2 (it + 2): " << *(it + 2) << std::endl;

	return 0;
#include <iostream>

template<typename T, size_t S>
class Array
{
public:
	constexpr size_t Size() const { return S; }

	T& operator[](size_t index) { return m_Data[index]; }

	const T& operator[](size_t index) const { return m_Data[index]; }

	T* Data() { return m_Data; }

	const T* Data() const { return m_Data; }

private:
	T m_Data[S];
};

int main()
{
	int size = 5;
	Array<int, 5> array;

	memset(&array[0], 0, array.Size() * sizeof(int));

	for (size_t i = 0; i < array.Size(); i++)
	{
		std::cout << array[i] << std::endl;
	}
}
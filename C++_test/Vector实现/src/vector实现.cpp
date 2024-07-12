#include <iostream>

template<typename T>
class Vector
{
public:
	Vector()
	{
		ReAlloc(2);
	}

	~Vector()
	{
		delete[] m_Data;
	}

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value) noexcept
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
		//m_Data[m_Size] = T(std::forward<Args>(args)...);

		return m_Data[m_Size++];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		m_Size = 0;
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	size_t Size() const { return m_Size; }

private:
	void ReAlloc(size_t newCapacity)
	{
		//1. allocate a new block of memory
		//2. copy/move old elements into new block
		//3. delete old elements

		T* newBlock = new T[newCapacity];

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);

		delete[] m_Data;
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

private:
	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3() {}

	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar) {}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copied" << std::endl;
	}

	Vector3(Vector3&& other) noexcept
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Moved" << std::endl;
	}

	~Vector3()
	{
		std::cout << "Destoryed" << std::endl;
	}

	Vector3& operator=(const Vector3& other)
	{
		std::cout << "Copy" << std::endl;

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& operator=(Vector3&& other) noexcept
	{
		std::cout << "Move" << std::endl;

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;
	std::cout << "-----------" << std::endl;
}

template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
	std::cout << "-----------" << std::endl;
}

int main()
{
	//Vector<std::string> vector;

	//vector.PushBack("Cherno");
	//vector.PushBack("C++");
	//vector.PushBack("Vector");

	//PrintVector(vector);

	Vector<Vector3> vector3;
	vector3.EmplaceBack(1.0f);
	vector3.EmplaceBack(2, 3, 4);
	vector3.EmplaceBack();

	PrintVector(vector3);

	std::cin.get();
}
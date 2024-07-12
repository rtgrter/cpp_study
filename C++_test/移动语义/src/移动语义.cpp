#include <iostream>
#include <string>

//C++三法则：如果需要析构函数，则一定需要拷贝构造函数、拷贝赋值操作符
//C++五法则：为了支持移动语义，又增加了移动构造函数和移动赋值操作符
class String
{
public:
	String() = default;								//默认构造函数

	String(const char* string)						//有参构造函数
	{
		std::cout << "Created" << std::endl;
		m_Size = strlen(string);
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string, m_Size + 1);
	}

	String(const String& other)						//拷贝构造函数
		: m_Size(other.m_Size)
	{
		std::cout << "Copied" << std::endl;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, other.m_Data, m_Size + 1);
	}

	String& operator=(const String& other)			//重载赋值操作符
	{
		if (this != &other)
		{
			delete[] m_Data;

			m_Size = other.m_Size;
			m_Data = new char[m_Size + 1];
			memcpy(m_Data, other.m_Data, m_Size + 1);
		}
		return *this;
	}

	String(String&& other) noexcept					//移动构造函数
		:m_Size(other.m_Size),m_Data(other.m_Data)
	{
		std::cout << "Moved" << std::endl;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	String& operator=(String&& other) noexcept		//重载移动操作符
	{
		std::cout << "Moved" << std::endl;

		if (this != &other)
		{
			delete[] m_Data;

			m_Data = other.m_Data;
			m_Size = other.m_Size;

			other.m_Data = nullptr;
			other.m_Size = 0;
		}
		return *this;
	}

	~String()										//析构函数
	{
		std::cout << "Destoryed" << std::endl;
		delete m_Data;
	}

	void Print()									//打印字符串
	{
		for (uint32_t i = 0; i < m_Size; i++)
			std::cout << m_Data[i];
		std::cout << std::endl;
	}
private:
	uint32_t m_Size;
	char* m_Data;
};

class Entity
{
public:
	Entity(const String& name)
		: m_Name(name)
	{
	}
	Entity(String&& name)
		:m_Name(std::move(name))
	{
	}
	void PrintName()
	{
		m_Name.Print();
	}
private:
	String m_Name;
};

int main()
{
	//Entity entity("Cherno");
	//entity.PrintName();

	{
		String apple("Apple");
		String dest;

		std::cout << "Apple:";
		apple.Print();
		std::cout << "Dest:";
		dest.Print();

		dest = std::move(apple);

		std::cout << "Apple:";
		apple.Print();
		std::cout << "Dest:";
		dest.Print();
	}

	std::cin.get();
}
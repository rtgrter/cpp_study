#include <iostream>
#include <string>

//拷贝构造函数，解决浅拷贝的问题

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}
	String(const String& other)
		:m_Size(other.m_Size)
	{
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}
	~String()
	{
		delete[] m_Buffer;
	}

	friend std::ostream& operator<<(std::ostream& ostream, const String& string);
};

std::ostream& operator<<(std::ostream& ostream, const String& string)
{
	ostream << string.m_Buffer;
	return ostream;
}

int main()
{
	String string = "Cherno";
	String second = string;
	std::cout << string << std::endl;
	std::cout << second << std::endl;


	std::cin.get();

}
#include <iostream>
#include <memory>
//智能指针shared_ptr实现
template<typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		: m_Ptr(ptr), m_Pcount(new int(1))
	{
	}

	SharedPtr(const SharedPtr& other)
		: m_Ptr(other.m_Ptr), m_Pcount(other.m_Pcount)
	{
		(*m_Pcount)++;
	}

	SharedPtr<T> operator=(const SharedPtr& other)
	{
		if (this != &other)
		{
			if (--(*(this->m_Pcount)) == 0)
			{
				delete this->m_Pcount;
				delete this->m_Ptr;
			}
			m_Ptr = other.m_Ptr;
			m_Pcount = other.m_PCount;
			(*m_Pcount)++;
		}
		return *this;
	}

	T& operator*()
	{
		return *(this->m_Ptr);
	}

	T* operator->()
	{
		return this->m_Ptr;
	}

	~SharedPtr()
	{
		--(*(this->m_Pcount));
		if ((*(this->m_Pcount)) == 0)
		{
			delete m_Ptr;
			delete m_Pcount;

			m_Ptr = nullptr;
			m_Pcount = nullptr;
		}
	}

private:
	T* m_Ptr;
	int* m_Pcount;
};
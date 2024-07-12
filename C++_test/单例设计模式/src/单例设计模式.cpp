#include <iostream>


//单例设计模式
class Random
{
public:
	Random(const Random&) = delete;

	static Random& Get()
	{
		//在静态函数中定义单例实例化静态变量
		static Random s_Instance;
		return s_Instance;
	}

	//间接调用IFloat
	static float Float() { return Get().IFloat(); }

private:
	Random() {}

	float IFloat() { return m_RandomGenerator; }

private:
	float m_RandomGenerator = 0.5f;
};

int main()
{
	float number = Random::Float();
	std::cout << number << std::endl;
	std::cin.get();
}
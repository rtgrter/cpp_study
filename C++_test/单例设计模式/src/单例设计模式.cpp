#include <iostream>


//�������ģʽ
class Random
{
public:
	Random(const Random&) = delete;

	static Random& Get()
	{
		//�ھ�̬�����ж��嵥��ʵ������̬����
		static Random s_Instance;
		return s_Instance;
	}

	//��ӵ���IFloat
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
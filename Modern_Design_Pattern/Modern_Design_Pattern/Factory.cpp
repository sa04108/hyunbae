/*
* Factory Pattern, ���� Factory ��� �Ѵ�.
* ��ü�� ������ ��� �ְų� ���� �����ϴ� Ŭ������ ������ �ô� Ŭ������ �и��ϴ°�.
* ��ü�� ������ �ô� Ŭ������ Factory �̴�.
* ���� ��ü�� �����ϴ� �Լ� ���� Factory �� �� �� �ִ�.
* �߻����丮�� ��� �������̽�(����Ŭ����)�� ���� ��ü���� �����ϰ� ������ ������ ���� �����Ѵ�.
*/

#include <iostream>
#include <memory>
#include <map>

using namespace std;

#pragma region Abstract Factory with RAII
struct HotDrink
{
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
	void prepare(int volume) override
	{
		cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << endl;
	}
};

struct Coffee : HotDrink
{
	void prepare(int volume) override
	{
		cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
	}
};

struct HotDrinkFactory
{
	virtual unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override
	{
		return make_unique<Coffee>();
	}
};

struct TeaFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override
	{
		return make_unique<Tea>();
	}
};

class DrinkFactory
{
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
	DrinkFactory()
	{
		hot_factories["coffee"] = make_unique<CoffeeFactory>();
		hot_factories["tea"] = make_unique<TeaFactory>();
	}
	unique_ptr<HotDrink> make_drink(const string& name, int volume)
	{
		auto drink = hot_factories[name]->make();
		drink->prepare(volume);
		return drink;
	}
};
#pragma endregion

int main()
{
#pragma region Abstract Factory
	DrinkFactory df;
	df.make_drink("coffee", 200);
#pragma endregion

	return 0;
}
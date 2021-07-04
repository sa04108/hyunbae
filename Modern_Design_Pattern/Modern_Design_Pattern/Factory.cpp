/*
* Factory Pattern, 보통 Factory 라고 한다.
* 객체의 정보를 담고 있거나 일을 수행하는 클래스와 생성을 맡는 클래스를 분리하는것.
* 객체의 생성을 맡는 클래스가 Factory 이다.
* 또한 객체를 생성하는 함수 역시 Factory 가 될 수 있다.
* 추상팩토리의 경우 인터페이스(가상클래스)를 통해 객체들을 생성하고 정보를 가지며 일을 수행한다.
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
#include <iostream>
using namespace std;

struct Weapon {
	int mPower;
};
struct Armor {
	int mDefence;
};

// Product
class Character
{
public:
	Weapon* mWeapon;
	Armor* mArmor;
	
	void DisplayParts() {
		std::cout << "Weapon power:" << mWeapon->mPower << std::endl;
		std::cout << "Armor defence:" << mArmor->mDefence << std::endl;
	}
};

// Builder 인터페이스
class CharacterBuilder
{
public:
	virtual Weapon* CreateWeapon() = 0;
	virtual Armor* CreateArmor() = 0;
};

// Director, Product 생성 공정을 책임 집니다.
class CharacterDirector
{
	CharacterBuilder* mBuilder;

public:
	void SetBuilder(CharacterBuilder* newBuilder) {
		// Up Casting
		mBuilder = newBuilder;
	}
	Character* CreateCharacter() {
		Character* character = new Character();
		character->mWeapon = mBuilder->CreateWeapon();
		character->mArmor = mBuilder->CreateArmor();
		return character;
	}
};

// Concrete Builder for archer
class ArcherBuilder : public CharacterBuilder
{
public:
	Weapon* CreateWeapon() override {
		Weapon* weapon = new Weapon();
		weapon->mPower = 200;
		return weapon;
	}
	Armor* CreateArmor() override {
		Armor* armor = new Armor();
		armor->mDefence = 50; return armor;
	}
};

// Concrete builder for warrior
class WarriorBuilder : public CharacterBuilder
{
public:
	Weapon* CreateWeapon() override {
		Weapon* weapon = new Weapon();
		weapon->mPower = 50;
		return weapon;
	}
	Armor* CreateArmor() override {
		Armor* armor = new Armor();
		armor->mDefence = 200;
		return armor;
	}
};

int main()
{
	Character* character;
	CharacterDirector director;
	ArcherBuilder archer;

	director.SetBuilder(&archer);
	character = director.CreateCharacter();
	character->DisplayParts();

	WarriorBuilder warrior;
	director.SetBuilder(&warrior);
	character = director.CreateCharacter();
	character->DisplayParts();
	return 0;
}
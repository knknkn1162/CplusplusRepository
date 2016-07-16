#include <iostream>
#include <functional>
#include <map>
#include <memory>
using namespace std;


class Pizza
{
private:
	double gredient;
public:
	virtual void prepare() { cout << "prepare default" << endl;  }
	virtual void bake() { cout << "bake default" << endl;}
	virtual void cut() { cout << "cut default" << endl; }
	virtual void box() { cout << "box default" << endl; }
	virtual ~Pizza() {}
};

class CheesePizza : public Pizza
{
private:
public:
	void prepare() { cout << "prepare Cheese" << endl;  }
	void bake() { cout << "bake Cheese" << endl;}
	void cut() { cout << "cut Cheese" << endl; }
	void box() { cout << "box Cheese" << endl; }
	~CheesePizza() {}
};

class ClamPizza : public Pizza
{
private:
public:
	void prepare() { cout << "prepare Clam" << endl;  }
	void bake() { cout << "bake Clam" << endl;}
	void cut() { cout << "cut Clam" << endl; }
	void box() { cout << "box Clam" << endl; }
	~ClamPizza() {}
};


class VegiPizza : public Pizza
{
private:
public:
	void prepare() { cout << "prepare Vegi" << endl;  }
	void bake() { cout << "bake Vegi" << endl;}
	void cut() { cout << "cut Vegi" << endl; }
	void box() { cout << "box Vegi" << endl; }
	~VegiPizza() {}
};




class PizzaFactory
{
public:
	using CreateShapeCallback = std::function<std::shared_ptr<Pizza>(void)>;
private:
	using CallbackMap = std::map<int, CreateShapeCallback>;
	using Pair = std::pair<int, CreateShapeCallback>;
	CallbackMap callbacks;
	PizzaFactory() {}
	~PizzaFactory() = default;
public:
	static PizzaFactory& getInstance() 
	{
		static PizzaFactory singleton = PizzaFactory();
		return singleton;
	}
	bool registerPizza(int shapeId, CreateShapeCallback createFn)
	{
		//pair<iterator,bool> insert (const value_type& val);
		return callbacks.insert(Pair(shapeId, createFn)).second;
		//return callback.insert(CallbackMap::value_type(shapeId, createFn)).second;
	}
	// bool unregisterPizza(int shapeId)
	// {
		// return callbacks.erase(shapeId);
	// }
	std::shared_ptr<Pizza> createPizza(int shapeId)
	{
		auto it = callbacks.find(shapeId);
		if(it == callbacks.end())
		{
			cout << "error" << endl;
			return nullptr;
		}
		return (it->second)();
	}
};

//�������O���
namespace
{
	enum EMenu
	{
		CHEESE, CLAM, VEGI
	};
	
	template<int v>
	struct Int2Type
	{
		enum {value = v};
	};
	// void init()
	// {
		// //PizzaFactory::getInstance().registerPizza(CHEESE, [](){return new CheesePizza();});
		// PizzaFactory::getInstance().registerPizza(CHEESE,
			// [](){return std::shared_ptr<Pizza>(new CheesePizza()); }
			// );
		// PizzaFactory::getInstance().registerPizza(CLAM,
			// [](){return std::shared_ptr<Pizza>(new ClamPizza()); }
			// );
		// PizzaFactory::getInstance().registerPizza(VEGI,
			// [](){return std::shared_ptr<Pizza>(new VegiPizza()); }
			// );
	// }
}


class PizzaStore
{
private:
	//�����萔����A�^�ɕϊ�����e���v���[�gInt2Type��p�ӂ��āA�֐��I�[�o�[���[�h�������āAif-else����r������
	//���ꂼ��Ⴄ�񋓑̂ɉ����āA���ꂼ��قȂ鏈�������������ꍇ�́A�I�[�o�[���[�h��p���Čʂɂ����B
	//�����łȂ��āA�e���v���[�g�̃p�����[�^�����݈̂ˑ����鏈���̏ꍇ�́Acreate<Emenu m>()�̂悤�ɂ���̂��悢�����B
	std::shared_ptr<Pizza> createPizza(Int2Type<CHEESE>) 
	{
		return std::shared_ptr<Pizza>(new CheesePizza());
	}
	std::shared_ptr<Pizza> createPizza(Int2Type<CLAM>) 
	{
		return std::shared_ptr<Pizza>(new ClamPizza());
	}
	std::shared_ptr<Pizza> createPizza(Int2Type<VEGI>) 
	{
		return std::shared_ptr<Pizza>(new VegiPizza());
	}
public:
	PizzaStore() {}
	~PizzaStore() {}
	
	template<EMenu m>
	std::shared_ptr<Pizza> orderPizza()
	{
		auto pizza = createPizza(Int2Type<m>());
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();	
		
		return pizza;
	}
};


int main(void)
{
	PizzaStore ps = PizzaStore();
	auto pizza = ps.orderPizza<EMenu::CHEESE>();
	return 0;
}
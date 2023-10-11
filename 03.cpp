#include <iostream>

template<typename T>
class vector_lite
{
public:
	vector_lite();
	vector_lite(const vector_lite& vl);
	~vector_lite();
	int size();
	void push_back(const T value);
	int capacity();
	T& at(const int& key);
	vector_lite& operator = (const vector_lite& vl);
private:
	int arr_length{ 1 };
	int arr_length_logic{ 0 };
	T* v{nullptr};
	T* create_arr();
	void delete_arr();
	void assign(const vector_lite& t);
	void expand_arr();
};

template<typename T>
vector_lite<T>::vector_lite()
{
	v = this->create_arr();
}

template<typename T>
vector_lite<T>::vector_lite(const vector_lite<T>& vl)
{
	this->assign(vl);
	this->arr_length_logic = vl.arr_length_logic;
}

template<typename T>
T* vector_lite<T>::create_arr()
{
	return new T [this->arr_length];
}

template<typename T>
void vector_lite<T>::push_back(const T value)
{
	if (this->arr_length_logic + 1 > this->arr_length)
	{
		this->expand_arr();
	}
	this->v[this->arr_length_logic] = value;
	++this->arr_length_logic;
}

template<typename T>
void vector_lite<T>::expand_arr()
{
	int nsz = this->arr_length << 1;

	T* tmp = new T[nsz];
	for (int i = 0; i < this->arr_length; ++i)
	{
		tmp[i] = this->v[i];
	}
	this->delete_arr();
	this->v = tmp;
	this->arr_length = nsz;
}

template<typename T>
int vector_lite<T>::size()
{
	return this->arr_length_logic;
}

template<typename T>
int vector_lite<T>::capacity()
{
	return this->arr_length - this->arr_length_logic;
}

template<typename T>
T& vector_lite<T>::at(const int& key)
{
	if ((key < 1 || key > this->arr_length_logic) || this->v == nullptr) throw std::out_of_range("Index out of array!");
	return this->v[key - 1];
}

template<typename T>
vector_lite<T>& vector_lite<T>::operator = (const vector_lite<T>& r)
{
	if (this != &r) {
		this->delete_arr();
		this->assign(r);
		this->arr_length_logic = r.arr_length_logic;
		return *this;
	}
	return *this;
}

template<typename T>
void vector_lite<T>::assign(const vector_lite<T>& t)
{
	this->v = new int[t.arr_length]{ 0 };
	this->arr_length = t.arr_length;
	for (int i = 0; i < this->arr_length; ++i)
	{
		this->v[i] = t.v[i];
	}
}

template<typename T>
void vector_lite<T>::delete_arr()
{
	delete[] this->v;
	this->v = nullptr;
}

template<typename T>
vector_lite<T>::~vector_lite()
{
	this->delete_arr();
}

int main()
{
	try
	{
		vector_lite<int> vl;
		vl.push_back(1);
		vl.push_back(4);
		vl.push_back(6);
		vl.push_back(-8);
		vl.push_back(17);
		std::cout << vl.at(1) << std::endl;
		std::cout << vl.at(4) << std::endl;
		std::cout << vl.size() << std::endl;
		std::cout << vl.capacity() << std::endl;
		std::cout << vl.at(10) << std::endl;
		vector_lite<int> vl1(vl);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	return 0;
}

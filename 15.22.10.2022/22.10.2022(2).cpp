#include <iostream>
#include <cassert>
#include <random>


template <typename T, unsigned N>
class Grid final {

private:
	using size_type = unsigned;
	size_type size;
	Grid<T, N - 1>* data;

public:
	using output_type = size_type;

	//метод создание тела сетки
	void make_data(unsigned tries = 0) {
		assert(tries != 5);
		data = static_cast<Grid<T, N - 1>*>(operator new[](size * sizeof(Grid<T, N - 1>)));
		if (data == nullptr) {
			make_data(tries + 1);
		}
		return;
	}


	//конструкторы
	Grid(T const& t) : size(1) {
		make_data();
		data[0] = t;
	}

	template<typename... Args>
	Grid(size_type size, Args ... subgrid) : size(size) {
		make_data();
		for (unsigned i = 0; i < size; i++) {
			new (data + i) Grid<T, N - 1>(subgrid...);
		}
	}

	//деструктор
	~Grid() {
		if (data != nullptr) {
			for (unsigned i = 0; i < size; i++) {
				data[i].~Grid();
			}
			operator delete(data);
		}
	}

	//конструктор копирования
	Grid(Grid<T, N> const& src) {
		size = src.get_size();
		make_data();
		for (unsigned i = 0; i < size; ++i) {
			new (data + i) Grid<T, N - 1>(src.data[i]);
		}
	}

	//конструктор перемещения
	Grid(Grid<T, N>&& src) noexcept {
		std::swap(this->data, src.data);
		std::swap(this->size, src.size);
	}

	//копирующие присваивание
	Grid<T, N>& operator=(Grid<T, N>& src) {
		if (this == &src)
			return *this;

		Grid<T, N> tmp(src);
		std::swap(this->data, tmp.data);
		std::swap(this->size, tmp.size);
	}

	//перемещающее присваивание
	Grid<T, N>& operator=(Grid<T, N>&& src) noexcept {
		Grid<T, N> tmp(src);
		std::swap(this->size, tmp.size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//оператор доступа к значению элемента
	template<typename... Args>
	T operator ()(size_type idx, Args ... subgrid) const {
		return data[idx](subgrid ...);
	}

	//оператор индексирования
	Grid<T, N - 1>& operator[](size_type idx) const {
		return data[idx];
	}

	//оператор получения размера
	size_type get_size() const {
		return size;
	}


	//оператор печати сетки
	void print() {
		using namespace std;
		for (unsigned i = 0; i < size; i++) {
			data[i].print();
			cout << endl;
		}
	}
};


template <typename T>
class Grid<T, 1> final {

private:
    using value_type = T;
	using size_type = unsigned;
	size_type size;
	T* data;

public:
	using output_type = size_type;

	//метод создание тела сетки
	void make_data(unsigned tries = 0) {
		assert(tries != 5);
		data = new (std::nothrow) T[size];
		if (data == nullptr) {
			make_data(tries + 1);
		}
		return;
	}

	//конструкторы
	Grid(T const& t) : size(1) {
		make_data();
		data[0] = t;
	}

	Grid(size_type size, T const& t) : size(size) {
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = t;
		}
	}

	//деструктор
	~Grid() {
		if (data != nullptr) {
			delete[] data;
		}
	}

	//конструктор копирования
	Grid(Grid<T, 1> const& src) {
		size = src.get_size();
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = src(i);
		}
	}

	//конструктор перемещения
	Grid(Grid<T, 1>&& src) {
		size = src.size;
		data = src.data;
		src.data = nullptr;
	}

	//копирующие присваивание
	Grid<T, 1>& operator=(Grid<T, 1>& src) {
		size = src.size;
		make_data();
		for (unsigned i = 0; i < size; i++) {
			data[i] = src(i);
		}
		return *this;
	}

	//перемещающее присваивание
	Grid<T, 1>& operator=(Grid<T, 1>&& src) noexcept {
		Grid<T, 1> tmp(src);
		std::swap(this->size, tmp.size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//оператор доступа к значению элемента
	T operator ()(size_type idx) const {
		return data[idx];
	}

	//оператор доступа к ссылке на элемент
	T& operator ()(size_type idx) {
		return data[idx];
	}

	//оператор индексирования
	T* operator[](size_type idx) {
		return data + idx;
	}

	//оператор получения размера
	size_type get_size() const {
		return size;
	}

	//оператор печати сетки
	void print() {
		using namespace std;
		for (unsigned i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}
};


void check() {
	Grid<float, 3> const g3(2, 3, 4, 1.0f);
	assert(1.0f == g3(1, 1, 1));

	Grid<float, 2> g2(2, 5, 2.0f);
	assert(2.0f == g2(1, 1));

	g2 = g3[1];
	assert(1.0f == g2(1, 1));
}

int main() {
	Grid<unsigned, 2> a(7, 7, 8);
	Grid<unsigned, 3> b(6, 6, 6, 8);
	Grid<unsigned, 3> d = std::move(b);
	d.print();
	check();
	return 0;
}
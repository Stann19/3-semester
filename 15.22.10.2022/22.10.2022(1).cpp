#include <iostream>
#include <cassert>
#include <random>

template <typename T>
class Grid final {
private:
	using value_type = T;
	using size_type = unsigned;
	T* data;
	size_type y_size, x_size;
public:
	using output_type = size_type;

	Grid(T const& t): data(new T[1]), x_size(1), y_size(1){
			data[0] = t;
	}

	Grid(size_type y_size, size_type x_size): data(new T[x_size * y_size]), y_size(y_size), x_size(x_size){
		assert(data != nullptr);
		std::random_device dev;
		std::mt19937 rng(dev());
		for (unsigned i = 0; i < (y_size) * (x_size); i++) {
			std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6);
			data[i] = dist(rng);
		}
	}

	Grid(size_type y_size, size_type x_size, T const& t) : data(new T[x_size * y_size]), y_size(y_size), x_size(x_size) {
		assert(data != nullptr);
		for (unsigned i = 0; i < (y_size) * (x_size); i++) {
			data[i] = t;
		}
	}

	//деструктор
	~Grid() {
		delete[] data;
	}

	//конструктор копирования
	Grid(Grid<T> const& src): Grid(src.x_size, src.y_size) {
		for (size_type i = 0; i < x_size; i++) {
			for (size_type j = 0; j < y_size; j++) {
				data[i * x_size + j] = src.data[i * x_size + j];
			}
		}
	}

	//конструктор копирующего присваивания
	Grid& operator = (Grid<T> & src) {
		if (this == &src)
			return *this;

		Grid<T> tmp(src);
		std::swap(this->data, tmp.data);
		std::swap(this->y_size, tmp.y_size);
		std::swap(this->x_size, tmp.x_size);
	}

	//конструктор перемещения
	Grid(Grid<T> && src) noexcept{
		std::swap(this->data, src.data);
		std::swap(this->y_size, src.y_size);
		std::swap(this->x_size, src.x_size);
	}

	//конструктор перемещающего присваивания
	Grid<T>& operator = (Grid<T>&& src) {
		Grid<T> tmp(src);
		std::swap(this->x_size, tmp.x_size);
		std::swap(this->y_size, tmp.y_size);
		std::swap(this->data, tmp.data);
		return *this;
	}

	//оператор доступа к ссылке на элемент
	T& operator ()(size_type y_idx, size_type x_idx) {
		return data[y_idx * x_size + x_idx];
	}

	//оператор индексирования
	T* operator[](size_type y_idx) {
		return data + y_idx * x_size;
	}

	//оператор получения координаты y
	size_type get_y_size() const {
		return y_size;
	}

	//оператор получения координаты x
	size_type get_x_size() const {
		return x_size;
	}

	void print() {
		assert(data != nullptr);
		for (size_type i = 0; i < y_size; i++) {
			for (size_type j = 0; j < x_size; j++) {
				std::cout << data[i * x_size + j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	Grid<unsigned> a(4, 4);
	Grid<unsigned> b = std::move(a);
	Grid<unsigned> c(6);
	c.print();
	b.print();
	std::cout << b(1, 2) << std::endl;
	Grid<float> g(3, 2, 0.0f);

	assert(3 == g.get_y_size());
	assert(2 == g.get_x_size());

	using gsize_t = Grid<int>::output_type;

	for (gsize_t y_idx = 0; y_idx < g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx < g.get_x_size(); ++x_idx) {
			assert(0.0f == g[y_idx][x_idx]);
		}

	for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
			g[y_idx][x_idx] = 1.0f;

	for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
		for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
			assert(1.0f == g(y_idx, x_idx));
	return 0;
}

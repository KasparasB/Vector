#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <cstring> 
template <typename T>
class Vector {
private:
	size_t sz = 0;
	size_t cap = 4;
	T* elem;
public:

	//KONSTRUKTORIAI
	Vector() : sz{ 0 }, cap{ 4 }, elem{ new T[4] }{};
	Vector(size_t s) : sz{ s }, cap{ s }, elem{ new T[s] } { std::fill_n(elem, s, 0); };
	Vector(size_t s, T val) : sz{ s }, cap{ s }, elem{ new T[s] }{ std::fill_n(elem, s, val); };
	Vector(const Vector& v) :elem{ new T[v.sz] }, sz{ v.sz }, cap{ v.cap } { // copy konstruktorius
		for (int i = 0; i != sz; i++) elem[i] = v.elem[i];
	}
	Vector(std::initializer_list<T> il)
		: sz(static_cast<int>(il.size())),
		cap(static_cast<int>(il.size())),
		elem(new T[il.size()])
	{
		std::copy(il.begin(), il.end(), elem);
	}

	Vector(T* first, T* last) {
		size_t i;
		size_t count = last - first;
		size_t rsrv_sz = count << 2;
		reserve(rsrv_sz);
		elem = new T[rsrv_sz];
		for (i = 0; i < count; ++i, ++first)
			elem[i] = *first;
		sz = count;
	}
	//KONSTRUKTORIAI

	//ITERATORIAI

	T* begin()
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[0];
		return first_elem;
	}

	const T* begin() const
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[0];
		return first_elem;
	}

	T* end()
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[sz];
		return first_elem;
	}

	const T* end() const
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[sz];
		return first_elem;
	}

	T* rbegin()
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[0];
		return --first_elem;
	}

	const T* rbegin() const
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[0];
		return --first_elem;
	}

	T* rend()
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[sz];
		return first_elem;
	}

	const T* rend() const
	{
		if (sz <= 0) throw std::runtime_error("No value found!");

		T* first_elem = &elem[0];
		return first_elem;
	}
	//ELEMENT ACCESS

	T& at(size_t i)
	{
		if (i < 0 || i >= size()) throw std::out_of_range{ "Vector:: at(). Element not found" };
		return elem[i];
	}

	const T& at(size_t i) const
	{
		if (i < 0 || i >= size()) throw std::out_of_range{ "Vector:: at(). Element not found" };
		return elem[i];
	}

	T& front()
	{
		if (size() <= 0) throw std::out_of_range{ "Vector:: front(). No elements found" };

		return elem[0];
	}

	const T& front() const
	{
		if (size() <= 0) throw std::out_of_range{ "Vector:: front(). No elements found" };

		return elem[0];
	}

	T& back()
	{
		if (size() <= 0) throw std::out_of_range("Vector:: back(). No elements found");
		return elem[sz - 1];
	}

	const T& back() const
	{
		if (size() <= 0) throw std::out_of_range("Vector:: back(). No elements found");
		return elem[sz - 1];
	}

	//ELEMENT ACCESS
	//ITERATORIAI

	//CAPACITY
	bool empty() const { return sz == 0; };
	size_t size() const { return sz; };
	size_t capacity() const { return cap; };

	void reserve(size_t new_cap)
	{
		if (new_cap > cap) {
			cap = new_cap;
			reallocate();
		}
	}


	void shrink_to_fit() {
		cap = sz;
		reallocate();
	}


	//CAPACITY

	//MODIFIERS

	void clear()
	{
		size_t i;
		for (i = 0; i < sz; ++i)
			elem[i].~T();
		sz = 0;
	};

	T* erase(const T* it) {
		T* iit = &elem[it - elem];
		(*iit).~T();
		memmove(iit, iit + 1, (sz - (it - elem) - 1) * sizeof(T));
		--sz;
		return iit;
	}

	void resize(size_t size) {
		if (size > sz) {
			if (size > cap) {
				cap = size;
				reallocate();
			}
		}
		else {
			size_t i;
			for (i = sz; i < sz; ++i)
				elem[i].~T();
		}
		sz = size;
	}

	T* erase(T* first, T* last)
	{
		size_t new_sz = 0;
		T* f = &elem[first - elem];
		if (first == last) return f;
		for (; first != last; ++first)
		{
			(*first).~T();
			new_sz++;
		}

		memmove(f, last, (sz - (last - elem)) * sizeof(T));
		sz -= new_sz;
		return f;
	}

	void push_back(const T& n)
	{
		int k = 0;
		if (sz == cap) {
			k++;
			std::cout << k << std::endl;
			cap <<= 2;
			reallocate();
		}
		elem[sz] = n;
		++sz;
	}


	void pop_back() {
		if (sz > 0) {
			delete &elem[--sz];
		}
	}

	void assign(size_t count, const T& value)
	{
		T* temp = new T[count];
		for (int i = 0; i < count; i++)
		{
			temp[i] = value;
		}

		delete[] elem;
		elem = temp;
	}


	void assign(T* first, T* last)
	{
		size_t i;
		size_t count = last - first;
		size_t rsrv_sz = count << 2;
		reserve(rsrv_sz);
		elem = new T[rsrv_sz];
		for (i = 0; i < count; ++i, ++first)
			elem[i] = *first;
		sz = count;
	}
	//MODIFIERS


	//OPERATORIAI

	Vector<T> operator=(const Vector<T> &other) {
		size_t i;
		if (sz < other.size()) {
			sz = other.size() << 2;
			reallocate();
		}
		for (i = 0; i < other.size(); ++i)
			elem[i] = other.elem[i];
		sz = other.size();
	}
	Vector<T> operator =(Vector<T> &&other) {
		size_t i;
		if (sz < other.size()) {
			sz = other.size() << 2;
			reallocate();
		}
		for (i = 0; i < other.size(); ++i)
			elem[i] = std::move(other.arr[i]);
		sz = other.size();
	}

	Vector<T> operator =(std::initializer_list<T> lst) {
		if (sz < lst.size()) {
			sz = lst.size() << 2;
			reallocate();
		}
		size() = 0;
		for (auto &item : lst)
			elem[sz++] = item;
	}

	Vector<T> operator+(const Vector& b)
	{
		if (sz != b.size())
			throw std::runtime_error("Vektorių dydžio neatitikimas!");
		auto size = sz;
		Vector c(size);
		for (auto i = 0; i != sz; i++)
			c[i] = elem[i] + b[i];
		return c;
	};

	T& operator[](size_t i)
	{
		if (i < 0 || i >= size()) throw std::out_of_range{ "Vector::operator[]" };
		return elem[i];
	}
	const T& operator[](size_t i) const
	{
		if (i < 0 || i >= size()) throw std::out_of_range{ "Vector::operator[]" };
		return elem[i];
	}
	//OPERATORIAI
	~Vector() {
		delete[] elem;
	};

	inline void reallocate() {
		T *tarr = new T[cap];
		size_t num = sz * sizeof(T);

		//std::move(&elem[0], &elem[sz], tarr);
		//delete[] elem;

		memcpy(tarr, elem, num );
		delete[] elem;
		elem = tarr;
	}

};
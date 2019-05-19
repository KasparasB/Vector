# Eksperimentiniai Vector klasės tyrimai

1. Vektorius turi daugumą std::vector klasės funkcijų. Trūksta insert, swap bei realizacijų po C++11 atnaujinimo. 
Gaunami rezultatai sutampa (kiek teko testuoti) su std::vector rezultatais, tačiau ženkliai skiriasi atlikimo sparta.

### Funkcijų apžvalga 

1. **at()**

Grąžina vartotojo nurodytą elementą prieš tai patikrindama ar toks elementas egzistuoja sąraše.

```shell
const T& at(size_t i) const
	{
		if (i < 0 || i >= size()) throw std::out_of_range{ "Vector:: at(). Element not found" };
		return elem[i];
	}
```

2. **reserve()**

Rezervuoja vartotojo nurodyta kiekį vietos vektoriuje prieš tai patikrindamas ar esamas kiekis nėra didesnis už vartotojo įrašytą. 

```shell
void reserve(size_t new_cap)
	{
		if (new_cap > cap) {
			cap = new_cap;
			reallocate();
		}
	}
```

**reallocate() funkcija**

Kadangi mano vektoriaus realizacijoje tenka dažnai kopijuoti atmintį, buvo sukurta funkcija nekartoti to pačio kodo kelis kartus rašant 
skirtingas funkcijas

```shell
inline void reallocate() {
		T *tarr = new T[cap];
		memcpy(tarr, elem, sz * sizeof(T));
		delete[] elem;
		elem = tarr;
	}
```

3. **operator+**

Sudeda dviejų vektorių elementus. Prieš tai funkcija patikrina, ar vektoriai yra vienodo dydžių ir tipų.

```shell
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
```

4. **erase()**

Sukurtos 2 realizacijos: galima ištrinti elementą nurodant jo adresą arba galima ištrinti elementus esančius tarp nurodytų adresų (įskaitant juos pačius).

```shell
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
```

5. **Vector(first, last) konstruktorius**

Naudojamas sukurti vektorių kito vektoriaus pagrindu.

```shell
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
```

### Vektorių užpildymas

| Dydis    | std::vector | Vector  |
|----------|-------------|-------------|
| 10 000     | 0.0064255s s | 0.0002147s   |
| 100 000   | 0.0642805s | 0.0023406s |
| 1 000 000  | 0.6417691s | 0.0196814s |
| 10 000 000 | 6.2121849s s  | 0.2075280s s |

### Perskirstymai

* std::vector - 25 perskirstymai
* Vector - 13 perskirstymų


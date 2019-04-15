
#include <iostream>
#include<iostream>


namespace student
{
	template <class T>
	class vector
	{
		void* data;
		size_t size;
		size_t capacity;
	public:
		class iterator
		{
			friend class vector<T>;
		public:


			iterator(T* point):pointer (point)
			{}
			iterator():pointer(nullptr)
			{}

			const T& operator *() const
			{
				return &pointer;
			}
			const T& operator ->() const
			{
				return &pointer;
			}
			iterator& operator ++()
			{
				++pointer;
				return *this;
			}
			iterator operator ++(int)
			{
				iterator I(pointer);
				++(*this);
				return I;
			}
			T& operator *() const
			{
				return &pointer;
			}
			T& operator ->() const
			{
				return &pointer;
			}

			bool operator == (const iterator I1)
			{
				return(I1.pointer == pointer);
			}
			bool operator != (const iterator I1)
			{
				return !(I1 == *this);
			}

			iterator& operator --()
			{
				--pointer;
				return *this;
			}
			iterator operator --(int)
			{
				iterator I(pointer);
				--pointer;
				return I;
			}
			iterator operator +(size_t x) const
			{
				return iterator(pointer + x);
			}
			iterator operator -(size_t x) const
			{
				return iterator(pointer - x);
			}
			iterator operator +=(size_t x) const
			{
				pointer += x;
				return this;
			}
			iterator operator -=(size_t x) const
			{
				pointer -= x;
				return this;
			}
			bool operator < (const iterator I)
			{
				return(pointer < I.pointer);
			}
			bool operator <= (const iterator I)
			{
				return(*this < I || *this == I);
			}
			bool operator > (const iterator I)
			{
				return!(*this < I || *this == I);
			}
			bool operator >= (const iterator I)
			{
				return !(*this < I);
			}
		private:
			T* pointer;
		};
		class const_iterator
		{

			friend class vector<T>;
		public:

			const_iterator(T* point): pointer (point)			
			{}
			const_iterator(): pointer (nullptr)
			{}

			const T& operator *() const
			{
				return &pointer;
			}
			const T& operator ->() const
			{
				return &pointer;
			}
			const_iterator& operator ++()
			{
				++pointer;
				return *this;
			}
			const_iterator operator ++(int)
			{
				const_iterator I(pointer);
				++(*this);
				return I;
			}
			T& operator *() const
			{
				return *pointer;
			}
			T& operator ->() const
			{
				return *pointer;
			}

			bool operator == (const const_iterator I1)
			{
				return(I1.pointer == pointer);
			}
			bool operator != (const const_iterator I1)
			{
				return !(I1 == *this);
			}

			const_iterator& operator --()
			{
				--pointer;
				return *this;
			}
			const_iterator operator --(int)
			{
				const_iterator I(pointer);
				--pointer;
				return I;
			}
			const_iterator operator +(size_t x) const
			{
				return const_iterator(pointer + x);
			}
			const_iterator operator -(size_t x) const
			{
				return const_iterator(pointer - x);
			}
			const_iterator operator +=(size_t x) const
			{
				pointer += x;
				return this;
			}
			const_iterator operator -=(size_t x) const
			{
				pointer -= x;
				return this;
			}
			bool operator < (const const_iterator I)
			{
				return(pointer < I.pointer);
			}
			bool operator <= (const const_iterator I)
			{
				return(*this < I || *this == I);
			}
			bool operator > (const const_iterator I)
			{
				return!(*this < I || *this == I);
			}
			bool operator >= (const const_iterator I)
			{
				return !(*this < I);
			}
		private:
			T* pointer;

		};
		class out_of_range
		{};

		vector(): capacity(0), size(0), data(operator new(sizeof(T) * capacity))
		{}
		vector(size_t filled_size, const T& value = T()): capacity(filled_size), size(0), data(operator new(capacity * sizeof(T)))
		{
			for (size_t i = 0; i < filled_size; i++)
			{
				push_back(value);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			capacity = 0;
			size = 0;
			data = operator new(sizeof(T) * capacity);
			for (InputIterator i = first; i < last; i++)
			{
				capacity++;
				new (static_cast<T*>(data) + size) T();
				size++;
			}
		}
		vector(vector const & V)
		{
			size = 0;
			capacity = V.capacity;
			data = operator new(sizeof(T) * capacity);
			for (size_t i = 0; i < V.size; i++)
			{
				push_back(*(V.data + i));
			}
		}
		vector(vector && V)
		{
			size = V.size;
			capacity = V.capacity;
			data = V.data;
			V.data = nullptr;
		}
		~vector()
		{
			
			while (size != 0 )
			{
				pop_back();
			}
			operator delete[](data);
		}
		size_t resize(size_t n, T value)
		{
			if (n >= capacity)
			{
				capacity = n * 2;
			}
			if (n > size)
			{
				for (size_t i = size; i < n; i++)
				{
					push_back(value);
				}
			}
			if (n < size)
			{
				for (size_t i = size; i > n; i--)
				{
					pop_back();
				}
			}
		}
		bool empty()
		{
			if (size == 0)
				return true;
			else
				return false;
		}
		void reserve(size_t x)
		{
			if (x > capacity)
			{
				capacity = x;
				void* Newdata;
				Newdata = operator new(sizeof(T) * capacity);
				for (size_t i = 0; i < size; i++)
				{
					new (static_cast<T*>(Newdata) + i) T(*(static_cast<T*>(data) + i));
				}
				data = Newdata;
				Newdata = nullptr;
			}
			if (x <= capacity)
			{
				for (size_t i = size; i >x; i--)
				{
					pop_back();
				}
			}
		}
		void shrink_to_fit()
		{
			reserve(size);
		}
		T operator[](int i) const
		{
			return *(static_cast<T*>(data) + i);
		}
		T at(size_t i)
		{
			if (i < size)
			{
				T hope = *(static_cast<T*>(data) + i);
				return *(static_cast<T*>(data) + i);
			}
			else
				throw out_of_range();
		}
		T operator[](int i)
		{
			return *(static_cast<T*>(data) + i);

		}
		T at(size_t i) const
		{
			if (i < size)
				return *(static_cast<T*>(data) + i);
			else
				throw out_of_range();
		}
		T back()
		{
			return (static_cast<T*>(data + size));
		}
		T front()
		{
			return (static_cast<T*>(data));
		}
		T back() const
		{
			return (static_cast<T*>(data + size));
		}
		T front() const
		{
			return (static_cast<T*>(data));
		}
		void push_back(T value)
		{
			if (capacity == size)
			{
				reserve(capacity * 2);
			}
			new (static_cast<T*>(data) + size) T(value);
			size= size + 1;
		}
		void pop_back()
		{
			(static_cast<T*>(data) + (size-1))->~T();
			size = size - 1;
		}
		iterator insert(const_iterator position, const T & val)
		{
			if (capacity == size)
			{
				reserve(capacity * 2);
			}

			for (size_t i = 0; i < (iterator(data + size)) - position; i++)
			{
				*(data + size - i + 1) = *(data + size - i);
			}
			*(position) = val;
		}
		iterator insert(const_iterator position, size_t n, const T & val)
		{
			if (capacity <= size + n)
				capacity = capacity + 2 * n;

			for (int i = 0; i < (iterator(data + size)) - position; i++)
			{
				*(data + size - i + n) = *(data + size - i);
			}
			for (int h = 0; h < n; h++)
			{
				*(position + h) = val;
			}
		}
		template <class InputIterator>
		iterator insert(const_iterator position, InputIterator first, InputIterator last)
		{
			int n = last - first;
			if (capacity <= size + n)
				capacity = capacity + 2 * n;

			for (int i = 0; i < (iterator(data + size)) - position; i++)
			{
				*(data + size - i + n) = *(data + size - i);
			}
			for (int h = 0; h < n; h++)
			{
				*(position + h) = *(first + h);
			}
		}
		iterator insert(const_iterator position, T && val)
		{
			if (capacity <= size)
				capacity = capacity * 2;

			for (int i = 0; i < (iterator(data + size)) - position; i++)
			{
				*(data + size - i + 1) = *(data + size - i);
			}
			*(position) = val;
		}
		iterator erase(const_iterator position)
		{
			delete* position;
			return position + 1;
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			for (int i = 0; i < last - first; i++)
			{
				delete* (first + i);
			}
			return last;
		}
		void swap(const vector & V)
		{
			vector Vcop(V);
			V.capacity = capacity;
			V.size = size;
			V.data = data;
			capacity = Vcop.capacity;
			size = Vcop.size;
			data = Vcop.data;
		}
		void clear()
		{
			for (size_t i = (size+1); i >0; i--)
			{
				pop_back();
			}
		}
		const_iterator cbegin()
		{
			return const_iterator(data);
		}
		const_iterator cend()
		{
			return const_iterator(data + size);
		}
		iterator begin()
		{
			return iterator(data);
		}
		iterator end()
		{
			return iterator(data + size);
		}
		iterator begin() const
		{
			return (iterator(data));
		}
		iterator end() const
		{
			return iterator(data + size);
		}
	};
	template<>
	class vector<bool>
	{

		using byte = unsigned char;
		size_t size;
		size_t capacity;
		size_t byte_capacity;
		byte* data;



		bool operator[](int i) const
		{
			int byte_index = i / 8;
			int bit_index = i % 8;
			return (data[byte_index] & (1 << bit_index)) >> bit_index;
		}


	};
}
int main()
{
	size_t length = 10;
	int value = 11;
	student::vector<int> V(length, value);
	int a = V.at(3);
	std::cout << "yes"<<std::endl;
	std::cout << V.at(1)<< std::endl;
    std::cout << "Hello World!\n"; 
	std::cout << V[9];
}



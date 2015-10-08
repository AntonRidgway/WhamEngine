#ifndef WE_POOLALLOC_H
#define WE_POOLALLOC_H

#include <list>

template <typename T> class PoolAllocator : public std::allocator<T> {
	private:
		static const int DEF_SIZE = 100; //Make it dumb for now.
		size_t numElements;
		T* typePool;
		bool* openSpots;
	public:
		//Allocator Typedefs and Rebind Struct
		typedef T         value_type;
		typedef size_t    size_type;
		typedef ptrdiff_t difference_type;
		typedef T*        pointer;
		typedef const T*  const_pointer;
		typedef T&        reference;
		typedef const T&  const_reference;
		template <class U> struct rebind {
			typedef PoolAllocator<U> other;
		};

		//Allocator Constructors/Deconstructor
		PoolAllocator() throw() {
			int numElements = DEF_SIZE;
			typePool = (pointer)malloc(DEF_SIZE*sizeof(T));
			openSpots = new bool[DEF_SIZE];
			for (int i = 0; i < DEF_SIZE; i++)
				openSpots[i] = true;
		}
		PoolAllocator(const allocator&) throw()
			: PoolAllocator() {}
		template <typename U> PoolAllocator(const PoolAllocator<U>&) throw()
			: PoolAllocator() {}
		~PoolAllocator() throw() {
			free(typePool);
			delete openSpots;
		}

		pointer address(reference x) const {
			for (int i = 0; i < numElements; i++)
				if (typePool[i] != NULL && typePool[i] == x)
					return &typePool[i];
			return NULL;
		}
		const_pointer address(const_reference x) const {
			for (int i = 0; i < numElements; i++)
				if (typePool[i] != NULL && typePool[i] == x)
					return &typePool[i];
			return NULL;
		}
		size_type max_size() const throw() {
			return sizeof(T);
		}
		pointer allocate(size_type n, PoolAllocator<void>::const_pointer hint = 0) {
			unsigned int i, numConsecutive;
			i = numConsecutive = 0;
			while (i < numElements && numConsecutive < n) {
				if (openSpots[i] == true) numConsecutive++;
				i++;
			}
			if (numConsecutive < n) return NULL;
			for (unsigned int j = i - numConsecutive; j < i; j++)
				openSpots[j] = false;
			return &typePool[i - numConsecutive];
		}
		void deallocate(pointer p, size_type n) {
			int i = (p - typePool) / sizeof(T);
			for (unsigned int j = i; j < n; j++)
				openSpots[j] = true;	//simply mark the spot as open
		}

		void construct(pointer p, const T& val) {
			new(static_cast<void*>(p)) T(val);
		}
		void destroy(pointer p) {
			destruct(p);
		}
		inline void destruct(char*) {}
		inline void destruct(wchar_t*) {}
		template <typename T> inline void destruct(T* t) { t->~T(); }

		bool operator ==(const_reference other) {
			return true;
		}
		bool operator !=(const_reference other) {
			return false;
		}
};

//Specialization to handle the void case.
template <> class PoolAllocator<void> {
public:
	typedef void*       pointer;
	typedef const void* const_pointer;
	typedef void value_type;
	template <class U> struct rebind {
		typedef PoolAllocator<U> other;
	};
};

#endif
#ifndef WE_DSTCKALLOC_H
#define WE_DSTCKALLOC_H

class DblStackAllocator
{
	private:
		int numBytes;
		uint8_t* stackMemory;
		uint8_t* leftPtr;
		uint8_t* rightPtr;
	public:
		DblStackAllocator(int nB)
		{
			numBytes = nB;
			stackMemory = new uint8_t[nB];
			leftPtr = stackMemory;
			rightPtr = stackMemory + nB;
		}
		~DblStackAllocator()
		{
			delete stackMemory;
		}
		bool hasSpace(int numBytes) {
			return leftPtr + numBytes < rightPtr;
		}
		uint8_t* allocateL(int numBytes)
		{
			if (hasSpace(numBytes)) {
				uint8_t* addr = leftPtr;
				leftPtr += numBytes;
				return addr;
			}
			else {
				return NULL;
			}
		}
		uint8_t* allocateR(int numBytes)
		{
			if (hasSpace(numBytes)) {
				rightPtr -= numBytes;
				return rightPtr;
			}
			else {
				return NULL;
			}
		}
		void freeToPtrL(uint8_t* ptr)
		{
			leftPtr = ptr;
		}
		void freeToPtrR(uint8_t* ptr)
		{
			rightPtr = ptr;
		}
		void clear()
		{
			leftPtr = stackMemory;
			rightPtr = stackMemory + numBytes;
		}
};

#endif
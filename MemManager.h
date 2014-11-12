/*
 * MemManager.h
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#ifndef MEMMANAGER_H_
#define MEMMANAGER_H_


#define MM_F_LOCK	1		// the memory is currently locked

class IAllocator
{
	virtual unsigned int AddString(const char *str, int len, char *&ppBuffer) = 0;
	virtual void get(int size) = 0;
};

class MemManager
{
	void dettach() const
	{
		mem = 0;
	}

public:
	MemManager();
	MemManager(void* mem, unsigned short size);
	virtual ~MemManager();

	/*!
	 *  copy constructor.
	 *  This object does not support copy, instead a move operation is done
	 */
	MemManager(const MemManager& m) :
			mem(m.mem), size(m.size), wr_pos(m.wr_pos), flag(m.flag)
	{
		m.dettach();
	}

	void AddString(const char *str, int len, char **ppBuffer);
	void Get(int size, void **ppBuffer, bool align = true);

	// get all remained free memory and lock, after that more memory can not be returned by class
	void lockRemained(void* &buffer, unsigned short &size);
	// consolidate memory, use this function after call lockRemained to specific how much data was really used
	// after call this function the memory is unlock
	void lockConsolidation(unsigned short size);

	inline void* lockAll()
	{
		flag |= MM_F_LOCK;
		wr_pos = size;
		return mem;
	}
	inline unsigned int getSize()
	{
		return size;
	}
	void Clear()
	{
		wr_pos = 0;
	}
	void Print()
	{
		//log_e("Use %d of %d ", wr_pos, size);
	}

private:

protected:
	mutable void* mem;
	unsigned short size;
	unsigned short wr_pos;
	unsigned char flag;
};

#endif /* MEMMANAGER_H_ */

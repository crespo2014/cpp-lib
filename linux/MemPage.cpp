/*
 * MemPage.cpp
 *
 *  Created on: 23 Aug 2013
 *      Author: lester
 */

#include "MemPage.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "errno.h"
#include "exception_base.h"
#include "log.h"

MemPage::MemPage()
{
	page_key = -1;
}

MemPage::~MemPage()
{
	if (mem) shmdt(mem);
}

void MemPage::Init(unsigned char count)
{
	wr_pos = 0;
	if (mem == 0)
	{
		//struct shmid_ds inf;
		// create a page if there is not

		size = sysconf(_SC_PAGESIZE) * count;

		if (page_key == -1)
		{
			if ((page_key = shmget(IPC_PRIVATE, size, IPC_CREAT | IPC_EXCL | S_IRWXU)) == -1)
			{
				throw error_maping(ERROR_INFO(), os::getLastApiError(), size);
			}
		}
		if (!mem)
		{
			if ((mem = shmat(page_key, 0, 0)) == (void*) -1)
			{
				throw error_maping(ERROR_INFO(), os::getLastApiError(), size);
			}
		}
	}
	/*
	 if (shmctl(page_key, IPC_RMID, 0) == -1)
	 {
	 log_e("ERR:%d", errno)
	 }

	 if (shmctl(page_key, IPC_STAT, &inf) == -1)
	 {
	 log_d("ERR:%d", errno)
	 }
	 */

	/*
	 if (shmctl(page_key, IPC_INFO, &inf) == -1)
	 {
	 logd("ERR:%d", errno)
	 }
	 if (shmctl(page_key, SHM_INFO, &inf) == -1)
	 {
	 logd("ERR:%d", errno);
	 }
	 */
}

void MemPage::CreateShare(key_t key, size_t size)
{
	//struct shmid_ds inf;
	if (mem == 0)
	{
		if ((page_key = shmget(key, size, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1)    //IPC_EXCL
		{
			throw error_memory(ERROR_INFO());
		}
		if ((mem = shmat(page_key, 0, 0)) == (void*) -1)
		{
			throw error_memory(ERROR_INFO());
		}
		this->size = size;
	}
	/*
	 if (shmctl(page_key, IPC_RMID, 0) == -1)
	 {
	 log_e("shmctl failed code %d", errno)
	 }

	 if (shmctl(page_key, IPC_STAT, &inf) == -1)
	 {
	 log_e("shmctl failed code %d", errno)
	 }
	 */
}

void MemPage::Open(key_t key, size_t size)
{
	//struct shmid_ds inf;
	if (mem == 0)
	{
		if ((page_key = shmget(key, size, 0)) == -1)
		{
			//if (errno == ENOENT) return ERR_NOT_FOUND;
			throw error_memory(ERROR_INFO());
		}
		if ((mem = shmat(page_key, 0, 0)) == (void*) -1)
		{
			throw error_memory(ERROR_INFO());
		}
		/*
		 if (shmctl(page_key, IPC_RMID, 0) == -1)
		 {
		 log_e("shmctl failed code %d", errno)
		 }

		 if (shmctl(page_key, IPC_STAT, &inf) == -1)
		 {
		 log_e("shmctl failed code %d", errno)
		 }
		 if (shmctl(page_key, SHM_INFO, &inf) == -1)
		 {
		 log_e("shmctl failed code %d", errno)
		 }
		 if (shmctl(page_key, SHM_INFO, &inf) == -1)
		 {
		 log_e("shmctl failed code %d", errno)
		 }
		 */
		this->size = size;
	}
}



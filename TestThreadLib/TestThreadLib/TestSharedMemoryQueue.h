#ifndef __TEST_SHARED_MEMORY_QUEUE_H__
#define __TEST_SHARED_MEMORY_QUEUE_H__


#define PROCESS_SHARED_QUEUE_PRODUCE_SIZE 20000


struct SProcessSharedQueueResult
{
	int		aiTaken[4];
	char	aszData[PROCESS_SHARED_QUEUE_PRODUCE_SIZE][257];
};


#endif // __TEST_SHARED_MEMORY_QUEUE_H__


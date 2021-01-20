#ifndef __TEST_SHARED_MEMORY_QUEUE_H__
#define __TEST_SHARED_MEMORY_QUEUE_H__


#define PROCESS_SHARED_QUEUE_PRODUCE_SIZE 20000
#define THREADED_SHARED_QUEUE_PRODUCE_SIZE 45000


struct SProcessSharedQueueResult
{
	int		aiTaken[4];
	char	aszData[PROCESS_SHARED_QUEUE_PRODUCE_SIZE][257];
};


struct SThreadedSharedQueueResult
{
	int		aiTaken[4];
	char	aszData[THREADED_SHARED_QUEUE_PRODUCE_SIZE][257];
};


#endif // __TEST_SHARED_MEMORY_QUEUE_H__


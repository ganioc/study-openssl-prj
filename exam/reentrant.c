#include "reentrant.h"

#if defined(WIN32)
#define MUTEX_TYPE HANDLE
#define MUTEX_SETUP(x) (x) = CreateMutex(NULL, FALSE, NULL)
#define MUTEX_CLEANUP(x) CloseHandle(x)
#define MUTEX_LOCK(x) WaitForSingleObject((x), INFINITE)
#define MUTEX_UNLOCK(x) ReleaseMutex(x)
#define THREAD_ID GetCurrentThreadId()
#elif defined(_POSIX_THREADS)
/* _POSIX_THREADS is normally defined in unistd.h if pthreads are available
   on your platform. */
#define MUTEX_TYPE pthread_mutex_t
#define MUTEX_SETUP(x) pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x) pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x) pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x) pthread_mutex_unlock(&(x))
#define THREAD_ID pthread_self()
#else
#error You must define mutex operations appropriate for your platform!
#endif

// Store all mutexes available to OpenSSL
static MUTEX_TYPE *mutex_buf = NULL;


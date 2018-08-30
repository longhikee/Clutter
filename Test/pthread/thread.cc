#include <iostream>
#include <pthread.h>

using namespace std;

void* start_thread(void* arg)
{
  cout << "thread" << endl;
}

int main()
{
  pthread_t thread_id;
  if (0 != pthread_create(&thread_id, NULL, start_thread, NULL))
  {
    cout << "create thread error" << endl;
    return -1;
  }

  pthread_join(thread_id, NULL);

  return 0;
}

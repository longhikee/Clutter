#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <string.h>
#include <windows.h>
using namespace std;

#define THREAD_NUM 2    //IO is sys limit resourse too many threads is useless
#define _K 1024
const char* baseName = "ostr_";
static unsigned long num = 0;
bool stop = false;

pthread_mutex_t g_mutex;

void genO(unsigned long num, char* oss)
{

  string fileName = baseName + to_string(num);
  ofstream file(fileName, ios::app | ios::binary);
  int big = 100;
  do{
  file.write(oss, 2 * 10 * _K * _K);
  file.seekp(ios::end);
  big--;
  if (stop)
  {
    cout << "create " << fileName << " stop!" << endl;
    return;
  }
  }while(big > 0);

  cout << "create " << fileName << " done .." << endl;
}

void* start_thread(void* arg)
{
  while(!stop)
  {
    pthread_mutex_lock(&g_mutex);
    unsigned long number = num++;
    pthread_mutex_unlock(&g_mutex);

    genO(number, static_cast<char*>(arg));
  }
}

void* reminder(void* arg)
{
  Sleep(1000 * 30);
  while(!stop)
  {
    cout << endl << "***************************" << endl << endl;;
    cout << "input stop to stop whole process" << endl;
    cout << endl << "****************************" << endl << endl;
    Sleep(1000 * 30);
  }
}

int main()
{
  char tmp[2 * _K] = {0};

  for (int i = 0; i < 2048; i++)
    tmp[i] = i%256 * 5 * 3;

  char* oss = new char[2 * 10 * _K * _K];
  for (unsigned i = 0; i < _K * 10 ; i++)
  {
    memcpy(oss + i * 2 * _K, tmp, 2 * _K);
  }

  pthread_t* thread[THREAD_NUM] = {0};
  pthread_mutex_init(&g_mutex, NULL);

  for (int i = 0; i < THREAD_NUM; i++)
  {
    pthread_t t;
    if (0 != pthread_create(&t, NULL, start_thread, oss))
    {
      cout << "create thread error" << endl;
      return -1;
    }
    thread[i] = &t;
  }

  pthread_t t_trace;
  if (0 != pthread_create(&t_trace, NULL, reminder, NULL))
  {
    cout << "create thread error" << endl;
    return -1;
  }

  cout << "gen files ..." << endl;
  cout << "input 'stop' to stop" << endl;
  string cmd;
  do{
  cin >> cmd;
  if ("stop" == cmd)
  {
    stop = true;
    break;
  }
  }while(true);

  cout << endl << "waiting all threads join in" << endl << endl;
  for (int i = 0; i < THREAD_NUM; i++)
  {
    pthread_join(*thread[i], NULL);
  }
//  pthread_join(t_trace, NULL);

  cout << "all work threads join in" << endl;

  pthread_mutex_destroy(&g_mutex);
  delete [] oss;
  return 0;
}

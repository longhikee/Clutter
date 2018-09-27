#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

#define UNSIGNED_MAX_LENTH 10

#define DEBUG false
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define TRACE(functionName, info) \
        if(DEBUG) cout << __FILE__ << ":" <<  __LINE__ << " " << functionName << info <<endl
#define TRACE_ERROR(info) \
        cout << __FILENAME__ << ":" <<  __LINE__ << " " << info << endl

bool charToInt(char* input, unsigned length, unsigned& seed)
{
  string functionName = "charToInt";
  if (length > 10)
  {
    TRACE_ERROR("Error: your seed is too large. It should be no more than 4294967295");
    return false;
  }
  int num[UNSIGNED_MAX_LENTH] = {0};
  unsigned long tmpSeed = 0;
  seed = 0;

  for (unsigned i = 0; i < length; i++)
  {
    num[i] = static_cast<int>(input[i]);
    if (num[i] > 57 || num[i] < 48)
    {
      TRACE_ERROR("invalid number");
      return false;
    }
  }
  for (unsigned i = 0; i < length; i++)
  {
    num[i] -= 48;
    tmpSeed += num[i] * pow(10, length - 1 - i);
  }
  if (tmpSeed > 4294967295)
  {
    TRACE_ERROR("Error: your seed is too large. It should be no more than 4294967295");
  }
  else
  {
    seed = (tmpSeed * 1021) & 0xFFFFFFFF;
  }

  TRACE(functionName, "charToInt seed: " << seed);
  return true;
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cout << "Usage" << endl;
    cout << "missing random seed." << endl;
    cout << "please supply a unsigned number as random seed" << endl;
    return -1;
  }

  if (argc > 3)
  {
    cout << "too many arguments." << endl;
  }

  unsigned int seed = 0;
  if (!charToInt(argv[1], strlen(argv[1]), seed))
  {
    return -1;
  }

  srand(seed);
  long int sig = rand();
  cout << sig << endl;

  return 0;
}

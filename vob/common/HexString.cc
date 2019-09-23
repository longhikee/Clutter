#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <string>
#include <fstream>

void HexString(const char* str, const unsigned long len, std::string& out)
{
    if (!str)
    {
        return;
    }

    out.reserve(1000);
    char row[100];

    long  i(0), j(0);
    for (i = 0; i < len;)
    {
        memset(row, ' ', 80);

        for (j = 0; j < 16 && i < len; i++, j++)
        {
            unsigned char c = 0xff & str[i];
            sprintf(&row[j * 3 + 7], "%02X ", c);   // hex equivalent
            row[j + 58] = isgraph(str[i]) ? c : '.'; // actual character
        }
        sprintf(row, "%4d:", (int)i);                  // character reached

        // sprintf appends \0, so overwrite the \0 entries ...
        row[5]     = ' ';  // ... after the row number
        row[3 * j + 7] = ' '; // ... after all hex numbers

        if (len != i)
        {
            row[58 + j]  = '\n'; // Add a new line at the end of the row
        }
        row[59 + j]  = '\0'; // End the line.
        out.append(row);
    }


}

int main()
{
  std::string out("\n");
  char c[64] = {0};
  for (unsigned i = 0; i < 64; i++)
  {
    c[i] = i;
  }

  HexString(c, 64, out);
  printf("%s", out.c_str());
  return 0;
}

#include <iostream>
#include <string>

using namespace std;
int convert_string_to_tbcd(const std::string& str, char* bcd_buffer)
{
    int str_len = str.length();
    char* p = (char*) str.c_str();
    int even_digit = 0, odd_digit = 0;

    int digit_len = str_len / 2;

    //bcd_buffer[0] = 0x91;

    for (int i = 0, j = 0; i < digit_len; i++)
    {
        odd_digit = p[j] - 0x0030;
        j++;

        even_digit = p[j] - 0x0030;
        even_digit = even_digit << 4;
        j++;

        bcd_buffer[i] = odd_digit | even_digit;
    }
    if (0 != str_len % 2)
    {
        odd_digit = p[str_len - 1] - 0x0030;
        bcd_buffer[digit_len] = odd_digit;
        bcd_buffer[digit_len] |= 0x00f0;
        return (digit_len + 1);
    }
    return (digit_len);
}


int main()
{
  string str("20801");
  char bcd[10] = {0};

  convert_string_to_tbcd(str, bcd);

  for (int i = 0; i < 10; i++)
  cout << (int)bcd[i] << " "<< endl;

}

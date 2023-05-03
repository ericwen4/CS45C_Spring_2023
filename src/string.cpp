#include <iostream>

using namespace std;

#include "string.hpp"

String::String(const char *s)
{
  int len = strlen(s);
  buf = new char[len + 1];
  strcpy(buf, s);
}

String::String(const String &s)
{
  int len = s.size();
  buf = new char[len + 1];
  strcpy(buf, s.buf);
}

String::String(String &&s)
  :buf(s.buf)
{
  s.buf = nullptr;
}

void String::swap(String &s)
{
  std::swap(this->buf, s.buf);
}

String &String::operator=(const String &s)
{
  strcpy(buf, s.buf);
  return *this;
}

String &String::operator=(String &&s)
{
  delete[] buf; buf = s.buf; s.buf = nullptr;
  return *this;
}

char &String::operator[](int index)
{
  return buf[index];
}

int String::size() const
{
  return strlen(buf);
}

String String::reverse() const
{
  int len = strlen(buf);
  char* new_buf = new char[len + 1];
  reverse_cpy(new_buf, buf);
  String dest(new_buf);
  delete[] new_buf;
  return dest;
}

int String::indexOf(char c) const
{
  const char *p = strchr(buf, c);
  return p ? p - buf : -1;
}

int String::indexOf(const String &s) const
{
  const char *p = strstr(buf, s.buf);
  if (p != nullptr)
  {
    return p - buf;
  }
  else
  {
    return -1;
  }
}

bool String::operator==(const String &s) const 
{
  return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const 
{
  return !(*this == s);
}

bool String::operator>(const String &s) const 
{
  return strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const 
{
  return (strcmp(buf, s.buf) < 0);
}

bool String::operator>=(const String &s) const 
{
  return strcmp(buf, s.buf) >= 0;
}

bool String::operator<=(const String &s) const 
{
  return strcmp(buf, s.buf) <= 0;
}

String String::operator+(const String &s) const
{
  int len = strlen(buf);
  int s_len = strlen(s.buf);
  int total_len = len + s_len;

  String result(total_len);
  strcpy(result.buf, buf);
  strcat(result.buf, s.buf);

  return result;
}

String String::operator+=(const String &s)
{
  strcat(buf, s.buf);
  return *this;
}

void String::print(std::ostream &out) const
{
  out << buf;
}

void String::read(std::istream &in)
{
    char* temp_buf = new char[1024];
    in >> temp_buf;
    int len = strlen(temp_buf);
    char* new_str = new char[len + 1];
    strcpy(new_str, temp_buf);
    new_str[len] = '\0';
    delete[] buf;
    buf = new_str;
    delete[] temp_buf;
}

String::~String()
{
  delete[] buf;
}

int String::strlen(const char *s)
{
  int i;
  int count = 0;
  for (i = 0; s[i] != '\0'; ++i)
    {
      ++count;
    }
  return count;
}

char *String::strcpy(char *dest, const char *src)
{
  int i;
  for (i = 0; src[i] != '\0'; ++i)
    {
      dest[i] = src[i];
    }
  dest[i] = '\0';
  return dest;
}

char *strdup(const char *src)
{
  int len = String::strlen(src) + 1;
  char* dup = new char[len];
  String::strcpy(dup, src);
  return dup;
}

char *String::strncpy(char *dest, const char *src, int n)
{
  int i;
  for (i = 0; (src[i] != '\0' && i < n); ++i)
    {
      dest[i] = src[i];
    }
  dest[i] = '\0';
  return dest;
}

char *String::strcat(char *dest, const char *src)
{
  if (dest == src) {
    char *temp = new char[strlen(dest) + 1];
    strcpy(temp, dest);
    strcpy(dest + strlen(dest), temp);
    delete[] temp;
  } else {
    strcpy(dest + strlen(dest), src);
  }
  return dest;
}

char *String::strncat(char *dest, const char *src, int n)
{
  if (dest == src) {
    char *temp = new char[strlen(dest) + 1];
    strcpy(temp, dest);
    strncat(dest, temp, n);
    delete[] temp;
  } else {
    int dest_len = String::strlen(dest);
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
      dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
  }
  return dest;
}
int String::strcmp(const char *left, const char *right)
{
  int len;
  int len_left = strlen(left);
  int len_right = strlen(right);
  if (len_left >= len_right)
  {
    len = len_left;
  }
  else
  {
    len = len_right;
  }
  for (int i = 0; i < len; ++i)
    {
      if (left[i] != right[i])
      {
        return left[i] - right[i];
      }
    }
  return 0;
}
int String::strncmp(const char *left, const char *right, int n)
{
  int len;
  int len_left = strlen(left);
  int len_right = strlen(right);
  if (len_left >= len_right)
  {
    len = len_left;
  }
  else
  {
    len = len_right;
  }
  for (int i = 0; (i < n && i < len); ++i)
    {
      if (left[i] != right[i])
      {
        return left[i] - right[i];
      }
    }
  return 0;
}
void String::reverse_cpy(char *dest, const char *src)
{
  int len = String::strlen(src);
  for (int i = 0; i < len; ++i)
    {
      dest[i] = src[len-i-1];
    }
  dest[len] = '\0';
}
const char *String::strchr(const char *str, char c)
{
  while (*str && *str != c) {
        str++;
    }
    if (*str == c) {
        return str;
    }
    return nullptr;
}
const char *String::strstr(const char *haystack, const char *needle)
{
  if (*needle == '\0') {
    return haystack;
  }
  int len = strlen(needle);
  const char* p = strchr(haystack, needle[0]);
  
  while (p != nullptr)
  {
    if (strncmp(p, needle, len) == 0)
      return p;
    
    p = strchr(p + 1, needle[0]);
  }
  
  return nullptr;
}

std::ostream &operator<<(std::ostream &out, const String &s)
{
  s.print(out);
  return out;
}
std::istream &operator>>(std::istream &in, String &s)
{
  s.read(in);
  return in;
}

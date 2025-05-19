#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef struct State {
  char* regs[256];
} State;
State state;
char str[1001];

int find(const char* str, const char elem) {
  int n = strlen(str);
  for (int i = 0; i < n; i++)
  {
    if (str[i] == elem) return 1;
  }
  return 0;
}

int cnt(const char* str, const char elem) {
  int n = strlen(str);
  int ch = 0;
  for (int i = 0; i < n; i++)
  {
    if (str[i] == elem) ch++;
  }
  return ch;
}

char** split_string(const char* str, char delimiter, int* num_substrings) {
  int num_delimiters = 0;
  for (const char* ptr = str; *ptr; ptr++) {
    if (*ptr == delimiter) {
      num_delimiters++;
    }
  }

  char** substrings = (char**)malloc((num_delimiters + 1) * sizeof(char*));
  if (!substrings) {
    return NULL;
  }



  int substring_index = 0;
  const char* start = str;
  const char* end = str;

  while (*end) {
    if (*end == delimiter) {
      int substring_length = end - start;
      substrings[substring_index] = (char*)malloc(substring_length + 1);
      strncpy(substrings[substring_index], start, substring_length);
      substrings[substring_index][substring_length] = '\0';
      substring_index++;
      start = end + 1;
    }
    end++;
  }

  int substring_length = end - start;
  if (*(end - 1) == '\n')
    substring_length--;
  if(*(end-2)=='\r')
    substring_length--;
  substrings[substring_index] = (char*)malloc(substring_length + 1);
  strncpy(substrings[substring_index], start, substring_length);
    substrings[substring_index][substring_length] = '\0';

  *num_substrings = num_delimiters + 1;
  return substrings;
}

void process_command(const char* plugin_name, const  char* function_name, char** args, int n) {
  char plugin_path[256];
  sprintf(plugin_path, "./%s.so", plugin_name);
  void* plugin_handle = dlopen(plugin_path,RTLD_LAZY);
  if (!plugin_handle) {
    printf("Missing plugin %s\n", plugin_name);
    return;
  }
  char full_function_name[256];
  sprintf(full_function_name, "%s_%d", function_name, n);
  void* function_ptr = dlsym(plugin_handle, full_function_name);
  if (!function_ptr) {
    printf("Missing function %s in plugin %s\n", full_function_name, plugin_name);
    dlclose(plugin_handle);
    return;
  }
  switch (n)
  {
  case 0:
    ((void(*)(State*))function_ptr)(&state);
    break;
  case 1:
    ((void(*)(State*, char*))function_ptr)(&state, args[0]);
    break;
  case 2:
    ((void(*)(State*, char*, char*))function_ptr)(&state, args[0], args[1]);
    break;
  case 3:
    ((void(*)(State*, char*, char*, char*))function_ptr)(&state, args[0], args[1], args[2]);
    break;
  default:
    break;
  }
  dlclose(plugin_handle);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  while (fgets(str, 1001, stdin))
  {
    int n = 0;
    char** params = split_string(str, ' ', &n);
    if (find(params[0], ':')) {
      int ind = 0;
      char** names = split_string(params[0], ':', &ind);
      process_command(names[0], names[1], params + 1, n - 1);
      for (int i = 0; i < ind; i++)
      {
        free(names[i]);
      }free(names);
    }
    else {
      process_command("core", params[0], params + 1, n==0?n:n-1);
    }
    for (int i = 0; i < n; i++)
    {
      free(params[i]);
    }free(params);
  }
  fclose(stdin);
  fclose(stdout);
}
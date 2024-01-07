#include <stdio.h>
#include "null0_api_filesystem.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <CART>\n", argv[0]);
    return 1;
  }

  if (!null0_init_filesystem(argv[1])) {
    return 1;
  }

  printf("Write-dir: %s\n", PHYSFS_getWriteDir());

  char* out = "a\n";

  if (!null0_file_append("log.txt", (unsigned char*)out, 2)) {
    printf("Could not append to log.\n");
    return 1;
  }

  char** i;
  printf("Here are the files:\n");
  for (i = null0_file_list("/"); *i != NULL; i++) {
    printf("  %s\n", *i);
  }

  uint32_t bytesRead = 0;
  unsigned char* bytes = null0_file_read("readme.txt", &bytesRead);
  printf("readme.txt (%d)\n%s\n", bytesRead, bytes);

  bytesRead = 0;
  unsigned char* bytesLog = null0_file_read("log.txt", &bytesRead);
  printf("log.txt (%d)\n%s\n", bytesRead, bytesLog);

  null0_unload_filesystem();
  return 0;
}
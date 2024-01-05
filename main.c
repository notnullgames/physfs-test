#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "physfs.h"
#include <libgen.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <CART>\n", argv[0]);
    return 1;
  }

  char* cartName = strtok(basename(argv[1]), ".");

  if (strlen(cartName) > 127) {
    printf("Name is too long.\n");
    return 1;
  }

  char pathname[134];
  snprintf(pathname, 134, "null0-%s", cartName);

  if (!PHYSFS_init("null0")) {
    printf("Could not init filesystem.\n");
    return 1;
  }

  const char* writeDir = PHYSFS_getPrefDir("null0", pathname);

  if (!PHYSFS_mount(argv[1], NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount filesystem.\n");
    return 1;
  }

  // put writeDir at end of search-path (so user can overwrite any files)
  if (!PHYSFS_mount(writeDir, NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount write-dir.\n");
    return 1;
  }

  if (!PHYSFS_setWriteDir(writeDir)){
    PHYSFS_deinit();
    printf("Could not set write-dir.\n");
    return 1;
  }

  printf("Write-dir: %s\n", PHYSFS_getWriteDir());

  // test writing a file
  PHYSFS_File* fw = PHYSFS_openAppend("log.txt");
  char* out = "a\n";
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(fw, out, 3);
  PHYSFS_close(fw);

  if (bytesWritten == 0) {
    printf("There was a problem writing to file.\n");
    PHYSFS_deinit();
    return 1;
  }

  // list files
  char **rc = PHYSFS_enumerateFiles("/");
  char **i;
  printf("Here are the files:\n");
  for (i = rc; *i != NULL; i++){
    printf("  %s\n", *i);
  }
  PHYSFS_freeList(rc);

  PHYSFS_deinit();
  return 0;
}
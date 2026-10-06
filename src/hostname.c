#include "fmgr.h"
#include "postgres.h"
#include "unistd.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;
PG_FUNCTION_INFO_V1(hostname);

Datum hostname(PG_FUNCTION_ARGS) {
  long max_len;
  char *server_hostname;

  max_len = sysconf(_SC_HOST_NAME_MAX);
  if (max_len <= 0) {
    max_len = 255;
  }

  server_hostname = palloc(max_len + 1);
  server_hostname[max_len] = '\0';

  if (gethostname(server_hostname, max_len) != 0) {
    PG_RETURN_NULL();
  }

  PG_RETURN_TEXT_P(cstring_to_text(server_hostname));
}

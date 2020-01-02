#include <stdio.h>
#include <string.h>
#include "common.h"

void do_client_loop(BIO *conn) {
    int err, nwritten;
    char buf[80];

    for (;;) {
      if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Break from loop fgets()\n");
        break;
      }else{
        printf("gets len:%ld\n", strlen(buf));
      }
      for (nwritten = 0; (unsigned long)nwritten < strlen(buf);
           nwritten += err) {
        err = BIO_write(conn, buf + nwritten, (strlen(buf) - nwritten));
        if (err <= 0)
          return;
        else
          printf("\nerr len sent: %d\n", err);
      }
    }
}

int main(int argc, char *argv[]) {
    BIO *conn;
    printf("argc is %d, length %ld\n", argc, sizeof(*argv));

    init_OpenSSL();

    conn = BIO_new_connect(SERVER ":" PORT);
    if (!conn) int_error("Error creating connection BIO");

    if (BIO_do_connect(conn) <= 0)
      int_error("Error connecting to remote machine");
    else
      printf("Connection succeeded\n");

    fprintf(stderr, "Connection opened\n");
    do_client_loop(conn);
    fprintf(stderr, "Connection closed\n");

    BIO_free(conn);
    return 0;
}

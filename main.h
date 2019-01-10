#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <pfring.h>

#define OPTIONS "a:hd:n:"
#define DEFAULT 1536

#define MAX_PKT_SIZE 65535
#define MIN_PKT_SIZE 64

/* Action to perform :: Arrest and Release */
enum act { ARREST, RELEASE};

/* Global variable */
extern int no;

/* Functions Declaration */
void arrest (char *, int);
void release (char *, int);

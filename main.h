#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pfring.h>

#define OPTIONS "hd:n:"
#define DEFAULT 1536

/* Global variable */
extern int no;

/* Functions Declaration */
void capture (char *);

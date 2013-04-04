#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "md5.h"
#include <math.h>

/* ------ FUNCTION DECLARATIONS ------ */
int permute(int length, const char arg[]);
void hash_test(const char arg[]);

/* 
   The main function prompts the user to enter a 32 character long MD5 hash,
   then generates permutations of a set of characters starting with a
   length of 1, and getting progressively longer as all premutations for
   a given length are created. An error message will be printed if
   a string of invalid length (not 32 chars) is entered. 
*/
int main(void) {
  int length = 1;
  char input_hash[33];
  
  printf("Enter the MD5 hash to decrypt: ");
  scanf("%s", input_hash);

  if (strlen(input_hash) == 32)
    /* processing will stop after length of 10 is reached, since
       computation time will be incredibly long and impractical */
    while (length <= 10 && permute(length, input_hash) == 0)
      length++;
  else
    printf("Invalid hash entered, program terminated.\n");

  /* hash_test("CRAIG"); */

  return 0;
}

/* 
   The permute function generates all permutations of a set of charachters 
   (set) of length 'length', hashes each permutation and compares it to the
   MD5 hash passed in as a parameter. Returns 1 if a match was found, 
   and 0 if not. 
*/
int permute(int length, const char arg[]) {
  int i, n, count = 1, index = 0, result = 0;
  int *a;
  char *temp;
  time_t start, stop;   /* <--  set up variables to record computation time */
  clock_t ticks;
  md5_state_t state;    /* <-- declare variables for MD5 function */
  md5_byte_t digest[16];
  char hex_output[33];
  int di;

  const char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; /* <-- this string contains all characters used in permutations */
  

  temp = malloc(sizeof(char) * (length + 1)); /* allocate space for temp */
  a = malloc(length * sizeof *a);
  n = sizeof set - 1;
    
  /* abort if memory allocation for arrays failed */
  if (!a || !temp)
    abort();
  
  /* initialize result array to all zeros */
  for (i = 0; i < length; ++i)
    a[i] = 0;
  
  time(&start); /* <-- start computation timer */

  do {
    /* print a counter that displays how many perutations have been made 
       for strings of this length */
    printf("%i -- ", count);
    count++;

    for (i = length - 1; i >= 0; --i) {
      temp[index] = set[a[i]]; /* stores next char at correct place in temp */
      index++;
    }
    
    temp[length] = '\0'; /* add null character to end of temp string */
      
    /* generate hash for current permutation */
    md5_init(&state);
    md5_append(&state, (unsigned char *)temp, strlen(temp));
    md5_finish(&state, digest);

    /* store hex digest as a char array in hex_output */
    for (di = 0; di < 16; di++)
      sprintf(hex_output + di * 2, "%02x", digest[di]);

    printf("%s", temp); /* print the current temp as plain text string */
      
    /* compare generated hash to parameter hash, stop looping if match found */
    if (strncmp(hex_output, arg, 32) == 0) {
      printf("\n\nFound: %s", temp);
      result = 1;
      break;
    }

    index = 0; /* reset index for placing new chars in temp array */
    putchar('\n'); /* print new line character */
    
    for (i = 0; i < length; ++i)
      if (++a[i] < n) 
	break; 
      else 
	a[i] = 0;
    
    ticks = clock();
  } while (i < length);

  time(&stop);
  
  /* print the computation time */
  printf("\n\n");
  printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
  printf("Computation time: %.0f seconds\n\n", difftime(stop, start));

  free(a);
  free(temp);

  return result;
}

/* This function takes a string literal as an argument and prints its
   MD5 hash. It's good for making sure everything is working right. */
void hash_test(const char temp[]){
  md5_state_t state;
  md5_byte_t digest[16];
  char hex_output[33];
  int di;

  md5_init(&state);
  md5_append(&state, (unsigned char *)temp, strlen(temp));
  md5_finish(&state, digest);

  for (di = 0; di < 16; di++)
    sprintf(hex_output + di * 2, "%02x", digest[di]);

  printf("Input:  %s\n", temp);
  printf("Result: %s\n", hex_output);
}

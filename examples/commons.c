
#include<stdio.h>
#include<string.h>

void print_str(unsigned char *s, size_t len){
/**
 * Print a charecter array in string
 * @param [in] s is the string to be printed 
 * @param [in] len is the number of character to be printed
 * 
 * @pre @a s and @b must not be NULL 
*/
  size_t i;
  printf("\n");
  for(i=0; i< len; i++)
    printf("%c", s[i]);
  printf("\n");
}


void print_hex(unsigned char *s, size_t len){
/**
 * Print a charecter array in string
 * @param [in] s is the string to be printed 
 * @param [in] len is the number of character to be printed
 * 
 * @pre @a s and @b must not be NULL 
*/
  size_t i;
  printf("\n");
  for(i=0; i< len; i++)
    printf("%02x", s[i]);
  printf("\n");
}
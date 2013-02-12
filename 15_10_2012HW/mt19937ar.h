#ifndef MT19937AR_H
#define MT19937AR_H

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);

#endif
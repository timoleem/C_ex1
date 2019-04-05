/*
Timo Leemans
10785612
*/

/* Do not edit this function, as it used in testing too
 * Add you own hash functions with different headers instead. */
unsigned long hash_too_simple(unsigned char *str) {
    
    return (unsigned long) *str;
}

/*

PSEUDO CODE (not used but planned to..) taken from wikipedia.. 

unsigned long ElfHash ( const unsigned char *s )
{
    unsigned long h = 0, high;
    while ( *s )
    {
        h = ( h << 4 ) + *s++;
        if ( high = h & 0xF0000000 )
            h ^= high >> 24;
        h &= ~high;
    }
    return h;
}

*/

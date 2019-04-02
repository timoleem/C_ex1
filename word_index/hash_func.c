
/* Do not edit this function, as it used in testing too
 * Add you own hash functions with different headers instead. */
unsigned long hash_too_simple(unsigned char *str) {
    
    return (unsigned long) *str;
}

// unsigned long hash(unsigned char *str) {
    
//     unsigned long hash = 5381;
//     int c;

//     while (c = *str++) {
//         hash = ((hash << 5) + hash) + c;
//     }

//     return hash;
// }



// unsigned

// unsigned long ElfHash ( const unsigned char *s )
// {
//     unsigned long   h = 0, high;
//     while ( *s )
//     {
//         h = ( h << 4 ) + *s++;
//         if ( high = h & 0xF0000000 )
//             h ^= high >> 24;
//         h &= ~high;
//     }
//     return h;
// }
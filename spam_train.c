#include <stdio.h>

int main(int argc, char *argv[]) {
    char str_tmp[1000000];
    FILE *pFile = NULL;

    pFile = fopen("dataset_spam_train100.csv", "r" );
    if( pFile != NULL )
    {   
        while( !feof( pFile ) ){
            fgets( str_tmp, 1024, pFile );          
            printf( "%s", str_tmp );            
        }       
    }
    fclose( pFile );
    
    return 0;
}
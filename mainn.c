#include "header.h"
#include "func.c"
#include "unit_test.c"

int main(){
        
    pthread_t reader,analyzer,printer;    
    size_check();
    size_t i=0;
    
         
     
    if(initialize()){
        
            
      for(i=0;i<5;){              
        pthread_create(&reader,NULL,&read_th,NULL);
        pthread_create(&analyzer,NULL,&analyze_th,NULL);
        pthread_create(&printer,NULL,&print_th,NULL);        
        pthread_join(reader,NULL);
        pthread_join(analyzer,NULL);
        pthread_join(printer,NULL);
        
        
              
        }
             
        free_global();   
    }
        
        
        
    
    
    
    return 0;
}

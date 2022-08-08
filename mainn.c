#include "header.h"
#include "func.c"
#include "thread_func.c"
#include "unit_test.c"

int main(){
        
    pthread_t reader,analyzer,printer;    
    size_check();
    size_t i=0,from_second=0;
    
         
     
    if(initialize()){
        
            
      for(i=0;i<5;){              
        if(from_second==1)fputs("Starting process monitoring\n",stdout);        
        pthread_create(&reader,NULL,&read_th,NULL);
        pthread_create(&analyzer,NULL,&analyze_th,NULL);
        if(from_second==2)pthread_create(&printer,NULL,&print_th,NULL);        
        pthread_join(reader,NULL);
        pthread_join(analyzer,NULL);
        if(from_second==2)pthread_join(printer,NULL);
                
        if(from_second==2){
             unit_result_test();
             printf("\n");       
        }
        else{
        from_second++;        
        }
        
              
        }
             
        free_global();   
    }
        
        
        
    
    
    
    return 0;
}

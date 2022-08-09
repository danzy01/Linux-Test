#include "header.h"


int main(){
        
    pthread_t reader,analyzer,printer;    
    size_check();
    size_t i=0,from_second=0;
    
         
    /*Funkcja initialize ma za zadanie dokonac alokacji pamieci dla globalnych wskaznikow*/
    if(initialize()){
        
       /*Petla real time*/     
      for(i=0;i<5;){
        /*Watek odpowiedzialny za wyswietlanie uruchamia sie po 2 s od startu programu*/              
        if(from_second==1)fputs("Starting process monitoring\n",stdout);        
        pthread_create(&reader,NULL,&read_th,NULL);
        pthread_create(&analyzer,NULL,&analyze_th,NULL);
        if(from_second==2)pthread_create(&printer,NULL,&print_th,NULL);        
        pthread_join(reader,NULL);
        pthread_join(analyzer,NULL);
        if(from_second==2)pthread_join(printer,NULL);
                
        if(from_second==2){
             unit_result_test(); /*test jednostkowy oparty na funkcji assert ktora wywolywana w petli sprawdza czy wartosci ktore obecnie sa wynikami, maja odzwierciedlenie w rzeczywistosci*/
             printf("\n");       
        }
        else{
        from_second++;        
        }
        
              
        }
             
        free_global(); /* uwolnienie zaalokowanej pamieci dla globalnych wskaznikow*/  
    }
        
        
        
    
    
    
    return 0;
}

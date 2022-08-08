#include "header.h"
/*Przydzielenie pamieci dla wskaznikow globalnych*/
size_t initialize(){
    size_t i=0;
    tab = (size_t **)malloc(core_amount*sizeof(size_t));    
    for(i=0;i<core_amount;i++){
        tab[i]=(size_t*)malloc(stat_fields*sizeof(size_t));    
    }
    ptab = (size_t **)malloc(core_amount*sizeof(size_t));    
    for(i=0;i<core_amount;i++){
        ptab[i]=(size_t*)malloc(stat_fields*sizeof(size_t));    
    }
    p_core_usage = (double*)malloc(core_amount*sizeof(double));
    if((tab==NULL) || (ptab==NULL) || (p_core_usage==NULL))return 0;
    else return 1;    

}
/*Dealokacja przydzielonej pamieci dla zmiennych globalnych*/
void free_global(void){
    size_t i=0;
    for(i=0;i<core_amount;i++){
        free(tab[i]);    
    }    
    free(tab);
    for(i=0;i<core_amount;i++){
        free(ptab[i]);    
    }    
    free(ptab);
    free(p_core_usage);
    
}
/* Sprawdzenie ilosci CPU w Proc/stat*/
void size_check(void){
    char buf[buf_size];    
    FILE *fp;
    size_t size=0;    
    fp=fopen("/proc/stat","r");
    if(fp){
        while(fgets(buf,buf_size,fp)){
            if(strstr(buf,"intr")!=NULL)break; /*Gdy w buforze pojawi sie wyraz intr liczenie zostaje przerwane*/
            size++;
        }
    }
    core_amount = size;
    fclose(fp);/*Zamkniecie otworzonego pliku proc/stat*/
}


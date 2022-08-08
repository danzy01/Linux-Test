#include "header.h"


void *read_th(void *arg){
    size_t i=0,j=0;
    char buf[buf_size];
    char* token;     
    FILE *fp; 
    sleep(1); 
    pthread_mutex_lock(&mutex);
        
    fp=fopen("/proc/stat","r");
    i=0;    
    while(fgets(buf,buf_size,fp) && (i<4)){
        if(strstr(buf,"intr")!=NULL)break;    
              
        token=strtok(buf," ");
        j=0   ;     
        while(token){
            if(j==0)tab[i][j]=0;
            else{          
            tab[i][j]=atol(token);
            }           
            token=strtok(NULL," ");
          j++;            
        }       
        memset(&buf[0],0,sizeof(buf));
        i++;    
    }
    fclose(fp);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void *analyze_th(void *arg){
    size_t i=0,j=0; 
    size_t Idle,PIdle,PNonIdle,PTotal,NonIdle,Total,totald,idled;   
    pthread_mutex_lock(&mutex);
        
    for(i=0;i<core_amount;i++){
        Idle = tab[i][4]+tab[i][5];
        PIdle =ptab[i][4]+ptab[i][5];
        
        NonIdle = tab[i][1]+tab[i][2]+tab[i][3]+tab[i][6]+tab[i][7]+tab[i][8];
PNonIdle = ptab[i][1]+ptab[i][2]+ptab[i][3]+ptab[i][6]+ptab[i][7]+ptab[i][8];    
        
        Total = Idle + NonIdle;
        PTotal = PIdle + PNonIdle;
        
        totald = Total - PTotal;
        idled = Idle - PIdle;
        p_core_usage[i] = (double)(totald - idled)/(double)totald*100;
        
    }
    for(i=0;i<core_amount;i++){
            for(j=0;j<stat_fields;j++){
                ptab[i][j] = tab[i][j];        
            }    
        }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *print_th(void *arg){
    size_t i=0;   
    pthread_mutex_lock(&mutex);
    for(i=0;i<core_amount;i++){
        if(i==0){        
            printf("Total: %lf",p_core_usage[i]);
            fputs("%\n",stdout);    
        }
        else{
            printf("cpu%ld: %lf",i-1,p_core_usage[i]);
            fputs("%\n",stdout);
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

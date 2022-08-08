#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#define buf_size 256
#define stat_fields 11
pthread_mutex_t mutex;
size_t a=2;
size_t b=3;
size_t core_amount=1;
size_t** tab = NULL;
size_t** ptab = NULL;
double* p_core_usage=NULL;

size_t initialize();
void free_global(void);
void *thread_func(void *arg);
void *zapis(void *arg);
void size_check(void);
void *read_th(void *arg);
void *analyze_th(void *arg);
void *print_th(void *arg);

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
    else return -1;   

}

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

void *thread_func(void *arg){
    size_t i=0,j=0; 
    sleep(1);   
    pthread_mutex_lock(&mutex);
            
     for(i=0;i<a;i++){
        for(j=0;j<b;j++){
            printf("%ld",tab[i][j]);            
        }    
        printf("\n");    
    }    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *zapis(void *arg){
    size_t i=0,j=0;    
    pthread_mutex_lock(&mutex);
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void size_check(void){
    char buf[buf_size];    
    FILE *fp;
    size_t size=0;    
    fp=fopen("/proc/stat","r");
    if(fp){
        while(fgets(buf,buf_size,fp)){
            if(strstr(buf,"intr")!=NULL)break; 
            size++;
        }
    }
    core_amount = size;
    fclose(fp);
}
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

int main(){
        
    pthread_t reader,analyzer,printer;    
    size_check();
    size_t i=0,j=0;
    char buf[buf_size];
    char* token;     
    //FILE *fp; 
        
    //fgets(buf,buf_size,fp);
    //printf("%s",buf);    
    if(initialize()){
        
            
      for(i=0;i<5;){              
        pthread_create(&reader,NULL,&read_th,NULL);
        pthread_create(&analyzer,NULL,&analyze_th,NULL);
        pthread_create(&printer,NULL,&print_th,NULL);        
        pthread_join(reader,NULL);
        pthread_join(analyzer,NULL);
        pthread_join(printer,NULL);
        
        //printf("%lf %lf\n",p_core_usage[0],p_core_usage[1]);
              
        }
             
        free_global();   
    }
        
        
        
    
    
    //
   // 

       
    //pthread_mutex_lock(&mutex);
        
    
    
    /*
    initialize(a,b);
       
    pthread_t t1,t2;
    
    pthread_create(&t1,NULL,&zapis,NULL);
    pthread_create(&t2,NULL,&thread_func,&j);
    
    printf("MAIN\n");
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    */    
    return 0;
}

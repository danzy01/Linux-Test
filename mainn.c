#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define buf_size 512

double proc(unsigned long long int tab[11],unsigned long long int ptab[11]){
   unsigned long long int Idle,PIdle,PNonIdle,PTotal,NonIdle,Total,totald,idled;
    Idle = tab[4]+tab[5];
    PIdle =ptab[4]+ptab[5];
    
    NonIdle = tab[1]+tab[2]+tab[3]+tab[6]+tab[7]+tab[8];
    PNonIdle = ptab[1]+ptab[2]+ptab[3]+ptab[6]+ptab[7]+ptab[8];    
    
    Total = Idle + NonIdle;
    PTotal = PIdle + PNonIdle;
    
    totald = Total - PTotal;
    idled = Idle - PIdle;    
    return (double)(totald - idled)/(double)totald*100;
}

void copy(unsigned long long int tab[4][11],unsigned long long ptab[4][11]){
    unsigned long long int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<11;j++){
            ptab[i][j] = tab[i][j];        
        }    
    }
}


int main() {
   
    char buf[buf_size];
    char* token;    
    unsigned long long int tab[4][11],prev[4][11],i=0,j=0,count;
    FILE* fp;
        
 for(count=0;count<8;count++){   
    fp=fopen("/proc/stat","r");
    i=0;    
    while(fgets(buf,buf_size,fp) && (i<4)){
        if(strstr(buf,"intr")!=NULL)break;    
              
        token=strtok(buf," ");
        j=0   ;     
        while(token){
            if(j==0)tab[i][j]=0;
            else{          
            tab[i][j]=(size_t)atol(token);
            }           
            token=strtok(NULL," ");
          j++;            
        }       
        memset(&buf[0],0,sizeof(buf));
        i++;    
    }
/*    
    for(i=0;i<4;i++){
        for(j=0;j<11;j++){
        printf("%ld ",tab[i][j]);        
        }    
        printf("\n");
    }
*/
if(count>0){    
    printf("\n%.3lf ",proc(tab[0],prev[0]));
printf("\n%.3lf ",proc(tab[1],prev[1])/3);
        printf("\n%.3lf ",proc(tab[2],prev[2])/3);
printf("\n%.3lf ",proc(tab[3],prev[3])/3);
    printf("\n");     
    }    
    copy(tab,prev);
    sleep(1);
    fclose(fp);
}

    /*
    if(fp=NULL){
        printf("blad");        
        return 1;    
    }
    else{
        i=0; 
        while(fgets(buf,buf_size,fp));
        
    } 
      fclose(fp);   
    /*        
    while((fgets(buf,buf_size,fp)!=NULL) && ( i<4)){
          if(strstr(buf,"intr")!=NULL){
                break; 
            }
          else{
             token = strtok(buf," ");
            j=0;             
            while((token!=NULL)&& (j<10)){
              if(j=0) tab[i][j]=i;
              else{
                tab[i][j]= atol(token);                
                }          
                token= strtok(0," ");
                j++;
             }
                  
        }
        i++;    
        memset(&buf[0],0,sizeof(buf));
    }
}
    //printf("Hello, World!");
*/   
return 0;
}


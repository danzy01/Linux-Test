#include "header.h"

void unit_result_test(void){
    size_t i=0;    
    
    for(i=0;i<core_amount;i++){
        assert(p_core_usage[i]<=(double)100.00);
        assert(p_core_usage[i]>=(double)0);
    }
}

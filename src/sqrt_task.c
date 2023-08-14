#include "config.h"


int main(int argc, char *argv[])
{

    
    long curr_clk, last_ref_clk, start_clk, start_clk_msec;
    double curr_per;
    int util_per = atoi(argv[2]);
    double dur = atoll(argv[1])*1000*1000;
    unsigned long l = 0x3fed0169L;
    unsigned long counter_comp = 0;
    unsigned long counter_operations = 0;
    unsigned long counter_sleep = 0;
    printf("The duration is %f and the utilization percentage is %d\n",dur/1000000, util_per);

    

    FILE* state_file;   
    FILE* out;    

    out = fopen("out.txt","w");  
    fclose(out);

    char buffer_state[32];
    printf("waiting for triger... \n" );
    while(1){
        state_file = fopen("state_sqrt_task.txt","r");  
        fgets(buffer_state, sizeof(buffer_state), state_file);
        if(buffer_state[0]==(int)('p')){
                usleep(SLEEP_INTERVAL_FOR_TIMING);
        }else
            break;
        fclose(state_file);
    }
    printf("starting... \n" );
    start_clk_msec = millis();
    last_ref_clk = nanos();
    start_clk = last_ref_clk;
    while(nanos()-start_clk <= dur){
        //curr_clk = nanos();     
        for(int i=0; i<=10000; i++) sqrt(l);
        counter_operations = counter_operations + 10;
        //counter_comp = counter_comp + nanos() - curr_clk;
        curr_clk = nanos();
        curr_per = (double)(curr_clk - last_ref_clk)  / ( (double)(curr_clk - last_ref_clk) + (double)(SLEEP_INTERVAL_FOR_IDLE_TIME_INJECTION) );    
        if( curr_per*100 >= util_per){
            //curr_clk = nanos();
            usleep(SLEEP_INTERVAL_FOR_IDLE_TIME_INJECTION);   
            //counter_sleep = counter_sleep + nanos() - curr_clk;
            last_ref_clk = nanos();
        }
    }
    printf("Total %ld k squareroot operations \n", counter_operations );
    printf("%ld / %ld k squareroot operations per \n", counter_operations,(millis()-start_clk_msec));
    //printf("Total time: %f \n", (double)(counter_comp + counter_sleep)/1000000 );
    //printf("Sleep time: %f \n", (double)counter_sleep /1000000 );
    //printf("Run time: %f \n", (double)counter_comp /1000000 );
    //printf("Util: %f \n", (double)counter_comp / (double)(counter_comp + counter_sleep) );
}

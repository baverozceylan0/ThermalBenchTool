#include "config.h"

void get_util(char line[MAX_LEN], int* data){
    int user_ctr, nice_ctr, system_ctr, iowait_ctr, irq_ctr, softirq_ctr, idle_ctr;
    char *ptr;
    ptr = strtok(line, " ");
  
    ptr = strtok(NULL, " ");
    user_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    nice_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    system_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    idle_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    iowait_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    irq_ctr = atoi(ptr);

    ptr = strtok(NULL, " ");
    softirq_ctr = atoi(ptr);    
    
    data[0] = idle_ctr;
    data[1] = user_ctr + nice_ctr + system_ctr + idle_ctr + iowait_ctr + irq_ctr + softirq_ctr;

}


int main(void)
{
    
	FILE* fp;
	char dir_path[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char dir_path_temp[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char buffer[MAX_LEN];


    FILE* util_file;

	
    long curr_clk, last_ref_clk;
    fp = fopen("util_data.csv","w");
    fprintf(fp,"time,cpu_idl,cpu_tot");
    for(int i = 0; i<8 ; i++)   
        fprintf(fp,",cpu%d_idl,cpu%d_tot",i,i);
    fprintf(fp,"\n");
    fclose(fp);
    
    FILE* state_file;
    state_file = fopen("state_util_record.txt","w");
    fprintf(state_file,"r");
    fclose(state_file);
    state_file = fopen("state_util_record.txt","r");    

    char buffer_state[32];
    int temp_util_data[2];
    char buffer_util[9][MAX_LEN];
    
	while(1){
        fgets(buffer_state, sizeof(buffer_state), state_file);
        if(buffer_state[0]==(int)('r')){        
            fp = fopen("util_data.csv","a");
            curr_clk = millis();
            fprintf(fp,"%lu",curr_clk);
            //fprintf(fp,",");
            
            util_file = fopen("/proc/stat","r");

		    fgets(buffer_util[0], sizeof(buffer_util[0]), util_file);            
            buffer_util[0][strlen(buffer)-1] = '\0';
            get_util(buffer_util[0], temp_util_data);
            fprintf(fp,",%d,%d",temp_util_data[0],temp_util_data[1]);
    
            for(int i = 1; i<9 ; i++){
                fgets(buffer_util[i], sizeof(buffer_util[i]), util_file); 
                buffer_util[i][strlen(buffer)-1] = '\0';
                get_util(buffer_util[i], temp_util_data);
                fprintf(fp,",%d,%d",temp_util_data[0],temp_util_data[1]);
            }
            fprintf(fp,"\n");
            fclose(util_file); 

            fclose(fp);
            while(millis() < (curr_clk+UTIL_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);    

            //printf("time: %lu \n", millis());
        }else{
            if(buffer_state[0]==(int)('k'))   
                break;         
            while(millis() < (curr_clk+UTIL_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);    

            printf("paused \r");                            
        }
    }
    

	
    fclose(state_file);
  	return 0;
}










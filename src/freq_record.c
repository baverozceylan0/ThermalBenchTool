

#include "config.h"



int main(void)
{
    
	FILE* fp;
	char dir_path[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char dir_path_temp[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char buffer[MAX_LEN];


    FILE* sensor_files[MAX_THERMALZONE_NUMBER];


    for(int i=0;i<8;i++){
		strcpy(dir_path_temp[i],"/sys/devices/system/cpu/cpu");
        sprintf(buffer,"%d",i);
		strcat(dir_path_temp[i],buffer);
        strcat(dir_path_temp[i],"/cpufreq/scaling_cur_freq");
    }

   for(int i=0;i<8;i++) {
		sensor_files[i] = fopen(dir_path_temp[i],"r");
	    if(sensor_files[i] == NULL)
		    perror("Failed: Couldn't find the file!");
        fclose(sensor_files[i]);
    }


    long curr_clk, last_ref_clk;
    fp = fopen("freq_data.csv","w");
    fclose(fp);

    FILE* state_file;
    state_file = fopen("state_freq_record.txt","w");
    fprintf(state_file,"r");
    fclose(state_file);
    state_file = fopen("state_freq_record.txt","r");

    char buffer_state[32];
	while(1){
        fgets(buffer_state, sizeof(buffer_state), state_file);
        if(buffer_state[0]==(int)('r')){  
            fp = fopen("freq_data.csv","a");
            curr_clk = millis();            
            fprintf(fp,"%lu",curr_clk);
            fprintf(fp,",");
            for(int i=0;i<8;i++){
                sensor_files[i] = fopen(dir_path_temp[i],"r");
		        fgets(buffer, sizeof(buffer), sensor_files[i]);
                rewind(sensor_files[i]);
                buffer[strlen(buffer)-1] = '\0';
                fprintf(fp,"%s",buffer);
                if(i<7)
                    fprintf(fp,",");
                else  
                    fprintf(fp,"\n");  
                fclose(sensor_files[i]);      
            }
            fclose(fp);
            while(millis() < (curr_clk+TEMPERATURE_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);   
        }else{
            if(buffer_state[0]==(int)('k'))   
                break;         
            while(millis() < (curr_clk+FREQ_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);    

            printf("paused \r");                            
        }
    }
	
    fclose(state_file);
  	return 0;
}












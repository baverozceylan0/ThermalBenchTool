#include "config.h"



int main(void)
{
    
	FILE* fp;
	char dir_path[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char dir_path_temp[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char buffer[MAX_LEN];


    FILE* sensor_files[MAX_THERMALZONE_NUMBER];

	fp = fopen("TempSensorPaths.txt","r");
	if(fp == NULL){
		perror("Failed: Couldn't find the TempSensorPaths.txt file!");
	}

	int thermal_zone_number = 0;
	while(fgets(buffer, sizeof(buffer), fp)) {
        buffer[strlen(buffer)-1] = '\0';
		strcpy(dir_path[thermal_zone_number],buffer);	
		thermal_zone_number++;
	}

	printf("There are %d ThermalZones:\n",thermal_zone_number);
	for(int i=0;i<thermal_zone_number;i++)
		printf("%s\n",dir_path[i]);


    for(int i=0;i<thermal_zone_number;i++){
		strcpy(dir_path_temp[i],dir_path[i]);
		strcat(dir_path_temp[i],"/temp");
    }

    for(int i=0;i<thermal_zone_number;i++) {
		sensor_files[i] = fopen(dir_path_temp[i],"r");
	    if(sensor_files[i] == NULL)
		    perror("Failed: Couldn't find the file!");
        fclose(sensor_files[i]);
    }

    long curr_clk, last_ref_clk;
    fp = fopen("temp_data.csv","w");
    fclose(fp);
    //fprintf(fp,"time,sensor0,sensor1,sensor2,sensor3 \n");
    
    FILE* state_file;
    state_file = fopen("state_temperature_record.txt","w");
    fprintf(state_file,"r");
    fclose(state_file);
    state_file = fopen("state_temperature_record.txt","r");

    

    char buffer_state[32];
	while(1){
        fgets(buffer_state, sizeof(buffer_state), state_file);
        if(buffer_state[0]==(int)('r')){        
            fp = fopen("temp_data.csv","a");
            curr_clk = millis();
            fprintf(fp,"%lu",curr_clk);
            fprintf(fp,",");
            for(int i=0;i<thermal_zone_number;i++){
                sensor_files[i] = fopen(dir_path_temp[i],"r");
		        fgets(buffer, sizeof(buffer), sensor_files[i]);
                rewind(sensor_files[i]);
                buffer[strlen(buffer)-1] = '\0';
                fprintf(fp,"%s",buffer);
                if(i<thermal_zone_number-1)
                    fprintf(fp,",");
                else  
                    fprintf(fp,"\n");  
                fclose(sensor_files[i]);      
            }
            fclose(fp);
            while(millis() < (curr_clk+TEMPERATURE_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);    

            //Sprintf("time: %lu \n", millis());
        }else{
            if(buffer_state[0]==(int)('k'))   
                break;         
            while(millis() < (curr_clk+TEMPERATURE_SAMPLING_PERIOD) )
                usleep(SLEEP_INTERVAL_FOR_TIMING);    

            printf("paused \r");                            
        }
    }
    

	
    fclose(state_file);
  	return 0;
}












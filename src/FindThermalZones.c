#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(void)
{
    
	DIR* dir;
	FILE* fp;
	char zone_num[THERMALZONE_DIGIT_NUMBER];
	char dir_path[MAX_THERMALZONE_NUMBER][MAX_LEN];
	char dir_path_type[MAX_LEN];
	char buffer[MAX_LEN];
	const char* dir_path_prefix = "/sys/class/thermal/thermal_zone";


	int n=0;
	int thermal_zone_index = 0;
	do{

		sprintf(zone_num,"%d",n);
		strcpy(dir_path[thermal_zone_index],dir_path_prefix);
		strcat(dir_path[thermal_zone_index],zone_num);
	
		dir = opendir(dir_path[thermal_zone_index]);

		if(dir == NULL){
			break;
		}else{
			
			strcpy(dir_path_type,dir_path[thermal_zone_index]);
			strcat(dir_path_type,"/type");	
			fp = fopen(dir_path_type, "r");
    			if (fp == NULL) {
      				perror("Failed: Couln't open ....thermal_zone*/type file!");
      				return 1;
    			}

   			while (fgets(buffer, MAX_LEN, fp))
    			{
        			// Remove trailing newline
        			buffer[strcspn(buffer, "\n")] = 0;
        			if(buffer[0] == 'c')	
    					thermal_zone_index++;
			}
    			fclose(fp); 
		}	
		
		n++;
	} while(n<MAX_THERMALZONE_NUMBER);

	if(n>9){
		printf("Error: Too many thermalzone folders!!");
	}else{
		printf("The number of detected thermal zones: %d \n",thermal_zone_index);
	}

	if(remove("TempSensorPaths.txt") == 0)
		printf("The previous TempSensorPaths.txt file has been removed!\n");

	fp = fopen("TempSensorPaths.txt","w");
	for(int i=0;i<thermal_zone_index;i++)
		fprintf(fp,"%s\n",dir_path[i]);

	fclose(fp);
	
	printf("The new TempSensorPaths.txt file has been created!\n");

    	return 0;
}

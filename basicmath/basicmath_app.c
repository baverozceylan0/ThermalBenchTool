#include "snipmath.h"
#include <math.h>
#include "config.h"


/* The printf's may be removed to isolate just the math calculations */


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
        run();
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

int run(void)
{
  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  /* solve soem cubic functions */
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  
  /* should get 1 solution: 2.5           */
  SolveCubic(a2, b2, c2, d2, &solutions, x);  
  SolveCubic(a3, b3, c3, d3, &solutions, x);
  SolveCubic(a4, b4, c4, d4, &solutions, x);
  /* Now solve some random equations */
  for(a1=1;a1<10;a1++) {
    for(b1=10;b1>0;b1--) {
      for(c1=5;c1<15;c1+=0.5) {
	    for(d1=-1;d1>-11;d1--) {
	        SolveCubic(a1, b1, c1, d1, &solutions, x);
	    }
      }
    }
  }
  
  /* perform some integer square roots */
  for (i = 0; i < 1001; ++i)
    {
      usqrt(i, &q);
    }
  usqrt(l, &q);
 
  for (X = 0.0; X <= 360.0; X += 1.0) deg2rad(X);
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180)) deg2rad(X);  
  
  return 0;
}

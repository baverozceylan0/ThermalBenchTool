Initial=180 # 5sec from the task start
Processing=300
Cooling=180

Percentage=50

./start_recording.sh $(($Initial+$Processing+$Cooling+5)) &

sleep $Initial

echo p > basicmath/state_sqrt_task.txt
taskset -c 4 ./basicmath/basicmath_app $Processing $Percentage &
taskset -c 5 ./basicmath/basicmath_app $Processing $Percentage &
taskset -c 6 ./basicmath/basicmath_app $Processing $Percentage &
echo r > basicmath/state_sqrt_task.txt
sleep $(($Processing+$Cooling+5))

sleep 5 #Waiting for files
python3 plot_files_static.py 





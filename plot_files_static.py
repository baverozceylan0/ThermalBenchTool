# Data_plot code
from matplotlib import dates as mdate
from matplotlib import pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import time


data = pd.read_csv('temp_data.csv', names=['time','sensor0','sensor1','sensor2','sensor3' ])
data_x = data['time']
data_y0 = data['sensor0']
data_y1 = data['sensor1']
data_y2 = data['sensor2']
data_y3 = data['sensor3']

fig, axs = plt.subplots(3,figsize=(8, 6))

data_x = data['time']/1000 - data['time'][0]/1000
data_y0 = data['sensor0']/1000
data_y1 = data['sensor1']/1000
data_y2 = data['sensor2']/1000
data_y3 = data['sensor3']/1000

data_average = pd.concat((data_y0, data_y1, data_y2, data_y3), axis=1)

axs[0].plot(data_x, data_average.mean(axis=1), '-', label = 'average', linewidth=2, alpha=1)
axs[0].plot(data_x, data_y0, '--', label = 'sensor0', linewidth=2, alpha=0.3)
axs[0].plot(data_x, data_y1, '--', label = 'sensor1', linewidth=2, alpha=0.3)
axs[0].plot(data_x, data_y2, '--', label = 'sensor2', linewidth=2, alpha=0.3)
axs[0].plot(data_x, data_y3, '--', label = 'sensor3', linewidth=2, alpha=0.3)

axs[0].set_ylim([30, 80])
axs[0].legend(loc="upper right")


data = pd.read_csv('util_data.csv')
data_x = data['time']/1000 - data['time'][0]/1000

data_cpu0_tot = data['cpu0_tot']
data_cpu1_tot = data['cpu1_tot']
data_cpu2_tot = data['cpu2_tot']
data_cpu3_tot = data['cpu3_tot']

data_cpu0_idl = data['cpu0_idl']
data_cpu1_idl = data['cpu1_idl']
data_cpu2_idl = data['cpu2_idl']
data_cpu3_idl = data['cpu3_idl']

data_cpu4_tot = data['cpu4_tot']
data_cpu5_tot = data['cpu5_tot']
data_cpu6_tot = data['cpu6_tot']
data_cpu7_tot = data['cpu7_tot']

data_cpu4_idl = data['cpu4_idl']
data_cpu5_idl = data['cpu5_idl']
data_cpu6_idl = data['cpu6_idl']
data_cpu7_idl = data['cpu7_idl']


data_cpu_ltl_tot = pd.concat((data_cpu0_tot, data_cpu1_tot, data_cpu2_tot, data_cpu3_tot), axis=1).sum(axis=1)
data_cpu_ltl_idl = pd.concat((data_cpu0_idl, data_cpu1_idl, data_cpu2_idl, data_cpu3_idl), axis=1).sum(axis=1)

data_cpu_big_tot = pd.concat((data_cpu4_tot, data_cpu5_tot, data_cpu6_tot, data_cpu7_tot), axis=1).sum(axis=1)
data_cpu_big_idl = pd.concat((data_cpu4_idl, data_cpu5_idl, data_cpu6_idl, data_cpu7_idl), axis=1).sum(axis=1)


data_cpu_ltl_per = (data_cpu_ltl_tot-data_cpu_ltl_idl).diff() / data_cpu_ltl_tot.diff()
data_cpu_big_per = (data_cpu_big_tot-data_cpu_big_idl).diff() / data_cpu_big_tot.diff()


axs[1].plot(data_x[1:], data_cpu_ltl_per[1:], '-', label = 'little', linewidth=2, alpha=1)
axs[1].plot(data_x[1:], data_cpu_big_per[1:], '-', label = 'big', linewidth=2, alpha=1)
axs[1].set_ylim([0, 1.1])
axs[1].legend(loc="upper right")

data = pd.read_csv('freq_data.csv', names=['time','cpu0','cpu1','cpu2','cpu3','cpu4','cpu5','cpu6','cpu7' ])
data_x = data['time']/1000 - data['time'][0]/1000
axs[2].plot(data_x, data['cpu0']/1000, '--', label = 'cpu0', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu1']/1000, '--', label = 'cpu1', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu2']/1000, '--', label = 'cpu2', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu3']/1000, '--', label = 'cpu3', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu4']/1000, '--', label = 'cpu4', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu5']/1000, '--', label = 'cpu5', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu6']/1000, '--', label = 'cpu6', linewidth=2, alpha=0.5)
axs[2].plot(data_x, data['cpu7']/1000, '--', label = 'cpu7', linewidth=2, alpha=0.5)
#axs[2].legend(loc="upper right")
axs[2].set_ylim([0, 2200])


axs[0].grid(b=True, which='major', color='#666666', linestyle='-', alpha=0.8)
axs[0].minorticks_on()
axs[0].grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.2)
axs[1].grid(b=True, which='major', color='#666666', linestyle='-', alpha=0.8)
axs[1].minorticks_on()
axs[1].grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.2)
axs[2].grid(b=True, which='major', color='#666666', linestyle='-', alpha=0.8)
axs[2].minorticks_on()
axs[2].grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.2)


plt.show()






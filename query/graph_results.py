import json
from pprint import pprint
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
import operator
import numpy as np
with open('queryResults.txt') as data_file:
    data = json.load(data_file)


results = data['data']
graph = [ ]

for res in results:
    t_time =  float(res['time'].encode('utf-8'))
    t_results =  float(res['total_results'].encode('utf-8'))
    graph.append( (t_results, t_time) )


totals = []
times = []
#sorted_d = sorted(graph.items(), key=lambda x: x[1])

graph.sort(key = operator.itemgetter(1), reverse = True)

for data_p in graph:

    totals.append(data_p[0])
    times.append(data_p[1])



totals.reverse( )
times.reverse( )

print(totals)
print(times)
#plt.plot(totals , times )

x = totals
y = times
slope, intercept = np.polyfit(x, y, 1)

# Create a list of values in the best fit line
abline_values = [slope * i + intercept for i in x]

# Plot the best fit line over the actual values
plt.plot(x, y, '--')
plt.plot(x, abline_values, 'b')
label = 'Time = ' + str(slope) + '* #hits  + ' + str(intercept)
slope_patch = mpatches.Patch(color='red', label= label)
plt.legend(handles=[slope_patch])
plt.ylabel('Time To Get Results (seconds)')
plt.xlabel('Total Number of Hits')
plt.title('Query Speed vs Total Number of Hits')
plt.show()
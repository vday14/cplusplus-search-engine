import json
from pprint import pprint
import matplotlib.pyplot as plt
import operator
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






plt.plot(totals , times )
plt.ylabel('Time To Get Results (seconds)')
plt.xlabel('Total Number of Hits')
plt.title('Query Speed vs Total Number of Hits')
plt.show()
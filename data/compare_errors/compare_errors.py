#!/usr/bin/python3

from matplotlib import pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.ticker import StrMethodFormatter
import matplotlib
import numpy as np
import re

def overlap(read_metadata,map_region):
    region = read_metadata.split("!")[1] # This is a pattern lets say "chr1"
    X = int(read_metadata.split("!")[2])
    Y = int(read_metadata.split("!")[3])
    # Extract the co-ordinates assuming region as a pattern
    pattern = region+':\d+-\d+'
    x = re.findall(pattern,map_region)
    X_ = []
    Y_ = []
    for i in range(len(x)):    
        X_.append(int(re.findall('\d+-\d+',x[i])[0].split("-")[0]))
        Y_.append(int(re.findall('\d+-\d+',x[i])[0].split("-")[1]))
    ## Compare here
    olp = 0.0
    for i in range(len(x)):
        olp = olp + (max(0, min(Y, Y_[i]) - max(X, X_[i]))/(Y-X))
    threshold = 0.10
    if olp >= threshold:
        return True
    else:
        return False

graphs = ["1H","10H","40H","80H","95H"]
tools = ["minichain","minigraph","GraphAligner","GraphChainer"]
wrong_region = dict()
correct_region = dict()
for tool in tools:
    wrong_count = []
    wrong_path = []
    read_count = []
    for graph in graphs:
        gaf_ = tool+"/wrong_mappings_"+graph+".gaf"
        wrong_gaf = []
        with open(gaf_) as file:
            for line in file:
                wrong_gaf.append(line)
        count_ = tool+"/count_mappings_"+graph+".gaf"
        read_count_ = 0
        with open(count_) as file:
            for line in file:
                read_count_ = read_count_ + int(line)
        read_count.append(read_count_)
        count = 0
        for i in range(len(wrong_gaf)):
            read_region = wrong_gaf[i].split("\t")[1].split("!")[1]
            map_region = wrong_gaf[i].split("\t")[2]
            read_metadata = wrong_gaf[i].split("\t")[1]
            #if read_region == map_region :  # No match than wrong region
            #    count = count + 1
            if overlap(read_metadata,map_region) == True: # No overlap then wrong region else wrong path
                count = count + 1
        wrong_count.append(len(wrong_gaf))
        wrong_path.append(count)
    wrong_count = np.asarray(wrong_count,dtype=float)
    wrong_path = np.asarray(wrong_path,dtype=float)
    wrong_count = wrong_count/read_count
    wrong_path = wrong_path/read_count
    wrong_region[tool] = wrong_count*100
    correct_region[tool] = wrong_path*100

graphs_ = []
for i in range(len(tools)):
    for graph in graphs:
        graphs_.append(graph)
    graphs_.append(" ")    

X_axis = np.arange(len(graphs))
fig, ax = plt.subplots()

##################### wrong region #############
i = 0
for tool in tools:
    ax.bar(X_axis + i*len(X_axis) + i,wrong_region[tool],zorder=3,color='tab:blue')
    i = i+1
##################### correct region ###########
i = 0
for tool in tools:
    ax.bar(X_axis + i*len(X_axis) + i ,correct_region[tool],zorder=3,color='tab:orange')
    i = i+1

##################### labeles ################
blue_patch = mpatches.Patch(color='tab:blue', label='Wrong region')
orange_patch = mpatches.Patch(color='tab:orange', label='Correct region')
plt.legend(handles=[blue_patch, orange_patch])
fig.set_size_inches(12, 3, forward=True)
ax.yaxis.set_major_formatter(StrMethodFormatter(u"{x:.1f}%"))
fig.autofmt_xdate()
plt.xticks(range(len(graphs_)),graphs_)
#plt.grid(zorder=0)
plt.text(0, 3.3, 'Minichain',
        fontsize = 11, color = 'black')
plt.text(5.5, 3.3, 'Minigraph',
        fontsize = 11, color = 'black')
plt.text(10.5, 3.3, 'GraphAligner',
        fontsize = 11, color = 'black')
plt.text(16.5, 3.3, 'GraphChainer',
        fontsize = 11, color = 'black')
plt.gca().yaxis.grid(True)
plt.rc('axes', labelsize=11)
plt.rc('xtick', labelsize=11)
plt.rc('ytick', labelsize=11)
matplotlib.rc('font', size=11)
matplotlib.rc('axes', titlesize=11)
plt.xlabel('Graphs')
plt.ylabel('Incorrectly aligned reads')
plt.savefig("compare_error.pdf",bbox_inches='tight',format='pdf')

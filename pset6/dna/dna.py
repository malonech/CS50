from sys import argv
from csv import reader, DictReader

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

with open(argv[2]) as dnafile:
    dnareader = reader(dnafile)
    for row in dnafile:
        dnalist = row

with open(argv[1]) as peopledata:
    peoplereader = reader(peopledata)
    for row in peoplereader:
        dnasequence = row               # dnasequence now contains all header names as 'items'
        dnasequence.pop(0)              # .pop(0) removes the first item in dnasequence, that beeing 'name'
        break                           # we now have a list that includes all SRT sequences

dnastring = dnalist
sequences = {}                          #initializing dictionary to store our sequnces and theyre longest chain

for item in dnasequence:                #creating a dictionary to store the max number of sequnces in order
    sequences[item] = 0                 #setting eeach entry to 0 as a placeholder
    
for key in sequences:
    keylength = len(key)                # determines the length of the sequnce (key) in question
    tmp = 0                             #initializing tmp and maximum tmp variables
    tmpmax = 0
    
    for i in range(len(dnastring)):     # for each 'letter' in the dna strand
        
        tmp = 0
        
        if dnastring[i: i + keylength] == key: # if next letters equal to size of key equal our key in question
            tmp = 1;
            while dnastring[i - keylength: i] == dnastring[i: i + keylength]:   # while the current key was repeated previous
                tmp += 1                                                        #increment our tmp counter
                i += len(key)                                                          #increment i by 1
                
            if tmp > tmpmax:                                                    #updating the max sequence succesion
                tmpmax = tmp
    
    sequences[key] = tmpmax                                                     #out of loop, recording the max number of repetition for key

with open(argv[1], newline='') as peopledata:                                   #reopen our csv to compare our results with our people data
    peoplereader = DictReader(peopledata)                                       #createss a dictionary
    for person in peoplereader:                                                 #for item in dictionary
        match = 0                                                               #initializing match identifier
        
        for dnastring in sequences:                                             #for each STR name in question
            if sequences[dnastring] == int(person[dnastring]):                  #if longest str chain equals the str chain for specific personn 
                match += 1                                                      #increment the macth counter
        if match == len(sequences):                                             #if match identifier eqauls the number of STR's, we found a perfect match
            print(person['name'])                                               #print match
            exit()                                                              #exit           
    
    print("no match")                                                           #if no matches were found, print no match


        
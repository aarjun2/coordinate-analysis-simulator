
# Coordinate analysis simulator

This program takes multiple coordinates pinpointed using latitudes and longitudes as a binary data file, gets the carrier value and noise floor which are communication values used by members in the field, analyzes the data and figures out the success rate of communication within those coordinates


## Features

- File mapping for faster reading
- multi threading for faster processing
- precomputer values for faster analysis
- ability to see multiple data values throughout the process


## FAQ

#### How is user input processed and what to provide?

Data File To Analyze
Number of Trials: 10000
number of threads
Standard Deviation (SD): 5.6
Noise Floor (NF): -131
Output File

if no output file is provided, it by default creates a output.txt, if no thread number is provided GCF is computed

#### what are the two output files generated?

1. contains the trial number and the retry value percentage and the retry percentage without fail
2. the other contains the data set generated with each trial


## Optimizations

- split the records ino multiple hreads which can be controlled by the user 
- error validation to make sure the thread values are divisible by the data records if inputted by user so data can be preserved or does GCF to make the most efficent processing 
- file mapping done using HANDLE which is much faster than fstream

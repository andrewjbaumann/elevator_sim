# elevator_sim
Elevator simulator in C++
TODO: BUG FIXES
"weight" handling does not work properly 

done for hunter college's CSCI 235 class with David Guy Brizan.

Assignment text:
Task 2: Elevator
If you choose this task, you may work in teams of no more than three students who are in this section of this course. Each
person submitting for this task will receive the same grade regardless of contribution.
Your assignment is to write a C++ program to support a simulation of the effect of taking an elevator offline in a building.
The building normally has a number of working elevators. Your program must calculate the total wait time and average wait
time for the elevator's customers and determine the difference in these times depending on the number of elevators in
operation.
Your program must support the following:
1. Determine the number of elevators in operation
The normal number of elevators in operation must be determined by the reading from a property file. See below for
details of the property file. The key in the property file for the number of elevators must be “elevators” and the
value must be a positive, non-zero integer. The program must also determine the effect of running one fewer
elevator than is indicated by the configuration. The program may run the two simulations in parallel or one after the
other. In addition, each elevator has a weight limit, keyed by “weight_limit” in the property file. If the elevator's
weight limit has been exceeded, the elevator will not move between floors.
2. Generate a number elevator customers throughout the simulated day
Customers appear on a floor and indicate the direction (up or down) in which they intend on going. Each customer
must have a weight and a destination. The program must determine the customer's weight randomly, based on the
configuration values in the property file. The customer's minimum weight is indicated by the key “min_weight”
and maximum weight indicated by “max_weight”. Each customer must also have a destination – a floor in the
building other than the floor in which the customer appears. When the customer enters an elevator, the customer
must then indicate the destination floor. One customer is possibly generated each minute on each floor randomly
according to the value in the property file keyed by “customers”.
100
1000
10000
25000
50000
100000
250000
500000
750000
1000000
0
0.5
1
1.5
2
2.5
3
3.5
List
SkipList
Items in Container
Average Retrieval Time
3. Handle the elevator customer's requests
Each elevator must operate according to an algorithm. Specifically, an elevator must collect all requests by
customers in the elevator. Once the elevator begins moving in one direction (going up, for example) it must
continue in that direction until all the customers in the elevator have been delivered to their destinations. An
elevator must also offer to pick up customers on waiting on floors if its weight limit has not been exceeded. An
elevator may move between up to 10 floors per minute; however, each stop the elevator makes requires one minute.
The elevators algorithm must also operate together (i.e. in a bank), ensuring that only one elevator responds to a
customer's request. The program may elect to have only the nearest elevator respond to a customer's request.
As described above, the program must read a property file, which will indicate the various configurations required by the
program. The property file will be “#” commented and be in key = value format. In other words, each line will either be
blank, will contain a comment (starting with a “#” symbol) or will contain a pair:
key = value
The name of the property file will be supplied to the program on command line. For example, if your program is named
“a5” and the property file “a5.prop”, the following Unix command would start your program and read the property file:
a5 a5.prop
A sample property file is as follows:
# Number of elevators in the elevator bank
elevators = 5
# Number of floors serviced by the elevators
floors = 20
# Maximum weight for customers in an elevator for the elevator to operate
weight_limit = 1500
# Weights for elevator customers
min_weight = 90
max_weight = 250
# Number of customers generated per minute per floor
customers = 0.1
Run the simulation for eight (8) consecutive hours of simulated time. Output the average amount of time spent waiting on
an elevator and average amount of time in total transit time (waiting for an elevator and riding on the elevator).
Submission
Submit your source code on Blackboard. If you choose Task 2, perform one submission for your group. Submit all your
code and documentation as one “tar.gz” file. A tar file concatenates a bunch of different files (without compressing them). A
gz (gzip) file compresses a single file. You can create a tar file (named "a5.tar") in the same directory from three files
(SkipList.hpp SortedLinkedList.hpp ListTester.cpp ListTester.hpp driver.cpp) with the following command:
tar -cvf ./a5.tar SkipList.hpp SortedLinkedList.hpp ListTester.*pp driver.cpp
You can gzip the tar file above with the following command:
gzip a5.tar
This creates a file in the same directory called "a5.tar.gz", which is what you should submit on Blackboard.

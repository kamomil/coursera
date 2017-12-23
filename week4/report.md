# Simulation assignment

### Consider the tasks T1(3, 0.5), T2(4, 1.5, 3), T3(7, 1.0, 5) and the EDF scheduler. A sporadic job arrives at t=50 having the execution time of 10 and a relative deadline of 30.

Create the sporadic task in SimSo by selecting: ”generate task set” and then list of act. Dates to the release time

Use SimSo to schedule the task set and provide a report answering the following questions:

* What is the minimum/maximum/average response time of all tasks?

T1: min: 0.5, max: 1.5, avg: 0.676

T2: min: 1.5, max: 2, avg: 1.7

T3: min: 1, max: 3.5, avg: 1.967

sporadic job: min: 29, max: 29, avg: 29


* Is any task missing the deadline? Which task? Where?

No task misses the deadline

* Is the sporadic job meeting its deadline?

No

* What is the response time for the sporadic job?

29 ms


### Consider the tasks T1(3, 0.5), T2(4, 1.5, 3), T3(7, 1.0, 5) and the RM scheduler. A sporadic job arrives at t=50 having the execution time of 10 and a relative deadline of 30.

Create the sporadic task in SimSo by selecting: ”generate task set” and then list of act. Dates to the release time

Use SimSo to schedule the task set and provide a report answering the following questions:

* What is the minimum/maximum/average response time of all tasks?

T1: min: 0.5, max: 0.5, avg: 0.5 

T2: min: 1.5, max: 2, avg: 1.84

T3: min: 1, max: 3, avg: 1.9


* Is any task missing the deadline? Which task? Where?

The sporadic job.

* Is the sporadic job meeting its deadline?

Yes

* What is the response time for the sporadic job?

Since it's not accepted at all, it has no response time.

* Which scheduler is better is better in this example; EDF or RM?

Since the RM is not feasible, the EDF is better.

# Programming assignment

The following questions should be solved with programming and the questions should be answered in a report:

* Is the system fast enough to handle all aperiodic tasks? Why?

No, once a certain aperiodic task finishes it deletes the task currently assigned to `aperiodic_handle` which is the last aperiodic task created.

* If not, solve this problem without alter the functionality of any task

My solution was to set the `aperiodic_handle` variable to the current running task pxCurrentTCB in the macro `traceTASK_SWITCHED_IN`

* What is the response time of the aperiodic task?

task 1:  963817 ms          
taks 2:  1072289 ms
taks 3:  1053179 ms
taks 4:  1083579 ms
taks 5:  1102515 ms
taks 6:  1107074 ms
taks 7:  1075665 ms
taks 8:  1097103 ms
taks 9:  1084937 ms
taks 10: 1053580 ms


* Provide a screenshot of the running system


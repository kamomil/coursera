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
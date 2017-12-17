## Theory assignment

* T1(15, 1, 14) T2(20, 2, 26) T3(22, 3):

```
$ python3 largest_frame.py '15,1,14' '20,2,26' '22,3'
H = 660
next 660 dividor f: 22
task=(15,1,14)
2*22 - gcd(15,22) = 43 > 14: try next f


next 660 dividor f: 20
task=(15,1,14)
2*20 - gcd(15,20) = 35 > 14: try next f


next 660 dividor f: 15
task=(15,1,14)
2*15 - gcd(15,15) = 15 > 14: try next f


next 660 dividor f: 12
task=(15,1,14)
2*12 - gcd(15,12) = 21 > 14: try next f


next 660 dividor f: 11
task=(15,1,14)
2*11 - gcd(15,11) = 21 > 14: try next f


next 660 dividor f: 10
task=(15,1,14)
2*10 - gcd(15,10) = 15 > 14: try next f


next 660 dividor f: 6
task=(15,1,14)
task=(20,2,26)
task=(22,3,22)
f=6 solves requirement 2
```

* T1(4, 1) T2(5, 2, 7) T3(20, 5)

```
$ python3 largest_frame.py '4,1' '5,2,7' '20,5'
H = 20
next 20 dividor f: 20
task=(4,1,4)
2*20 - gcd(4,20) = 36 > 4: try next f


next 20 dividor f: 10
task=(4,1,4)
2*10 - gcd(4,10) = 18 > 4: try next f


next 20 dividor f: 5
task=(4,1,4)
2*5 - gcd(4,5) = 9 > 4: try next f


next 20 dividor f: 4
task=(4,1,4)
task=(5,2,7)
task=(20,5,20)
f=4 solves requirement 2
```

* T1(5, 0.1) T2(7, 1) T3(12, 6) T4(45, 9)

```
$ python3 largest_frame.py '5,0.1' '7,1' '12,6' '45,9'
H = 1260
next 1260 dividor f: 45
task=(5,0,5)
2*45 - gcd(5,45) = 85 > 5: try next f


next 1260 dividor f: 42
task=(5,0,5)
2*42 - gcd(5,42) = 83 > 5: try next f


next 1260 dividor f: 36
task=(5,0,5)
2*36 - gcd(5,36) = 71 > 5: try next f


next 1260 dividor f: 35
task=(5,0,5)
2*35 - gcd(5,35) = 65 > 5: try next f


next 1260 dividor f: 30
task=(5,0,5)
2*30 - gcd(5,30) = 55 > 5: try next f


next 1260 dividor f: 28
task=(5,0,5)
2*28 - gcd(5,28) = 55 > 5: try next f


next 1260 dividor f: 21
task=(5,0,5)
2*21 - gcd(5,21) = 41 > 5: try next f


next 1260 dividor f: 20
task=(5,0,5)
2*20 - gcd(5,20) = 35 > 5: try next f


next 1260 dividor f: 18
task=(5,0,5)
2*18 - gcd(5,18) = 35 > 5: try next f


next 1260 dividor f: 15
task=(5,0,5)
2*15 - gcd(5,15) = 25 > 5: try next f


next 1260 dividor f: 14
task=(5,0,5)
2*14 - gcd(5,14) = 27 > 5: try next f


next 1260 dividor f: 12
task=(5,0,5)
2*12 - gcd(5,12) = 23 > 5: try next f


next 1260 dividor f: 10
task=(5,0,5)
2*10 - gcd(5,10) = 15 > 5: try next f


next 1260 dividor f: 9
task=(5,0,5)
2*9 - gcd(5,9) = 17 > 5: try next f


next 1260 dividor f: 7
task=(5,0,5)
2*7 - gcd(5,7) = 13 > 5: try next f


next 1260 dividor f: 6
task=(5,0,5)
2*6 - gcd(5,6) = 11 > 5: try next f


next 1260 dividor f: 5
task=(5,0,5)
task=(7,1,7)
2*5 - gcd(7,5) = 9 > 7: try next f


next 1260 dividor f: 4
task=(5,0,5)
2*4 - gcd(5,4) = 7 > 5: try next f


next 1260 dividor f: 3
task=(5,0,5)
task=(7,1,7)
task=(12,6,12)
task=(45,9,45)
f=3 solves requirement 2
```

## Simulation assignment

###  Input the tasks T1(2, 0.5), T2(3, 1.2), T3(6, 0.5) with RM scheduler

* What is the utilization factor of the system and what is the value for Urm(3) ?
Utilization =  0.5/2 + 1.2/3 + 0.5/6 = 0.25 + 0.4 + 0.0833 = 0.733
Urm(3) = 3(2^(1/3) - 1) = 0.78 

* What is the minimum/maximum/average response time of all tasks?
my calc:
t1: max: 0.5 min: 0.5 avg: 0.5
t2: max: 1.7 min: 1.7 avg: 1.7
t2: max: 2.7 min: 2.7 avg: 2.7

simso:
t1: max: 0.5 min: 0.5 avg: 0.5
t2: max: 1.7 min: 1.7 avg: 1.7
t2: max: 2.7 min: 2.7 avg: 2.7

* Is any task missing the deadline? Which task? Where?
No task is missing

* If a deadline is missed, could it be avoided by changing the scheduler?

### Input the tasks T1(2, 0.5, 1.9) T2(5, 2) T3(1, 0.1, 0.5) T4(10, 5, 20) with EDF scheduler

* What is the utilization factor of the system and what is the value for Urm(4)
U = 0.5/2 + 2/5 + 0.1/1 + 5/10 = 0.25 + 0.4 + 0.1 + 0.5 = = 1.25
urm(4) = 0.757

* What is the minimum/maximum/average response time of all tasks?
my_calc:
t1: max: 0.6 min: 0.6 avg: 0.6
t2: max: 3.6 min: 2.8 avg: 3.2
t3: max: 0.1 min: 0.1 avg: 0.1
t4: misses deadline

* Is any task missing the deadline? Which task? Where?
t4

* If a deadline is missed, could it be avoided by changing the scheduler?
no, because the utilization is larger than 1


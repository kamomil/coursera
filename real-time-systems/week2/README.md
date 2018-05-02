## why is "matrixtask" using most of the CPU utilization?
   It does a lot of cpu computation as opposed to communication task that only writes to stout.

   
## Why must the priority of "communicationtask" increase in order for it to work properly
   As long as "matrixtask" has the highest priority it will keep rescheduling if it is not blocked.
   Since "matrixtask" does a lot of cpu stuff, it takes time until it set itself to block.
   When "communicationtask" is ready to run it still have to wait to "matrixtask" to block and that might take more than 200 milisec.
   

## What happens to the completion time of "matrixtask" when the priority of "communicationtask" is increased?
   The completion time of "matrixtask" will increase a little since uppon the next tick, it will be switched by "communicationtask" and will have to wait a little until it "communicationtask" blockes again.


## How many seconds is the period of "matrixtask"? (Hint: look at vApplicationTickHook() to measure it)
* It's about 2.472000 seconds when "matrixtask" has lower priority than "communicationtask"
* It's about 2.464000 seconds when "matrixtask" has higher priority than "communicationtask"

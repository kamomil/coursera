import sys;
from fractions import gcd

def lcm(numbers):

    if len(numbers) == 1:
        return numbers[0]
    if len(numbers) == 2:
        return (numbers[0]*numbers[1]) /  gcd (numbers[0] , numbers[1])
    return  (numbers[0]*lcm(numbers[1:])) /  gcd (numbers[0] , lcm(numbers[1:]))


def main(args):
"""
input should be a list of either triples 'preiod,execution-time,deadline' or pairs 'period,execution-time'.
For pairs it is implied that the deadline equals the period.
example:
python3 largest_frame.py "15,1,14" "20,2,26" "22,3"
"""
    tasks = []
    periods = []
    for a in args[1:]:
        print(a.split(","))
        task = list(map(int,a.split(",")))
        periods.append(task[0])
        if(len(task) == 2):
            task.append(task[0])
        task = tuple(task)
        tasks.append(task)


if __name__ == "__main__":
    main(sys.argv)

import sys;
from fractions import gcd

def divisorGenerator(n,p):
    for i in range(p,1,-1):
        if n%i == 0: yield i
    yield n

def lcm(numbers):

    if len(numbers) == 1:
        return numbers[0]
    if len(numbers) == 2:
        return (numbers[0]*numbers[1]) /  gcd (numbers[0] , numbers[1])
    return  (numbers[0]*lcm(numbers[1:])) /  gcd (numbers[0] , lcm(numbers[1:]))


def main(args):
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

    H = int(lcm(periods))
    print("H = %d" % H)
    for f in divisorGenerator(H,max(periods)):
        print("next %d dividor f: %d" % (H,f))
        is_ok = True
        for t in tasks:
            print("task=(%d,%d,%d)"%(t[0],t[1],t[2]))
            x = 2*f - gcd(t[0],f)
            if(x>t[2]):
                print("2*%d - gcd(%d,%d) = %d > %d: try next f"%(f,t[0],f,x,t[2]))
                is_ok = False
                break
        if is_ok:
            print("f=%d solves requirement 2" % f)
            break
        else:
            print("\n")


if __name__ == "__main__":
    main(sys.argv)

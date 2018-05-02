"""
Partitionned EDF using PartitionedScheduler.
"""
from simso.core.Scheduler import SchedulerInfo
from simso.utils import PartitionedScheduler
from simso.schedulers import scheduler


@scheduler("simso.schedulers.P_RM")
class P_RM(PartitionedScheduler):

    def init(self):
        PartitionedScheduler.init(self, SchedulerInfo("simso.schedulers.RM_mono"))

    def packer(self):
        # First Fit

        # first element of the tuple is the utilization
        # second element of the tuple is the number of tasks in the cpu

        cpus = [[cpu, (0,0) ] for cpu in self.processors]

        print(cpus);

        # self.log_file1.write(cpus)
        for task in self.task_list:

            for c in cpus:

                data = c[1]

                n = data[1] + 1# data[1] holds the number of tasks

                Urm = n*( (2**(1/float(n)) ) - 1)

                #data[0] holds the utilization of the cpu
                if data[0] + float(task.wcet) / task.period < Urm:

                    # we assign the current task to the to the cpu with the highst utilization
                    self.affect_task_to_processor(task, c[0])

                    # Update utilization and number of tasks
                    new_data = (data[0] + float(task.wcet) / task.period , data[1]+1)
                    c[1] = new_data
                    break
        return True

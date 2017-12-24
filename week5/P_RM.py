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
        self.log_file1 = open('/home/dafna/rm_log1.txt','w')
        self.log_file2 = open('/home/dafna/rm_log2.txt','w')
        self.log_file2.write("asdasdfsdf sdfdsfsd asdfasdf asdf asdf")
        self.log_file2.close()
        fdsfs dfdsfsd

    def packer(self):
        # First Fit
        cpus = [[cpu, 0] for cpu in self.processors]
        self.log_file1.write("packer dafna");
        self.log_file1.write(cpus)
        for task in self.task_list:
            m = cpus[0][1]
            j = 0
            # Find the processor with the lowest load.
            for i, c in enumerate(cpus):
                if c[1] < m:
                    m = c[1]
                    j = i

            # Affect it to the task.
            self.affect_task_to_processor(task, cpus[j][0])

            # Update utilization.
            cpus[j][1] += float(task.wcet) / task.period
        return True

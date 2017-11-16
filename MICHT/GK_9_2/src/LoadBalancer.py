from abc import ABC
import psutil
import os


from src.Model import *


class LoadBalancer(ABC):
    determined_worker = None

    def distribute(self, load):
        if Model.is_logging():
            print("Tasks finished by workers: "+ str([x.get_tasks_finished() for x in Model.get_worker()]))
            print("Tasks received by workers: " + str([x.get_tasks_received() for x in Model.get_worker()]))
            print("CPU Usage: " + str(psutil.cpu_percent()))
            print("General RAM Usage: " + str(psutil.virtual_memory()))  # physical memory usage
            pid = os.getpid()
            py = psutil.Process(pid)
            memoryUse = py.memory_info()[0] / 2. ** 30  # memory use in GB...I think
            print('Process RAM Usage: ', memoryUse)

class LeastConnection(LoadBalancer):
    def distribute(self, load):
        super().distribute(load)
        if Model.is_logging():
            print("Current Mode: Least Connection\n")

        determined_worker = min(Model.get_worker(), key=lambda x: x.get_tasks_received())

        determined_worker.do_task(load)

class AgentBasedAdaptiveBalancing(LoadBalancer):
    def distribute(self, load):
        super().distribute(load)

        if Model.is_logging():
            print("Current Mode: Agent Based Adaptive Balancing\n")

        determined_worker = min(Model.get_worker(), key=lambda x: x.get_load())

        if determined_worker.get_load() == 101 or determined_worker.get_load() == 99:
            print("Task was dismissed because all Workers are overloaded or disabled!")
            return
        else:
            determined_worker.do_task(load)
from abc import ABC
import psutil
import os


from src.Model import *


class LoadBalancer(ABC):
    """
    Since there are no interfaces in python, the LoadBalncer is defined as an Abstract Base Class (ABC).

    The method distribute() gets predefined and also some sort of logging gets also implemented for the inhereting
    classes to use.

    Basically the load balancer decides which worker gets the task on the metrics these workers provide, depending
    on the load balancing method.
    """
    def distribute(self, load):
        """
        predefine the distribute method for the inhereting classes
        :param load: the load which gets processed by the worker
        :return: None
        """
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
    """
    This load balancing method decides which worker to forward the task depending on the amount of tasks this worker
    has already received
    """
    def distribute(self, load):
        super().distribute(load)
        if Model.is_logging():
            # log the current load balancing method
            print("Current Mode: Least Connection\n")

        # determine the the worker which has the lowest amount of tasks received
        determined_worker = min(Model.get_worker(), key=lambda x: x.get_tasks_received())

        determined_worker.do_task(load)

class AgentBasedAdaptiveBalancing(LoadBalancer):
    """
    This load balancing method decides which worker to forward the task depending on the load this worker provides
    """
    def distribute(self, load):
        super().distribute(load)

        # log the current load balancing method
        if Model.is_logging():
            print("Current Mode: Agent Based Adaptive Balancing\n")

        # determine the worker which hsa the lowest load
        determined_worker = min(Model.get_worker(), key=lambda x: x.get_load())

        # if the determined worker has a load of 101 or 99 it means that all workers are either overloaded
        # or disabled
        if determined_worker.get_load() == 101 or determined_worker.get_load() == 99:
            print("Task was dismissed because all Workers are overloaded or disabled!")
            return
        else:
            determined_worker.do_task(load)
import sys
import threading
import time

from src.LoadBalancer import *
from src.Worker import *

from src.Model import *


def find_worker(id):
    """
    static method which returns a worker object which gets found by the identifier
    :param id: the unique identifier by which the worker gets found
    :return: a worker object
    """
    worker = None
    for w in Model.get_worker():
        if w.get_id() == id:
            return w
    if worker == None:
        print("This worker doesn't exist, please choose another one!")

class Controller():
    """
    The controller handles the instances of the classes the user input.
    """
    def __init__(self):
        # at the beginning 10 workers get added
        for i in range(0,10):
            self.add_worker()

        # start the TaskDispatcher thread
        self.td = TaskDispatcher()
        self.td.start()

    def add_worker(self):
        """
        a worker instance gets created, started and added to the list in the model
        :return: None
        """
        w = Worker(Model.get_last_id()+1)
        w.start()
        Model.add_worker(w)
        print("The worker %d has been aded" % (w.get_id()))


    def print_worker_information(self, id):
        """
        prints the information of a certain worker
        :param id: the unique identifier of the worker whose information gets printed
        :return: None
        """
        # find the worker by the unique identifier
        worker = find_worker(id)

        if worker == None:
            return


        # print the amount of finished tasks, the remaining tasks, the status/load and the time needed for the last task
        print("Information of Worker %d\n"
              "---------------------------\n"
              "Finished tasks: %d\n"
              "Remaining tasks: %d\n"
              "Status: %s\n"
              "Time needed for last task: %s\n"
              "---------------------------\n" %
              (worker.get_id(), worker.get_tasks_finished(), worker.get_tasks_remaining(), worker.get_load() , str(worker.get_time_last_task())))

    def print_all_workers(self):
        """
        print the information of all workers
        :return: None
        """
        for w in Model.get_worker():
            self.print_worker_information(w.get_id())

    def delete_worker(self, id):
        """
        delete a certain worker
        :param id: the unique identifier of the worker who gets deleted
        :return: None
        """
        worker = find_worker(id)
        if worker == None:
            return

        Model.delete_worker(worker)
        print("Worker %d has been deleted" % worker.id)

    def set_time_interval(self, time):
        """
        delegate the parameter to the function of the TaskDispatcher since the time-interval is defined there
        :param time: the amount of time inbetween each dispatch of a task
        :return: None
        """
        self.td.set_time_interval(time)

    def disable_enable_worker(self, id):
        """
        disable or enable a worker, depening on whether the certain worker is already enabled or disabled
        :param id: the unique identfier of the worker which gets enabled or disabled
        :return:
        """
        worker = find_worker(id)
        if worker == None:
            return

        if worker.get_disabled():
            worker.enable()
        else:
            worker.disable()

    def disable_enable_logging(self):
        """
        disable or enable logging, depending on whether logging has already been enabled or disabled
        :return: None
        """
        if Model.is_logging():
            Model.disable_logging()
        else:
            Model.enable_logging()

    def set_least_connection(self):
        """
        set the current load balancing method to LeastConnection
        :return: None
        """
        self.td.set_load_balancer(LeastConnection())

    def set_agent_based(self):
        """
        set the current load balancing method AgentBasedAdaptiveBalancing
        :return: None
        """
        self.td.set_load_balancer(AgentBasedAdaptiveBalancing())

class TaskDispatcher(threading.Thread):
    """
    The TaskDispatcher is a thread which delegates a task every x seconds to the LoadBalancer
    """
    def __init__(self):
        threading.Thread.__init__(self)
        # since it makes handling closing the application more convenient, the TaskDispatcher is a daemon thread
        self.daemon = True
        # the standard balancing method is LeastConnection
        self.lb = LeastConnection()
        # the standard time interval is 0.5
        self.time_interval = 0.5

    def run(self):
        """
        in a while true loop, call the distribute method of the unknown load balancer with the load
        the load is a number which gets incremented each time it loops
        :return: None
        """
        number = 0
        while(True):
            number += 1
            self.lb.distribute(number)
            time.sleep(self.time_interval)

    def set_time_interval(self, time):
        """
        :param time: the amount of time inbetween each dispatch of a task
        :return: None
        """
        self.time_interval = time

    def set_load_balancer(self, lb):
        """
        set the load balancer method
        :param lb: the load balancer object which gets set
        :return: None
        """
        self.lb = lb

if __name__ == '__main__':
    # start the controller
    c = Controller()

    # create a command line interface for the user to use
    while(True):
        response = input("To add a new Worker, write 'A' \n"
              "To get information of a Worker, write 'I #id' \n"
              "To delete a Worker, write 'X #id' \n"
              "To list all Worker's information, write 'S'\n"
              "To set time interval between each task dispatch, write 'T #seconds'\n"
              "To disable\enable a Worker, write 'D #id'\n"
              "To enable\disable logging, write 'L'\n"
              "To use the LeastConnection method, write 'LC'\n"
              "To use the AgentBasedAdaptiveBalancing method, write 'AB'\n"
              "To exit the program, write 'E'\n").upper()

        if response == '':
            pass
        elif response == 'A':
            c.add_worker()
        elif response[0] == 'I':
            try:
                c.print_worker_information(int(response[2:]))
            except ValueError:
                print("If you want to see information of a worker, please specify a valid id with the format 'I #id'")
        elif response[0] == 'X':
            try:
                c.delete_worker(int(response[2:]))
            except ValueError:
                print("If you want to delete a worker, please specify a valid id with the format 'D #id'")
        elif response == 'E':
            sys.exit(0)
        elif response == 'L':
            c.disable_enable_logging()
        elif response == 'S':
            c.print_all_workers()
        elif response == 'LC':
            c.set_least_connection()
        elif response == 'AB':
            c.set_agent_based()
        elif response[0] == 'T':
            try:
                c.set_time_interval(int(response[2:]))
            except ValueError:
                print("If you want to set the time interval, please specify a valid time with the format 'T #seconds'")
        elif response[0] == 'D':
            try:
                c.disable_enable_worker(int(response[2:]))
            except ValueError:
                print("If you want to disable or enable a worker, please specify a valid id with the format 'D #id'")
        else:
            print("Please give a valid command")


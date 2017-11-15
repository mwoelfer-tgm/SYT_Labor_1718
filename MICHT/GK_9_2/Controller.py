import threading
from LoadBalancer import *
from Model import *
from Worker import *
import time
import sys

class Controller(threading.Thread):
    def __init__(self):
        Thread.__init__(self)
        self.daemon = True

        for i in range(0,10):
            self.add_worker()

        self.td = TaskDispatcher()
        self.td.start()

    def add_worker(self):
        w = Worker(Model.get_last_id()+1)
        w.start()
        Model.add_worker(w)
        print("The worker %d has been aded" % (w.get_id()))


    def print_worker_information(self, id):
        worker = self.find_worker(id)


        print("Information of Worker %d\n"
              "---------------------------\n"
              "Finished tasks: %d\n"
              "Remaining tasks: %d\n"
              "Status: %s\n"
              "Time needed for last task: %s\n"
              "---------------------------\n" %
              (worker.get_id(), worker.get_tasks_finished(), worker.get_tasks_remaining(), worker.get_load() , str(worker.get_time_last_task())))

    def print_all_workers(self):
        for w in Model.get_worker():
            self.print_worker_information(w.get_id())

    def delete_worker(self, id):
        worker = self.find_worker(id)

        Model.delete_worker(worker)
        print("Worker %d has been deleted" % worker.id)

    def find_worker(self, id):
        worker = None
        for w in Model.get_worker():
            if w.get_id() == id:
                return w
        if worker == None:
            print("This worker doesn't exist, please choose another one!")
            return

    def set_time_interval(self, time):
        self.td.set_time_interval(time)

    def disable_enable_worker(self, id):
        worker = self.find_worker(id)

        if worker.get_disabled():
            worker.enable()
        else:
            worker.disable()

    def disable_enable_logging(self):
        if Model.is_logging():
            Model.disable_logging()
        else:
            Model.enable_logging()

    def set_least_connection(self):
        self.td.set_load_balancer(LeastConnection())

    def set_agent_based(self):
        self.td.set_load_balancer(AgentBasedAdaptiveBalancing())

class TaskDispatcher(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.daemon = True
        self.lb = AgentBasedAdaptiveBalancing()
        self.time_interval = 0.5

    def run(self):
        number = 0
        while(True):
            number += 1
            self.lb.distribute(number)
            time.sleep(self.time_interval)

    def set_time_interval(self, time):
        self.time_interval = time

    def set_load_balancer(self, lb):
        self.lb = lb

if __name__ == '__main__':

    c = Controller()
    c.start()

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
              "To disable\enable a Worker, write 'D #id'\n"
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
                print("If you want to set the time interval, please specify a valid time with the format 'T #seconds'")
        else:
            print("Please give a valid command")


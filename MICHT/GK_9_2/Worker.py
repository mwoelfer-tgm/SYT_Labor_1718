from threading import *
import time
import queue

class Worker(Thread):
    curr_number = 1
    desired_number = 0
    tasks_received = 0
    progress = 0
    time_last_task = 0
    tasks_finished = 0
    is_disabled = False

    def __init__(self, id):
        Thread.__init__(self)
        self.id = id
        self.daemon = True
        self.__q = queue.Queue()

    def do_task(self, number):
        self.tasks_received += 1
        self.__q.put(number)


    def run(self):
        while True:
            if not self.is_disabled:
                self.desired_number = self.__q.get()
                start_time = time.clock()
                for i in range(1, self.desired_number):
                    self.curr_number *= i
                    self.progress = i
                    time.sleep(0.1)
                self.time_last_task = time.clock() - start_time
                self.progress += 1
                self.tasks_finished += 1


    def get_result(self):
        return self.curr_number

    def get_tasks_received(self):
        return self.tasks_received

    def get_id(self):
        return self.id

    def get_load(self):
        if self.desired_number == 0:
            return 0

        load = int((self.progress / self.desired_number) * 100)
        if load == 100:
            return 0
        elif self.is_disabled:
            return 101
        elif self.__q.qsize() > 1:
            return 99
        else:
            return load

    def get_time_last_task(self):
        return self.time_last_task

    def get_tasks_finished(self):
        return self.tasks_finished

    def get_tasks_remaining(self):
        return self.__q.qsize()

    def disable(self):
        self.is_disabled = True

    def enable(self):
        self.is_disabled = False

    def get_disabled(self):
        return self.is_disabled
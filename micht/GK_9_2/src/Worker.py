from threading import *
import time
import queue

class Worker(Thread):
    """
    The worker is a thread, which puts tasks into a queue and then processes these tasks each.

    It has to provide certain statistics in order for the load balancing methods to work.
    """
    # the current number which gets the faculty value of each new task added to
    curr_number = 1
    # the desired number which gets read out of the queue and then the faculty value calculated
    desired_number = 0
    # the amount of tasks put into the queue
    tasks_received = 0
    # the progress of the faculty calculation, gets reset after each task is finished processing
    progress = 0
    # the amount of time the last task took to process
    time_last_task = 0
    # the amount of finished tasks
    tasks_finished = 0
    # whether this worker is disabled or not
    is_disabled = False

    def __init__(self, id):
        """
        :param id: the unique identifier this worker is initialized with
        """
        Thread.__init__(self)
        self.id = id
        # each worker is a daemon thread, since it makes handling closing the application more convenient
        self.daemon = True
        # the queue where the tasks get put in
        self.__q = queue.Queue()

    def do_task(self, number):
        """
        This function gets called by the load balancer methods, it increments the tasks_received member and puts
        the task into the internal queue
        :param number:
        :return: None
        """
        self.tasks_received += 1
        self.__q.put(number)


    def run(self):
        """
        The run function is a while True loop
        :return: None
        """
        while True:
            if not self.is_disabled:
                # get the number to be calculated out of the queue
                # important: if there is no item in the queue, the thread waits in this step until there is an item
                self.desired_number = self.__q.get()
                start_time = time.clock()
                # add the faculty of the task value to the curr_number member
                for i in range(1, self.desired_number):
                    self.curr_number *= i
                    self.progress = i
                    time.sleep(0.1)
                # calculate the time it took for the calculation
                self.time_last_task = time.clock() - start_time
                # since the for loop has to start at 1 to avoid multiplying by 0, 1 has to be added in order to
                # make it 100%
                self.progress += 1
                # increment the tasks_finished member
                self.tasks_finished += 1


    def get_result(self):
        """
        :return: the curr_number as an int
        """
        return self.curr_number

    def get_tasks_received(self):
        """
        :return: the amount of tasks received (=> the amount of tasks put into the queue) as an int
        """
        return self.tasks_received

    def get_id(self):
        """
        :return: the unique identifier as an int
        """
        return self.id

    def get_load(self):
        """
        The Agent Based Adaptive Balancing algorithm needs the worker to provice a numeric valuei in the range of 0 and 102.
        In this case, 0 = idle, 99 = overload, 101 = server down/administratively disabled
        :return: the amount of stress this worker is under or a status code
        """
        # avoid division by 0
        if self.desired_number == 0:
            return 0

        # calculate the percentage of load by dividing the progress by the desired_number
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
        """
        :return: the amount of time the last task took to process as a float
        """
        return self.time_last_task

    def get_tasks_finished(self):
        """
        :return: the amount of tasks finished
        """
        return self.tasks_finished

    def get_tasks_remaining(self):
        """
        :return: the amount of tasks remaining to be processed
        """
        return self.__q.qsize()

    def disable(self):
        """
        disables this worker
        :return: None
        """
        self.is_disabled = True

    def enable(self):
        """
        enables this worker
        :return: None
        """
        self.is_disabled = False

    def get_disabled(self):
        """
        :return: whether this worker is disabled or enabled as a boolean
        """
        return self.is_disabled
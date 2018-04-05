class Model:
    """
    The model holds all the relevant data. Since there are no static classes in python, the methods have to annotated
    with the @staticmethod annotation in order to access the functions without an instance.
    """
    worker_list = []
    logging = False

    @staticmethod
    def get_worker():
        """
        :return: the list of Worker threads
        """
        return Model.worker_list

    @staticmethod
    def get_last_id():
        """
        :return: the id of the last worker added to the list as an int
        """
        if len(Model.worker_list) == 0:
            return 0
        else:
            return Model.worker_list[-1].get_id()

    @staticmethod
    def add_worker(w):
        """
        :param w: the worker to be added to the worker list
        :return: None
        """
        Model.worker_list.append(w)

    @staticmethod
    def delete_worker(w):
        """
        :param w: the worker to be deleted from the worker list
        :return: None
        """
        Model.worker_list.remove(w)

    @staticmethod
    def enable_logging():
        """
        sets the logging member to True
        :return: None
        """
        Model.logging = True

    @staticmethod
    def disable_logging():
        """
        sets the logging member to False
        :return: None
        """
        Model.logging = False

    @staticmethod
    def is_logging():
        """
        :return: the logging member whether it's True or False
        """
        return Model.logging
class Model:
    worker_list = []
    logging = False

    @staticmethod
    def get_worker():
        return Model.worker_list

    @staticmethod
    def get_last_id():
        if len(Model.worker_list) == 0:
            return 0
        else:
            return Model.worker_list[-1].get_id()

    @staticmethod
    def add_worker(w):
        Model.worker_list.append(w)

    @staticmethod
    def delete_worker(w):
        Model.worker_list.remove(w)

    @staticmethod
    def enable_logging():
        Model.logging = True

    @staticmethod
    def disable_logging():
        Model.logging = False

    @staticmethod
    def is_logging():
        return Model.logging
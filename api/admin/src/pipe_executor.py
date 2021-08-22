import os


class PipeExecutor:
    def __init__(self, host_pipe: str) -> None:
        if not os.path.exists(host_pipe):
            raise ValueError("Host pipe has to be mounted to create PipeExecutor!")
        self.host_pipe = host_pipe


    def addGroup(self, group_name: str):
        os.system(f'echo "sudo groupadd {group_name}" > {self.host_pipe}')

    def getGroups(self):
        os.system(f'echo "groups" > {self.host_pipe}')

    def getUsers(self):
        os.system(f'echo "ls /home" > {self.host_pipe}')
    
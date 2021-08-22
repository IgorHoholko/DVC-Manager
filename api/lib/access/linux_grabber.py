from os import stat
from subprocess import Popen, PIPE
from typing import List, Union, Optional, Tuple


class LinuxGrabber:

    @staticmethod
    def identify(id: str) -> Optional[Tuple[str, str, str]]:
        username = id.split('-')[-1]
        if not LinuxGrabber.isUserPresented(username):
            return None
        return username, LinuxGrabber.getShadow(username), LinuxGrabber.getUserGroups(username)


    @staticmethod
    def isUserPresented(username: str) -> bool:
        try:
            users = Popen(f"ls /home",  shell=True, stdout=PIPE )
        except:
            raise RuntimeError("Failed to read /home for user verigication!")
        users = users.stdout.read().decode().strip()

        return username in users.split()
        

    @staticmethod
    def getShadow(username: str) -> str:
        try:
            shadow_entry = Popen(f"cat /etc/shadow | grep {username}",  shell=True, stdout=PIPE )
        except:
            raise RuntimeError("Failed to read /etc/shadow for user verigication!")
        shadow_entry = shadow_entry.stdout.read().decode().strip()

        return shadow_entry


    @staticmethod
    def getUserGroups(username: str) -> List[str]:

        try:
            group_entry = Popen(f"cat /etc/group | grep {username}",  shell=True, stdout=PIPE )
        except:
            raise RuntimeError("Failed to read /etc/group for user verigication!")
        group_entry = group_entry.stdout.read().decode()

        print(group_entry)
        groups = list(  map(lambda line: line.split(':')[0], group_entry)  )

        return groups


    @staticmethod
    def isUserAdmin(name: str) -> bool:
        return "root" in LinuxGrabber.getUserGroups(name)

    @staticmethod
    def isUserAdmin(groups: List[str]) -> bool:
        return "root" in groups

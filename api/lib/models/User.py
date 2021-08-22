from lib.access.linux_grabber import LinuxGrabber
from typing import List


class User:

    def __init__(self, username: str = None, hashed_password: str = None, groups: List[str] = None):
        self.username = username
        self.hashed_password = hashed_password
        self.groups = groups if groups is not None else []
                
    @property
    def rolenames(self):
        return self.groups

    @classmethod
    def identify(self, id):
        meta = LinuxGrabber.identify(id)
        return User(*meta) if meta is not None else User()

    def lookup(self):
        return self

    @property
    def identity(self):
        return f"id-{self.username}"

    @property 
    def password(self):
        return self.hashed_password

    def is_valid(self):
        return True
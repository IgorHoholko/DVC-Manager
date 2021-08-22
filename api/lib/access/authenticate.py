from subprocess import Popen, PIPE
from typing import Optional

from .linux_grabber import LinuxGrabber
from lib.models import User


def authenticate(username, password) -> Optional[User]:
    if not LinuxGrabber.isUserPresented(username):
        return None

    shadow_entry = LinuxGrabber.getShadow(username)

    _, crypto, salt, hash_true = shadow_entry.split('$')
    hash_true = hash_true.split(":")[0].strip()

    hash_ = Popen(f"openssl passwd -{crypto} -salt {salt} {password}",  shell=True, stdout=PIPE )
    hash_ = hash_.stdout.read().decode()   
    hash_ = hash_.split('$')[-1].strip()

    if hash_ != hash_true:
        return None

    groups = LinuxGrabber.getUserGroups(username)

    return User(username, shadow_entry, groups)

    


from subprocess import Popen, PIPE


class PasswordManager:

    def __init__(self, shadow: str = "/etc/shadow"):
        self.shadow = shadow

    def checkAuth(self, user: str, password: str) -> bool:
        try:
            shadow_entry = Popen(f"cat /etc/shadow | grep {user}",  shell=True, stdout=PIPE )
        except:
            raise RuntimeError("Failed to read /etc/shadow for user verigication!")
        
        shadow_entry = shadow_entry.stdout.read().decode()
        if len(shadow_entry) == 0:
            return False

        _, crypto, salt, hash_true = shadow_entry.split('$')
        hash_true = hash_true.split(":")[0].strip()

        hash_ = Popen(f"openssl passwd -{crypto} -salt {salt} {password}",  shell=True, stdout=PIPE )
        hash_ = hash_.stdout.read().decode()   
        hash_ = hash_.split('$')[-1].strip()

        return hash_ == hash_true


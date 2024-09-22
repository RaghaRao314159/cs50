class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        self._size = 0


    def __str__(self):
        return  "🍪" * self.size

    def deposit(self, n):
        self._size += n
        self.size

    def withdraw(self, n):
        self._size -= n
        self.size

    @property
    def capacity(self):
        if self._capacity < 0:
            raise ValueError("capacity should be a non-negative number")
        else:
            return self._capacity

    @property
    def size(self):
        if self._size > self.capacity:
            raise ValueError("size has exceeded capacity")
        elif self._size < 0:
            raise ValueError("cannot remove cookies as no cookies left")

        return self._size


def main():
    jar = Jar()
    print(jar.capacity)
    print(str(jar))
    jar.deposit(20)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

main()

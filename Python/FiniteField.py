class gfException(Exception):
    pass

class FiniteField:
    characteristic = 1234577
    
    def __init__(self, value=0):
        self.setValue(value)

    def getValue(self):
        return self.value

    def setValue(self, value):
        while value < 0:
            value += FiniteField.characteristic
        
        self.value = value % FiniteField.characteristic

    @staticmethod
    def getCharacteristic():
        return FiniteField.characteristic

    @staticmethod
    def gcdExtended(a, b):
        if a == 0:
            return b, 0, 1
        gcd, x1, y1 = FiniteField.gcdExtended(b % a, a)
        x = y1 - (b // a) * x1
        y = x1
        return gcd, x, y

    @staticmethod
    def findInverse(value):
        try:
            g, x, y = FiniteField.gcdExtended(value, FiniteField.characteristic)
            if g != 1:
                raise gfException("GF field exception")
            else:
                return FiniteField(x)
        except gfException as e:
            print(e)

        return FiniteField()

    def assign(self, obj):
        if isinstance(obj, FiniteField):
            return self.value == obj.value
        elif isinstance(obj, int):
            return self.value == obj
        else:
            return False

    #use >> in c style
    def __rshift__(self, in_stream):
        try:
            value = int(in_stream.readline().strip())
            self.setValue(value)
        except Exception as e:
            print(e)
        return self

    #print(object)
    def __str__(self):
        return str(self.value)
    
    def __add__(self, obj):
        return FiniteField((self.value + obj.value) % FiniteField.characteristic)

    def __sub__(self, obj):
        result = self.value - obj.value
        return FiniteField(FiniteField.characteristic + result) if result < 0 else FiniteField(result)
    
    @staticmethod
    def fastMultiplication(a, b):
        if a == 0 or b == 0:
            return 0
        elif a == 1:
            return b
        elif b == 1:
            return a

        res = FiniteField.fastMultiplication(a, b // 2)

        if b % 2 == 0:
            return (res + res) % FiniteField.characteristic
        else:
            return ((a % FiniteField.characteristic) + (res + res)) % FiniteField.characteristic

    def __mul__(self, obj):
        if isinstance(obj, FiniteField):
            res = FiniteField.fastMultiplication(self.value, obj.value)
            return FiniteField(res)
        elif isinstance(obj, int):
            res = FiniteField.fastMultiplication(self.value, obj)
            return FiniteField(res)
        else:
            return NotImplemented

    def __truediv__(self, obj):
        res = self.findInverse(obj.value)
        return self * res

    def __iadd__(self, obj):
        self.setValue((self.value + obj.value) % FiniteField.characteristic)
        return self

    def __isub__(self, obj):
        result = self.value - obj.value
        self.setValue(FiniteField.characteristic + result if result < 0 else result)
        return self

    def __imul__(self, obj):
        self = self * obj
        return self

    def __itruediv__(self, obj):
        res = self.findInverse(obj.value)
        self *= res
        return self

    def __eq__(self, other):
        if isinstance(other, FiniteField):
            return self.value == other.value
        elif isinstance(other, int):
            return self.value == other
        else:
            return NotImplemented

    def __ne__(self, other):
        if isinstance(other, FiniteField):
            return self.value != other.value
        elif isinstance(other, int):
            return self.value != other
        else:
            return NotImplemented

    def __le__(self, other):
        if isinstance(other, FiniteField):
            return self.value < other.value
        elif isinstance(other, int):
            return self.value < other
        else:
            return NotImplemented

    def __ge__(self, other):
        if isinstance(other, FiniteField):
            return self.value > other.value
        elif isinstance(other, int):
            return self.value > other
        else:
            return NotImplemented

    def __lt__(self, other):
        if isinstance(other, FiniteField):
            return self.value <= other.value
        elif isinstance(other, int):
            return self.value <= other
        else:
            return NotImplemented

    def __gt__(self, other):
        if isinstance(other, FiniteField):
            return self.value >= other.value
        elif isinstance(other, int):
            return self.value >= other
        else:
            return NotImplemented
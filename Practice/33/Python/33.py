def create(size, first, dis):
   return [first + i*dis for i in range(size)]

def sort(array):
   return sorted(array)

_print = print
def print(array):
   return _print(array)

size = int(input())
first_el = int(input())
step = int(input())

arr = create(size, first_el, step)
arr = sort(arr)
print(arr)
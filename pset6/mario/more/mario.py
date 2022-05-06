from cs50 import get_int

while True:
    print("Height:  ", end="")
    height = get_int("")
    if height > 0 and height < 9:
        break

for i in range(height):
    print(" " * (height - (i + 1)), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))
# TODO

while True:
    try:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break
    except:
        pass

for row in range(1, height + 1):
    print(" " * (height - row) + "#" * row + "  " + "#" * row)

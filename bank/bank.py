greeting = input("Greeting: ").lower()
price = 100

if greeting[0] == 'h':
    if greeting[1:5] == 'ello':
        price = 0
    else:
        price = 20

print(f"${price}")

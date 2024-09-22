# TODO


def valid(number):
    n = len(number)
    sum = 0
    for i in range(n):
        idx = n - i - 1
        if i % 2 == 0:
            sum += int(number[idx])
        else:
            temp = int(number[idx]) * 2
            for digit in str(temp):
                sum += int(digit)

    if sum % 10 == 0:
        return True

    return False


def card(number):
    n = len(number)

    if n == 15:
        # check if american express
        if number[:2] in ("34", "37"):
            output = "AMEX"
        else:
            return "INVALID"

    elif n == 13:
        # check if visa
        if number[0] == "4":
            output = "VISA"
        else:
            return "INVALID"

    elif n == 16:
        # check if visa or mastercard
        if number[0] == "4":
            output = "VISA"
        elif number[:2] in ("51", "52", "53", "54", "55"):
            output = "MASTERCARD"
        else:
            return "INVALID"
    else:
        return "INVALID"

    if not valid(number):
        output = "INVALID"

    return output


number = input("Number: ")
print(card(number))

# TODO

import re

text = input("Text: ")
sentences = text.replace("!", ".").replace("?", ".").split(".")
if len(sentences[-1]) == 0 or (len(sentences[-1]) == 1 and not sentences[-1].isalpha()):
    sentences.pop()

words = text.split(" ")

letters = 0
for char in text:
    if char.isalpha():
        letters += 1

L = 100 * letters / len(words)

S = 100 * len(sentences) / len(words)

index = round(0.0588 * L - 0.296 * S - 15.8)

if index >= 16:
    print("Grade 16+")
elif index <= 0:
    print("Before Grade 1")
else:
    print(f"Grade {index}")

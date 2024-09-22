#import dependancies
from pyfiglet import Figlet
import sys
import requests
import random

# The API endpoint
url1 = "https://github.com/pwaller/pyfiglet/tree/d78b6ab6e05bf39370a134f6847b79e28a937b2e/pyfiglet/fonts-standard"
url2 = "https://github.com/pwaller/pyfiglet/tree/d78b6ab6e05bf39370a134f6847b79e28a937b2e/pyfiglet/fonts-contrib"

# A GET request to the API
response1 = requests.get(url1)

# Print the response
response_json1 = response1.json()['payload']['tree']['items']
standard_fonts = []

for i in response_json1:
    if i['name'].endswith(".flf") or i['name'].endswith(".ttf"):
        standard_fonts.append(i['name'][:-4])

contributed_fonts = []
# A GET request to the API
response2 = requests.get(url2)

# Print the response
response_json2 = response2.json()['payload']['tree']['items']

for i in response_json2:
    if i['name'].endswith(".flf") or i['name'].endswith(".ttf"):
        contributed_fonts.append(i['name'][:-4])

argv = sys.argv

if len(argv) == 3:
    if argv[1] == "-f" or argv[1] == "--font":
        if argv[2].lower() in standard_fonts or argv[2].lower() in contributed_fonts :
            font = argv[2].lower()
        else:
            sys.exit("no such font")

    else:
        sys.exit("usage: figlet.py -f fontname")

elif len(argv) == 1:
    font = random.choice(standard_fonts)

else:
    sys.exit("usage: figlet.py -f fontname")


text = input("Input: ")
f = Figlet(font=font)
print(f.renderText(text))





'''
contributed_fonts = []
# A GET request to the API
response2 = requests.get(url2)

# Print the response
response_json2 = response2.json()['payload']['tree']['items']

for i in response_json2:
    if i['name'].endswith(".flf") or i['name'].endswith(".ttf"):
        contributed_.append(i['name'][:-4])


print(contributed_)
'''

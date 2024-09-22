import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ").strip()
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}
    for row in reader:
        new_cases[row['state']] = new_cases.get(row['state'],[])+[int(row['cases']) - previous_cases.get(row['state'],[0])[-1]]
        previous_cases[row['state']] = previous_cases.get(row['state'],[])+[int(row['cases'])]
        if len(new_cases[row['state']]) > 7:
            new_cases[row['state']].pop(0)
            previous_cases[row['state']].pop(0)
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        if len(new_cases[state]) >= 7:
            n = 7
            average = sum(new_cases[state][-7:])/7
            previous_average = sum(new_cases[state][:7])/len(new_cases[state][:7])
            percent = 100*(average - previous_average)/previous_average
            if percent < 0:
                change = "decrease"
            else:
                change = "increase"

            print(f"{state} had a {n}-day average of {round(average,2)}", end = " ")
            print(f"and a {change} of {abs(percent)}%.")


        else:
            n = len(new_cases[state])
            average = sum(new_cases[state])/n
            print(f"{state} had a {n}-day average of {round(average,2)}")

main()

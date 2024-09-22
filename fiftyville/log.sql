-- Keep a log of any SQL queries you execute as you solve the mystery

-- 1) check if this crime is recorded in the crime_scene_reports table
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street LIKE '%Humphrey%';
-- There are 2 cromes and indeed the CS50 duck theft is recorded. ,3 interviews have happened, theft happened at Humphrey Street bakery and 10:15am


-- 2) check the interview logs
SELECT * FROM interviews LIMIT 1; -- explore the type of information provided by this table
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28; -- there are 7 interviews on this day
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%'; -- exact 3 interviews obtained
-- The thief left in a car between 10:15am and 10:25am (suggests checking bakery_security_logs)
-- Before 10:15am the thief is spotted at Leggett Street ATM withdrawing money
-- Between 10:15am and 10:25am, a < 1 min call was made at bakery by the thief.
-- Earliest flight out of Fiftyville on 29 July 2021, ticket purchaced between 10:15am and 10:25am.


-- 3) check bakery_security_logs
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10; -- not sufficient, there are still 14 events
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND minute > 14 AND activity = 'exit'; -- 8 cars exited

-- 4) check atm_transactions
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw'; -- 8 such transactions
-- get the owners of these accounts
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw');

-- 5) check phone_calls table
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60; -- 9 such calls

-- 6) Invesitigate flight ticket
-- Determine the airport of departure (in Fiftyville)
SELECT * FROM airports WHERE city LIKE 'fiftyville'; -- one airport, Fiftyville Regional Airport

-- Find the earliest flight the next day that departs from fiftyville
SELECT * FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
        AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
    ORDER BY hour ASC LIMIT 1; -- find the earliest flight that departs from fiftyville

SELECT * FROM airports WHERE id in (
    SELECT destination_airport_id FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29
            AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
        ORDER BY hour ASC LIMIT 1
    ); -- find the destination (LaGuardia Airport, New York City)

-- flight passengers
SELECT passport_number FROM passengers WHERE flight_id IN
    (SELECT id FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29
            AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
        ORDER BY hour ASC LIMIT 1;)

-- 7) find the thief

--
SELECT * FROM people WHERE
    phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND
    license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND minute > 14 AND activity = 'exit') AND
    passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
        (SELECT id FROM flights
            WHERE year = 2021 AND month = 7 AND day = 29
                AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
            ORDER BY hour ASC LIMIT 1)) AND
    id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw'));
--THE THIEF IS BRUCE

-- 8) Find the accomplice

-- determine the accomplice's phone number
SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
 (
    SELECT phone_number FROM people WHERE
    phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND
    license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND minute > 14 AND activity = 'exit') AND
    passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
        (SELECT id FROM flights
            WHERE year = 2021 AND month = 7 AND day = 29
                AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
            ORDER BY hour ASC LIMIT 1)) AND
    id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw'))
 );

 -- determine the owner of this number
 SELECT * FROM people WHERE phone_number IN
  (
    SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
    (
        SELECT phone_number FROM people WHERE
        phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND
        license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND minute > 14 AND activity = 'exit') AND
        passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN
            (SELECT id FROM flights
                WHERE year = 2021 AND month = 7 AND day = 29
                    AND origin_airport_id IN (SELECT id FROM airports WHERE city LIKE 'fiftyville')
                ORDER BY hour ASC LIMIT 1)) AND
        id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw'))
    )
  );

  -- ACOMPLICE IS ROBIN






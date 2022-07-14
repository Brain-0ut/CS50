-- Keep a log of any SQL queries you execute as you solve the mystery.

select * from crime_scene_reports WHERE description LIKE '%duck%';

--/*
select name, transcript
    from interviews, crime_scene_reports
    where transcript like '%bakery%'
    and description LIKE '%duck%'
    and interviews.day = crime_scene_reports.day;
--*/

--/*
select destination_airport_id, city, day, min(hour), minute
            from airports, flights
            where airports.id = flights.origin_airport_id
            and city like '%fiftyville%'
            and day = 29
            order by hour, minute;
--*/

--/*
select city from airports
    where id IN (
        select destination_airport_id
            from airports, flights
            where airports.id = flights.origin_airport_id
            and city like '%fiftyville%'
            and day = 29
            and hour = 8
            order by hour, minute);
--*/

-- ident a license plate of a car, whom left the parking after theft
select license_plate, activity, minute from bakery_security_logs
    where day = 28
    and hour = 10
    and minute > 15
    and minute < 25
;

select transaction_type, account_number, amount from atm_transactions
    where atm_location like '%Leggett Street%'
    and day = 28
    and transaction_type is not 'deposit'
;

select name, bank_accounts.account_number, phone_number, passport_number, license_plate
    from atm_transactions, bank_accounts, people
    where atm_location like '%Leggett Street%'
    and atm_transactions.account_number = bank_accounts.account_number
    and bank_accounts.person_id = people.id
    and people.license_plate in
    (select license_plate from bakery_security_logs
    where day = 28
    and hour = 10
    and minute > 15
    and minute < 25)
    and day = 28
    and transaction_type is not 'deposit'
;

select name, passport_number, caller, receiver, day, duration from phone_calls, people
    where caller in
    (select distinct phone_number
    from atm_transactions, bank_accounts, people
    where atm_location like '%Leggett Street%'
    and atm_transactions.account_number = bank_accounts.account_number
    and bank_accounts.person_id = people.id
    and people.license_plate in
    (select license_plate from bakery_security_logs
    where day = 28
    and hour = 10
    and minute > 15
    and minute < 25)
    and day = 28
    and transaction_type is not 'deposit')
    and day = 28
    and duration < 60
    and phone_number = caller
    order by duration
    ;

select distinct name, receiver from phone_calls, people
    where receiver in
    (select receiver from phone_calls, people
    where caller in
    (select distinct phone_number
    from atm_transactions, bank_accounts, people
    where atm_location like '%Leggett Street%'
    and atm_transactions.account_number = bank_accounts.account_number
    and bank_accounts.person_id = people.id
    and people.license_plate in
    (select license_plate from bakery_security_logs
    where day = 28
    and hour = 10
    and minute > 15
    and minute < 25)
    and day = 28
    and transaction_type is not 'deposit')
    and day = 28
    and duration < 60
    and phone_number = caller)
    and phone_number = receiver
;

select distinct passengers.passport_number, name from passengers, flights, people
    where flight_id = flights.id
    and flights.id in
    (select flights.id
            from airports, flights
            where airports.id = flights.origin_airport_id
            and city like '%fiftyville%'
            and day = 29
            and hour = 8)
    and passengers.passport_number in
    (select passport_number from phone_calls, people
    where caller in
    (select distinct phone_number
    from atm_transactions, bank_accounts, people
    where atm_location like '%Leggett Street%'
    and atm_transactions.account_number = bank_accounts.account_number
    and bank_accounts.person_id = people.id
    and people.license_plate in
    (select license_plate from bakery_security_logs
    where day = 28
    and hour = 10
    and minute > 15
    and minute < 25)
    and day = 28
    and transaction_type is not 'deposit')
    and day = 28
    and duration < 60
    and phone_number = caller
    order by duration)
    and people.passport_number = passengers.passport_number
    ;
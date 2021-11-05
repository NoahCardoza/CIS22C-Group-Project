import sys
from datetime import datetime
from random import choice, randint
from uuid import uuid4

MALE_NAMES = ('Abel', 'Allen', 'Andrew', 'Bradley', 'Bram', 'Brandon', 'Christian', 'Daniel', 'David', 'Joash', 'Joel', 'Joseph', 'Justin', 'Tran', 'Matthew', 'Nigel', 'Noah', 'Ran', 'Randy', 'Runze', 'Ryan', 'Kevin')
FEMALE_NAMES = ('Cassie', 'Chanakarn',  'Eileen', 'Giovany', 'Hebai', 'Isha',  'Karen', 'Karthik',  'Kyu Beom',  'Pawandeep', 'Phat', 'Qiancheng',  'Sarina', 'Seokyoung', 'Shreeya', 'Silvia', 'Steven', 'Sumin', 'Swikar', 'Tannaz',  'Varun')

FIRST_NAME_CHOICES = {
    'M': MALE_NAMES,
    'F': FEMALE_NAMES,
    'O': (*MALE_NAMES, *FEMALE_NAMES),
}

LAST_NAME_CHOICES = ('Adhikari', 'Anvari', 'Avila', 'Ayyappan', 'Bar-Niv', 'Boonmuen', 'Calleja', 'Campos', 'Cardoza', 'Chun', 'Chung', 'Darshani', 'David', 'Erlund', 'Hashemi', 'He', 'Ho', 'Ho', 'Hong', 'Hui', 'Huynh', 'Karki', 'Kim', 'Lee', 'Lian', 'Nandakumar', 'Oskuie', 'Pei', 'Pham', 'Rabia', 'Reich', 'Rothman', 'Salas', 'Say', 'Seno', 'Singh', 'Taylor', 'Tran', 'Tu', 'Vinh', 'Vuong')

STATUS_ENUM = ('S', 'R', 'D')
COUNTRY_CODE_ENUM = ('US', 'MX', 'CA', 'FR', 'EN', 'IN', 'CN', 'ES', 'DE', 'NG')
GENDER_ENUM = ('M', 'F', 'O')



def random_date():
    return int(datetime(
        year=randint(2020, 2021),
        month=randint(1, 12),
        day=randint(1, 28),
        hour=randint(0, 23),
        minute=randint(0, 59),
        second=randint(0, 59),
    ).timestamp())


def random_name(gender):
    return f"{choice(FIRST_NAME_CHOICES[gender])} {choice(LAST_NAME_CHOICES)}"


def patiant():
    gender = choice(GENDER_ENUM)
    return [
        str(uuid4()),               # id
        random_name(gender),        # name
        *tuple(str(i) for i in sorted((
            random_date(),          # checkin date
            random_date())          # checkout date
        )),
        choice(STATUS_ENUM),        # status
        str(randint(5, 81)),        # age
        choice(COUNTRY_CODE_ENUM),  # country code
        gender,                     # gender
    ]


if len(sys.argv) != 2:
    print("A simple utility to generate test data.\n")
    print(f"usage: {sys.argv[0]} <number-of-records>")
    exit(1)

n = sys.argv[1]
if not n.isdecimal():
    print("Error: Only whole numbers are accepted.")
    exit(1)

n = int(n)

if n == 0:
    print("Error: The number of records must be greater than 0.")
    exit(1)


print('id,name,checkin date,checkout date,status,age,country code,gender')
for i in range(n):
    print(','.join(patiant()))

#!/usr/bin/env python3

import icalendar
import sys

with open(sys.argv[1]) as ics_file:
    calendar = icalendar.Calendar.from_ical(ics_file.read())

events = [
    {
        'what': str(component['SUMMARY']).strip(),
        'where': str(component['LOCATION']).strip(),
        'when': component['DTSTART'].dt,
        'length': component['DTEND'].dt - component['DTSTART'].dt
    }
    for component in calendar.walk()
    if component.name == 'VEVENT'
]
events.sort(key=lambda x: x['when'] + x['length'])

print('static std::array<Entry, {}> constexpr SCHEDULE = {{'.format(len(events)))

for event in events:
    print('\tEntry{')
    print('\t\t.what = "{}",'.format(event['what']))
    print('\t\t.where = "{}",'.format(event['where']))
    print('\t\t.when = std::tm {')
    print('\t\t\t.tm_min = {},'.format(event['when'].minute))
    print('\t\t\t.tm_hour= {},'.format(event['when'].hour))
    print('\t\t\t.tm_mday= {},'.format(event['when'].day))
    print('\t\t\t.tm_mon= {},'.format(event['when'].month))
    print('\t\t\t.tm_year= {},'.format(event['when'].year - 1900))
    print('\t\t},')
    print('\t\t.length = {}min,'.format(int(event['length'].seconds / 60)))
    print('\t},')

print('};')

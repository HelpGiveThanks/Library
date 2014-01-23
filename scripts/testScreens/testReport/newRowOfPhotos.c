testScreens: testReport: NewRowOfPhotos
Set Variable [ $$item; Value:report::ktest ]
#create new report record and put in all required information
New Record/Request
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
January 7, 平成26 14:30:19 Imagination Quality Management.fp7 - NewRowOfPhotos -1-

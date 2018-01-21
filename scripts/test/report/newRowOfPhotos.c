January 15, 2018 15:45:08 Library.fmp12 - newRowOfPhotos -1-
test: report: newRowOfPhotos
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (new)” ]
#
Set Variable [ $testSubsection; Value:report::ktestSubsection ]
#
#create new report record and put in all required information
New Record/Request
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
#
#IMPORTANT!!! Commit record or else it will
#not be deleted if user suddently decides to
#delete the last test result record.
Commit Records/Requests
#

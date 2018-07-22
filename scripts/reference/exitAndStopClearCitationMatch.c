July 21, 2018 14:45:52 Library.fmp12 - exitAndStopClearCitationMatch -1-
test: test: exitAndStopClearCitationMatch
#
#Not sure what this does, and need to test
#to document, when time permits.
If [ $$turnOffThisScript = 1 ]
Set Variable [ $$turnOffThisScript; Value:2 ]
End If
#
#After a user selects a popup calendar date,
#the variable below is set. FileMaker leaves the
#date field and enters the help field, which
#thanks to this variable will not run, giving the
#user a pleasant experience of selecting a
#calendar date and watching the calendar go
#away without anything else happening.
Set Variable [ $$pleaseExitUserJustLeftCalendarField; Value:1 ]

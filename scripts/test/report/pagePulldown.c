January 21, 2018 11:03:27 Library.fmp12 - pagePulldown -1-
test: report: pagePulldown
Go to Field [ ]
Set Variable [ $$first ]
Set Variable [ $$last ]
Set Variable [ $record; Value:TEMP::ktestSubsection ]
If [ testSubsectionTemplate::_LtestSubsection = $record ]
Exit Script [ ]
End If
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testSubsectionTemplate::_LtestSubsection = $record ]
Go to Record/Request/Page
[ Next ]
End Loop
Perform Script [ “loadSetupTestSubsection” ]

testScreens: testReport: PagePulldown
Go to Field [ ]
Set Variable [ $$first ]
Set Variable [ $$last ]
Set Variable [ $record; Value:TEMP::ktest ]
If [ test::_Ltest = $record ]
Exit Script [ ]
End If
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ test::_Ltest = $record ]
Go to Record/Request/Page
[ Next ]
End Loop
Perform Script [ “loadSetupTestRecord” ]
January 7, 平成26 14:04:03 Imagination Quality Management.fp7 - PagePulldown -1-

January 15, 2018 15:30:31 Library.fmp12 - previousPage -1-
test: report: previousPage
Set Variable [ $$last ]
Set Variable [ $$first; Value:testSubsectionTemplate::_LtestSubsection ]
Go to Record/Request/Page
[ Previous ]
If [ $$first ≠ testSubsectionTemplate::_LtestSubsection or Get (LastError) = 101 ]
Set Field [ TEMP::theme; testSubsectionTemplate::name ]
Perform Script [ “loadSetupTestSubsection (update name change loadSetupTestRecord)” ]
Refresh Window
End If
Go to Field [ ]

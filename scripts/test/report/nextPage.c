January 15, 2018 15:28:27 Library.fmp12 - nextPage -1-
test: report: nextPage
Set Variable [ $$first ]
Set Variable [ $$last; Value:testSubsectionTemplate::_LtestSubsection ]
Go to Record/Request/Page
[ Next ]
If [ $$last ≠ testSubsectionTemplate::_LtestSubsection or Get (LastError) = 101 ]
Set Field [ TEMP::theme; testSubsectionTemplate::name ]
Perform Script [ “loadSetupTestSubsection” ]
End If
Go to Field [ ]

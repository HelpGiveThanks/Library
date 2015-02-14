testScreens: testReport: PreviousPage
Set Variable [ $$last ]
Set Variable [ $$first; Value:test::_Ltest ]
Set Variable [ $library; Value:test::ksection ]
Go to Record/Request/Page
[ Previous ]
If [ test::ksection ≠ $library ]
Go to Record/Request/Page
[ Next ]
Refresh Window
Exit Script [ ]
End If
If [ $$first ≠ test::_Ltest or Get (LastError) = 101 ]
Set Field [ TEMP::theme; test::testName ]
Perform Script [ “loadSetupTestRecord” ]
Refresh Window
// Go to Layout [ “testSetup” (test) ]
// Go to Layout [ original layout ]
End If
Go to Field [ ]
January 7, 平成26 14:14:20 Imagination Quality Management.fp7 - PreviousPage -1-

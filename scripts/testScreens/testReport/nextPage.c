testScreens: testReport: NextPage
Set Variable [ $$first ]
Set Variable [ $$last; Value:test::_Ltest ]
Set Variable [ $library; Value:test::ksection ]
Go to Record/Request/Page
[ Next ]
If [ test::ksection ≠ $library ]
Go to Record/Request/Page
[ Previous ]
Refresh Window
Exit Script [ ]
End If
If [ $$last ≠ test::_Ltest or Get (LastError) = 101 ]
Set Field [ TEMP::theme; test::testName ]
Perform Script [ “loadSetupTestRecord” ]
// Go to Layout [ “testSetup” (test) ]
// Go to Layout [ original layout ]
End If
Go to Field [ ]
January 7, 平成26 14:13:28 Imagination Quality Management.fp7 - NextPage -1-

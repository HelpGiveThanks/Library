tagMenu: loadItemRecordForTestSetupTagMenu
If [ $$ID = test::_Ltest
 or
$$ID = "ignore" ]
Exit Script [ ]
End If
Go to Field [ ]
Set Variable [ $$ID; Value:test::_Ltest ]
Set Variable [ $item; Value:test::testName ]
Set Field [ TEMP::ktest; test::_Ltest ]
Set Field [ TEMP::testName; test::testName ]
Set Field [ TEMP::ksection; test::ksection ]
January 7, 平成26 16:07:20 Imagination Quality Management.fp7 - loadItemRecordForTestSetupTagMenu -1-

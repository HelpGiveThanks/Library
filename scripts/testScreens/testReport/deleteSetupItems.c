testScreens: testReport: DeleteSetupItems
Go to Object [ Object Name: "item" ]
If [ test::_Ltest ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: "You can delete this record only after you delete all items assigned to this category in these location(s)."; Buttons: “OK” ]
Go to Field [ ]
Halt Script
End If
Go to Field [ ]
Delete Record/Request
January 7, 平成26 14:22:00 Imagination Quality Management.fp7 - DeleteSetupItems -1-

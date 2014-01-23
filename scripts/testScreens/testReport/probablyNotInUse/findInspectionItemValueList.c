probablyNotInUse: testScreens: testReport: FindInspectionItemValueList
#
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $list; Value:<Table Missing>::<Field Missing> ]
Enter Find Mode [ ]
Set Field [ <Table Missing>; $list ]
Perform Find [ ]
If [ Get (LastError) = "401" ]
Show Custom Dialog [ Title: "!"; Message: "There are no value lists. Create a new one if you like."; Buttons: “OK” ]
End If
January 7, 平成26 14:17:48 Imagination Quality Management.fp7 - FindInspectionItemValueList -1-

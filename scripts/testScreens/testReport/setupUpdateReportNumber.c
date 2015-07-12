testScreens: testReport: setupUpdateReportNumber
If [ Get (FoundCount) = 0 and $$stopFocusLoad = "" or
Get (FoundCount) ≠ 0 and $$stopFocusLoad = 1 or
$$stopSetReportNumber = 1 ]
Exit Script [ ]
End If
Set Field [ TEMP::reportNumber; tagTestSubjectLocation::reportNumber ]
// Set Field [ TEMP::kdefaultNodeTestSubject; tagTestSubjectLocation::knode ]
Go to Field [ ]
July 11, 平成27 23:20:30 Library.fp7 - setupUpdateReportNumber -1-

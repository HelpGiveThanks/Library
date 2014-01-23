testScreens: testReport: setupUpdateReportNumber
If [ Get (FoundCount) = 0 and $$stopFocusLoad = "" or
Get (FoundCount) ≠ 0 and $$stopFocusLoad = 1 ]
Exit Script [ ]
End If
Set Field [ TEMP::reportNumber; tagTestSubjectLocation::reportNumber ]
// Set Field [ TEMP::kdefaultNodeTestSubject; tagTestSubjectLocation::knode ]
Go to Field [ ]
January 7, 平成26 14:44:39 Imagination Quality Management.fp7 - setupUpdateReportNumber -1-

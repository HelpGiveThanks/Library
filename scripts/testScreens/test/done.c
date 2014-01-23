testScreens: test: done
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Freeze Window
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ InspectItems::kcfocusALL; $$itemLocation ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Exit Script [ ]
End If
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
If [ tagTestSubjectLocation::inUse = "t" ]
Set Field [ tagTestSubjectLocation::inUse; "d" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: done" ]
Exit Script [ ]
End If
Set Field [ tagTestSubjectLocation::inUse; "t" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
January 7, 平成26 12:34:20 Imagination Quality Management.fp7 - done -1-

learn: CancelLearnFind
#
#If the user decides to cancel their the ﬁnd, then return
#to the main record window and show all records.
If [ Get ( LayoutTableName ) = "reference" ]
Go to Layout [ $$ﬁndReferenceLayout ]
Set Variable [ $$ﬁndReferenceLayout ]
Else
Go to Layout [ $$ﬁndLearnLayout ]
Set Variable [ $$ﬁndLearnLayout ]
End If
Show/Hide Status Area
[ Hide ]
Show/Hide Text Ruler
[ Hide ]
Enter Find Mode [ ]
If [ Get ( LayoutTableName ) = "reference" ]
Set Field [ reference::kcsection; TEMP::ksection ]
Else
Set Field [ testlearn::kcsection; TEMP::ksection ]
End If
Perform Find [ ]
Sort Records [ ]
[ No dialog ]
Go to Record/Request/Page
[ First ]
January 7, 平成26 17:28:13 Imagination Quality Management.fp7 - CancelLearnFind -1-

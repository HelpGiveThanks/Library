learn: cancelLearnFind
#
#If the user decides to cancel their the find, then return
#to the main record window.
If [ Get ( LayoutTableName ) = "reference" ]
Go to Layout [ $$findReferenceLayout ]
Set Variable [ $$findReferenceLayout ]
Else
Go to Layout [ $$findLearnLayout ]
Set Variable [ $$findLearnLayout ]
End If
Enter Browse Mode
#
#DO NOT find all records. Just show user what
#they where looking at before clicking find.
// Show/Hide Status Area
[ Hide ]
// Show/Hide Text Ruler
[ Hide ]
// Enter Find Mode [ ]
// If [ Get ( LayoutTableName ) = "reference" ]
// Set Field [ reference::kcsection; TEMP::ksection ]
// Else
// Set Field [ testlearn::kcsection; TEMP::ksection ]
// End If
// Perform Find [ ]
// Sort Records [ ]
[ No dialog ]
// Go to Record/Request/Page
[ First ]
June 27, 平成27 19:13:48 Library.fp7 - cancelLearnFind -1-

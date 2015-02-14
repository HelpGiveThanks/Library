learn: probablyNotInUse: findLearnRecord Copy
If [ Get (WindowMode) = 1 ]
Set Variable [ $$stopFindScript ]
End If
If [ Get (WindowMode) = 1 ]
// Perform Find [ ]
Enter Browse Mode
Exit Script [ ]
Else
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
Enter Find Mode [ ]
Go to Layout [ “learnFIND” (testlearn) ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Show/Hide Status Area
[ Hide ]
Go to Field [ testlearn::Caption ]
Pause/Resume Script [ Indefinitely ]
// Perform Find [ ]
Enter Browse Mode
Go to Field [ ]
Exit Script [ ]
End If
// Sort Records [ ]
[ No dialog ]
January 7, 平成26 17:29:17 Imagination Quality Management.fp7 - findLearnRecord Copy -1-

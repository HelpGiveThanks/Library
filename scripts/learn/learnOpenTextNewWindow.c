learn: LearnOpenTextNewWindow
If [ Get ( WindowMode ) = 1 ]
Go to Field [ testlearn::Caption ]
Exit Script [ ]
End If
If [ $$stopOpenNewTextWindow = 1 ]
Set Variable [ $$stopOpenNewTextWindow ]
Exit Script [ ]
End If
Go to Field [ ]
Set Variable [ $record; Value:testlearn::_Ltestlearn ]
Set Variable [ $$stopLoadCitation; Value:1 ]
New Window [ Name: "Learn: Edit Note" ]
If [ tagTLNodePrimary::orderOrLock = "" ]
Go to Layout [ “LearnTextWindow” (testlearn) ]
Go to Field [ testlearn::Caption ]
Else If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Go to Layout [ “LearnTextWindowLocked” (testlearn) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $record ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indefinitely ]
January 7, 平成26 17:26:12 Imagination Quality Management.fp7 - LearnOpenTextNewWindow -1-

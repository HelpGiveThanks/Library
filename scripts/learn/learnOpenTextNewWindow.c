learn: learnOpenTextNewWindow
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
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “LearnTextWindowStuff” (testlearn) ]
Else
Go to Layout [ “LearnTextWindow” (testlearn) ]
End If
Go to Field [ testlearn::Caption ]
Else If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Go to Layout [ “LearnTextWindowLocked” (testlearn) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $record ]
Perform Find [ ]
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indefinitely ]
May 10, 平成27 11:33:37 Library.fp7 - learnOpenTextNewWindow -1-

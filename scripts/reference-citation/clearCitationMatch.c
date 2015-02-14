reference(citation): clearCitationMatch
#
#If node is currenlty locked then stop script, inform user.
If [ tagNodeCreator::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#In order to reset the conditional formatting
#it is neccessary at the end of this script to go
#and refresh the other window, which makes
#the popout calendar go away, so to make it
#come back the system goes to the next field
#and back to the current field which triggers
#this script and why this next step is neccessary
#to prevent an infinite logic loop.
If [ $$turnOffThisScript = 1 ]
Set Variable [ $$turnOffThisScript ]
Exit Script [ ]
Else If [ $$turnOffThisScript = 2 ]
Set Variable [ $$turnOffThisScript ]
Go to Field [ ]
// Exit Script [ ]
// Halt Script
End If
Set Variable [ $$turnOffThisScript; Value:1 ]
If [ $$add = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Clear any conditional formatting tied to the
#citation match variable in both windows.
Set Variable [ $$citationMatch ]
Set Variable [ $$stopFileNameCheck; Value:1 ]
Set Variable [ $table; Value:Get ( LayoutTableName ) ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
End If
If [ $table = "reference" ]
Go to Layout [ “ReferenceMenuNoTags” (tagMenus) ]
Else
Go to Layout [ “learnTagWindowNoTags” (tagMenus) ]
End If
#
#Return user to field user clicked into to start this script.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Go to Next Field
Set Variable [ $$turnOffThisScript; Value:1 ]
Go to Previous Field
Set Variable [ $$turnOffThisScript; Value:1 ]
Set Variable [ $$stopFileNameCheck ]
January 7, 平成26 17:52:34 Imagination Quality Management.fp7 - clearCitationMatch -1-

learn: editTestLearn
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the
password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$stoploadCitation; Value:1 ]
#
#If in find mode, exit find mode.
If [ $$findMode= 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$findLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "Learn"; Current file ]
End If
#
#Capture layout name.
Set Variable [ $$testLearnLayoutName; Value:Get (LayoutName) ]
#
#Go to edit layout for this record.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “learn4EDITstuff” (testlearn) ]
Else
Go to Layout [ “learn4EDIT” (testlearn) ]
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
Set Variable [ $$stoploadCitation ]
December 10, ଘ౮27 17:46:03 Library.fp7 - editTestLearn -1-

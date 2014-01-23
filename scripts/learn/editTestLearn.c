learn: editTestLearn
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit script.
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Exit ﬁnd mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$stoploadCitation; Value:1 ]
#
#If in ﬁnd mode, exit ﬁnd mode.
If [ $$ﬁndMode= 1 ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $$ﬁndMode ]
Set Variable [ $$ﬁrstFind ]
Set Variable [ $$ﬁrstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "Learn"; Current ﬁle ]
End If
#
#Capture layout name.
Set Variable [ $$testLearnLayoutName; Value:Get (LayoutName) ]
#
#Go to edit layout for this record.
Go to Layout [ “learn4EDIT” (testlearn) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
Set Variable [ $$stoploadCitation ]
January 7, 平成26 17:24:31 Imagination Quality Management.fp7 - editTestLearn -1-

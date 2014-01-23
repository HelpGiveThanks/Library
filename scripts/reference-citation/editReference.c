reference(citation): editReference
#
#If node is currenlty locked then stop script, inform user.
If [ tagNodeCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit script.
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel ﬁnd mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
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
Select Window [ Name: "References"; Current ﬁle ]
End If
#
#If user is in tag ﬁeld and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Field [ ]
Select Window [ Name: "References"; Current ﬁle ]
If [ $$referenceSort = 2 ]
Sort Records [ Speciﬁed Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "" ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Speciﬁed Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
End If
#
#Go to edit layout for this record.
Go to Layout [ “ReferenceEDIT” (reference) ]
#
#Get rid of spaces in bookChapter ﬁeld, if any.
Set Field [ reference::bookChapter; Trim ( reference::bookChapter ) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
January 7, 平成26 17:31:47 Imagination Quality Management.fp7 - editReference -1-

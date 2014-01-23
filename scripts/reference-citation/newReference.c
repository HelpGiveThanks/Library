reference(citation): newReference
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
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
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
New Record/Request
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ktest; TEMP::ktest ]
Set Field [ reference::incomplete; "incomplete" & ¶ ]
If [ Get ( LayoutName ) = "Reference" ]
Set Field [ reference::ﬁlterFind; "main" & ¶ ]
Set Variable [ $$stoploadCitation ]
#
#Note that citation is for either the node or keyword depending on the citation match.
Else If [ Right ( Get ( LayoutName ) ; 3 ) = "TAG" ]
Set Field [ reference::ﬁlterFind; $$addToTag & ¶ ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
Go to Layout [ “ReferenceEDIT” (reference) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
January 7, 平成26 17:30:34 Imagination Quality Management.fp7 - newReference -1-

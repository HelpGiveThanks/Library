reference(citation): newReference
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel find mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
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
Select Window [ Name: "References"; Current file ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
If [ $$referenceSort = 2 ]
Sort Records [ Specified Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Specified Sort Order: reference::createDate; descending
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
If [ Get ( LayoutName ) = "Reference" or Get ( LayoutName ) = "ReferenceStuff" ]
Set Field [ reference::filterFind; "main" & ¶ ]
Set Variable [ $$stoploadCitation ]
#
#Note that citation is for either the node or keyword depending on the citation match.
Else If [ Right ( Get ( LayoutName ) ; 3 ) = "TAG" ]
Set Field [ reference::filterFind; $$addToTag & ¶ ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
#
#Go to edit layout for this record.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “ReferenceEDITstuff” (reference) ]
Else
Go to Layout [ “ReferenceEDIT” (reference) ]
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
May 10, 平成27 11:58:08 Library.fp7 - newReference -1-

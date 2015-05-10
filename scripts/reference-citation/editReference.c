reference(citation): editReference
#
#If node is currenlty locked then stop script, inform user.
If [ tagNodeCreator::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
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
#Go to edit layout for this record.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “ReferenceEDITstuff” (reference) ]
Else
Go to Layout [ “ReferenceEDIT” (reference) ]
End If
#
#Get rid of spaces in bookChapter field, if any.
Set Field [ reference::bookChapter; Trim ( reference::bookChapter ) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
May 10, 平成27 12:01:46 Library.fp7 - editReference -1-

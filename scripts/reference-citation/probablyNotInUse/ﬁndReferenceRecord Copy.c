reference(citation): probablyNotInUse: findReferenceRecord Copy
#
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel find in Tag Menus window then click this button."; Buttons: “OK” ]
Exit Script [ ]
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
If [ Get (WindowMode) = 1 ]
Perform Find [ ]
Else
// Close Window [ Name: "Find References"; Current file ]
// Set Variable [ $$stoploadCitation; Value:1 ]
// New Window [ Name: "Find References" ]
Set Variable [ $$findReferenceLayout; Value:Get (LayoutName) ]
Show/Hide Status Area
[ Hide ]
Enter Find Mode [ ]
Go to Layout [ “ReferenceFIND” (reference) ]
// Set Variable [ $$stoploadCitation ]
Go to Field [ reference::referenceForReferenceSort ]
Pause/Resume Script [ Indefinitely ]
Perform Find [ ]
Exit Script [ ]
End If
Sort Records [ ]
[ No dialog ]
January 7, 平成26 18:04:21 Imagination Quality Management.fp7 - findReferenceRecord Copy -1-

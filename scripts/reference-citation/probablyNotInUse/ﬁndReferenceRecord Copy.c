reference(citation): probablyNotInUse: ﬁndReferenceRecord Copy
#
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel ﬁnd in Tag Menus window then click this button."; Buttons: “OK” ]
Exit Script [ ]
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
If [ Get (WindowMode) = 1 ]
Perform Find [ ]
Else
// Close Window [ Name: "Find References"; Current ﬁle ]
// Set Variable [ $$stoploadCitation; Value:1 ]
// New Window [ Name: "Find References" ]
Set Variable [ $$ﬁndReferenceLayout; Value:Get (LayoutName) ]
Show/Hide Status Area
[ Hide ]
Enter Find Mode [ ]
Go to Layout [ “ReferenceFIND” (reference) ]
// Set Variable [ $$stoploadCitation ]
Go to Field [ reference::referenceForReferenceSort ]
Pause/Resume Script [ Indeﬁnitely ]
Perform Find [ ]
Exit Script [ ]
End If
Sort Records [ ]
[ No dialog ]
January 7, 平成26 18:04:21 Imagination Quality Management.fp7 - ﬁndReferenceRecord Copy -1-

reference(citation): sortReferences
If [ $$referenceSort = 2 ]
// Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort ]
Else If [ $$referenceSort = "" ]
Sort Records [ Specified Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:1 ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Specified Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:2 ]
End If
December 30, ଘ౮27 11:08:01 Library.fp7 - sortReferences -1-

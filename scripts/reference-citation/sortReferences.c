reference(citation): sortReferences
If [ $$referenceSort = 2 ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort ]
Else If [ $$referenceSort = "" ]
Sort Records [ Speciﬁed Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:1 ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Speciﬁed Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:2 ]
End If
January 7, 平成26 17:42:59 Imagination Quality Management.fp7 - sortReferences -1-

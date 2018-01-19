January 18, 2018 15:27:05 Library.fmp12 - sortRefByDate -1-
reference: sortRefByDate
#
#
#
Show Custom Dialog [ Message: "Sort by date created or modified or published?"; Default Button: “created”, Commit: “Yes”; Button 2:
“modified”, Commit: “No”; Button 3: “published”, Commit: “No” ]
#
If [ Get ( LastMessageChoice ) = 1 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::createDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:"dateCreated" ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::modifyDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:"dateModified" ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByDatePublished; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:"datePublished" ]
End If
#
#

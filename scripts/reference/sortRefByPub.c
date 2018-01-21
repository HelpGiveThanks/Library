January 18, 2018 15:32:42 Library.fmp12 - sortRefByPub -1-
reference: sortRefByPub
#
#Give user the option of either sorting
#by publication or by publisher.
Show Custom Dialog [ Message: "Sort by publication or publisher?"; Default Button: “publisher”, Commit: “Yes”; Button 2:
“publication”, Commit: “No” ]
#
If [ Get ( LastMessageChoice ) = 1 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagPublisher::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:"publisher" ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByPublication; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Set Variable [ $$referenceSort; Value:"publication" ]
End If
#

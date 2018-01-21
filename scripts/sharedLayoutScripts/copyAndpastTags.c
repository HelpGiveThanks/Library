January 18, 2018 15:55:32 Library.fmp12 - copyAndpastTags -1-
sharedLayoutScripts: copyAndpastTags
#
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The node that created this record, " & tagTLNodePrimary::tag & ", is locked, so all this node's
records are locked too. Go back to Setup to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
Else If [ refCreatorNode::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The node that created this record, " & $$lockedMainRefRecord & ", is locked, so all this node's
records are locked too. Go back to Setup to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If there are no tags exit script and
#inform user why.
If [ testlearn::kcKeywordOther = "" and testlearn::kKeywordPrimary = "" and $$copyAndpastTagsRECORD = "" and Get
( LayoutTableName ) = "testlearn"
or
reference::kkeywordOther = "" and reference::kkeywordPrimary = "" and $$copyAndpastTagsRECORD = "" and Get
( LayoutTableName ) = "Reference" ]
Show Custom Dialog [ Message: "There are no keywords to copy. You can add some by copying them from a note that has
them, or by adding some keywords from the Tag Menus' key menu."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#This is a scripts purpose is to copy tags from a
#learn or reference record and paste them
#in a different record.
If [ $$copyAndpastTagsRECORD = "" ]
Set Variable [ $$copyAndpastTagsPrimaryID; Value:Case ( Get (LayoutTableName) = "reference" ; reference::kkeywordPrimary ;
testlearn::kKeywordPrimary ) ]
Set Variable [ $$copyAndpastTagsOtherID; Value:Case ( Get (LayoutTableName) = "reference" ; reference::kkeywordOther ;
testlearn::kcKeywordOther ) ]
Set Variable [ $$copyAndpastTagsOther; Value:Case ( Get (LayoutTableName) = "reference" ; reference::OtherKeyWords ;
testlearn::OtherKeyWords ) ]
Set Variable [ $$copyAndpastTagsRECORD; Value:Case ( Get (LayoutTableName) = "reference" ; reference::_Lreference ;
testlearn::_Ltestlearn ) ]
Else
If [ $$copyAndpastTagsRECORD = reference::_Lreference or $$copyAndpastTagsRECORD = testlearn::_Ltestlearn ]
Set Variable [ $$copyAndpastTagsPrimaryID ]
Set Variable [ $$copyAndpastTagsOtherID ]
Set Variable [ $$copyAndpastTagsOther ]
Set Variable [ $$copyAndpastTagsRECORD ]
Else
If [ $$copyAndpastTagsOtherID = "" and $$copyAndpastTagsPrimaryID = "" ]
Show Custom Dialog [ Message: "Paste blanks? FYI: You copied blanks, and pasting them will delete/blank this
record's keywords."; Default Button: “yes”, Commit: “Yes”; Button 2: “Cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Replace this record's keywords with the copied ones?"; Default Button: “yes”,
Commit: “Yes”; Button 2: “Cancel”, Commit: “No” ]
End If
If [ Get (LastMessageChoice) = 1 ]
If [ Get (LayoutTableName) = "reference" ]
#
#Because keyword primary in the Reference
#window will change the records location, not
#this and re-sort the window to keep the
#the selected record in view (scrolled to).
If [ $$copyAndpastTagsPrimaryID ≠ reference::kkeywordPrimary ]
Set Variable [ $sort; Value:1 ]
End If
Set Field [ reference::kkeywordPrimary; $$copyAndpastTagsPrimaryID ]
Set Field [ reference::kkeywordOther; $$copyAndpastTagsOtherID ]
Set Field [ reference::OtherKeyWords; $$copyAndpastTagsOther ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
Set Variable [ $$PrimaryKey; Value:reference::kkeywordPrimary ]
Set Variable [ $$Key; Value:reference::kkeywordOther ]
Set Variable [ $$OtherKey; Value:reference::kkeywordOther ]
Refresh Window
If [ $sort = 1 ]
Sort Records [ ]
[ No dialog ]
End If
If [ $$citationMatch = "key" ]
Set Variable [ $currentWindow; Value:Get (WindowName) ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Select Window [ Name: $currentWindow; Current file ]
End If
Else
Set Field [ testlearn::kKeywordPrimary; $$copyAndpastTagsPrimaryID ]
Set Field [ testlearn::kcKeywordOther; $$copyAndpastTagsOtherID ]
Set Field [ testlearn::OtherKeyWords; $$copyAndpastTagsOther ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Refresh Window
If [ $$citationMatch = "key" ]
Set Variable [ $currentWindow; Value:Get (WindowName) ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Select Window [ Name: $currentWindow; Current file ]
End If
End If
Set Variable [ $$copyAndpastTagsPrimaryID ]
Set Variable [ $$copyAndpastTagsOtherID ]
Set Variable [ $$copyAndpastTagsOther ]
Set Variable [ $$copyAndpastTagsRECORD ]
Else
Set Variable [ $$copyAndpastTagsPrimaryID ]
Set Variable [ $$copyAndpastTagsOtherID ]
Set Variable [ $$copyAndpastTagsOther ]
Set Variable [ $$copyAndpastTagsRECORD ]
End If
End If
End If
#
Refresh Window
#

sharedMainLayoutScripts: copyAndpastTags
#
#
#This is a script I'm developing and is not on any
#layout yet. Its purpose is to copy tags from a
#learn or reference record and then paste them
#in a different record.
If [ $$copyAndpastTagsPrimaryID = "" ]
Set Variable [ $$copyAndpastTagsPrimaryID; Value:reference::kkeywordPrimary ]
Set Variable [ $$copyAndpastTagsOtherID; Value:reference::kkeywordOther ]
Set Variable [ $$copyAndpastTagsOther; Value:reference::OtherKeyWords ]
Else
Set Field [ reference::kkeywordPrimary; $$copyAndpastTagsPrimaryID ]
Set Field [ reference::kkeywordOther; $$copyAndpastTagsOtherID ]
Set Field [ reference::OtherKeyWords; $$copyAndpastTagsOther ]
Set Variable [ $$copyAndpastTagsPrimaryID ]
Set Variable [ $$copyAndpastTagsOtherID ]
Set Variable [ $$copyAndpastTagsOther ]
End If
May 10, 平成27 12:35:52 Library.fp7 - copyAndpastTags -1-

tagMenu: addORremoveRefTagStep1
#Remove focus from ﬁeld so can see
#conditional formatting.
Go to Field [ ]
#
#Determine if user is looking at nodes or keywords.
If [ $$citationMatch = "cite" ]
Perform Script [ “addTagToMainRecord” ]
Else If [ $$citationMatch = "ref" ]
If [ Right ( Get (LayoutName) ; 7 ) = "RefCite" ]
Perform Script [ “addORremoveCiteOrRefTLTag” ]
Select Window [ Name: "Learn"; Current ﬁle ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
End If
Perform Script [ “addORremoveCitationOrReferenceRefTag” ]
End If
January 7, 平成26 16:26:21 Imagination Quality Management.fp7 - addORremoveRefTagStep1 -1-

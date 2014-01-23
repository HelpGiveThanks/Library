tagMenu: gotoLessLayoutsTag
#
#If in add mode, keep user on the evenMore layout.
If [ $$add = 1 ]
Show Custom Dialog [ Message: "Turn off add mode (click 'add' button) to reduce number of pictures shown and full link names."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Reveal more or fewer pictures and links for tag.
If [ Right ( Get (LayoutName) ; 8 ) = "evenmore" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK3” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "d" ]
Go to Layout [ “defaultNode2” (tagMenus) ]
End If
Else If [ Right ( Get (LayoutName) ; 4 ) = "more" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "d" ]
Go to Layout [ “defaultNode1” (tagMenus) ]
End If
End If
#
#Remember layout user is on so they can be
#returned to correct view.
If [ $$citationMatch = "node" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Set Field [ TEMP::layoutLtagN; Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Set Field [ TEMP::layoutRtagN; Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "d" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; Get (LayoutName) ]
End If
Else If [ $$citationMatch = "key" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Set Field [ TEMP::layoutLtagK; Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Set Field [ TEMP::layoutRtagK; Get (LayoutName) ]
End If
End If
January 7, 平成26 16:36:07 Imagination Quality Management.fp7 - gotoLessLayoutsTag -1-

tagMenu: ToggleTagMenuWindowView
#
#Reveal more or fewer pictures and links for tag.
#
#First toggle from current view to next view.
If [ Left (Get (LayoutName) ; 1) = "l" and $$citationMatch = "key" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Go to Layout [ “ltagNK3” (tagMenus) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Go to Layout [ “ltagNK4” (tagMenus) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Go to Layout [ “ltagNK3” (tagMenus) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "l" and $$citationMatch = "node" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Go to Layout [ “ltagNK3” (tagMenus) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Go to Layout [ “ltagNK4” (tagMenus) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Go to Layout [ “ltagNK3” (tagMenus) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "r" and $$citationMatch = "key" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode3” (tagMenus) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "r" and $$citationMatch = "node" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode3” (tagMenus) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "d" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Go to Layout [ “defaultNode2” (tagMenus) ]
#from 2 to 3
Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Go to Layout [ “defaultNode3” (tagMenus) ]
#from 3 to 2
Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ] January 7, 平成26 16:19:31 Imagination Quality Management.fp7 - ToggleTagMenuWindowView -1-tagMenu: ToggleTagMenuWindowView Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
Go to Layout [ “defaultNode2” (tagMenus) ]
#from 2 to 1
Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
Go to Layout [ “defaultNode1” (tagMenus) ]
End If
End If
#
#
#
#
#Remember layout user is on so they can be
#returned to correct view.
If [ $$citationMatch = "node" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagN; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagN; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagN; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagN; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagN; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagN; "more" & Get (LayoutName) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagN; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagN; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagN; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagN; "more" & Get (LayoutName) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "d" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "more" & Get (LayoutName) ]
End If
End If
#
#
Else If [ $$citationMatch = "key" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagK; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagK; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagK; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagK; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagK; "less" & Get (LayoutName) ]
January 7, 平成26 16:19:31 Imagination Quality Management.fp7 - ToggleTagMenuWindowView -2-tagMenu: ToggleTagMenuWindowView
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutLtagK; "more" & Get (LayoutName) ]
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagK; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagK; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagK; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagK; "more" & Get (LayoutName) ]
End If
#
End If
End If
January 7, 平成26 16:19:31 Imagination Quality Management.fp7 - ToggleTagMenuWindowView -3-

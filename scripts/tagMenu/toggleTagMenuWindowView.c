January 15, 2018 17:14:26 Library.fmp12 - toggleTagMenuWindowView -1-
tagMenu: toggleTagMenuWindowView
#
#Reveal more or fewer pictures and links for tag.
#
#Speed up script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLockCheck; Value:1 ]
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
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Go to Layout [ “ltagNK5” (tagMenus) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
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
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs2” (tagMenus) ]
Else
Go to Layout [ “ltagNK2” (tagMenus) ]
End If
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs3” (tagMenus) ]
Else
Go to Layout [ “ltagNK3” (tagMenus) ]
End If
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs5” (tagMenus) ]
Else
Go to Layout [ “ltagNK5” (tagMenus) ]
End If
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs4” (tagMenus) ]
Else
Go to Layout [ “ltagNK4” (tagMenus) ]
End If
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs4” (tagMenus) ]
Else
Go to Layout [ “ltagNK4” (tagMenus) ]
End If
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs3” (tagMenus) ]
Else
Go to Layout [ “ltagNK3” (tagMenus) ]
End If
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs2” (tagMenus) ]
Else
Go to Layout [ “ltagNK2” (tagMenus) ]
End If
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs1” (tagMenus) ]
Else
Go to Layout [ “ltagNK1” (tagMenus) ]
End If
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "l" and $$citationMatch = "learn" and Get (LayoutTableName) = "testLearn" ]
#from 1 to 2
If [ Left ( TEMP::layoutLtagL ; 4 ) = "more" ]
Go to Layout [ “learnMenu4RefCite” (testlearn) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
End If
#from 2 to 1
Else
Go to Layout [ “learnMenu4noPicRefCite” (testlearn) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
End If
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "l" and $$citationMatch = "ref" ]
#from 1 to 2
If [ Left ( TEMP::layoutLtagR ; 4 ) = "more" ]
Go to Layout [ “learnMenu3Cite” (reference) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
End If
#from 2 to 1
Else
Go to Layout [ “learnMenu3CiteS” (reference) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
End If
End If
#
Else If [ Left (Get (LayoutName) ; 1) = "r" and $$citationMatch = "key" ]
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode2” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
End If
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode3” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode3” (tagMenus) ]
End If
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode4” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode4” (tagMenus) ]
End If
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode5” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode5” (tagMenus) ]
End If
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode4” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode4” (tagMenus) ]
End If
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode3” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode3” (tagMenus) ]
End If
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode2” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
End If
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceMenu2SkeywordOrNode1” (tagMenus) ]
Else
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
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
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode4” (tagMenus) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Go to Layout [ “ReferenceMenu2keywordOrNode5” (tagMenus) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Go to Layout [ “ReferenceMenu2keywordOrNode4” (tagMenus) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
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
#from 3 to 4
Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Go to Layout [ “defaultNode4” (tagMenus) ]
#from 4 to 3
Else If [ Left (Get (LayoutName) ; 1) = "d"
and
Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
Go to Layout [ “defaultNode3” (tagMenus) ]
#from 3 to 2
Else If [ Left (Get (LayoutName) ; 1) = "d"
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
#
#
Else If [ $$citationMatch = "cite" and Get (LayoutTableName) = "reference" ]
#from 1 to 2
If [ Get (LayoutName) = "ReferenceMenu3CiteNoPicture" ]
Go to Layout [ “ReferenceMenu3Cite” (reference) ]
#from 2 to 1
Else
Set Field [ TEMP::layoutLtagL; Get (LayoutName) = "ReferenceMenu3CiteNoPicture" ]
Go to Layout [ “ReferenceMenu3CiteNoPicture” (reference) ]
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
Set Field [ TEMP::layoutLtagN; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagN; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagN ; 4 ) = "less" ]
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
Set Field [ TEMP::layoutRtagN; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagN; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutRtagN ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagN; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagN; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagN ; 4 ) = "less" ]
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
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "more" ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::DefaultmoreORLessLayoutNode ; 4 ) = "less" ]
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
Set Field [ TEMP::layoutLtagK; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagK; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLtagK ; 4 ) = "less" ]
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
Set Field [ TEMP::layoutRtagK; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagK; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutRtagK ; 4 ) = "more" ]
Set Field [ TEMP::layoutRtagK; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
Set Field [ TEMP::layoutRtagK; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutRtagK ; 4 ) = "less" ]
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
#
#
Else If [ $$citationMatch = "learn" and Get (LayoutTableName) = "testLearn" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
#
#from 1 to 2
If [ Left ( TEMP::layoutLtagL ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagL; "less" & Get (LayoutName) ]
#from 2 to 1
Else
Set Field [ TEMP::layoutLtagL; "more" & Get (LayoutName) ]
End If
#
End If
#
#
Else If [ $$citationMatch = "ref" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
#
#from 1 to 2
If [ Left ( TEMP::layoutLtagR ; 4 ) = "more" ]
Set Field [ TEMP::layoutLtagR; "less" & Get (LayoutName) ]
#from 2 to 1
Else
Set Field [ TEMP::layoutLtagR; "more" & Get (LayoutName) ]
End If
#
End If
#
#
End If
#
#Turn back on essential scripts.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLockCheck ]
#
#Bring selected record to the top.
Scroll Window
[ End ]
Sort Records [ ]
[ No dialog ]
#
